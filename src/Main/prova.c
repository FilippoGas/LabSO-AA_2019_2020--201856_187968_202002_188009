#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include"../macro_libglob.h"


int main(){
	signal(SIGPIPE, SIG_IGN);
	int pipe[2];
	pipe2(pipe,__O_DIRECT);
	int f=fork();
	if(f>0){
	close(pipe[READ]);
	int prova = write(pipe[WRITE],"lol",4);
	printf("prova=%d\n",prova);
	}
	else{
		close(pipe[WRITE]);
		char message[4];
		read(pipe[READ],message,4);
		printf("il messaggio e' lol");
	}
	return 0;
}
