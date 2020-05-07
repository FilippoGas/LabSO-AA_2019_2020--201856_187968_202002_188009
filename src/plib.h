#ifndef PLIB_H
#define PLIB_H


//Reading e Writing delle pipe
#define RD 0
#define WR 1
//Segnali che le Q mandano
#define PREADY '0'
#define QREADY '1'
#define QEND '2'
//Numero di caratteri ASCII
#define MAXASCII 256


void createPipes(char ***fifoQ, char ***pQ,int nQ);
char *letturaQ(char* fifoQ);
void lettura_str_in(int ***cose, char *str_in,int nfile);
int lettura_numero(char *str_in);
void sommatoria(int ***mat1, int **mat2, int n);
void createQ(int *figlio, char* fifoQ,int parteQ,char *nomefiles[],int nfile);


#endif
