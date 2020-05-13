#include "../../macro_libglob.h"
/* Divide i file tra i processi P (DEPRECATO)
 */
char*** fileDivisor(int n, char** files, int nFiles);

/* Crea la matrice per gli argomenti P: processo P, m, pipe read, pipe write, file
 * per P e NULL
 */
char ***createArgsForP(int n, int m, char **files, int nFiles, int pipeRead, int pipeWrite);

/* Libera gli argomenti allocati dinamicamente nella matrice per P
 */
void freeArgsForP(char *** matrix, int row);
