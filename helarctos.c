#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>

#include "hd.h"


/* hd_data_t definition
   https://github.com/openSUSE/hwinfo/blob/6cfa8b8cc036d4caeba69abb01eb35df65546eac/src/hd/hd.h#L2609
 */

char *spoofed_id = "spoof'd";
hd_data_t *spoofed_hd_data = NULL;

void hd_add_id(hd_data_t *hd_data, hd_t *hd) {
	static void(*lib_hd_add_id)(hd_data_t *hd_data, hd_t *hd) = NULL;
	void *handle;

	if (!lib_hd_add_id) {
		handle = dlopen("/usr/lib/libhd.so.22", RTLD_LAZY);
		if(!handle) {
			fputs(dlerror(), stderr);
			exit(1);
		}

		lib_hd_add_id = dlsym(handle, "hd_add_id");
		if (dlerror() != NULL) {
			fprintf(stderr, "error in dlsym: +%s\n", dlerror());
			exit(1);
		}
	}

  fprintf(stderr, "%s %d\n", hd->device.name, hd->device.id);

  hd->unique_id=spoofed_id;

  spoofed_hd_data = hd_data;

	lib_hd_add_id(hd_data, hd);

}

hd_data_t *hd_free_hd_data(hd_data_t *hd_data) { // freeing the spoofed hd_data creates a segfault -- just skip the function entirely
  return NULL; // causes a memory leak but I don't care :D
               // could be something to fix in the future though, it does leave a way to detect something's off
}
