#include "processPfunc.h"
#include "../Debug/utility.h"

int main(int argc, char *argv[]){
	int m, pipe_read, pipe_write;
	char **files;
	//./p m pipe_read pipe_write files

	//Leggo l'input
	int nfiles = readInput(argc, argv, &m, &pipe_read, &pipe_write, &files);
	close(pipe_read);
	

	int pQ[2];
	pipe2(pQ, __O_DIRECT);
	//Creo la chiamata per le Q
	char **argvQ = create_ArgvQ(m, pQ, files, nfiles);
	int i = 0;
	//Creo le Q
	while(i < m){
		sprintf(argvQ[1],"%d",i);
		int f=createChildren(argvQ);
		if(f>0){
			i++;
		}
	}

	freeStringArray(argvQ, nfiles + ARGS_Q_START_FILE_OFFSET + 1);

	i=0;
	while(i<m){
		char message[PIPE_BUF];
		read(pQ[READ],message,PIPE_BUF);
		if(exitMessage(message)){
			i++;
		}
		else{
			//Rimando ad A
			char *msgtoA=writeA(message);
			int try=write(pipe_write,msgtoA,PIPE_BUF);
			if(try<0){
				//SYSTEMCALL!!!
				perror("Errore di scrittura ad A:");
			}
			free(msgtoA);
		}

	}
	//Chiudo P
	close(pipe_write);
	wait(NULL);
	return 0;
}
