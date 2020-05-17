#include "processPfunc.h"
#include "../Debug/utility.h"

int main(int argc, char *argv[]){
	int m, pipe_read, pipe_write;
	char **files;
	//./p m pipe_read pipe_write files

	//Leggo l'input
	int nfiles = readInput(argc, argv, &m, &pipe_read, &pipe_write, &files);
	close(pipe_read);
	

	int **pipe_for_Q = initPipes(m);
	
	//Creo le chiamate per le Q
	char ***argvQ = create_ArgvQ(m, pipe_for_Q, files, nfiles);
		
	printArgumentMatrix(argvQ, m);	
	//Creo le Q
	int *pids_Q = startAllQ(pipe_for_Q, argvQ, m);

	//freeStringArray(argvQ, nfiles + ARGS_Q_START_FILE_OFFSET + 1);
	
	readFromPipes(pipe_for_Q, m, pipe_write);
	
	//Chiudo P
	int i = 0;
	while(i < m){
		close(pipe_for_Q[i][READ]);
		i++;
	}
	close(pipe_write);
	wait(NULL);
	return 0;
}
