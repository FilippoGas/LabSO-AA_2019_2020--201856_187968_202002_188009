#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include"../macro_libglob.h"


int main(){
	signal(SIGPIPE, SIG_IGN);
	int f=fork();
	if(f > 0){
		int status;
		int i=0;
		waitpid(f,&status,WNOHANG);
		printf("f = %d\n",	WIFEXITED(status));
		sleep(6);
		waitpid(f,&status,WNOHANG);
		printf("f = %d\n",	WIFEXITED(status));
	}
	else{
		printf("SONO IL FIGLIO!\n");
		sleep(5);
		printf("IL FIGLIO HA FINITO!!\n");
	}
	return 0;
}
