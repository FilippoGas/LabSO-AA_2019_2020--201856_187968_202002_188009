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
int readInput(int argc, char *argv[], int *m, int *pipe_read, int *pipe_write, char ***files, int pipe_control[]){
	(*m) = atoi(argv[1]);
	(*pipe_read) = atoi(argv[2]);
	(*pipe_write) = atoi(argv[3]);
	pipe_control[READ] = atoi(argv[4]);
	pipe_control[WRITE] = atoi(argv[5]);
	(*files) = arrayStringSubset(argc, ARGS_P_START_FILE_OFFSET, argv);
	return argc - ARGS_P_START_FILE_OFFSET;
}


/*Creo Q.
 */
int createChildren(int *pid, char **argvQ, int **pipe, int **pipe_control, int m, int i){
        int res = 0;
	(*pid) = fork();

        if((*pid) == 0){
		int j = 0;
		while(j < m){
			if(j != i){
				close(pipe_control[j][READ]);
				close(pipe_control[i][WRITE]);
				close(pipe[j][READ]);
				close(pipe[j][WRITE]);
			}
			j++;
		}
		res = execvp(argvQ[0], argvQ);
	    }
	return res;
}

int *startAllQ(int **pipe, int **pipe_control, char ***argvQ, int m){
	int i = 0;
	int *pids = (int *)malloc(m * sizeof(int));
	while(i < m){
		if(createChildren(pids + i, argvQ[i], pipe, pipe_control, m, i)){
			perror("Error on creation of Q:");
		}
		close(pipe[i][WRITE]);
		close(pipe_control[i][READ]);
		i++;
	}
	return pids;
}



/* Crea la chiamata di Q.
 * FORMATO CHIAMATA Q:
 * ./Q nQ m pipe_read pipe_write file0 file1 . . . filek NULL
 */
char ***create_ArgvQ(int m, int **pipe, int **pipe_control, char **files, int nfiles){
        char ***ret = (char ***)malloc(m * sizeof(char **));
	int i = 0;
	while(i < m){
		ret[i] = calloc(nfiles + ARGS_Q_START_FILE_OFFSET + 1,sizeof(char *));
		ret[i][0]=(char *)calloc((strlen(QNAME) + 1), sizeof(char));
        	sprintf(ret[i][0], "%s", QNAME);

        	ret[i][1]=(char *)calloc((INTMAXCHAR + 1), sizeof(char));
		sprintf(ret[i][1], "%d", i);

        	ret[i][2]=(char *)calloc((INTMAXCHAR + 1), sizeof(char));
        	sprintf(ret[i][2], "%d", m);

        	ret[i][3]=(char *)calloc(INTMAXCHAR + 1, sizeof(char));
        	sprintf(ret[i][3], "%d", pipe[i][READ]);

        	ret[i][4]=(char *)calloc(INTMAXCHAR + 1, sizeof(char));
        	sprintf(ret[i][4], "%d", pipe[i][WRITE]);

		ret[i][5]=(char *)calloc(INTMAXCHAR + 1, sizeof(char));
        	sprintf(ret[i][5], "%d", pipe_control[i][READ]);

        	ret[i][6]=(char *)calloc(INTMAXCHAR + 1, sizeof(char));
        	sprintf(ret[i][6], "%d", pipe_control[i][WRITE]);

        	int j=0;
		while(j < nfiles){
        	        ret[i][j + ARGS_Q_START_FILE_OFFSET]=(char *)malloc(strlen(files[j]) + 1);
        	        sprintf(ret[i][j + ARGS_Q_START_FILE_OFFSET], "%s ", files[j]);
			j++;
		}
		//ret[j+ARGS_Q_START_FILE_OFFSET]=NULL;
		i++;
	}
	return ret;
}


/*Dealloca un array di stringhe.
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
void writeA(char *mess, int fd){
   	char* ret = malloc((PIPE_BUF + 1) * sizeof(char));
        sprintf(ret, "%d %s", getpid(), mess);
	write(fd, ret, PIPE_BUF);
}



int **initPipes(int m){
	int **res = (int **)malloc(m * sizeof(int *));
	int i = 0;
	while(i < m){
		res[i] = (int *)malloc(2 * sizeof(int));
		pipe2(res[i], __O_DIRECT | O_NONBLOCK);
		i++;
	}
	return res;
}

int **initEmptyPipes(int m){
	int **res = (int **)malloc(m * sizeof(int *));
	int i = 0;
	while(i < m){
		res[i] = (int *)malloc(2 * sizeof(int));
		res[i][0] = -1;
		res[i][1] = -1;
		i++;
	}
	return res;
}

void freeIntMatrix(int **in, int n){
	int i = 0;
	while(i < n){
		free(in[i]);
		i++;
	}
	free(in);
}

void readFromPipes(int **pipe_for_Q, int m, int pipe_to_A, int pipe_from_A, int **pipe_control_for_Q){
	int byteRead = -1;
	while(byteRead != 0){
		if(pipe_from_A != -1){
			execChangeOnTheFly(pipe_from_A, m, pipe_control_for_Q);
		}
		int i = 0;
		byteRead = 0;
		while(i < m){
			char message[PIPE_BUF];
			int temp = read(pipe_for_Q[i][READ], message, PIPE_BUF);
			if(temp > 0){
				writeA(message, pipe_to_A);
			}
			byteRead += temp;
			i++;
		}
	}
}
