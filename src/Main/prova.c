#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main(){

	int pipe[2];
	pipe2(pipe,__O_DIRECT | O_NONBLOCK );
	close(pipe[0]);
	printf("Prima del write\n");
	write(pipe[1],"ciao",5);
	printf("Ho scritto\n");

	return 0;
}
