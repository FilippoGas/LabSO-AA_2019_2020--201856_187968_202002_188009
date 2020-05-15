#include<stdlib.h>
#include<stdio.h>
#include<string.h>


char *getIn(){
        int i=2;
	char *prova=malloc(i);
	char car_in=getc(stdin);
	prova[0]=car_in;
	prova[1]='\0';
        while(car_in!='\n'){
		i++;
		char tmp[i];
		strcpy(tmp,prova);
		car_in=getc(stdin);
		tmp[i-2]=car_in;
		free(prova);
		prova=malloc(i);
		strcpy(prova,tmp);
        }
	printf("lol=%s\n",prova);
	return prova;
}


int main(){
	printf("prova a scrivere\n");
	char *prova;
	prova=getIn();
	printf("Hai scritto %s\n",prova);
	free(prova);
	printf("scrivi dinuovo\n");
	prova=getIn();
	printf("Hai scritto %s\n",prova);
	free(prova);
	return 0;
}
