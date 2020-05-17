#include "messageHandler.h"

int isTermination(char *in){
	return !strcmp(in, END);
}

char* getFileNameFromMessage(char *message, int *childId, int n, char ***args_for_p){
	/* Leggo childId e FileNumberInChildId in modo da ottenere il nome del file
	 */
	int row = -1;
	int column;
	char *temp;
	temp = strtok(message, " ");
	int value = atoi(temp);
	int t = 0;
	while(t < n && row == -1){
		if(childId[t] == value)
			row = t;
		t++;
	}
	temp = strtok(NULL , " ");
	value = atoi(temp);		
	column = value;
	char *res = malloc((strlen(args_for_p[row][column]) + 1) * sizeof(char));
	sprintf(res, "%s", args_for_p[row][column]);
	return res;
}



int getPosInFileList(char *filename, char **file_list, int nFiles){
	int i = 0, res = -1;
	while(i < nFiles && res == -1){
		if(!strcmp(filename, file_list[i]))
			res = i;
		i++;
	}
	return res;
}

int **initResMatrix(int nFiles){
	int **res = calloc(nFiles, sizeof(int *));
	int i = 0;
	while(i < nFiles){
		res[i] = calloc(ALPHABET_SIZE, sizeof(int));
		i++;
	}
	return res;
}



void readMessage(char *message, int **value, int *childId, int n, char ***args_for_p, char ** file_list, int nFiles){
	/*FORMATO MESSAGGIO: 
	 * childId FileNumberInChildID value1 value2 . . . value 256\n
	 */
	char *filename = getFileNameFromMessage(message, childId, n, args_for_p);
	int value_row = getPosInFileList(filename, file_list, nFiles);
	free(filename);
	int z = 0;
	while(z < ALPHABET_SIZE){
		char *temp = strtok(NULL, " ");
		int value_read = atoi(temp);
		value[value_row][z] += value_read;
		z++;
	}
}

int **readFromPipes(int **pipe_for_P, int *p_pid_array, char ***p_argv_matrix, int n, char **files, int nfiles){
	int **data = initResMatrix(nfiles);
	int byteRead = -1;
	while(byteRead != 0){
		int i = 0;
		byteRead = 0;
		while(i < n){
			char message[PIPE_BUF];
			int temp = read(pipe_for_P[i][READ], message, PIPE_BUF);
			if(temp > 0){
				readMessage(message, data, p_pid_array, n, p_argv_matrix, files, nfiles);
				int dfifo = openFIFO();
				if(dfifo != -1){
					writeToReport(data, files, nfiles, dfifo);
					close(dfifo);
				}
			}
			byteRead += temp;
			i++;
		}	
	}
	return data;
}




