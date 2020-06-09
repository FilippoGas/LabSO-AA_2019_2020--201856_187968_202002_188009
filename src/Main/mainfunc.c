#include"mainfunc.h"

#define NCHIAMATECOST 12


//PRIMARY FUNCIONTS
//Set or remove the recurtion option
void recurtion( int *rec ){
	if( (*rec) == 0 ){
		printf( "The recursion is on.\n" );
		(*rec) = 1;
	}
	else{
		printf( "The recursion is off.\n" );
		(*rec) = 0;
	}
}

//set M or N depending to the selection
void setmN( int *num, char selez, int pipe[2],int analpid){
	int exit = 0;
	while( exit < 1 ){
		printf("Type a number for %c\n",selez);
		char *cnum = getIn();
		if(isNum(cnum)&&atoi(cnum)>0){
			(*num) = atoi(cnum);
			sms_change_mn(cnum,selez,pipe);
			exit = 1;
		}
		else{
			printf("The string typed is't a number\n" );
			printf("Write a number different form 0m without spaces and other characters\n");
			printf("Scrivere un numero diverso da zero, senza spazi e altri caratteri\n");
			exit = 0;
		}
	}
}

//Exit from menu' of A
void exitAnal(){
}

//Create the call of A
char **createExec( int n, int m, char **vari, int nvari, int rec, int *elimin, int pipe_to_a[2], int pipe_from_a[2] ){
	//path n m nvari r -p NULL
	int lung = nvari + NCHIAMATECOST;
	char **ret = calloc(lung, sizeof(char *));
	int i=0;
	for(i=0; i < lung; i++){
		ret[i] = NULL;
	}

	//Add path_analizer
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

	//FILE and DIRS
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

//Start analizer form the menu'
int eseguiAnal( char **execAnal,int lung){
	int f = fork();
	while( f < 0 ){
		f = fork();
	}
	if( f == 0 ){
		execvp(execAnal[0], execAnal);

		fprintf( stderr, "Errore di esecuzione Analizer\n" );
		exit(-1);
	}
	return f;
}

//Return the numer of files or dirs not remuved
int printlist(char **vari, int nvari, int *elimin){
	int i=0,j=0;
	for( i = 0; i < nvari; i++ ){
		if( elimin[i] == 0 ){
			printf("%d. %s\n",j+1,(vari)[i]);
			j++;
		}
	}
	return j;
}

//Remove one of the argument of the call A
void elimSelec(char **vari, int nvari, int *elimin, int pipe[2], int analpid){
	if(nvari > 0){
		int nnomi = printlist(vari, nvari, elimin );
		if( nnomi > 0 ){
			printf("Which file do you want to remove? Che file vuoi eliminare?\n");
			printf("If you want to return to analizer menu' type q .\n");
			printf("Type one of the previous numbers.\n" );
			char *cnum = getIn();
			if( isNum(cnum) && atoi(cnum) > nnomi && atoi(cnum) < 1){
				free(cnum);
				cnum = calloc( 3, sizeof(char) );
				sprintf(cnum,"NO");
			}
			while( !isNum(cnum) && strcmp(cnum,"q")){
				printf("Sorry but the typed command isn't a number or is to high.\n\n");
				printf("Type one of the following numbers:\n");
				printlist(vari,nvari,elimin);

				free(cnum);
				cnum = getIn();
				if(isNum(cnum) && atoi(cnum) > nnomi && atoi(cnum) < 1){
					free(cnum);
					cnum = calloc( 3, sizeof(char) );
					sprintf( cnum, "NO" );
				}
			}
			if( strcmp( cnum, "q") ){
				int num = atoi(cnum);
				int i=0,j=0;
				for(i = 0; i < nvari && num != j; i++){
					if( elimin[i] == 0 ){
						j++;
					}
					if( num == j ){
						elimin[i] = 1;
					}
				}
				i--;
				sms_rmfile(vari[i],pipe);
				printf("Removed \"%s\"\n",vari[i]);
			}
			free(cnum);
		}
		else{
			printf("There is no file to remove\n");
		}
	}
	else{
		printf("There is no file to remove\n");
	}
}

//Add a file or dir in an array and add a box in a elimin
void addtoArray( char ***array, int *ndata, char *add, int **elimin ){
	char **tmp = calloc( (*ndata) + 1, sizeof(char *) );
	int i = 0;
	for( i = 0; i < (*ndata); i++ ){
		tmp[i] = (*array)[i];
	}
	tmp[*ndata] = add;
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

//Add a file to the list with his path
void addFile( char ***vari, int *nvari, int **elimin, int pipe[2], int analpid ){
	//DEBUG
	printf("Type one or more dirs or files\n" );
	printf("To undo don't write nothing\n");
	char *aggiunta = getIn();
	char *puntat = aggiunta;
	char *ptr = index(aggiunta,' ');
		while( ptr != NULL ){
		int lung = strcspn(puntat," ");
		if( lung > 0 ){
			char *tmp = calloc( lung + 1, sizeof(char) );
			strncat( tmp, puntat, lung );
			addtoArray( vari, nvari, tmp, elimin );
			sms_addfile( (*vari)[(*nvari) - 1], pipe );
			puntat = ptr+1;
		}
		else{
			puntat ++;
		}
		ptr = index(puntat,' ');
	}
	if( strlen(puntat) > 0 ){
		int lung = strcspn(puntat," ");
		char *tmp=malloc(lung+1);
		strcpy(tmp,puntat);
		addtoArray(vari,nvari,tmp,elimin);
		sms_addfile( (*vari)[(*nvari) - 1], pipe );
	}
	free(aggiunta);
}


//Start the analizer if there is no analizer already started
void startAnal(int *n, int *m, char ***vari, int *nvari, int *rec , int **elimin, int pipe_to_a[2],int pipe_from_a[2],int *analpid){
	int status;
	int test = waitpid(*analpid, &status, WNOHANG);
	if(test != 0){
		int lung = (*nvari) + NCHIAMATECOST;
		pipe2( pipe_to_a, __O_DIRECT | O_NONBLOCK );
		pipe2( pipe_from_a, __O_DIRECT );
		char **execAnal = createExec( *n, *m, *vari, *nvari, *rec ,*elimin,pipe_to_a,pipe_from_a);
		(*analpid) = eseguiAnal( execAnal, lung );

		free(execAnal);
		close( pipe_to_a[READ] );
		close( pipe_from_a[WRITE] );
		if((*vari) != NULL)
			freeStringArray(*vari, *nvari);
		if((*elimin) != NULL)
			free(*elimin);
		(*nvari) = 0;

		leggo_input_pipe(vari, nvari, elimin, pipe_from_a, pipe_to_a);
		close(pipe_to_a[READ]);
	}
	else{
		printf("The analizer is still in execution, wait until it's done.\n" );
	}
}


//Menu' of analizer
void enterAnalMenu( int *n, int *m, char ***vari, int *nvari, int *rec, int **elimin, int pipe_to_a[2], int pipe_from_a[2], int *analpid ){
	//Initialize vari in the case it hasn't been allocated
	if( (*nvari) < 1 ){
		(*vari) = calloc(1 , sizeof(char **));
	}
	int i = 0, option = 1;
	char *aggiunta, **execAnal;
	int lung;
	while(option >= 0){
		lung = (*nvari) + NCHIAMATECOST;
		printOpAnal();
		char *input = getIn();
		//Controll if you want to return in the main menu'
		if( !(strcmp(input, "q") && strcmp(input, "b") && strcmp(input, "back")) ){
			option = -1;
		}
		//Controll if you want to do a print of execAnal
		else if( !(strcmp(input, "v") && strcmp(input, "V")) ){
			option = 69;
		}
		else option = atoi(input);
		free(input);
		//Options
		switch(option) {
			case 1:
				//Create the exec and try to start the analizer
				startAnal(n, m, vari, nvari, rec, elimin, pipe_to_a, pipe_from_a, analpid);
				break;
			case 2:
				//Add dir or file
				addFile( vari, nvari, elimin, pipe_to_a, *analpid );
				break;
			case 3:
				//Set or remove the recursion option
				recurtion(rec);
				break;
			case 4:
				//set M
				setmN(m,'m',pipe_to_a,*analpid);
				break;
			case 5:
				//set N
				setmN(n,'n',pipe_to_a,*analpid);
				break;
			case 6:
			//Elimina selettivamente i file
				elimSelec( *vari, *nvari, *elimin, pipe_to_a, *analpid);
				break;
			case 7:
				//Reset Analiler
				presetAnal( n, m, vari, nvari, rec, elimin );
				break;

			case 69:
				//Visualize the call line of analizer
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
				printf("The option entered is not valid\n\n" );
				printf("Write a number form an action in the list:\n\n");
				option=0;
		}
	}
	//In case there are no files or dirs
	if((*nvari) < 1){
		free(*vari);
	}
}

//Start the reporter
void startReporter(){
	printf("Starting the reporter\n");
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

//Close the programm
void ending(int analpid){
	int status;
	printf("Quitting...\n");
	waitpid(analpid,&status, 000);
	printf("\nThank you for using the analysis program\n" );
	printf("And always remember:\n");
	printf("\033[1m\033[33m\t\t If you want quality, my name is GEFF!\033[0m\n");

	exit(0);
}

//Get an input, if q then exit
char *getInputorExit(int analpid){
	char *ret = getIn();
	if( !(strcmp(ret,"q") && strcmp(ret,"quit") && strcmp(ret,"exit")) ){
		free(ret);
		ending(analpid);
	}
	return ret;
}

//Read files and path of files that come from A
void leggo_input_pipe( char ***input, int *ninput, int **elimin, int pipe_from_a[2], int pipe_to_a[2]){
	char message[PIPE_BUF + 1] = "";
	read( pipe_from_a[READ], message, PIPE_BUF );
	(*ninput) = atoi(message);
	(*input)=calloc( (*ninput), sizeof(char *) );
	int i=0;
	for(i=0; i < (*ninput); i++ ){
		char message1[PIPE_BUF + 1] = "";
		read( pipe_from_a[READ], message1, PIPE_BUF );
		(*input)[i] = calloc( strlen(message1) + 1, sizeof(char) );
		sprintf( (*input)[i], "%s", message1);
	}
	write(pipe_to_a[WRITE], "1", 1);
	*elimin = calloc( *ninput, sizeof(int) );
}


//Start analizer for the first time
int firstStartAnal( char *argv[], int argc, int pipe_to_a[2], int pipe_from_a[2], char ***input,int *ninput, int **elimin ){
	pipe2(pipe_to_a,__O_DIRECT | O_NONBLOCK);
	pipe2(pipe_from_a,__O_DIRECT);

	//Initialize
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
	int analpid = eseguiAnal(dich,lung);
	close(pipe_to_a[READ]);
	close(pipe_from_a[WRITE]);
	for(; first_dim > i + 6; i++ ){
		free(dich[first_dim]);
	}
	leggo_input_pipe(input,ninput,elimin,pipe_from_a, pipe_to_a);
	return analpid;
}



//UTIL FUNCIONTS

//Get an input
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

//Count the digits in a natural number
int cifre( int num ){
	int ret = 1;
	while( num/10 != 0 ){
		ret++;
		num = num/10;
	}
	return ret;
}
//Convert an int in a char * and alloc it
char *intToChar( int num ){
	char *ret = calloc( cifre(num)+1, sizeof(char) );
	sprintf(ret,"%d",num);
	return ret;
}

//If a string contains onty numbers, return true
int	isNum( char *pnum ){
	int ret = 0;
	if(pnum != NULL)
	if(strlen(pnum) > 0)
		if(strlen(pnum) == strspn(pnum,"0123456789")){
			ret = 1;
	}
	return ret;
}

//Copy the content of arrey2 in arrey1 by reallocating it
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

//Do the print of the options of the starting menu'
void printOptions(){
	int i=0;
	printf("\nACTIONS:\n");
	char *laz[AZIONI] = {"Analazer Menu'", "Reporter", "Acion List"};
	for( i = 0; i < AZIONI; i++ ){
		printf("%d. %s\n",i+1,laz[i]);
	}
	printf("q/quit/exit  EXIT\n\n");
}

//Do the print of the options of the Analizer menu'
void printOpAnal(){
	int i=0;
	char *lazAnal[AZIONIMENUANAL]={"Start Analazer","Add files or directories","Set recurtion on directories", "Set m", "Set n","Remove files or directories","reset settings"};
	printf("\nANALIZER:\n");
	printf("ACTIONS:\n");
	for( i=0; i < AZIONIMENUANAL; i++ ){
		printf("%d. %s\n",i+1,lazAnal[i]);
	}
	printf("v/V view the call line of analizer\n");
	printf("b/back/return return to Menu'\n");
}

//Reset the call of analizer
void presetAnal( int *n, int *m, char ***vari, int *nvari, int *rec, int **elimin ){
	printf("Are you sure tou want to reset the call line of analizer? Y/n");
	char *risp=getIn();
	if(!(strcmp(risp,"Y")&&strcmp(risp,"y"))){
		printf("Removing all the save data, continue?\n Y/n" );
		free(risp);
		risp=getIn();
		if(!(strcmp(risp,"Y") && strcmp(risp,"y"))){
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

//Free an arrey of strings
void freeStringArray(char **stringarray, int n){
	int i = 0;
	while(i < n){
		if(stringarray[i] != NULL)
			free(stringarray[i]);
		i++;
	}
	free(stringarray);
}
