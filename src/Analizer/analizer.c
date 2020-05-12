#include "../CheckInput/inputcheck.h"
#include "../Debug/utility.h"
#include "../CheckInput/pPreprocessing.h"
#include "WriteToReport/messageToReport.h"
#include "ReadMessage/messageHandler.h"
#include <fcntl.h>
#include <sys/wait.h>
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

	int m = 3, n = 4, ninput, recursive, nfiles, ndirs, ret = 0;
	char **input, **dir_list, **file_list;

	//legge l'input, alloca dinamicamente **input
	readInput(argc, argv, &input, &ninput, &n, &m, &recursive);

	printInput(m, n, input, ninput, recursive);

	//recupera vere cartelle e file nell'input, libera **input, alloca dinamicamente **dir_list e **file_list
	validateInput(input, ninput, &file_list, &dir_list, &nfiles, &ndirs);

	printf("Directories:\n");
	printStringArray(dir_list, ndirs);
	printf("Files:\n");
	printStringArray(file_list, nfiles);

	//Recupera i contenuti delle directory
	int dir_content_size;
	char **dir_content = getContentOfDirs(dir_list, ndirs, recursive, &dir_content_size);
	freeStringArray(dir_list, ndirs);	//libero dir_list
	printf("Files in directories:\n");
	printStringArray(dir_content, dir_content_size);

	//Unisce i file in file_list e in dir_content e salva in un array tutti i percorsi reali;
	int def_file_list_size;
	char **def_file_list = getAllFullPath(file_list, nfiles, dir_content, dir_content_size, &def_file_list_size);
	freeStringArray(file_list, nfiles);	//libero file_list
	freeStringArray(dir_content, dir_content_size);		//libero dir_content
	printf("Definitive file list:\n");
	printStringArray(def_file_list, def_file_list_size);

	//cambia i file da string a idfile e li mette in un array
	int file_size = def_file_list_size;
	struct idfile **files = polishFileList(def_file_list, def_file_list_size);
	printIdfileArray(files, file_size);


	//genero n processi P

	//assegno i file agli n processi p
	//in ogni riga i di fileMatrix ci sono i file relativi al processo i
	
	//char ***fileMatrix = fileDivisor(n,def_file_list,def_file_list_size);
	//printStringMatrix(fileMatrix,n, def_file_list_size);
	
	int pipe_for_P[2];
	pipe2(pipe_for_P, __O_DIRECT);
	char ***p_argv_matrix = createArgsForP(n, m, def_file_list, def_file_list_size, pipe_for_P[0], pipe_for_P[1]);
	printf("QUESTA E` LA TABELLA DEGLI ARGOMENTI DI P:\n");
	printArgumentMatrix(p_argv_matrix, n);
	
	printf("\n\n\n\n\n\nORA GENERO I PROCESSI P e ASPETTO CHE MI INVIINO OGNUNO M MESSAGGI\n\n\n");

	int nP = 0;
	int p_pid_array[n];
	while(nP < n){
		p_pid_array[nP] = fork();
		if(p_pid_array[nP] == 0)
			execvp(p_argv_matrix[nP][0], p_argv_matrix[nP]);
		nP++;
	}
	
	nP = 0;
	close(pipe_for_P[1]);
	int **data = initResMatrix(def_file_list_size);
	while(nP < n){			//Prestare attenzione al caso in cui un P termini senza aver inviato tutto
		char message[PIPE_BUF];
		read(pipe_for_P[0], message, PIPE_BUF);	
		printf("Sono il padre e ho ricevuto il messaggio: %s\n", message);
		
		if(isTermination(message))
			nP++;
		else{
			readMessage(message, data, p_pid_array, n, p_argv_matrix, def_file_list, def_file_list_size);
			int dfifo = openFIFO();	
			if(dfifo != -1){
				writeToReport(data, def_file_list, def_file_list_size, dfifo);
				close(dfifo);
			}
		}
	
	}
	wait(NULL); 	//? NON SO SE SERVA
	unlink(FIFO_NAME);
	close(pipe_for_P[0]);
	int fd = open(REPORT_FILE, O_WRONLY);	
	writeToReport(data, def_file_list, def_file_list_size, fd);
	close(fd);



	//Libero memoria allocata dinamicamente
	freeIdfileArray(files, file_size);
	//libero def_file_list
	freeStringArray(def_file_list, def_file_list_size);
	//Libero p_argv_matrix
	freeArgsForP(p_argv_matrix, n);
	return ret;

}
