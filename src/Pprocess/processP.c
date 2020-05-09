#include "processPfunc.h"
#include "../Debug/utility.h"

int main(int argc, char *argv[]){
	int m, pipe_read, pipe_write;
	char **files;
	int nfiles = readInput(argc, argv, &m, &pipe_read, &pipe_write, &files);
	char ***q_matrix = createQmatrix(m, pipe_write, files, nfiles);
	printf("\e[1;34m");
	printArgumentMatrix(q_matrix, m);
	printf("\e[0m");
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
	
	freeStringArray(files, nfiles);
	freeArgsForQ(q_matrix, m);
	return 0;
}
