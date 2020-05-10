#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define ALPHABET_SIZE 256

int isTermination(char *in);

char* getFileNameFromMessage(char *message, int *childId, int n, char ***args_for_p, int *x);

void readMessage(char *message, int **value, int *childId, int n, char ***args_for_p, char **file_list, int nFiles);

int **initResMatrix(int nFiles);
