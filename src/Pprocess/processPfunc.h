#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define INTMAXCHAR 13
#define QNAME "/LabSO-AA_2019_2020--201856_187968_202002_188009/TestExe/Qprocess/Q.out"
#define READ 0
#define WRITE 1
#define MAXMESS 10000
#define ENDM "\\end"

/* Legge l'input per un processo P, non metto il controllo in quanto in teoria viene solo eseguito da A
 * se non si puo` fare in modo che l'utente lo esegua andranno creati per far piacere a Naimoli
 */
int readInput(int argc, char *argv[], int *m, int *pipe_read, int *pipe_write, char ***files);

/* Prendo un sottoinsieme di una stringa e la salvo una nuova allocata dinamicamente
 */
char **arrayStringSubset(int dim, int start, char **in);

/* Creo la matrice per i processi Q, devono essere fatti con: QNAME pipe di scrittura,
 * m, porzione di file da leggere, file da leggere e NULL
 */
char ***createQmatrix(int m, int pipe[2], char **files, int nfiles);

/* Libera un array di stringhe allocato dinamicamente
 */
void freeStringArray(char **in, int dim);

/* Libera la matrice dei processi Q allocata dinamicamente
 */
void freeArgsForQ(char *** matrix, int row);


char **create_ArgvQ(int m, int pipe[2], char **files, int nfiles);

int exitMessage(char *);

int notNULL(char *);
