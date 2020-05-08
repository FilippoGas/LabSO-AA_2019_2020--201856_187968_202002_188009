#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>


#define PNAME "/LabSO-AA_2019_2020--201856_187968_202002_188009/TestExe/P/P.out"		//PLACEHOLDER
#define INTMAXSIZE 11
char*** fileDivisor(int n, char** files, int nFiles);
//char*** fileDivisorProva(int n, char** files, int nFiles);

char ***createArgsForP(int n, int m, char **files, int nFiles, int pipeRead, int pipeWrite);
