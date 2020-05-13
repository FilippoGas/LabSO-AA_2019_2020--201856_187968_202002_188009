#include "messageHandler.h"

int isTermination(char *in){
	return !strcmp(in, END);
}

char* getFileNameFromMessage(char *message, int *childId, int n, char ***args_for_p){
	/* Leggo childId e FileNumberInChildId in modo da ottenere il nome del file
	 */
	int row;
	int column;
	int i = 0, z = 0;
	char *temp;
	temp = strtok(message, " ");
	int value = atoi(temp);
	int t = 0;
	while(t < n){
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
	int i = 0;
	char *filename = getFileNameFromMessage(message, childId, n, args_for_p);
	int value_row = getPosInFileList(filename, file_list, nFiles);
	int z = 0;
	while(z < ALPHABET_SIZE){
		char *temp = strtok(NULL, " ");
		int value_read = atoi(temp);
		value[value_row][z] += value_read;
		z++;
	}
}






