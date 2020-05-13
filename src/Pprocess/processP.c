#include "processPfunc.h"
#include "../Debug/utility.h"

int main(int argc, char *argv[]){
	int m, pipe_read, pipe_write;
	char **files;
	//./p m pipe_read pipe_write files
	int nfiles = readInput(argc, argv, &m, &pipe_read, &pipe_write, &files);
	close(pipe_read);


	int pQ[2];
	pipe2(pQ, __O_DIRECT);
	//./Q nQ m pipe_read pipe_write files
	char **argvQ = create_ArgvQ(m, pQ, files, nfiles);
	int i = 0;
	while(i < m){
		sprintf(argvQ[1],"%d",i);
		int f=createChildren(argvQ);
		if(f>0){
			i++;
		}
	}


	freeStringArray(argvQ, nfiles+ ARGS_Q_START_FILE_OFFSET + 1);

	i=0;
	while(i<m){
		char message[PIPE_BUF];
		read(pQ[READ],message,PIPE_BUF);
		if(exitMessage(message)){
			i++;
		}
		else{
			char *msgtoA=writeA(message);
			write(pipe_write,msgtoA,PIPE_BUF);
			free(msgtoA);
			
		}

	}
	char endm[PIPE_BUF];
	sprintf(endm, "%s", END);
	write(pipe_write, endm, PIPE_BUF);
	wait(NULL);
	return 0;
}
