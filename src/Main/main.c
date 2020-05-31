#include"../macro_libglob.h"
#include"../Analizer/CheckInput/inputcheck.h"

#define AZIONI 3
#define AZIONIMENUANAL 9
#define NUMAZIONIPOSSIBILI 6
#define NPATHANAL 8
#define PATHANAL "./TestArea/anal"



char *getIn(){
	int i = 1;
	char *ret = malloc(i);
	char car_in = getc(stdin);
	ret[0] = '\0';
	while( car_in != '\n' ){
		i++;
		char tmp[i];
		strcpy(tmp,ret);
		tmp[ i - 2 ] = car_in;
		tmp[ i - 1 ] = '\0';
		free(ret);
		ret = malloc(i);
		strcpy(ret,tmp);
		car_in = getc(stdin);
  }
  return ret;
}


void printOptions(){
	int i=0;
	printf("\nAZIONI:\n");
	char *laz[AZIONI] = {"Analazer Menu'", "Reporter", "Lista Azioni"};
	for(i=0;i<AZIONI; i++){
		printf("%d. %s\n",i+1,laz[i]);
	}
	printf("q/quit/exit  EXIT\n\n");
}

void printOpAnal(){
	int i=0;
	char *lazAnal[AZIONIMENUANAL]={"Iniziare Analazer","Aggiungere file/s","Aggiungere cartella/e","Impostare ricorsione su cartelle", "Impostare m", "Impostare n","Eliminare file","Eliminare cartella","reset impostazioni"};
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
	for( i=0; i < NUMAZIONIPOSSIBILI; i++ ){
		if(execAnal[i] != NULL)
			free(execAnal[i]);
	}
	free(execAnal);
}

void presetAnal(int *n, int *m, char ***file, char ***dir, int *nfile, int *ndir, int *rec){
	printf("Sei sicuro di voler resettare la linea di dichiarazione di Analizer? S/n\n");
	char *risp=getIn();
	if(!(strcmp(risp,"S")&&strcmp(risp,"s"))){
		printf("Elimino tutti i dati salvati di dichiarazione, continuare? S/n\n");
		free(risp);
		risp=getIn();
		if(!(strcmp(risp,"S")&&strcmp(risp,"s"))){
			(*n)=3;(*m)=4;
			freeStringArray(*file,*nfile);
			freeStringArray(*dir,*ndir);
			(*nfile)=0;(*ndir)=0;
			(*rec)=0;
		}
	}
	free(risp);
}


void addtoArray(char ***array,int *ndata,char *add){
	int nadd=0;
	char *ptr = add;
	char **datisep;
	while( ptr != NULL ){
		while( strcspn(ptr," ") < 1 && strlen(ptr) > 1){
    	ptr++;
    }

  	if(strlen(ptr) > 1){
    	nadd++;
   		char **tmp = calloc( nadd, sizeof(char *) );
   		int lung = strcspn( ptr, " " );
      int i=0;
      for( i=0; i < nadd - 1; i++ ){
      	tmp[i] = datisep[i];
      }
      tmp[nadd - 1] = malloc(lung+1);
      strncpy(tmp[nadd - 1], ptr, lung);
      tmp[nadd - 1][lung] = '\0';
      if(nadd != 0){
      	freeStringArray(datisep,nadd - 1);
      }
      datisep = tmp;
      ptr = ptr + lung;
    }
    else{
    	ptr = NULL;
    }
	}
	if( nadd != 0 ){
		char **tmp = calloc( (*ndata) + nadd,sizeof(char *) );
		int i = 0;
		for( i = 0; i < (*ndata); i++ ){
			tmp[i] = malloc( strlen((*array)[i]) );
			sprintf( tmp[i], "%s", (*array)[i] );
		}
		i = 0;
		for(i=0; i < nadd; i++){
			tmp[i + (*ndata)] = datisep[i];
		}
		freeStringArray(*array,(*ndata));
		*array = tmp;
		(*ndata)++;
	}
}


void recurtion( int *rec ){
	if( (*rec) == 0 ){
		printf( "La ricorsione e' attiva\n" );
		(*rec) = 1;
	}
	else{
		printf( "La ricorsione e' disattivata\n" );
		(*rec) = 0;
	}
}

int	isNum(char *pnum){
	int ret = 0;
	if(strlen(pnum) > 0)
		if(strlen(pnum) == strspn(pnum,"0123456789")){
			ret = 1;
	}
	return ret;
}


void setmN( int *num, char selez ){
	int exit = 0;
	while( exit < 1 ){
		printf("Scrivi un numero per %c\n",selez);
		char *cnum = getIn();
		if(isNum(cnum)){
			(*num) = atoi(cnum);
			exit = 1;
		}
		else{
			printf("La stringa digitata non e' un numero:\n");
			printf("Scrivere un numero senza spazi o altri caratteri\n");
			exit = 0;
		}
	}
}

void exitAnal(){
	printf("TODO exitAnal?\n");
}

int cifre(int num){
	int ret = 1;
	while( num/10 != 0 ){
		ret++;
		num = num/10;
	}
	return ret;
}

char **createExec(int n,int m,char **file,char **dir,int nfile,int ndir,int rec){
	//path n m nfile ndir r NULL
	int lung = 1 + 2 + 2 + nfile + ndir + 1 + 1;
	char **ret = calloc(lung, sizeof(char *));
	int i = 0;
	for(i=0; i < lung; i++){
		ret[i] = NULL;
	}
	//
	ret[0] = PATHANAL;
	//N
	ret[1] = malloc(4);
	sprintf(ret[1],"-n ");
	ret[2] = malloc(cifre(n)+1);
	sprintf(ret[2],"%d",n);

	//M
	ret[3] = malloc(4);
	sprintf(ret[3], "-m ");
	ret[4] = malloc(cifre(m)+1);
	sprintf(ret[4], "%d", m);
	//FILE
	i = 0;
	for(i=0; i < nfile; i++){
		ret[i + 5] = malloc(strlen(file[i]));
		sprintf(ret[i + 5], "%s",file[i]);
	}
	//DIR
	i = 0;
	for(i=0; i < ndir; i++){
		ret[i + nfile + 5] = malloc(strlen(dir[i]));
		sprintf(ret[i + nfile + 5], "%s",dir[i]);
	}
	//RECU
	if(rec == 1){
		ret[lung-2] = malloc(4);
		sprintf(ret[lung -2],"-r ");
	}
	return ret;
}

void eseguiAnal(char **execAnal,int lung){
	int f = fork();
	while( f < 0 ){
		f = fork();
	}
	if( f == 0 ){
		execv(execAnal[0], execAnal);
	}
	else {
		//DEBUG
		printf("Ricordati il freeStringArray\n");
		//freeStringArray(execAnal,lung-1);
	}
}

void elimSelec(char ***file,int *nfile, char *filedir){
	int exit = 0;
	while(exit < 1){
		printf("Scrivi il nome di un%s\n",filedir);
		char *nome = getIn();
		int i=0;
		int trovato = 0;
		//Cerco il nome dato
		for( i=0; i < (*nfile) && trovato == 0; i++ ){
			if(!strcmp(nome,(*file)[i])){
				trovato = 1;
			}
		}

		if(trovato == 1){
			//Caso in cui ho trovato il nome dato
			char **tmp = calloc( (*nfile) - 1, sizeof(char *) );
			//mi salvo la posizione del file da eliminare
			int floc = i-1;
			i = 0;
			//copio la prima parte
			for(i = 0; i < floc; i++){
				tmp[i] = (*file)[i];
			}
			//Elimino la locazione di memoria
			free((*file)[floc]);
			//Copio la seconda parte
			i = floc + 1;
			for(i = floc + 1; i < (*nfile); i++){
				tmp[i-1] = (*file)[i];
			}
			//Copio nel file
			free(*file);
			(*nfile)--;
			*file = tmp;
			printf( "Elimitato \"%s\"\n", nome );
			printf("Eliminare altro? S/n");
		}
		else{
			//Caso in cui non ho trovato il nome
			printf( "Non ho trovato nessun%s con il nome \"%s\".\n", filedir, nome );
			printf( "Riprovare? S/n\n" );
		}
		//Richiesta di ricominciare
		char *risp = getIn();
		if( !(strcmp(risp,"S")&&strcmp(risp,"s")) )
			exit = 0;
		else exit = 1;
		free(risp);
		free(nome);
		}
}

//Menu di anal
void enterAnalMenu(int *n,int *m,char ***file,char ***dir,int *nfile,int *ndir,int *rec){
	//Iniz. di dir e file nel caso in cui non sono stati allocati
	if( *nfile < 1 ){
		*file = malloc(1);
	}
	if(*ndir<1){
		*dir = malloc(1);
	}
	int i=0, option = 1;
	char *aggiunta, **execAnal;;
	int lung;
	while(option >= 0){
		//La lungezza di execAnal
		//DEBUG quando faccio il freeStringArray su execAnal mi dice
		//lunghezza di free() errata
		lung=1 + 2 + 2 + (*nfile) + (*ndir) + 2;
		printOpAnal();

		char *input = getIn();
		//Controllo se si vuole tornare al menu' principale
		if( !(strcmp(input,"q") && strcmp(input,"b") && strcmp(input,"back")) ){
			option = -1;
		}
		//Controllo se si vuole fare una stampa di execAnal
		else if( !(strcmp(input, "v") && strcmp(input,"V")) ){
			option = 69;
		}
		else option = atoi(input);
		free(input);
		//Opzioni
		switch(option) {
			case 1:
				//creo l'exec e faccio partire l'analizer
				printf("Faccio partire Analizer\n");
				execAnal = createExec(*n,*m,*file,*dir,*nfile,*ndir,*rec);
				eseguiAnal(execAnal,lung);
				break;
			case 2:
				//Add File
				printf( "Digitare uno o piu' file\n" );
				aggiunta = getIn();
				addtoArray(file,nfile,aggiunta);
				free(aggiunta);
				break;
			case 3:
				//Add dir
				printf( "Digirare uno o piu' cartelle" );
				aggiunta = getIn();
				addtoArray(dir,ndir,aggiunta);
				free(aggiunta);
				break;
			case 4:
				//Accendo e spengo la ricorsione
				recurtion(rec);
				break;
			case 5:
				//set M
				setmN(m,'m');
				break;
			case 6:
				//set N
				setmN(n,'n');
				break;
			case 7:
				//Elimina selettivamente file
				elimSelec(file, nfile, " file");
				break;
			case 8:
				elimSelec(dir, ndir, "a cartella");
				//Elimina selettivamente dir
				break;
			case 9:
				//Reset Anal
				presetAnal(n, m, file, dir, nfile, ndir, rec);
				break;

			case 69:
				//Visualizza linea di comando
				execAnal = createExec(*n, *m, *file, *dir, *nfile, *ndir, *rec);
				for( i = 0; i < lung; i++ ){
					if( execAnal[i] != NULL )
						printf("%s ",execAnal[i]);
				}
				printf("\n");
				//DEBUG
				printf("Ricordati il freeStringArray\n");
				//freeStringArray(execAnal,lung);
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
	//Nel caso non ci siano piu' files o dir
	if(*nfile<1){
		free(*file);
	}
	if(*ndir<1){
		free(*dir);
	}
}

//Faccio partire il reporter
void startReporter(){
	printf("Faccio partire il reporter\n");
	int f = fork();
	while( f < 0 )
		f=fork();
	if( f == 0 ){
		char *questo = "./TestArea/report";
		execv(questo,&questo);
	}
	int status;
	wait(&status);
}

void ending(){
	//TODO: Uccidere gli zo2bie rimanenti
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
 *
 {
 * CREARE una pipe fra M e A
 * Controllare pipe per nuovi file/cartelle bloccante
 * No discriminazione fra cartelle e file
 * Elimina i file dopo aver ricevuto i dati da pipe
 * -p due pipe  Mscrive Mlegge Ascrive Alegge
 }
 *
 */




int main( int argv, char *argc[] ){
	int f = fork();
	while ( f < 0 ) {
		f = fork();
	}
	if( f == 0 ){
		argc[0] = PATHANAL;
		f = execv(argc[0],argc);
		if( f < 0 ){
			exit(-1);
		}
	}
	char **input,**file,**dir;

	int n=3,m=4,rec=0,nfile=0,ndir=0,ninput=0;
	//Leggo gli args, tutto di Giaco
	if(argv>1){
		readInput(argv,argc,&input,&ninput,&n,&m,&rec);
		validateInput(input,ninput,&file,&dir,&nfile,&ndir);
	}
	printf("Grazie per aver scelto il programma di analisi dati di G.E.F.F. & co.\n\n");
	sleep(1);
	printf( "Con che azione volete cominciare?\n" );
	printOptions();

	int option;
	//Menu principale
	while( option >= 0 ){
		char *input = getInputorExit();
		option = atoi(input);
		free(input);
		printf("\n");
		switch(option){
			case 1:
				//Apri il menu di anal
				enterAnalMenu(&n,&m,&file,&dir,&nfile,&ndir,&rec);
				printf( "Siete nel menu' principale.\n" );
				break;

			case 2:
				//Fai partire il reporter
				startReporter();
				printf( "Siete nel menu' principale.\n" );
				break;

			case 3:
				//Stampa le azioni
				printf( "Le azionie sono:\n" );
				break;

			default:
				//Input sbagliato
				printf( "L'opzione inserita non e' valida\n\n" );
				printf( "Prego digitare il numero di un azione in elenco:\n\n" );
				option=0;
		}
		printOptions();
	}
	//Libero i due array
	freeStringArray(dir,ndir);
	freeStringArray(file,nfile);
	return 0;
}
