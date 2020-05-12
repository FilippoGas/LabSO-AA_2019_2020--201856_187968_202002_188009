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

int createChildren(char **argvQ){
        //Creo Q
        int f=fork();
        while(f<0){
                f=fork();
        }
        if(f==0){
        	//execv order 66
		int try=execv(argvQ[0],argvQ);
    		if(try<0){
			printf("MIINCHIA NON FUNZIONA!!!\n");
			exit(1);
		}
	    }
	return f;
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
	ret=calloc(nfiles+6,sizeof(char *));
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
                sprintf(ret[i+5], "%s ", files[i]);
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
	return !strcmp(mess,ENDQ);
}


//conto le cifre di un numero intero
int cifre_int(int n){
        int i=0;
        if(i!=0){
                while(n/10!=0)
                i++;
                return i;
                }
        else return 1;
}

//Scrivo il messaggio che va mandato ad Anal.
char *writeA(char *mess){
        int num=lettura_numero(&mess)-2;
        char *ret=(char *)malloc(strlen(mess)+cifre_int(num)+1);
        sprintf(ret, "%d %s",num,mess);
        return ret;
}


//
int lettura_numero(char **str_in){
        char *temp = strchr(*str_in,' ');

        if(( (long) temp ) == 0){
                return atoi(*str_in);
        }

        int ntemp = (int)(temp - *str_in);
        char numero[ntemp+1];

        strncpy(numero, *str_in, ntemp);
        *str_in=temp+1;
        numero[ntemp]='\0';
        return atoi(numero);
}












