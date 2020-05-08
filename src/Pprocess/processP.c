#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	int m = atoi(argv[1]);
	int pipe_read = atoi(argv[2]);
	int pipe_write = atoi(argv[3]);
	//printf("\e[1;34mSONO IL FIGLIO CON ARGC %d\n\e[0m", argc);	
	close(pipe_read);

	int i = 0;
	while(i < m){
		char messaggio[100000];
		sprintf(messaggio, "Sono il figlio %d e invio il messaggio numero %d, con files: ", getpid(), i);
		int j = 4;
		while(j < argc){
			sprintf(messaggio, "%s %s", messaggio, argv[j]);
			j++;
		}
		write(pipe_write, messaggio, strlen(messaggio) + 1);
		i++;
	}

	return 0;
}
