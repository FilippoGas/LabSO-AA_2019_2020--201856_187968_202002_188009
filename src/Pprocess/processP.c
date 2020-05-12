#include "processPfunc.h"
#include "../Debug/utility.h"

/*
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


int lungnum(int m){
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

	ret[2]=(char *)malloc(lungnum(m))+1);
	sprintf(ret[2], "%d", m);

	ret[3]=(char *)malloc(lungnum(pipe[READ])+1);
	sprintf(ret[3], "%d", pipe[READ]);

	ret[4]=(char *)malloc(lungnum(pipe[WRITE])+1);
	sprintf(ret[4], "%s", pipe[WRITE]);
	int i=0;
	while(i<nfiles){
		ret[i+5]=(char *)malloc(strlen(files[i])+1);
		sprintf(ret[i+5], "%s", files[i]);
	i++;
	}
	ret[i+5]=malloc(strlen(NULL));
	sprintf(ret[i+5],"%s",NULL);


	return ret;
}

*/
int main(int argc, char *argv[]){
	int m, pipe_read, pipe_write;
	char **files;
	int nfiles = readInput(argc, argv, &m, &pipe_read, &pipe_write, &files);
	close(pipe_read);


	int pQ[2];
	pipe(pQ);
	char **argvQ = create_ArgvQ(m, pQ, files, nfiles);
	int i = 0;
	while(i < m){
		sprintf(argvQ[1],"%d",i);
		int f=createChildren(argvQ);
		if(f>0){
			i++;
		}
	}

	freeStringArray(argv, nfiles+5);
	i=0;
	while(i<m){
		char message[MAXMESS];
		read(pQ[READ],message,MAXMESS);
		if(notNULL(message)){
			if(exitMessage(message))
				i++;
			else write(pipe_write,message,MAXMESS);
		}
	}
	write(pipe_write,ENDM,strlen(ENDM)+1);
	return 0;
}
