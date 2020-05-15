#include "processPfunc.h"


/*Crea una stringa dove andranno salvati i nomi dei file.
 */
char **arrayStringSubset(int dim, int start, char **in){
	char **res = (char **)malloc((dim - start) * sizeof(char *));
	int i = start;
	while(start < dim){
		res[start - i] = (char *)malloc((strlen(in[start]) + 1) * sizeof(char));
		sprintf(res[start - i], "%s", in[start]);
		start++;
	}
	return res;
}


/* Leggo l'input che mi viene da Anal.
 * FORMATO MESSAGGIO DA ANAL
 * ./p m pipe_read pipe_write file0 file1 . . . filek
 */
int readInput(int argc, char *argv[], int *m, int *pipe_read, int *pipe_write, char ***files){
	(*m) = atoi(argv[1]);
	(*pipe_read) = atoi(argv[2]);
	(*pipe_write) = atoi(argv[3]);
	(*files) = arrayStringSubset(argc, ARGS_P_START_FILE_OFFSET, argv);
	return argc - ARGS_P_START_FILE_OFFSET;
}


/*Creo Q.
 */
int createChildren(char **argvQ){
        int f=fork();
        while(f<0){
                f=fork();
        }
        if(f==0){
		int try=execv(argvQ[0],argvQ);
    		if(try<0){
			//SYSTEMCALL!!!
			perror("Errore di chiamata Q :");
			exit(-1);
		}
	    }
	return f;
}


/*Calcola le cifre dell'intero n.
 */
long lungnum(int n){
        int i=1;
        while(n/10!=0){
        n=n/10;
        i++;
        }
        return i;
}


/* Crea la chiamata di Q.
 * FORMATO CHIAMATA Q:
 * ./Q nQ m pipe_read pipe_write file0 file1 . . . filek NULL
 */
char **create_ArgvQ(int m, int pipe[2], char **files, int nfiles){
        char **ret;
	ret=calloc(nfiles + ARGS_Q_START_FILE_OFFSET + 1,sizeof(char *));
	ret[0]=(char *)malloc(strlen(QNAME)+1);
        sprintf(ret[0], "%s", QNAME);

        ret[1]=(char *)malloc((INTMAXCHAR+1) * sizeof(char));

        ret[2]=(char *)malloc(lungnum(m)+1);
        sprintf(ret[2], "%d", m);

        ret[3]=(char *)malloc(lungnum(pipe[READ])+1);
        sprintf(ret[3], "%d", pipe[READ]);

        ret[4]=(char *)malloc(lungnum(pipe[WRITE])+1);
        sprintf(ret[4], "%d", pipe[WRITE]);
        int i=0;
	while(i<nfiles){
                ret[i+ ARGS_Q_START_FILE_OFFSET]=(char *)malloc(strlen(files[i])+1);
                sprintf(ret[i+5], "%s ", files[i]);
		i++;
	}
	ret[i+ARGS_Q_START_FILE_OFFSET]=NULL;
	return ret;
}


/*Dealloca un arrey di stringhe.
 */
void freeStringArray(char **in, int dim){
	int i = 0;
	while(i < dim){
		free(in[i]);
		i++;
	}
	free(in);
}


/* Scrivo il messaggio che va mandato ad Anal.
 * FORMATO DEL MESSAGGIO:
 * PID nfile carattere0 carattere1 . . . carattere255 \n
 */
char *writeA(char *mess){
   	char* ret = malloc(PIPE_BUF * sizeof(char));
        sprintf(ret, "%d %s", getpid(), mess);
        return ret;
}


/*Riconosce se la stringa in lettura è un messaggio di END.
 */
int exitMessage(char *mess){
	return !strcmp(mess,END);
}
