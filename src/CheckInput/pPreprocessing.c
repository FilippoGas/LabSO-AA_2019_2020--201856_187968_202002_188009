#include "pPreprocessing.h"

char*** fileDivisor(int n, char** files, int nFiles){
  char*** res = (char ***)malloc(n*sizeof(char**));
  int i=0,j=0;
  while(i<n){
    res[i]= malloc(nFiles*sizeof(char));
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
