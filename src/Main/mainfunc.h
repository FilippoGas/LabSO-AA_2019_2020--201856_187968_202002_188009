#include"../Analizer/CheckInput/inputcheck.h"
#include"messages.h"
#define AZIONI 3
#define AZIONIMENUANAL 7
#define NUMAZIONIPOSSIBILI 6
#define NPATHANAL 8
#define PATHANAL "./TestArea/anal"

#ifndef MAINFUNC_H
#define MAINFUNC_H



char *getIn();

int cifre(int num);

char *intToChar(int num);

void printOptions();

void printOpAnal();

void presetAnal(int *n, int *m, char ***vari, int *nvari, int *rec, int **elimin);

void addtoArray(char ***array,int *ndata,char *add,int **elimin);

void recurtion( int *rec );

int	isNum(char *pnum);

void setmN( int *num, char selez,int pipe[2]);

char **createExec(int n,int m,char **vari,int nvari,int rec,int *elimin,int pipe_to_a[2],int pipe_from_a[2]);

void eseguiAnal(char **execAnal,int lung);

void elimSelec(char **vari,int nvari,int **elimin,int pipe[2]);

void addFile(char ***vari,int *nvari,int **elimin,int pipe[2]);

void enterAnalMenu(int *n, int *m, char ***vari, int *nvari, int *rec,int **elimin,int pipe_to_a[2],int pipe_from_a[2]);

void startReporter();

void exitAnal();

void ending();

char *getInputorExit();

void cpArray(char ***array1, int *narray1, char **array2, int narray2);

void leggo_input_pipe(char ***input,int *ninput, int **elimin,int pipe_from_a[2]);

void firstStartAnal(char *argv[],int argc, int pipe_to_a[2], int pipe_from_a[2], char ***input,int *ninput,int **elimin);

#endif
