#include"plib.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>


#define RD 0
#define WR 1
#define PREADY '0'
#define QREADY '1'
#define QEND '2'
#define VARMOM 42

#define MAXASCII 256

void aggiungo_NULL(char **vet1, char **vet2, int n){
	int i=0;
	while(i<n){
	vet1[i]=vet2[i];
	}
	vet1[n+1]=NULL;
}

//conto le cofre di un numero intero
int cifre_int(int n){
	int i=0;
	if(i!=0){
		while(n/10!=0)
		i++;
		return i;
		}
	else return 1;
}



//Creo le pipes da definire
void createPipes(char ***fifoQ, char ***pQ,int nQ){
/*	int i=0;
	while(i<nQ){
		pipe(pQ[i]);
		printf( "Ho creato una pipe\n" );
		int n_char_path=cifre_int(getpid())+cifre_int(i)+8;
		*(fifoQ[i])=malloc(n_char_path);
		sprintf( *(fifoQ[i]), "/tmp/Q%d_%i", getpid(), i);
		printf( "Ho nominato una fifo\n" );
		mkfifo(*fifoQ[i], 0666);
		printf("ho creato la fifoQ[%i] = %s\n",i,*fifoQ[i]);
		i++;
	}*/

}

//Converto int in char
void convert_char(int num,char *ret){
	int i=cifre_int(num);
	int cnum=i+1;
	while(num!=0){
		ret[i]=(num%10) + '0';
		num=num/10;
		i--;
	}
	ret[cnum]='\0';
	return ret;
}




//Creo le Q
void createQ(int *figlio, char* fifoQ,int parteQ,char *nomefiles[],int nfile){

	(*figlio) = fork();
	while((*figlio) < 0){

		(*figlio) = fork();

	}
	if((*figlio)==0){
		//Questo printf sara' da sostituire a una chiamata exec di Q
		//a cui dovro' mandare i, pQ[i] e fifoQ[i]
		int i=getpid();
		char nomefilesNULL[nfile+3];
		aggiungo_NULL(nomefilesNULL,nomefiles,nfile+2);
		//DA DEFINIRE:
		//-Percorso dell'eseguibile Q
		//-

		//DEFINITO:
//Dichiarazione di Q:
//./path/Q parteQ nQ nome_file1 nome_file2 nome_file3 ...
//NOTA: argv[] di P e' lo stesso del **nomefile quindi basta cambiare 
		/*
		char *pathQ="./path/Q";
		char char_parteQ[cifre_int(parteQ)+1];
		convert_char(parteQ,char_parteQ);
		nomefilesNULL[1]=char_parteQ;
		numefilesNULL[0]=pathQ;
		while(test==-1){
			test=execvp(nomefilesNULL[0],nomefilesNULL);
		}
		*/
		printf("Io sono la Q%d\n",getpid());
		exit(0);
	}
}


//Sommo due matrici
void sommatoria(int ***mat1, int **mat2, int n){
	int i=0,j=0;
	for(i=0;i<n;i++)
		for(j=0;j<MAXASCII;j++)
			*mat1[i][j]=*mat1[i][j]+mat2[i][j];
}


//Vado a leggere il primo numero della stringa in entrata,
int lettura_numero(char *str_in){
	char *temp = strchr(str_in,' ');

	if(( (long) temp ) == 0){
		return atoi(str_in);
	}

	int ntemp = (int)(temp - str_in);
	char numero[ntemp];

	strncat(numero, str_in, ntemp);
	str_in=temp+1;
	return atoi(numero);
}


//
void lettura_str_in(int ***cose, char *str_in,int nfile){
	//Suddivido str_in nei vari input scritti
	char *pointer = strchr(str_in,'\n');
	char **char_dati;
	(char_dati[0]) = str_in;
	int i=0;
	while((long) pointer != 0){
		*pointer = '\0';
		i++;
		if(strchr(pointer,'\n') != 0){
			char_dati[i]=(pointer+1);
		}
		pointer=strchr(pointer, '\n');
	}
	int ndati=i;
	int j=0;
	    i=0;
	//Inizializzo ret
	int **ret;
	for(i=0;i<nfile;i++)
		for(j=0;j<MAXASCII;j++)
			ret[i][j]=0;

	i=0;
	while(i<ndati){
		//Il primo dato dell'input della Q e' sempre
		//il numero del file
		int n_lettura_file=lettura_numero(char_dati[i]);
		j=0;
		while(j<MAXASCII){
			ret[n_lettura_file][j]=lettura_numero(char_dati[i]);
			j++;
		}
	}
	sommatoria(cose,ret,nfile);
}


//Leggo l'ingresso di fifoQ
char *letturaQ(char *fifoQ){
	int fd = open(fifoQ, O_RDONLY);
	int len=lseek(fd, NULL, SEEK_END);
	char *str_in;
	read(fd,str_in,len);
	close(fd);
	/*fd=open(fifoQ,O_WRONLY);
	write(fd,"0",1);*/
	return str_in;
}





