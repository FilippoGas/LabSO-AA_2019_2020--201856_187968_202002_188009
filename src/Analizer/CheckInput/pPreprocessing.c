#include "pPreprocessing.h"

char ***createArgsForP(int n, int m, char **files, int nFiles, int pipeRead, int pipeWrite){
	int row_size_max = ceil((double)nFiles/(double)n) + ARGS_P_START_FILE_OFFSET + 1;
	char ***res = (char ***)malloc(n * sizeof(char **));
	int i = 0, j = 0;
	while(i < n){
		res[i] = (char **)calloc(row_size_max, sizeof(char *));
		
		//NOME DI P
		res[i][0] = (char *)malloc((strlen(PNAME) + 1) * sizeof(char));
		sprintf(res[i][0], "%s", PNAME);
		//DIMENSIONE DI M
		res[i][1] = (char *)malloc((INTMAXCHAR + 1) * sizeof(char));
		sprintf(res[i][1], "%d", m);
		//FILE DESCRIPTOR PER LA TERMINAZIONE DI READ DELLA PIPE
		res[i][2] = (char *)malloc((INTMAXCHAR + 1) * sizeof(char));
		sprintf(res[i][2], "%d", pipeRead);
		//FILE DESCRIPTOR PER LA TERMINAZIONE DI WRITE DELLA PIPE
		res[i][3] = (char *)malloc((INTMAXCHAR + 1) * sizeof(char));
		sprintf(res[i][3], "%d", pipeWrite);
		i++;
	}
	i = 0;
	j = ARGS_P_START_FILE_OFFSET;
	while(i < nFiles){
		res[i % n][j] = (char *)malloc((strlen(files[i]) + 1) * sizeof(char));
		sprintf(res[i % n][j], "%s", files[i]);
		i++;
		if((i + 1) % n == 0)
			j++;
	}
	return res;
}

void freeArgsForP(char *** matrix, int row){
	row--;
	while(row >= 0){
		int j = 0;
		while(matrix[row][j] != NULL){
			free(matrix[row][j]);
			j++;
		}
		free(matrix[row]);
		row--;
	}
	free(matrix);
}
