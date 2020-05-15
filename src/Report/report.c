#include "report.h"

void printMenu(){

    printf("\n ****************************************************************");
    printf("\n REPORT UTILITY MENU, SELECT THE DESIRED OPERATION, OR 0 TO EXIT:\n");
    printf(" ****************************************************************");
    printf("\n\n");
    printf("    1) Print absolute stats\n");
    printf("    2) Print percentage stats\n");
    printf("    3) print absolute stats to file\n");
    printf("    4) Print percentage stats to file\n");
    printf("    5) Update reports\n");
    printf("    0) Exit\n");
    printf("\n");
    printf("> ");
}

int getUserOption(int min, int max){
    
    int option,done = 1;
    

    while(done){

        if(scanf("%d",&option) != 1 ||  option < min || option >max){

            printf("Invalid input. Choose one in %d..%d\n> ",min,max);
            while (fgetc(stdin) != '\n'){}
        
        }else{

            done = 0;
    
        }
    
    }

    return option;

}


void generateRandomReports(int ***reports, int nfiles){

    

    srand(time(NULL));

    (*reports) = malloc(nfiles * sizeof(int *));

    int i=0;
    for ( i ; i < nfiles ; i++ )
    {
        (*reports)[i] = malloc(ASCII_SIZE * sizeof(int));
        int j=0;
        for ( j; j < ASCII_SIZE; j++){
            (*reports)[i][j] = rand() % 5000;
        }
        
    }
    
}

void getFileNames(char ***fileNames, int nfiles, char* argv[]){

    (*fileNames) = malloc((nfiles) * sizeof(char*));
    
    int i;
    for (i = 0; i < (nfiles); i++){
        
        (*fileNames)[i] = malloc((strlen(argv[i+1])+1) * sizeof(char));
        sprintf((*fileNames)[i],"%s",argv[i+1]);
        
    }

}

void printFileSelection(){

    printf("\n");
    printf(" Do you want to see reports for all files or a set of files?\n\n");
    printf("    0) All files\n");
    printf("    1) Set of files\n\n");
    printf(" >");

}

void getFileSelection(char **fileNames, int nfiles, int **selection, int *nselection){

    int sel, buff[10000];  //invece che dim=1000, check se supero la dimensione e la aumento

    int i = 0;

    for ( i ; i < nfiles; i++){
        buff[i] = -1;
    }

    printf("\n\n ****************************************************************");
    printf("\n AVAILABLE FILES FOR REPORT\n");
    printf(" ****************************************************************\n\n");

    i = 0;
    for ( i ; i < nfiles; i++){
        printf("    %d) %s\n",i+1,fileNames[i]);
    }

    printf("\n Type the numbers of the desired files one at a time followed by ENTER, or 0 to exit the selection\n\n");

    i = 0;
    do{
        printf("> ");
        sel = getUserOption(0,nfiles);

        if(sel){

            buff[i] = sel-1;
            i++;

        }
        
    }while(sel != 0);

    (*nselection) = i;
    (*selection) = malloc((*nselection) * sizeof(int));
    
    i = 0;
    while(buff[i] != -1){
        (*selection)[i] = buff[i];
        i++;
    }

}

void removeUnselectedReports(int ***reports, int *selection, int nselection){

    int **temp = malloc(nselection * sizeof(int*));

    int i = 0;
    for ( i = 0; i < nselection; i++)
    {
        temp[i] = malloc(ALPHABET_SIZE * sizeof(int));
        //memcpy(temp[i],reports[selection[i]],sizeof(reports[selection[i]]));
        int j = 0;
        for ( j = 0; j < ALPHABET_SIZE; j++)
        {
            temp[i][j] = (*reports)[selection[i]][j];
        }
            
    }

    (*reports) = temp;    

}

void removeUnselectedNames(char ***fileNames, int *selection, int nselection){

    char **temp = malloc(nselection * sizeof(char*));

    int i = 0;
    for ( i = 0; i < nselection; i++)
    {
        temp[i] = malloc(sizeof(fileNames[selection[i]]));
        sprintf(temp[i],"%s",(*fileNames)[i]);
    }
    
    (*fileNames) = temp;

}



void printReports(int **reports, char **fileNames, int nfiles, int *selection, int nselection, int percentage){

    if(selection){

        //tolgo da reports e da nileNames i file non desiderati
        nfiles = nselection;
        removeUnselectedReports(&reports,selection,nselection);
        removeUnselectedNames(&fileNames,selection,nselection);

    }

    int i = 0;
    for (i ; i < nfiles ; i++){

        printf("\n\n ****************************************************************");
        printf("\n FILE NAME: %s    FILE PATH: un giorno ci sarà\n",fileNames[i]);
        printf(" ****************************************************************\n\n");

        int j = ASCII_START; 
        for ( j ; j < ALPHABET_SIZE ; j++){

            if(j == 127){

                if(percentage){
                    printf("| %4c : %.2f%c   ",32,getPerc(reports[i][j],getTotalChar(reports[i])),'%');
                }else{
                    printf("| %4c : %4d  ",32,(reports[i][j]));
                }

                if(((j-ASCII_START+1)%COLS)==0 && j!=0){
                    printf("|\n\n");
                }

            }else{
                if(percentage){
                    printf("| %4c : %.2f%c   ",j,getPerc(reports[i][j],getTotalChar(reports[i])),'%');
                }else{
                    printf("| %4c : %4d  ",j,(reports[i][j]));
                }
                if(((j-ASCII_START+1)%COLS)==0 && j!=0){
                    printf("|\n\n");
                }
            }
        }

        printf("\n\n");

    }
        
}

int getTotalChar(int *report){

    int totalChar= 0;

    int i = 0;
    for( i ; i < ALPHABET_SIZE ; i++){
        totalChar+=report[i];
    }

    return totalChar;

}

float getPerc(int x, int y){

        return (float)(100.0*x)/(float)y;
        
}

int openFIFO(){

	if(mkfifo(FIFO_NAME, 0777) == -1){		//DA CAMBIARE
		if(errno != EEXIST){
			perror("Fatal error on fifo creation: ");
			exit(-1);
		}
	}
 	
	int fd;

	if((fd = open(FIFO_NAME, O_RDONLY | O_NONBLOCK)) == -1){
		if(errno != ENXIO){
			perror("Fatal error on FIFO opening: ");
			exit(-1);
		}
	
	}
	return fd;
}

int openReportFile(){
    int fd;

    if((fd = open(REPORT_FILE, O_RDONLY | O_NONBLOCK)) == -1){
		if(errno != ENXIO){
			perror("Fatal error on file: ");
			//exit(-1);
		}
	
	}

    return fd;

}

void printTime(const long int rawtime){

    struct tm  ts;
    char buf[80];

    // Format time, "ddd yyyy-mm-dd hh:mm:ss zzz"
    ts = *localtime(&rawtime);
    strftime(buf, sizeof(buf), "%a %Y-%m-%d %H:%M:%S %Z", &ts);
    printf("\nUltimo aggiornamento: %s\n", buf);

}

void fillReports(int *report,char *buff){

    int j = 0;
    report[j] = atoi(strtok(buff," "));
    for ( j = 1; j < ALPHABET_SIZE; j++)
    {
        report[j] = atoi(strtok(NULL," "));
    }
     

}

void readPipe(int fd,int ***reports, char ***fileNames, int *nfiles,int *lastUpdate, int stopRecursion){

    char buff[4096];
    int empty = 1;
    while(read(fd,buff,22) > 0){
        empty = 0;
        char *timestamp = strtok(buff," ");
        (*lastUpdate) = atoi(timestamp);
        printTime(*lastUpdate);

        (*nfiles) = atoi(strtok(NULL," "));
        (*reports) = malloc((*nfiles)* sizeof(int*));
        (*fileNames) = malloc((*nfiles)* sizeof(char*));

        int i = 0;
        for ( i ; i < (*nfiles); i++)
        {
            (*reports)[i] = malloc(ALPHABET_SIZE * sizeof(int));
            (*fileNames)[i] = malloc( 4096 * sizeof(char));
            read(fd,(*fileNames)[i],4096);
            read(fd,buff,4096);
            fillReports((*reports)[i],buff);
        }
	printf("FINITO WHILE\n");

    }

    //Se la FIFO è vuota richiamo ricorsivamente readPipe con fd riferito al file invece che alla FIFO
    if(empty && !stopRecursion){		
        
        fd = openReportFile();
        if(fd != -1){

            readPipe(fd,reports,fileNames,nfiles,lastUpdate,1);

        }else{

            printf("\nFIFO empty\nFILE not found\n\n");
            exit(-1);

        }

    }

}

void addNewLine(char *in){
	int j = strlen(in);
	in[j] = '\n';
	in[j + 1] = '\0';
}

void addPadding(char *in, int dim_to_have){
	while(strlen(in) < dim_to_have){
		int j = strlen(in);
		in[j] = ' ';
		in[j + 1] = '\0';
	}
}   

char *contentToString(int *data){
	char *res = calloc(1,(PIPE_BUF + 1) * sizeof(char));
	int i = 0;
	while(i < ALPHABET_SIZE){
		sprintf(res, "%s %d", res, data[i]);
		i++;
	}
	sprintf(res, "%s\n", res);
	addPadding(res, PIPE_BUF);
	return res;
}

void generateRandomReportFile(int **reports, char **fileNames, int nfiles){

    int fd;

    if((fd = open(REPORT_FILE, O_WRONLY | O_NONBLOCK | O_CREAT)) == -1){
		if(errno != ENXIO){
			perror("Fatal error on file(generateRandomReportFile): ");
			//exit(-1);
		}
	
	}

    time_t current = time(NULL);
	char  timetemp[(2 * INTMAXCHAR) + 1];
	sprintf(timetemp, "%ld %d", current, nfiles);
	addPadding(timetemp, (2 * INTMAXCHAR) - 1);
	addNewLine(timetemp);
	write(fd, timetemp, (2 * INTMAXCHAR));
	int i = 0;
	while(i < nfiles){

		char nomeFile[PIPE_BUF + 1];
		sprintf(nomeFile, "%s", fileNames[i]);
		addPadding(nomeFile, PIPE_BUF);

        printf("\n\nnome file: %s\n",nomeFile);

		write(fd, nomeFile, PIPE_BUF);	
        char *content = contentToString(reports[i]);

        printf("\ncontent: %s\n",content);

		int writtenBytes = write(fd, content, PIPE_BUF);

        printf("\n\nWritten bytes: %d\n\n",writtenBytes);
        perror("Error writing content");

		free(content);
		i++;

	}

    close(fd);

}