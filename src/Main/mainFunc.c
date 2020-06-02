
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
	char *lazAnal[AZIONIMENUANAL]={"Iniziare Analazer","Aggiungere file o cartelle","Impostare ricorsione su cartelle", "Impostare m", "Impostare n","Eliminare file o cartelle","reset impostazioni"};
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

void presetAnal(int *n, int *m, char ***vari, int *nvari, int *rec){
	printf("Sei sicuro di voler resettare la linea di dichiarazione di Analizer? S/n\n");
	char *risp=getIn();
	if(!(strcmp(risp,"S")&&strcmp(risp,"s"))){
		printf("Elimino tutti i dati salvati di dichiarazione, continuare? S/n\n");
		free(risp);
		risp=getIn();
		if(!(strcmp(risp,"S")&&strcmp(risp,"s"))){
			(*n)=3;(*m)=4;
			freeStringArray(*vari,*nvari);
			(*vari) = 0;
			(*rec) = 0;
		}
	}
	free(risp);
}



void addtoArray(char ***array,int *ndata,char *add){
	//TODO: DEBUG

	int nadd=0;
	char *ptr = add;
	char **datisep;
	int exit = 0;
	while( ptr != NULL ){
		while( strcspn(ptr," ") < 1 && strlen(ptr) > 1 ){
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
      if(nadd > 1){
      	freeStringArray( datisep, nadd - 1 );
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

char **createExec(int n,int m,char **vari,int nvari,int rec){
	//path n m nvari r NULL
	int lung = 1 + 2 + 2 + nvari + 1 + 1;
	char **ret = calloc(lung, sizeof(char *));
	int i = 0;
	for(i=0; i < lung; i++){
		ret[i] = NULL;
	}
	//Aggiungi path_analizer
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
	//FILE e CARTELLE
	i = 0;
	for(i=0; i < nvari; i++){
		ret[i + 5] = malloc(strlen(vari[i]));
		sprintf(ret[i + 5], "%s",vari[i]);
	}
	//RECU
	if(rec == 1){
		ret[lung - 2] = malloc(4);
		sprintf(ret[lung - 2],"-r ");
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
		fprintf( stderr, "Errore di esecuzione Analizer\n" );
		exit(-1);
	}
	else {
		//DEBUG
		printf( "Ricordati il freeStringArray\n" );
		//freeStringArray(execAnal,lung-1);
	}
}

void elimSelec(char ***vari,int *nvari){
	int exit = 0;
	while(exit < 1){
		printf("Scrivi il nome di una cartella o file\n");
		char *nome = getIn();
		int i=0;
		int trovato = 0;
		//Cerco il nome dato
		for( i=0; i < (*nvari) && trovato == 0; i++ ){
			if(!strcmp(nome,(*vari)[i])){
				trovato = 1;
			}
		}

		if(trovato == 1){
			//Caso in cui ho trovato il nome dato
			char **tmp = calloc( (*nvari) - 1, sizeof(char *) );
			//mi salvo la posizione del file da eliminare
			int floc = i-1;
			i = 0;
			//copio la prima parte
			for(i = 0; i < floc; i++){
				tmp[i] = (*vari)[i];
			}
			//Elimino la locazione di memoria
			free((*vari)[floc]);
			//Copio la seconda parte
			i = floc + 1;
			for(i = floc + 1; i < (*nvari); i++){
				tmp[i-1] = (*vari)[i];
			}
			//Copio nel file
			free(*vari);
			(*nvari)--;
			*vari = tmp;
			printf( "Elimitato \"%s\"\n", nome );
			printf("Eliminare altro? S/n");
		}
		else{
			//Caso in cui non ho trovato il nome
			printf( "Non ho trovato nessun file o cartella con il nome \"%s\".\n", nome );
			printf( "Riprovare? S/n\n" );
		}
		//Richiesta di ricominciare
		char *risp = getIn();
		if( !(strcmp(risp,"S") && strcmp(risp,"s")) )
			exit = 0;
		else exit = 1;
		free(risp);
		free(nome);
		}
}

//Menu di anal
void enterAnalMenu(int *n, int *m, char ***vari, int *nvari, int *rec){
	//Iniz. di dir e file nel caso in cui non sono stati allocati
	if( (*nvari) < 1 ){
		*vari = malloc(1);
	}
	int i=0, option = 1;
	char *aggiunta, **execAnal;;
	int lung;
	while(option >= 0){
		//La lungezza di execAnal
		//DEBUG quando faccio il freeStringArray su execAnal mi dice
		//lunghezza di free() errata
		lung=1 + 2 + 2 + (*nvari) + 2;
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
				execAnal = createExec( *n, *m, *vari, *nvari, *rec );
				eseguiAnal( execAnal, lung );
				break;
			case 2:
				//Add dir o file
				printf( "Digirare uno o piu' cartelle ofile\n" );
				aggiunta = getIn();
				addtoArray(vari,nvari,aggiunta);
				free(aggiunta);
				break;
			case 3:
				//Accendo e spengo la ricorsione
				recurtion(rec);
				break;
			case 4:
				//set M
				setmN(m,'m');
				break;
			case 5:
				//set N
				setmN(n,'n');
				break;
			case 6:
				elimSelec(vari, nvari);
				//Elimina selettivamente vari
				break;
			case 7:
				//Reset Anal
				presetAnal( n, m, vari, nvari, rec );
				break;

			case 69:
				//Visualizza linea di comando
				execAnal = createExec(*n, *m, *vari, *nvari, *rec);
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
	if((*nvari) < 1){
		free(*vari);
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


void cpArray(char ***array1, int *narray1, char **array2, int narray2){
	char *tmp[(*narray1)];
	if( (*narray1) > 1 ){
		int i=0;
		for( i=0; i < (*narray1); i++ ){
			tmp[i] = (*array1)[i];
		}
		free( (*array1) );
	}
	(*array1) = calloc( (*narray1) + narray2, sizeof(char *) );
	int i = 0;
	for(i = 0; i < (*narray1); i++ ){
		(*array1)[i]=tmp[i];
	}
	i = 0;
	for( i = 0; i < narray2; i++ ){
		(*array1)[i+(*narray1)] = array2[i];
	}
	(*narray1) = *narray1 + narray2;
}

char *intToChar(int num){
	char *ret = calloc( cifre(num)+1, sizeof(char) );
	sprintf(ret,"%d",num);
	return ret;
}
void firstStartAnal(char *argv[],int argc, int **pipe_to_a, int **pipe_form_a, char ***input,int *ninput){
	pipe2(*pipe_to_a,__O_DIRECT | __O_NONBLOCK);
	pipe2(*pipe_form_a,__O_DIRECT);							//Controlla

	//dichiarazione
	int lung=argc+6;
	char *dich[lung];
	dich[0] = PATHANAL;
	int i = 1;
	for( i = 1; i < argc; i++ ){
		dich[i] = argv[i];
	}
	dich[lung - 5] = intToChar(pipe_to_a[0]);
	dich[lung - 4] = intToChar(pipe_to_a[1]);
	dich[lung - 3] = intToChar(pipe_form_a[0]);
	dich[lung - 2] = intToChar(pipe_form_a[1]);
	dich[lung - 1] = NULL;
	eseguiAnal(dich,lung);
	i=5;
	for( i = 5; i > 0; i-- ){
		free(dich[lung - i]);
	}
	close(pipe_form_a[WRITE]);
	char *message;
	read(pipe_form_a,message,PIPE_BUF);
	(*ninput) = atoi(message);
	(*input)=calloc( (*ninput), sizeof(char *) );
	for(i=0; i < (*ninput); i++ ){
		read(pipe_from_a, message, PIPE_BUFF);
		(*input)[i] = calloc( strlen(message), sizeof(char) );
		sprintf((*input)[i], "%s", message);
	}
}
