#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define SETN 0
#define SETM 1
#define HELP 2
#define COMMAND 0
#define FILES 1
#define DIRS 2
#define WSIZE 81
#define MANPATH "/LabSO-AA_2019_2020--201856_187968_202002_188009/src/ManFiles/"

void readInput(int argc, char *argv[], char ***files, char ***dirs, int *nfiles, int *ndir, int *n, int *m);

void optionN(int *n, char *value);

void optionM(int *m, char *value);

int typeOfArgument(char *value);

int typeOfCommand(char *value);

int executeCommand(int type, int *n, int *m, int argc, int i, char *value);

int isNumber(char *value);

void changeNOrM(int type, int *n, int *m, char *value);

char **getNames(char *argv[], int *pos, int n);

