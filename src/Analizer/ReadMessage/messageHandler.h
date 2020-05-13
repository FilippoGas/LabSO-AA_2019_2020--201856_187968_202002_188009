#include "../../macro_libglob.h"
int isTermination(char *in);

char* getFileNameFromMessage(char *message, int *childId, int n, char ***args_for_p);

void readMessage(char *message, int **value, int *childId, int n, char ***args_for_p, char **file_list, int nFiles);

int **initResMatrix(int nFiles);
