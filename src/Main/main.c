#include "./mainfunc.h"


int main( int argc, char *argv[] ){
	signal(SIGPIPE, SIG_IGN);
	int pipe_to_a[2], pipe_from_a[2];
	char **input;
	int *elimin,ninput = 0;

	char errorFile[PATH_MAX] = MANPATH;
	strcat(errorFile, "main_usage.txt");
	char *args[] = {"more", errorFile, NULL};
	int i=0;
	for( i=0; i < argc; i++ ){
		if( !(strcmp(argv[i],"-h") && strcmp(argv[i],"--help")) ){
			if(execvp("/bin/more", args)){
				fprintf(stderr, "Cannot open man file %s\n", errorFile);
				exit(-1);
			}
		}
}

	int analpid = firstStartAnal( argv, argc, pipe_to_a, pipe_from_a, &input, &ninput, &elimin);
	int n = 3, m = 4, rec = 0;
	for(i = 0; i < argc; i++){
		if( !strcmp(argv[i],"-n") ){
			if(isNum(argv[i+1]))
				n = atoi(argv[i+1]);
		}
		else if( !strcmp(argv[i], "-m" ) ){
			if(isNum(argv[i+1]))
				m = atoi(argv[i+1]);
		}
		else if( !strcmp(argv[i], "-r") ){
			rec = 1;
		}
	}
	printf("Thank you for choosing the programm analizer of G.E.F.F. & co.\n\n");
	printf( "What action do you want to start on?\n" );
	printOptions();

	int option;
	//Menu principale
	while( option >= 0 ){
		char *azione = getInputorExit(analpid);
		option = atoi(azione);
		free(azione);
		printf("\n");
		switch(option){
			case 1:
				//Open the main menu of anal
				enterAnalMenu(&n,&m,&input,&ninput,&rec,&elimin,pipe_to_a,pipe_from_a,&analpid);
				printf( "You are in the main menu'.\n" );
				break;
			case 2:
				//Start the reporter
				startReporter();
				printf( "You are in the main menu'.\n" );
				break;

			case 3:
				//Print actions
				printf( "The actions are:\n" );
				break;

			default:
				//Wrong input
				printf( "The option is not valid\n\n" );
				printf( "Please, write a number in the action list:\n\n" );
				option=0;
		}
		printOptions();
	}
	freeStringArray( input, ninput );
	return 0;
}
