#include "messageHandler.h"

int isTermination(char *in){
	return !strcmp(in, "\\end");
}

char* getFileNameFromMessage(char *message, int *childId, int n, char ***args_for_p, int *x){
	/* Leggo childId e FileNumberInChildId in modo da ottenere il nome del file
	 */
	int row;
	int column;
	int i = 0, z = 0;
	while(z < 2){
		int j = i;
		while(j < strlen(message) && message[j] != ' ')
			j++;
		char *temp;
		strncat(temp, message + i, j - 1);
		int value = atoi(temp);
		if(z == 0){
			int t = 0;
			while(t < n){
				if(childId[t] == value)
					row = t;
				t++;
			}
		}
		else
			column = value;
		i = j + 1;
		z++;
	}
	(*x) = i;
	char *res = malloc((strlen(args_for_p[row][column]) + 1) * sizeof(char));
	sprintf(res, "%s", args_for_p[row][column]);
	return res;
}



int getPosInFileList(char *filename, char **file_list, int nFiles){
	int i = 0, res = 0;
	while(i < nFiles){
		if(!strcmp(filename, file_list[i]))
			res = i;
		i++;
	}
	return res;
}

int **initResMatrix(int nFiles){
	int **res = calloc(nFiles, sizeof(int *));
	int i = 0;
	while(i < nFiles)
		res[i] = calloc(ALPHABET_SIZE, sizeof(int));
	return res;
}



void readMessage(char *message, int **value, int *childId, int n, char ***args_for_p, char ** file_list, int nFiles){
	/*FORMATO MESSAGGIO: 
	 * childId FileNumberInChildID value1 value2 . . . value 256\n
	 */
	int i = 0;
	char *filename = getFileNameFromMessage(message, childId, n, args_for_p, &i);
	int value_row = getPosInFileList(filename, file_list, nFiles);
	int z = 0;
	while(z < 256){
		int j = i;
		while(j < strlen(message) && message[j] != ' ')
			j++;
		char *temp;
		strncat(temp, message + i, j - 1);
		int value_read = atoi(temp);
		value[value_row][z] += value_read;
		z++;
		i = j + 1;
	}
}






