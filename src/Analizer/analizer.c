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

	int m = 3, n = 4, recursive, ret = 0, pipe_from_main[2], pipe_to_main[2];
	char **def_file_list;
	//Recupero input
	int def_file_list_size = manageInput(&def_file_list, argc, argv, &m, &n, &recursive, pipe_from_main, pipe_to_main);
	
	if(pipe_from_main[READ] != -1 && pipe_from_main[WRITE])
		close(pipe_from_main[WRITE]);
	
	if(pipe_to_main[READ] != -1 && pipe_to_main[WRITE] != -1){
		close(pipe_to_main[READ]);
		int i = 0;
		while(i < def_file_list_size){
			char message[PATH_MAX + 2];
			sprintf(message, "%s\n", def_file_list[i]);
			write(pipe_to_main[WRITE], message, strlen(message));
		}
		close(pipe_to_main[WRITE]);
	}

	// apro una pipe per P
	int **pipe_for_P = initPipeMatrix(n);
	int **pipe_for_control_P = NULL;
	if(pipe_from_main[READ] != -1 && pipe_from_main[WRITE] != -1)
		pipe_for_control_P = initPipeMatrix(n);
	else{
		pipe_for_control_P = initEmptyPipeMatrix(n);
	}	
	
	// Creo la matrice con gli argomenti per P
	char ***p_argv_matrix = createArgsForP(n, m, def_file_list, def_file_list_size, pipe_for_P, pipe_for_control_P);
	printf("QUESTA E` LA TABELLA DEGLI ARGOMENTI DI P:\n");
	printArgumentMatrix(p_argv_matrix, n);
	
	//printf("\n\n\n\n\n\nORA GENERO I PROCESSI P e ASPETTO CHE MI INVIINO OGNUNO M MESSAGGI\n\n\n");
	
	//genero n processi P, chiudendo per ognuno le pipe che non gli appartengono
	int *p_pid_array = startAllP(n, pipe_for_P, pipe_for_control_P, p_argv_matrix);
	

	int nP = 0;
	printf("A INIZIA A LEGGERE\n");	
	int **data = readFromPipes(pipe_for_P, pipe_for_control_P, p_pid_array, p_argv_matrix, n, def_file_list, def_file_list_size, pipe_from_main[READ]);
	printf("A ha finito di leggere\n");
	free(p_pid_array);
	closePipeMatrix(pipe_for_P, n, READ);
	closePipeMatrix(pipe_for_control_P, n, WRITE);
	freePipeMatrix(pipe_for_control_P, n);
	freePipeMatrix(pipe_for_P, n);
	printf("A HA FINITO DI LEGGERE\n");
	wait(NULL); 	//? NON SO SE SERVA
	unlink(FIFO_NAME);
	int i = 0; 
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
