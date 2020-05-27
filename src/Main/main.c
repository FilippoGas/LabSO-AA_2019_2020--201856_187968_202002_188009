#include <errno.h>
#include <fcntl.h>
#include <math.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>


#define AZIONI 3
#define AZIONIMENUANAL 7
#define NUMAZIONIPOSSIBILI 8
#define NPATHANAL 8
#define PATHANAL "./a.out"



char *getIn(){
	int i = 1;
	char *ret = malloc(1);
	char car_in = getc(stdin);
	ret[0] = '\0';
	while( car_in != '\n' ){
		i++;
		char tmp[i];
		strcpy(tmp,ret);
		tmp[i-2]=car_in;
		tmp[i-1]='\0';
		free(ret);
		ret = malloc(i);
		strcpy(ret,tmp);
		car_in=getc(stdin);
  }
  return ret;
}


void printOptions(){
	int i=0;
	printf("\nAZIONI:\n");
	char *laz[AZIONI]={"Analazer Menu'", "Reporter", "Lista Azioni"};
	for(i=0;i<AZIONI; i++){
		printf("%d. %s\n",i+1,laz[i]);
	}
	printf("q/quit/exit  EXIT\n\n");
}

void printOpAnal(){
	int i=0;
	char *lazAnal[AZIONIMENUANAL]={"Iniziare Analazer","Aggiungere file/s","Aggiungere cartella","Impostare ricorsione su cartelle", "Impostare m", "Impostare n","reset impostazioni"};
	printf("\nANALIZER:\n");
	printf("AZIONI:\n");
	for(i=0;i<AZIONIMENUANAL;i++){
		printf("%d. %s\n",i+1,lazAnal[i]);
	}
	printf("v/V visualizza linea di comando main attuale\n");
	printf("b/back/return tornare al Menu'\n");
}

void freeMem(char **execAnal){
	int i=0;
	for(i=0;i<NUMAZIONIPOSSIBILI;i++){
		if(execAnal[i]!=NULL)
			free(execAnal[i]);
	}
	free(execAnal);
}

void presetAnal( char **execAnal ){
	int i = 0;
	for(i = 0; i < NUMAZIONIPOSSIBILI;i++){
		if( execAnal[i] != NULL ){
			free(execAnal[i]);
		}
	}
	execAnal[0] = malloc( NPATHANAL );
	sprintf( execAnal[0], "%s", PATHANAL );
	i = 1;
	for( i = 1; i < NUMAZIONIPOSSIBILI; i++ ){
		execAnal[i] = malloc(2);
		strcpy(execAnal[i], " ");
	}
}

void addcarFile(char **strFiles, int cF){
	char *cartellaFile[2] = { "cartelle","file" };
	char *inizio[2]={ "-d ","   " };
	int loop=1;
	while(loop){
		printf( "Digirare il nome di uno o piu' %s:\n", cartellaFile[cF] );
		char *nomefile = getIn();
		if( !strcmp(*strFiles," ") ){
			*strFiles = malloc( 3 + strlen(nomefile) );
			sprintf( *strFiles,"%s %s",inizio[cF],nomefile );
		}
		else{
			char *tmp=malloc( strlen(*strFiles) );
			sprintf(tmp,"%s",*strFiles);
			*strFiles = realloc( *strFiles, strlen(tmp) + strlen(nomefile) + 1 );
			sprintf( *strFiles, "%s %s",tmp,nomefile );
			free(tmp);
		}
		free(nomefile);
		char Ie[2]={'e','i'};
		printf( "Vuoi aggiungere altr%c %s? S/n\n",Ie[cF],cartellaFile[cF] );
		nomefile = getIn();
		if( !(strcmp( nomefile, "S" ) && strcmp( nomefile, "s" )) )
			loop = 1;
		else loop = 0;
		free(nomefile);
	}
}

void recurtion( char **strrecur ){
	if( !strcmp(*strrecur, " ") ){
		printf( "La ricorsione e' attiva\n" );
		*strrecur = malloc(3);
		sprintf( *strrecur,"-r" );
	}
	else{
		printf( "La ricorsione e' disattivata\n" );
		free( *strrecur );
		*strrecur = malloc(2);
		strcpy(*strrecur," ");
	}
}

void setm( char **strm ){
	//TODO Controllo se input e' numero
	printf( "Digitare il numero desiderato di m:\n" );
	char *numero = getIn();
	if( *strm != NULL ){
		free(*strm);
	}
	*strm = malloc( 3 + strlen(numero) );
	int num = atoi(numero);
	printf("-m %d",num);
	free(numero);
}

void setn(char **strn){
	//TODO controllo se input e' input
	printf("Digitare il numero desiderato di n:\n");
	char *numero=getIn();
	if( *strn != NULL ){
		free(*strn);
	}
	*strn = malloc( 3 + strlen(numero) );
	int num = atoi(numero);
	printf( "-n %d",num );
	free(numero);
}

void exitAnal(){
	printf("TODO exitAnal?\n");
}


void enterAnalMenu(char **execAnal){
	int i=0;
	if(execAnal[0] == NULL){
		presetAnal(execAnal);
	}
	int option=1;
	while(option>=0){

		printOpAnal();

		char *input=getIn();

		if( !(strcmp(input,"q") && strcmp(input,"b") && strcmp(input,"back")) ){
			option = -1;
		}
		else if( !(strcmp(input, "v") && strcmp(input,"V")) ){
			option = 8;
		}
		else option=atoi(input);

		free(input);
		switch(option) {
			case 1:
				printf("Faccio partire Analizer\n");
				execv(execAnal[0],execAnal);
				break;
			case 2:
				addcarFile(&execAnal[1],1);
				break;
			case 3:
				addcarFile(&execAnal[2],0);
				break;
			case 4:
				recurtion(&execAnal[3]);
				break;
			case 5:
				setm(&execAnal[4]);
				break;
			case 6:
				setn(&execAnal[5]);
				break;
			case 7:
				printf("Resetto Analizer\n");
				presetAnal(execAnal);
				break;
			case 8:
				for( i = 0; i < NUMAZIONIPOSSIBILI; i++ ){
					if(execAnal[i]!=NULL)
						printf("%s ",execAnal[i]);
				}
				printf("\n");
				break;
			case -1:
				exitAnal();
				break;
			default:
				printf("L'opzione inserita non e' valida\n\n");
				printf("Prego digitare il numero di un azione in elenco:\n\n");
				option=0;
		}
	}
}

void startReporter(){
	printf("Faccio partire il reporter\n");
	int f = fork();
	while( f < 0 )
		f=fork();
	if( f == 0 ){
		char *questo="./TestArea/report";
		execv(questo,&questo);
	}
	int status;
	wait(&status);
}

void ending(){
	//TODO: Uccidere gli zombie rimanenti
	printf("Grazie per aver utilizzato il programma di analisi.\n");
	printf("E ricoedatevi sempre:\n");
	printf("\x1b[33m\t\t Se volete qualita', il nostro nome e' GEFF!\n");
	exit(0);
}



char *getInputorExit(){
	char *ret = getIn();
	if( !(strcmp(ret,"q") && strcmp(ret,"quit") && strcmp(ret,"exit")) ){
		free(ret);
		ending();
	}
	return ret;
}

/*
 * CREARE una pipe fra M e A
 * ARGOMENTI MAIN COPIATI NELLA CHIAMATA DI ANAL
 * SUBITO ESEGUE Analizer
 * Selezione di file/cartelle da eliminare.
 * Controllare pipe per nuovi file/cartelle.
 */




int main(){
	printf("Grazie per aver scelto il programma di analisi dati di G.E.F.F. & co.\n\n");
	sleep(1);
	printf("Con che azione volete cominciare?\n");
	printOptions();
	char **memAnal = calloc( NUMAZIONIPOSSIBILI , sizeof(char *) );
	int option;
	while( option >= 0 ){
		char *input = getInputorExit();
		option = atoi(input);
		free(input);
		printf("\n");
		switch(option){
			case 1:
				enterAnalMenu(memAnal);
				printf( "Siete nel menu' principale.\n" );
				break;

			case 2:
				startReporter();
				printf("Siete nel menu' principale.\n");
				break;

			case 3:
				printf("Le azionie sono:\n");
				break;

			default:
				printf("L'opzione inserita non e' valida\n\n");
				printf("Prego digitare il numero di un azione in elenco:\n\n");
				option=0;
		}
		printOptions();
	}
	freeMem(memAnal);
	return 0;
}
