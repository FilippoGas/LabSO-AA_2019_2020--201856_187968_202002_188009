#include "processPfunc.h"

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


int readInput(int argc, char *argv[], int *m, int *pipe_read, int *pipe_write, char ***files){
	(*m) = atoi(argv[1]);
	(*pipe_read) = atoi(argv[2]);
	(*pipe_write) = atoi(argv[3]);
	(*files) = arrayStringSubset(argc, 4, argv);
	return argc - 4;
}
/*
char ***createQmatrix(int m, int pipe[2], char **files, int nfiles){
	char ***res = (char ***)malloc(m * sizeof(char **));
	int i = 0;
	while(i < m){
		res[i] = (char **)calloc((5 + nfiles), sizeof(char *));

		res[i][0] = (char *)malloc((strlen(QNAME) + 1) * sizeof(char));
		sprintf(res[i][0], "%s", QNAME);

		res[i][1] = (char *)malloc((INTMAXCHAR + 1) * sizeof(char));
		sprintf(res[i][4], "%d", pipe[READ]);

		res[i][1] = (char *)malloc((INTMAXCHAR + 1) * sizeof(char));
		sprintf(res[i][3], "%d", pipe[WRITE]);

		res[i][2] = (char *)malloc((INTMAXCHAR + 1) * sizeof(char));
		sprintf(res[i][2], "%d", m);

		res[i][3] = (char *)malloc((INTMAXCHAR + 1) * sizeof(char));
		sprintf(res[i][1], "%d", i);

		int j = 0;
		while(j < nfiles){
			res[i][j + 4] = (char *)malloc((strlen(files[j]) + 1) * sizeof(char));
			sprintf(res[i][j + 4], "%s", files[j]);
			j++;
		}
		i++;
	}
	return res;
}
*/

void createChildren(char **argvQ){
        //Creo Q
        int f=fork();
        while(f<0){
                f=fork();
        }
        if(f==0){
        //exec order 66
        //execpv(argvQ[0],argvQ);
        }
}


long lungnum(int m){
        int i=1;
        while(m/10!=0){
        m=m/10;
        i++;
        }
        return i;
}


char **create_ArgvQ(int m, int pipe[2], char **files, int nfiles){
        char **ret;
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
                ret[i+5]=(char *)malloc(strlen(files[i])+1);
                sprintf(ret[i+5], "%s", files[i]);
        i++;
        }
        ret[i+5]=NULL;
        return ret;
}





void freeStringArray(char **in, int dim){
	int i = 0;
	while(i < dim){
		free(in[i]);
		i++;
	}
	free(in);
}

void freeArgsForQ(char *** matrix, int row){
	row--;
	while(row >= 0){
		int j = 0;
		while(matrix[row][j] != NULL){
			free(matrix[row][j]);
			j++;
		}
		free(matrix[row]);
		row--;
	}
	free(matrix);
}


int exitMessage(char *mess){
	int ret=0;
	if(strlen(mess)>5)
		ret=1;
	return ret;
}

int notNULL(char *mess){
	return !strcmp(ENDM, mess);
}
