#include "pPreprocessing.h"

char ***createArgsForP(int n, int m, char **files, int nFiles, int **pipeMatrix, int **pipeMatrixControl){
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
		sprintf(res[i][2], "%d", pipeMatrix[i][READ]);
		//FILE DESCRIPTOR PER LA TERMINAZIONE DI WRITE DELLA PIPE
		res[i][3] = (char *)malloc((INTMAXCHAR + 1) * sizeof(char));
		sprintf(res[i][3], "%d", pipeMatrix[i][WRITE]);
		//FILE DESCRIPTOR PER LA TERMINAZIONE DI READ DELLA PIPE DI CONTROLLO
		res[i][4] = (char *)malloc((INTMAXCHAR + 1) * sizeof(char));
		sprintf(res[i][4], "%d", pipeMatrixControl[i][READ]);
		//FILE DESCRIPTOR PER LA TERMINAZIONE DI WRITE DELLA PIPE DI CONTROLLO
		res[i][5] = (char *)malloc((INTMAXCHAR + 1) * sizeof(char));
		sprintf(res[i][5], "%d", pipeMatrixControl[i][WRITE]);
		i++;
	}
	i = 0;
	j = ARGS_P_START_FILE_OFFSET;
	while(i < nFiles){
		res[i % n][j] = (char *)malloc((strlen(files[i]) + 1) * sizeof(char));
		sprintf(res[i % n][j], "%s", files[i]);
		i++;
		if(i % n == 0)
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

int **initPipeMatrix(int n){
	int **res = (int **)malloc(n * sizeof(int *));
	int i = 0;
	while(i < n){
		res[i] = (int *)malloc(2 * sizeof(int));
		pipe2(res[i], __O_DIRECT | O_NONBLOCK);
		i++;
	}
	return res;
}

int **initEmptyPipeMatrix(int n){
	int **res = (int **)malloc(n * sizeof(int *));
	int i = 0;
	while(i < n){
		res[i] = (int *)malloc(2 * sizeof(int));
		res[i][0] = -1;
		res[i][1] = -1;
		i++;
	}
	return res;
}

void freePipeMatrix(int **in, int n){
	int i = 0;
	while(i < n){
		free(in[i]);
		i++;
	}
	free(in);
}

int initP(int *pid, char **args, int **pipe_for_P, int **pipe_for_control_P, int n, int i){
	int res = 0;
	(*pid) = fork();
	if((*pid) == 0){
		int j = 0;
		while(j < n){
			if(j != i){
				close(pipe_for_P[j][READ]);
				close(pipe_for_P[j][WRITE]);
				close(pipe_for_control_P[j][READ]);
				close(pipe_for_control_P[i][WRITE]);
			}
			j++;
		}
		res = execvp(args[0], args);
	}
	return res;
}

int *startAllP(int n, int **pipe_for_P, int **pipe_for_control_P, char ***p_argv_matrix){
	int *p_pid_array = (int *)malloc(n * sizeof(int));
	int i = 0;
	while(i < n){
		if(initP(p_pid_array + i, p_argv_matrix[i], pipe_for_P, pipe_for_control_P, n, i))
			printf("ERRORE NELLA GENERAZIONE DI P");
		close(pipe_for_P[i][WRITE]);
		close(pipe_for_control_P[i][READ]);
		i++;
	}
	return p_pid_array;
}

void closePipeMatrix(int **matrix, int n, int i){
	int j = 0;
	while(j < n){
		close(matrix[j][i]);
		j++;
	}
}
