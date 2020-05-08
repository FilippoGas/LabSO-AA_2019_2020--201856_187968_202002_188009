#include "pPreprocessing.h"

char*** fileDivisor(int n, char** files, int nFiles){
  char*** res = (char ***)malloc(n*sizeof(char**));
  int i=0,j=0;
  while(i<n){
    res[i]= malloc(nFiles*sizeof(char *));
    i++;
  }
  i=0;
  int indexFile = 0;
  while(indexFile<nFiles){
    res[i][j] = (char *)malloc((strlen(files[indexFile])+1)*sizeof(char));
    sprintf(res[i][j], "%s",files[indexFile]);
    indexFile++;
    i++;
    if(i==n){
      i=0;
      j++;
    }
  }
  return res;
}

char ***createArgsForP(int n, int m, char **files, int nFiles, int pipeRead, int pipeWrite){
	int row_size_max = ceil((double)nFiles/(double)n) + 5;
	char ***res = (char ***)malloc(n * sizeof(char **));
	int i = 0, j = 0;
	while(i < n){
		res[i] = (char **)calloc(row_size_max, sizeof(char *));
		
		//NOME DI P
		res[i][0] = (char *)malloc((strlen(PNAME) + 1) * sizeof(char));
		sprintf(res[i][0], "%s", PNAME);
		//DIMENSIONE DI M
		res[i][1] = (char *)malloc((INTMAXSIZE + 1) * sizeof(char));
		sprintf(res[i][1], "%d", m);
		//FILE DESCRIPTOR PER LA TERMINAZIONE DI READ DELLA PIPE
		res[i][2] = (char *)malloc((INTMAXSIZE + 1) * sizeof(char));
		sprintf(res[i][2], "%d", pipeRead);
		//FILE DESCRIPTOR PER LA TERMINAZIONE DI WRITE DELLA PIPE
		res[i][3] = (char *)malloc((INTMAXSIZE + 1) * sizeof(char));
		sprintf(res[i][3], "%d", pipeWrite);
		i++;
	}
	i = 0;
	j = 4;
	while(i < nFiles){
		res[i % n][j] = (char *)malloc((strlen(files[i]) + 1) * sizeof(char));
		sprintf(res[i % n][j], "%s", files[i]);
		if(i != 0 && ((i + 1) % n) == 0)
			j++;
		i++;
	}
	printf("FINITA LA TABELLA\n");
	return res;
}


//char*** fileDivisor(int n, char** files, int nFiles){
  /*char*** res = (char ***)malloc(n*sizeof(char**));
  int i=0;
  while(i<n){
    int dimRiga=nFiles-i*n;
    if(dimRiga>n)
      dimRiga=n;
    res[i] = (char **)malloc(dimRiga*sizeof(char*));
    int j=i*n;
    while(j<(i+1)*n && j<nFiles){
      //printf("dimensione file %d \n",(int)strlen(files[j])+1);
      res[i][j-i*n]= (char *)malloc((strlen(files[j])+1)*sizeof(char));
      printf("%s \n",files[j]);
      sprintf(res[i][j-i*n],"%s",files[j]);
      j++;
    }
    printf("\n");
    i++;

  }
  return res;*/
//}
