#include "processPfunc.h"
#include "../Debug/utility.h"

int *pids_Q;
int m;

void killHandler(int signal){
	int i=0;
	printf("IL SIGTERM e` stato dichiarato\n");
	while(i<m){
		kill(pids_Q[i],SIGTERM);
		i++;
	}
	exit(0);
}

int main(int argc, char *argv[]){
	signal(SIGTERM, killHandler);
	sleep(15);
	int pipe_read, pipe_write, pipe_control[2];
	char **files;
	//./p m pipe_read pipe_write files

	//Leggo l'input
	int nfiles = readInput(argc, argv, &m, &pipe_read, &pipe_write, &files, pipe_control);
	close(pipe_read);
	if(pipe_control[2] != -1)
		close(pipe_control[WRITE]);

	int **pipe_for_Q = initPipes(m);
	int **pipe_control_for_Q;
	if(pipe_control[READ] == -1 && pipe_control[WRITE] == -1)
		pipe_control_for_Q = initEmptyPipes(m);
	else
		pipe_control_for_Q = initPipes(m);
	//Creo le chiamate per le Q
	char ***argvQ = create_ArgvQ(m, pipe_for_Q, pipe_control_for_Q, files, nfiles);
	printArgumentMatrix(argvQ, m);
	//Creo le Q
	pids_Q = startAllQ(pipe_for_Q, pipe_control_for_Q, argvQ, m);

	//freeStringArray(argvQ, nfiles + ARGS_Q_START_FILE_OFFSET + 1);

	readFromPipes(pipe_for_Q, m, pipe_write, pipe_control[READ], pipe_control_for_Q);

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
