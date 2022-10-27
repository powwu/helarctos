BINARY_NAME=helarctos

build:
	
	 GOARCH=amd64 GOOS=linux gcc -Wall -Werror -ggdb -O0 -fpic -shared -ldl -o ${BINARY_NAME}.so ${BINARY_NAME}.c
	 

clean:
	 rm ${BINARY_NAME}.so
