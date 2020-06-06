#include"mainfunc.h"

#define NCHIAMATECOST 12


//PRIMARY FUNCIONTS
//Setta o togle l'opzione di ricorsione
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

//setta o M o N a seconda della selezione
void setmN( int *num, char selez, int pipe[2] ){
	int exit = 0;
	while( exit < 1 ){
		printf("Scrivi un numero per %c\n",selez);
		char *cnum = getIn();
		if(isNum(cnum)){
			(*num) = atoi(cnum);
			//DEBUG
			sms_change_mn(cnum,selez,pipe);
			//EDEBUG
			exit = 1;
		}
		else{
			printf("La stringa digitata non e' un numero:\n");
			printf("Scrivere un numero senza spazi o altri caratteri\n");
			exit = 0;
		}
	}
}

//Esce dal menu' di A
void exitAnal(){
}

//Crea la chiamata di A
char **createExec( int n, int m, char **vari, int nvari, int rec, int *elimin, int pipe_to_a[2], int pipe_from_a[2] ){
	//path n m nvari r -p NULL
	int lung = nvari + NCHIAMATECOST;
	char **ret = calloc(lung, sizeof(char *));
	int i=0;
	for(i=0; i < lung; i++){
		ret[i] = NULL;
	}
	//Aggiungi path_analizer

	ret[0] = ANAME;
	//N
	ret[1] = malloc(4);
	sprintf(ret[1],"-n");
	ret[2] = malloc(cifre(n)+1);
	sprintf(ret[2],"%d",n);

	//M
	ret[3] = malloc(4);
	sprintf(ret[3], "-m");
	ret[4] = malloc(cifre(m)+1);
	sprintf(ret[4], "%d", m);
	//FILE e CARTELLE
	i = 0;
	for( i=0; i < nvari; i++ ){
		if( elimin[i] == 0 ){
		ret[i + 5] = calloc(strlen(vari[i]) + 1, sizeof(char));
		sprintf(ret[i + 5], "%s",vari[i]);
		}
		else{
			ret[i + 5] = malloc(1);
			ret[i + 5][0] = '\0';
		}
	}
	i += 5;
	//RECU
	if(rec == 1){
		ret[i] = malloc(4 * sizeof(char));
		sprintf(ret[i],"-r");
		i++;
	}
	ret[i] = malloc(4 * sizeof(char));
	sprintf(ret[i],"-p");
	ret[i + 1] = intToChar( pipe_to_a[READ] );
	ret[i + 2] = intToChar( pipe_to_a[WRITE] );
	ret[i + 3] = intToChar( pipe_from_a[READ] );
	ret[i + 4] = intToChar( pipe_from_a[WRITE] );
	ret[i + 5] = NULL;

	return ret;
}

//Fa partire A dal menu' di A
void eseguiAnal( char **execAnal,int lung){
	int f = fork();
	while( f < 0 ){
		f = fork();
	}
	if( f == 0 ){
		execvp(execAnal[0], execAnal);

		fprintf( stderr, "Errore di esecuzione Analizer\n" );
		exit(-1);
	}
	else {
		//DEBUG
		printf( "Ricordati ilffreeStringArray\n" );
    int i=1;
    //for(i=1;i<lung;i++){
    //    free(execAnal[i]);
    //}
    //free(execAnal);
	}
}

//Elimina uno dei file dagli argomenti della chiamata di A
void elimSelec( char **vari, int nvari, int **elimin, int pipe[2] ){
	printf("Che file vuoi eliminare?\n");
	printf("Se si vuole tornare al menu' digitare q\n");
	printf("Digita un numero fra i seguenti:\n" );

	int i=0,j=1;
	for(i = 0;i < (nvari);i++){
		if((*elimin)[i]==0){
			printf("%d. %s\n",j,(vari)[i]);
			j++;
		}
	}
	sleep(1);
	int nnomi = j-1;
	char *cnum = getIn();
	if(isNum(cnum)&&atoi(cnum)>nnomi){
		free(cnum);
		cnum = malloc(3);
		sprintf(cnum,"NO");
	}
	while(!isNum(cnum)&&strcmp(cnum,"q")){
		printf("Mi dispiace ma il comando digitato non e' un numero,\n");
		printf("o e' un numero troppo alto.\n");
		printf("Digitare un numero fra i seguenti elencati:\n");
		i=0;j=1;
		for(i = 0; i < nvari;i++)
			if( (*elimin)[i] == 0 ){
				printf("%d. %s\n",j,vari[i]);
				j++;
			}
			free(cnum);
			cnum = getIn();
			if(isNum(cnum)&&atoi(cnum)>nnomi){
				free(cnum);
				cnum = malloc(3);
				sprintf(cnum,"NO");
			}
	}
	int num = atoi(cnum);
	i=0;j=0;
	for(i = 0; i < nvari && num != j; i++){
		if( (*elimin)[i] == 0 ){
			j++;
		}
		if(num == j){
			(*elimin)[i] = 1;
		}
	}
	free(cnum);
	//sms_rmfile((*vari)[i],pipe);
	i--;
	printf("Eliminto \"%s\"\n",vari[i]);
}

//Aggiunge ad un array un dato e aggiunge una casella a elimina
void addtoArray( char ***array, int *ndata, char *add, int **elimin ){
	char **tmp = calloc( (*ndata) + 1, sizeof(char *) );
	int i = 0;
	for( i = 0; i < (*ndata); i++ ){
		tmp[i] = (*array)[i];
	}
	tmp[*ndata]=add;
	free(*array);
	*array = tmp;
	(*ndata)++;
	int *newelimin=calloc( (*ndata), sizeof(int) );
	i=0;
	for( i=0; i < (*ndata) - 1; i++){
		newelimin[i]=(*elimin)[i];
	}
	free(*elimin);
	*elimin = newelimin;
}

//Aggiungo un file, con il proprio path, nella lista dei file
void addFile( char ***vari, int *nvari, int **elimin, int pipe[2] ){
	printf( "Digitare uno o piu' cartelle o file\n" );
	char *aggiunta = getIn();
	while(index(aggiunta,' ') != NULL){
		printf("Aggiungere solo un file alla volta, grazie.\n");
		free(aggiunta);
		aggiunta = getIn();
	}
	addtoArray(vari,nvari,aggiunta,elimin);
	//DEBUG
	printf("%s\n", (*vari)[(*nvari) - 1]);
	sms_addfile((*vari)[(*nvari)-1],pipe);
	//EDEBUG
}

//Menu di anal
void enterAnalMenu( int *n, int *m, char ***vari, int *nvari, int *rec, int **elimin, int pipe_to_a[2], int pipe_from_a[2] ){
	//Iniz. di dir e file nel caso in cui non sono stati allocati
	if( (*nvari) < 1 ){
		(*vari) = (char **)malloc(1 * sizeof(char **));
	}
	int i=0, option = 1;
	char *aggiunta, **execAnal;
	int lung;
	while(option >= 0){
		lung = (*nvari) + NCHIAMATECOST;
		printOpAnal();
		printf("HO STAMPATO IL MENU\n");
		char *input = getIn();
		//Controllo se si vuole tornare al menu' principale
		if( !(strcmp(input, "q") && strcmp(input, "b") && strcmp(input, "back")) ){
			option = -1;
		}
		//Controllo se si vuole fare una stampa di execAnal
		else if( !(strcmp(input, "v") && strcmp(input,"V")) ){
			option = 69;
		}
		else option = atoi(input);
		printf("Prima di liberare input\n");
		free(input);
		printf("Dopo aver liberato input\n");
		//Opzioni
		switch(option) {
			case 1:
				//creo l'exec e faccio partire l'analizer
				pipe2( pipe_to_a, __O_DIRECT | O_NONBLOCK );
        			pipe2( pipe_from_a, __O_DIRECT );
				execAnal = createExec( *n, *m, *vari, *nvari, *rec ,*elimin,pipe_to_a,pipe_from_a);
				eseguiAnal( execAnal, lung );
        			close( pipe_to_a[READ] );
        			close( pipe_from_a[WRITE] );
				if((*vari) != NULL)
					freeStringArray(*vari, *nvari);
				if((*elimin) != NULL)
					free(*elimin);
				(*nvari) = 0;

        			leggo_input_pipe(vari,nvari,elimin,pipe_from_a, pipe_to_a);
				close(pipe_to_a[READ]);
				break;
			case 2:
				//Add dir o file
				addFile(vari,nvari,elimin,pipe_to_a);
				break;
			case 3:
				//Accendo e spengo la ricorsione
				recurtion(rec);
				break;
			case 4:
				//set M
				setmN(m,'m',pipe_to_a);
				break;
			case 5:
				//set N
				setmN(n,'n',pipe_to_a);
				break;
			case 6:
			//Elimina selettivamente i file
				elimSelec( *vari, *nvari, elimin, pipe_to_a );
				break;
			case 7:
				//Reset Anal
				presetAnal( n, m, vari, nvari, rec, elimin );
				break;

			case 69:
				//Visualizza linea di comando
				execAnal = createExec(*n, *m, *vari, *nvari, *rec, *elimin, pipe_to_a, pipe_from_a);
				for( i = 0; i < lung; i++ ){
					if( execAnal[i] != NULL )
						printf( "%s ", execAnal[i] );
				}
				printf("\n");
			  	for(i=1;i<lung;i++){
          				free(execAnal[i]);
        			}
        			free(execAnal);
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
		char *questo[] = {RNAME, NULL};
		execvp(questo[0], questo);
		perror("");
		exit(-1);
	}
	int status;
	waitpid(f, &status, 000);
}

//Chiudo il programma
void ending(){
	//TODO: Uccidere gli zombie rimanenti
	printf("Grazie per aver utilizzato il programma di analisi.\n");
	printf("E ricoedatevi sempre:\n");
	printf("\x1b[33m\t\t Se volete qualita', il nostro nome e' GEFF!\033[0m\n");
	exit(0);
}

//prendo un input o, se "q", esco
char *getInputorExit(){
	char *ret = getIn();
	if( !(strcmp(ret,"q") && strcmp(ret,"quit") && strcmp(ret,"exit")) ){
		free(ret);
		ending();
	}
	return ret;
}

//Leggo i path dei file che mi vengono da A
void leggo_input_pipe( char ***input, int *ninput, int **elimin, int pipe_from_a[2], int pipe_to_a[2]){
	char message[PIPE_BUF + 1];
	read( pipe_from_a[READ], message, PIPE_BUF );
	(*ninput) = atoi(message);
	(*input)=calloc( (*ninput), sizeof(char *) );
	int i=0;
	for(i=0; i < (*ninput); i++ ){
		char message1[PIPE_BUF + 1] = "";
		read( pipe_from_a[READ], message1, PIPE_BUF );
		printf("%s\n", message1);
		(*input)[i] = calloc( strlen(message1) + 1, sizeof(char) );
		sprintf( (*input)[i], "%s", message1);
	}
	write(pipe_to_a[WRITE], "1", 1);
	*elimin = calloc( *ninput, sizeof(int) );
}

//Faccio partire A per la prima volta
void firstStartAnal( char *argv[], int argc, int pipe_to_a[2], int pipe_from_a[2], char ***input,int *ninput, int **elimin ){
	pipe2(pipe_to_a,__O_DIRECT | O_NONBLOCK);
	pipe2(pipe_from_a,__O_DIRECT);							//Controlla

	//dichiarazione
	int lung=argc+7;
	char *dich[lung];
	dich[0] = ANAME;
	int i = 1;
	for( i = 1; i < argc; i++ ){
		dich[i] = argv[i];
	}
	int first_dim = i;
	dich[i] = malloc(3 * sizeof(char));
	sprintf(dich[i],"-p");
	dich[i + 1] = intToChar( pipe_to_a[READ] );
	dich[i + 2] = intToChar( pipe_to_a[WRITE] );
	dich[i + 3] = intToChar( pipe_from_a[READ] );
	dich[i + 4] = intToChar( pipe_from_a[WRITE] );
	dich[i + 5] = NULL;
	eseguiAnal(dich,lung);
	close(pipe_to_a[READ]);
	close(pipe_from_a[WRITE]);
	for(; first_dim > i + 6; i++ ){
		free(dich[first_dim]);
	}
	leggo_input_pipe(input,ninput,elimin,pipe_from_a, pipe_to_a);
}



//UTIL FUNCIONTS
//Prendi un input
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

//conta le cifre di un numero naturale
int cifre( int num ){
	int ret = 1;
	while( num/10 != 0 ){
		ret++;
		num = num/10;
	}
	return ret;
}
//converte int in un char *
char *intToChar( int num ){
	char *ret = calloc( cifre(num)+1, sizeof(char) );
	sprintf(ret,"%d",num);
	return ret;
}

//Guarda se una stringa contiene SOLO cifre
int	isNum( char *pnum ){
	int ret = 0;
	if(pnum != NULL)
	if(strlen(pnum) > 0)
		if(strlen(pnum) == strspn(pnum,"0123456789")){
			ret = 1;
	}
	return ret;
}

//Copia il contenuto di array2 in arrey1 riallocandolo (allargandolo)
void cpArray( char ***array1, int *narray1, char **array2, int narray2 ){
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

//Fa il print delle Opzioni nel menu' principale
void printOptions(){
	int i=0;
	printf("\nAZIONI:\n");
	char *laz[AZIONI] = {"Analazer Menu'", "Reporter", "Lista Azioni"};
	for(i=0;i<AZIONI; i++){
		printf("%d. %s\n",i+1,laz[i]);
	}
	printf("q/quit/exit  EXIT\n\n");
}

//Fa il print delle Opzioni nel menu' di Analize
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

//Resetta la chiamata di Anal
void presetAnal( int *n, int *m, char ***vari, int *nvari, int *rec, int **elimin ){
	printf("Sei sicuro di voler resettare la linea di dichiarazione di Analizer? S/n\n");
	char *risp=getIn();
	if(!(strcmp(risp,"S")&&strcmp(risp,"s"))){
		printf("Elimino tutti i dati salvati di dichiarazione, continuare? S/n\n");
		free(risp);
		risp=getIn();
		if(!(strcmp(risp,"S") && strcmp(risp,"s"))){
			(*n)=3;(*m)=4;
			if((*vari) != NULL){
				freeStringArray(*vari,*nvari);
				(*vari) = malloc(1);
			}
			(*nvari) = 0;
			(*rec) = 0;
			if((*elimin) != NULL){
				free(*elimin);
				*elimin = malloc(1);
			}
		}
	}
	free(risp);
}

void freeStringArray(char **stringarray, int n){
	int i = 0;
	while(i < n){
		if(stringarray[i] != NULL)
			free(stringarray[i]);
		i++;
	}
	free(stringarray);
}
