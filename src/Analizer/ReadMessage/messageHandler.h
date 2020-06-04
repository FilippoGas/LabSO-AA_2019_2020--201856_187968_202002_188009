#include "../../macro_libglob.h"
#include "../WriteToReport/messageToReport.h"
#include "../OnTheFly/onTheFlyHandler.h"
int isTermination(char *in);

char* getFileNameFromMessage(char *message, int *childId, int n, char ***args_for_p, int *finished);

int getPosInFileList(char *filename, char **file_list, int nFiles);

int **initResMatrix(int nFiles);

void readMessage(char *message, int **value, int *childId, int n, char ***args_for_p, char **file_list, int nFiles, int *finished, int *file_finished);

int **initResMatrix(int nFiles);

int **readFromPipes(int ***pipe_for_P, int ***pipe_control, int **p_pid_array, char ****p_argv_matrix, int *n, char ***files, int *nfiles, int pipe_from_M, int *m);
