#include "processPfunc.h"
#include "../Debug/utility.h"


int main(int argc, char *argv[]){
	int m, pipe_read, pipe_write;
	char **files;
	//./p m pipe_read pipe_write files
	int nfiles = readInput(argc, argv, &m, &pipe_read, &pipe_write, &files);
	close(pipe_read);


	int pQ[2];
	pipe(pQ);
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


	freeStringArray(argvQ, nfiles+6);

	i=0;
	while(i<m){
		fflush(stdout);
		char message[MAXMESS];
		read(pQ[READ],message,MAXMESS);
		if(exitMessage(message)){
			i++;
		}
		else{
			char *msgtoA=writeA(message);
			write(pipe_write,msgtoA,MAXMESS);
			free(msgtoA);
		}
	}
	write(pipe_write,ENDQ,strlen(ENDQ)+1);

	return 0;
}
