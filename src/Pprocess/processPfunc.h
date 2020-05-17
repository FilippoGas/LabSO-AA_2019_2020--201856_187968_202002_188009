#include "../macro_libglob.h"

/* Legge l'input per un processo P, non metto il controllo in quanto in teoria viene solo eseguito da A
 * se non si puo` fare in modo che l'utente lo esegua andranno creati per far piacere a Naimoli
 */
int readInput(int argc, char *argv[], int *m, int *pipe_read, int *pipe_write, char ***files);

/* Prendo un sottoinsieme di una stringa e la salvo una nuova allocata dinamicamente
 */
char **arrayStringSubset(int dim, int start, char **in);


/* Libera un array di stringhe allocato dinamicamente
 */
void freeStringArray(char **in, int dim);

char ***create_ArgvQ(int m, int **pipe, char **files, int nfiles);

int createChildren(int *pid, char **argvQ, int **pipe, int m, int i);


int *startAllQ(int **pipe, char ***argvQ, int m);

void writeA(char *mess, int fd);


int **initPipes(int m);
void freeIntMatrix(int **in, int n);
void readFromPipes(int **pipe_for_Q, int m, int pipe_to_A);

