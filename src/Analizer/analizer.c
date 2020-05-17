#include "./CheckInput/inputcheck.h"
#include "../Debug/utility.h"
#include "./CheckInput/pPreprocessing.h"
#include "WriteToReport/messageToReport.h"
#include "ReadMessage/messageHandler.h"
void printIdfileArray(struct idfile **in, int size){
	int i = 0;
	while(i < size){
		printf("\t%d:\n", i);
		printf("\t\tName: %s\n", in[i]->name);
		printf("\t\tPath: %s\n", in[i]->path);
		i++;
	}

}

int main(int argc, char *argv[]){

	int m = 3, n = 4, recursive, ret = 0;
	char **def_file_list;
	//Recupero input
	int def_file_list_size = manageInput(&def_file_list, argc, argv, &m, &n, &recursive);
	// apro una pipe per P
	int **pipe_for_P = initPipeMatrix(n);
	
	// Creo la matrice con gli argomenti per P
	char ***p_argv_matrix = createArgsForP(n, m, def_file_list, def_file_list_size, pipe_for_P);
	printf("QUESTA E` LA TABELLA DEGLI ARGOMENTI DI P:\n");
	printArgumentMatrix(p_argv_matrix, n);
	
	printf("\n\n\n\n\n\nORA GENERO I PROCESSI P e ASPETTO CHE MI INVIINO OGNUNO M MESSAGGI\n\n\n");
	
	//genero n processi P, chiudendo per ognuno le pipe che non gli appartengono
	int *p_pid_array = startAllP(n, pipe_for_P, p_argv_matrix);
	

	int nP = 0;
	printf("A INIZIA A LEGGERE\n");
	
	int **data = readFromPipes(pipe_for_P, p_pid_array, p_argv_matrix, n, def_file_list, def_file_list_size);

	free(p_pid_array);
	printf("A HA FINITO DI LEGGERE\n");
	wait(NULL); 	//? NON SO SE SERVA
	unlink(FIFO_NAME);
	int i = 0; 
	while(i < n){
		close(pipe_for_P[i][READ]);
		i++;
	}
	int fd = open(REPORT_FILE, O_WRONLY | O_CREAT | O_TRUNC);	
	writeToReport(data, def_file_list, def_file_list_size, fd);
	close(fd);


	//Libero memoria allocata dinamicamente
	//freeIdfileArray(files, file_size);
	//libero def_file_list
	freeStringArray(def_file_list, def_file_list_size);
	//Libero p_argv_matrix
	freeArgsForP(p_argv_matrix, n);
	printf("A ha terminato\n");
	return ret;

}
