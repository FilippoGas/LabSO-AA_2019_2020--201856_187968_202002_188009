#include "./mainfunc.h"


int main( int argc, char *argv[] ){
	signal(SIGPIPE, SIG_IGN);
	int pipe_to_a[2], pipe_from_a[2];
	char **input;
	int *elimin,ninput=0;
	printf("Devo chiamare A\n");
	firstStartAnal( argv, argc, pipe_to_a, pipe_from_a, &input, &ninput, &elimin);
	printf("Ho chiamato A per la prima volta\n");
	int i=0;
	int n = 3, m = 4, rec = 0;
	for(i = 0; i < argc; i++){
		if( !strcmp(argv[i],"-n") ){
			if(isNum(argv[i+1]))
				n = atoi(argv[i+1]);
		}
		else if( !strcmp(argv[i],"-m") ){
			if(isNum(argv[i+1]))
				m = atoi(argv[i+1]);
		}
		else if( !strcmp(argv[i],"-r") ){
			rec = 1;
		}
	}
	printf("Grazie per aver scelto il programma di analisi dati di G.E.F.F. & co.\n\n");
	printf( "Con che azione volete cominciare?\n" );
	printOptions();

	int option;
	//Menu principale
	while( option >= 0 ){
		char *azione = getInputorExit();
		option = atoi(azione);
		free(azione);
		printf("\n");
		switch(option){
			case 1:
				//Apri il menu di anal
				enterAnalMenu(&n,&m,&input,&ninput,&rec,&elimin,pipe_to_a,pipe_from_a);
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
	freeStringArray( input, ninput );
	return 0;
}
