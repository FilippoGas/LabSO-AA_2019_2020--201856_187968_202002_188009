#include "messageToReport.h"


void addPadding(char *in, int dim_to_have){
	while(strlen(in) < dim_to_have){
		int j = strlen(in);
		in[j] = ' ';
		in[j + 1] = '\0';
	}
}

void addNewLine(char *in){
	int j = strlen(in);
	in[j] = '\n';
	in[j + 1] = '\0';
}


int openFIFO(){
	if(mkfifo(FIFO_NAME, 0777) == -1){		//DA CAMBIARE
		if(errno != EEXIST){
			perror("Fatal error on fifo: ");
			exit(-1);
		}
	}
 	
	int fd;

	if((fd = open(FIFO_NAME, O_WRONLY | O_NONBLOCK)) == -1){
		if(errno != ENXIO){
			perror("Fatal error: ");
			exit(-1);
		}
	
	}
	return fd;
}

char *contentToString(int *data){
	char *res = malloc((PIPE_BUF + 1) * sizeof(char));
	int i = 0;
	while(i < ALPHABET_SIZE){
		sprintf(res, "%s %d", res, data[i]);
		i++;
	}
	sprintf(res, "%s\n", res);
	addPadding(res, PIPE_BUF);
	return res;
}

void writeToReport(int **data, char **file_list, int file_list_size,  int fd){
	time_t current = time(NULL);
	char  timetemp[(2 * INTMAXCHAR) + 1];
	sprintf(timetemp, "%ld %d", current, file_list_size);
	addPadding(timetemp, (2 * INTMAXCHAR) - 1);
	addNewLine(timetemp);
	write(fd, timetemp, (2 * INTMAXCHAR));
	int i = 0;
	while(i < file_list_size){
		char nomeFile[PIPE_BUF + 1];
		sprintf(nomeFile, "%s", file_list[i]);
		addPadding(nomeFile, PIPE_BUF);
		write(fd, nomeFile, PIPE_BUF);	
		char *content = contentToString(data[i]);
		write(fd, content, PIPE_BUF);
		free(content);
		i++;
	}
}


