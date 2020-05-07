#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<string.h>
#include"plib.h"





int main(int argc, char *argv[]){
	if(argc<3){
		printf("?Errore di chiamata di P\n");
		return -1;
	}
	int nfiles=argc-2;
	int nQ=atoi(argv[1]);
	//pQ[nQ][2]Viene utilizzato per dire quando P puo' leggere attravarso la fifo e
	//P per comunicare quando Q puo' scrivere.
	int pQ[nQ][2];
	//Nomi delle varie fifo
	char *fifoQ[nQ];
	//Da definire
	createPipes(&fifoQ,&pQ,nQ);
	int i=0;
	int figli[nQ];
	while(i<nQ){
		createQ(&figli[i],fifoQ[i],i,argv,nfiles);
		//chiudo Q per debugging
		if(figli[i]==0){
			return 0;
		}
		i++;
	}


	//Lettura uscite Q
	//Controlla se tutte le Q hanno finito
	int allEnd=1;

	//I caratteri dei file in entrata
	int caratteri_in[nfiles][MAXASCII];
	int Q_End=0;
	i=0;
	//messaggio di entrata: /path/nome_file

	do{
		//Controllo degli ingressi, da definire
		/*
		char temp[1];
		close(pQ[i][WR]);
		read(pQ[i][RD], temp, 1);
		if(temp[0]!=QEND){
			//Almeno una Q non ha finito
			Q_End=1;
			if(temp[0]==QREADY){

				//Lettura dell'entrata di Q
				char *str_in=letturaQ(fifoQ[i]);
				lettura_str_in(&caratteri_in,str_in,nfiles);

				//Scrivo che la coda e' vuota
				close(pQ[i][RD]);
				temp[0]=PREADY;
				write(pQ[i][WR],temp,1);
				close(pQ[i][WR]);
			}
		}
		else close(pQ[i][RD]);


		i++;
		if(i>=nQ){
			i=0;
			if(Q_End==0)
				allEnd=0;
			Q_End=0;
		}*/
	}
	while(allEnd);
	return 0;
}
