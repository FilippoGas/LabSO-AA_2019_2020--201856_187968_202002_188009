#include"../../Analizer/CheckInput/inputcheck.h"

int cifre(int num){
	int ret = 1;
	while( num/10 != 0 ){
		ret++;
		num = num/10;
	}
	return ret;
}


char *intToChar(int num){
	char *ret = calloc( cifre(num)+1, sizeof(char) );
	sprintf(ret,"%d",num);
	return ret;
}

int main(int argc, char *argv[]){
	printf("\nPARTE ANALIZER\n");
	char **input;
	int ninput;
	int n;
	int m;
	int recursive;
	int pipe_from_m[2];
	int pipe_to_m[2];
	readInput(argc, argv, &input, &ninput, &n, &m, &recursive, pipe_from_m, pipe_to_m);
	int i=0;
	printf("Ho ricevuto questi file:\n");
	for(i=0;i<ninput;i++){
		printf("%s\n",input[i]);
	}
	close(pipe_to_m[READ]);
	close(pipe_from_m[WRITE]);
	//char *prova=intToChar(ninput);
	printf("pipe_to_m = %d %d\n",pipe_to_m[0],pipe_to_m[1] );
	char prova[INTMAXCHAR];
	sprintf(prova,"%d",ninput);
	write(pipe_to_m[WRITE],prova,PIPE_BUF);
	perror("\t");
	printf("Ho mandato=%s\n",prova);
	for(i=0;i<ninput;i++){
		printf("Ho mandato=%s\n",input[i]);
		write(pipe_to_m[WRITE],input[i],PIPE_BUF);
	}
	return 0;
}
