#include "../../macro_libglob.h"
/* Divide i file tra i processi P (DEPRECATO)
 */
char*** fileDivisor(int n, char** files, int nFiles);

/* Crea la matrice per gli argomenti P: processo P, m, pipe read, pipe write, file
 * per P e NULL
 */
char ***createArgsForP(int n, int m, char **files, int nFiles, int **pipeMatrix);

/* Libera gli argomenti allocati dinamicamente nella matrice per P
 */
void freeArgsForP(char *** matrix, int row);

int **initPipeMatrix(int n);
void freePipeMatrix(int **in, int n);

int initP(int *pid, char **args, int **pipe_for_P, int n, int i);

int *startAllP(int n, int **pipe_for_P, char ***p_argv_matrix);
