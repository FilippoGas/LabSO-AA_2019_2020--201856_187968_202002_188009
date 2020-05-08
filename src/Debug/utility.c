#include "utility.h"

void printInput(int m, int n, char **input, int ninput, int rec){
	printf("m ha valore: %d\nn ha valore: %d\n", m, n);
	printf("Ci sono %d input\nINPUTS:\n", ninput);
	printStringArray(input, ninput);
	if(rec)
		printf("La ricerca deve essere ricorsiva\n");
	else
		printf("La ricerca non deve essere ricorsiva\n");
}

void printStringArray(char **in, int n){
	int i = 0;
	while(i < n){
		printf("\t %d:\t%s\n", i, in[i]);
		i++;
	}

}

void printStringMatrix(char ***matrix,int row, int total){
	int i=0, j=0;
	int fileTotali = total;
	printf("\n");
	while(i<row && i<total && fileTotali){
		printf("Il processo %d ha il file %s \n",i,matrix[i][j]);
		fileTotali--;
		i++;
		if(i==row){
			i=0;
			j++;
		}
	}
}

void printArgumentMatrix(char ***matrix, int n){
	int i = 0;
	while(i < n){
		int j = 0;
		printf("P %d: ", i);
		fflush(stdout);
		while(matrix[i][j] != NULL){
			printf("%s\t", matrix[i][j]);
			j++;
		}
		printf("\n\n");
		i++;
	}
}
