#include "../../macro_libglob.h"
#include "../WriteToReport/messageToReport.h"
int isTermination(char *in);

char* getFileNameFromMessage(char *message, int *childId, int n, char ***args_for_p);

void readMessage(char *message, int **value, int *childId, int n, char ***args_for_p, char **file_list, int nFiles);

int **initResMatrix(int nFiles);

int **readFromPipes(int **pipe_for_P, int *p_pid_array, char ***p_argv_matrix, int n, char **files, int nfiles);
