#include "report.h"

void printMenu(){

    printf("\n ****************************************************************");
    printf("\n REPORT UTILITY MENU, SELECT THE DESIRED OPERATION, OR 0 TO EXIT:\n");
    printf(" ****************************************************************");
    printf("\n\n");
    printf("    1) Print absolute stats\n");
    printf("    2) Print percentage stats\n");
    printf("    3) Print stats for categories\n");
    printf("    4) Print absolute stats per directory\n");
    printf("    5) Print percentage stats per directory\n");
    printf("    6) Update reports\n");
    printf("    0) Exit\n");
    printf("\n");
    printf("> ");
}

int getUserOption(int min, int max){
    
    int option = 0, done = 1;
    

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

    int i;
    for ( i = 0 ; i < nfiles ; i++ )
    {
        (*reports)[i] = malloc(ASCII_SIZE * sizeof(int));
        int j;
        for ( j = 0; j < ASCII_SIZE; j++){
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

    int sel;
    int buff[nfiles];

    int i = 0;

    for ( i = 0 ; i < nfiles; i++){
        buff[i] = -1;
    }   

    printf("\n\n ****************************************************************");
    printf("\n AVAILABLE FILES FOR REPORT\n");
    printf(" ****************************************************************\n\n");

    for ( i = 0 ; i < nfiles; i++){
        printf("    %d) %s\n",i+1,fileNames[i]);
    }

    printf("\n Type the numbers of the desired files one at a time followed by ENTER, or 0 to exit the selection\n\n");

    //doen't save repeated files

    i = 0;
    do{
        printf("> ");
        sel = getUserOption(0,nfiles);

        if(sel){

            if(!alreadySelectedFile(sel-1,buff,nfiles)){
                buff[i] = sel-1;
                i++;
            }
        }
        
    }while(sel != 0 && i < nfiles);

    (*nselection) = i;
    (*selection) = malloc((*nselection) * sizeof(int));

    i = 0;
    while(buff[i] != -1 && i < nfiles){
        (*selection)[i] = buff[i];
        i++;
    }
}

int alreadySelectedFile(int n, int buff[], int size){

    int i;
    for ( i = 0; i < size; i++)
    {
        if (buff[i] == n)
        {
            return 1;
        }
        
    }
    

    return 0;

}
void removeUnselectedReports(int ***reports, int *selection, int nselection){


    int **temp = malloc(nselection * sizeof(int*));

    int i = 0;
    for ( i = 0; i < nselection; i++)
    {
        temp[i] = malloc(ALPHABET_SIZE * sizeof(int));
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
        temp[i] = malloc(sizeof(char) * (strlen((*fileNames)[selection[i]])+1));
        sprintf(temp[i],"%s",(*fileNames)[selection[i]]);
    }
    
    (*fileNames) = temp;

}



void printReports(int **reports, char **fileNames, int nfiles, int *selection, int nselection, int percentage){

    if(selection && nselection < nfiles){
        nfiles = nselection;
        removeUnselectedReports(&reports,selection,nselection);
        removeUnselectedNames(&fileNames,selection,nselection);

    }

    int i;
    for (i = 0 ; i < nfiles ; i++){

        printf("\n\n ****************************************************************");
        printf("\n FILE: %s\n",fileNames[i]);
        printf(" ****************************************************************\n\n");

        int j; 
        printf("\n  **EXTENDED ASCII TABLE CHARS (0-32)**\n\n\n");
        for ( j = 0; j < ASCII_START; j++)
        {
            if(percentage){
                printf("| %4d : %.2f%c   ",j,getPerc(reports[i][j],getTotalChar(reports[i])),'%');
            }else{
                printf("| %4d : %4d  ",j,(reports[i][j]));
            }
            if(((j+1)%COLS)==0 && j!=0){
                printf("|\n\n");
            }
        }
        printf("\n\n");
        printf("\n  **PRINTABLE ASCII TABLE CHARS**\n\n\n");
        for ( j = ASCII_START ; j < ALPHABET_SIZE ; j++){

            //char #127 is the DELETE char, that would shift the printing, SPACE is printed instead
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
    
    if(selection){
        free(selection);
    }

    if(selection && nselection < nfiles){
        freeReports(&reports,nselection);
        freeFileNames(&fileNames,nselection);
    }
        
}

int getTotalChar(int *report){

    int totalChar= 0;

    int i;
    for( i = 0 ; i < ALPHABET_SIZE ; i++){
        totalChar+=report[i];
    }

    return totalChar;

}

float getPerc(int x, int y){

        return (float)(100.0*x)/(float)y;
        
}

int openFIFO(){

    //FIFO creation
	if(mkfifo(FIFO_NAME, 0777) == -1){
		if(errno != EEXIST){
			perror("Fatal error on fifo creation: ");
			exit(-1);
		}
	}
 	
	int fd;

    //FIFO opening
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
            printf("\nQUITTING . . .\n");
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

    //repotrs are suquences of 255 numbers, one per every ASCII character

    int j = 0;
    //remove first space
    strtok(buff," ");
    report[j] = atoi(strtok(NULL," "));
    for ( j = 1; j < ALPHABET_SIZE; j++)
    {
        report[j] = atoi(strtok(NULL," "));
    }
}

void readPipe(int fd,int ***reports, char ***fileNames, int *nfiles,int *lastUpdate, int stopRecursion){

    //FIFO max message size 4960 byte
    char buff[4096];
    int empty = 1;  //check for empty FIFO

    //first line of message is timestamp, 22 byte
    while(read(fd,buff,22) == 22){

        //if in a recursive cycle, read from file instead
        if(!stopRecursion){
            printf("\nReading from PIPE\n");
        }else{
            printf("\nReading from FILE\n");
        }
        empty = 0;
        char *timestamp = strtok(buff," ");
        (*lastUpdate) = atoi(timestamp);
        printTime(*lastUpdate);

        //number of file reported in current message/file
        (*nfiles) = atoi(strtok(NULL," "));
        (*reports) = malloc((*nfiles) * sizeof(int*));
        (*fileNames) = malloc((*nfiles)* sizeof(char*));

        int i;
        //for each file read name and report
        for ( i = 0 ; i < (*nfiles); i++)
        {
            (*reports)[i] = malloc(ALPHABET_SIZE * sizeof(int));

            char name[4096];
            read(fd,name,4096);
            strtok(name,"/");
            char *nameOnly = strtok(NULL,"\n");
            int j = 0;
            for ( j = 4000; j >= 0 && nameOnly[j] == 32; j--){}
            (*fileNames)[i] = calloc(1,(sizeof(char)*(j+3))); //+2 (/ iniziale e carattere terminatore)
            strcat((*fileNames)[i],"/");
            strncat((*fileNames)[i],nameOnly,j+1);
            read(fd,buff,4096);
            fillReports((*reports)[i],buff);
        }
    }

    //Se la FIFO è vuota richiamo ricorsivamente readPipe con fd riferito al file invece che alla FIFO
    if(empty && !stopRecursion){		
        
        printf("\nOpening file\n");

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

void printCategoriesReports(int **reports, char **fileNames, int nfiles, int *selection, int nselection, int *categoriesSelection){
    
    if(selection){

        //tolgo da reports e da nileNames i file non desiderati
        nfiles = nselection;
        removeUnselectedReports(&reports,selection,nselection);
        removeUnselectedNames(&fileNames,selection,nselection);

    }

    int i;
    for (i = 0 ; i < nfiles ; i++){

        int letters = 0;
        int upperCase = 0;
        int lowerCase = 0;
        int numbers = 0;
        int symbols = 0;
        int punctuation = 0;
        int extendedASCII = 0;

        printf("\n\n ****************************************************************");
        printf("\n FILE: %s\n",fileNames[i]);
        printf(" ****************************************************************\n\n");

        int j; 
        for ( j = ASCII_START ; j < ALPHABET_SIZE ; j++){

            if(j>=48 && j<=57){
                numbers+=reports[i][j];
            }

            if(j>=65 && j<=90){
                letters+=reports[i][j];
                upperCase+=reports[i][j];
            }
            
            if(j>=97 && j<=122){
                letters+=reports[i][j];
                lowerCase+=reports[i][j];
            }

            if((j>=34 && j<=43) || (j>=60 && j<=62) || (j>=91 && j<=96) || (j>=123 && j<=126) || j==45 || j==47 || j== 64){
                symbols+=reports[i][j];
            }

            if(j==32 || j==33 || j== 44 || j==46 || j==58 || j==59 || j==63){
                punctuation+=reports[i][j];
            }

            if(j>=128){
                extendedASCII+=reports[i][j];
            }

        }

        int totalChar = getTotalChar(reports[i]);

        //only print selected categories
        if(categoriesSelection[0]){
            printf("\n LETTERS: %d - %.2f%c\n",letters,getPerc(letters,totalChar),'%');
        }
        if(categoriesSelection[1]){
            printf("\n UPPERCASE LETTERS: %d - %.2f%c\n",upperCase,getPerc(upperCase,totalChar),'%');
        }
        if(categoriesSelection[2]){
            printf("\n LOWERCASE LETTERS: %d - %.2f%c\n",lowerCase,getPerc(lowerCase,totalChar),'%');
        }
        if(categoriesSelection[3]){
            printf("\n NUMBERS: %d - %.2f%c\n",numbers,getPerc(numbers,totalChar),'%');
        }
        if(categoriesSelection[4]){
            printf("\n PUNCTUATION: %d - %.2f%c\n",punctuation,getPerc(punctuation,totalChar),'%');
        }
        if(categoriesSelection[5]){
            printf("\n SYMBOLS: %d - %.2f%c\n",symbols,getPerc(symbols,totalChar),'%');
        }
        if(categoriesSelection[6]){
            printf("\n EXTENDED ASCII TABLE: %d - %.2f%c\n",extendedASCII,getPerc(extendedASCII,totalChar),'%');
        }
    
    }

    
}


void freeReports(int ***reports, int size){

    int i = 0;

    for ( i = 0; i < size; i++)
    {
        free((*reports)[i]);
    }
    
    free((*reports));

}

void freeFileNames(char ***fileNames, int size){

    int i = 0;

    for ( i = 0; i < size; i++)
    {
        free((*fileNames)[i]);
    }

    free((*fileNames));

}

int getDirs(char **fileNames, int nfiles, char ***dirs){

    char **tempDirs = calloc(1,nfiles * sizeof(char*));
    int ndirs = 0, firstSlash = 0;
    
    int i;
    for ( i = 0; i < nfiles; i++)
    {
        tempDirs[i] = NULL;
    }
    //cycle for every file name
    for ( i = 0; i < nfiles; i++)
    {
        int j;
        firstSlash = 1;
        for(j = 0 ; j < strlen(fileNames[i]) ; j++){
            int doubleDir = 0;
            if(fileNames[i][j] == 47){
                if(firstSlash){
                    firstSlash = 0;
                }else{
                    char buff[j+1];
                    strncpy(buff,fileNames[i],j);
                    buff[j] = '\0';
                    //check if already saved
                    int k = 0;
                    while(tempDirs[k] != NULL){
                        if(strcmp(tempDirs[k],buff) == 0){
                            doubleDir = 1;
                        }
                        k++;
                    }
                    if(!doubleDir){
                        tempDirs[ndirs] = calloc(1,sizeof(buff));
                        sprintf(tempDirs[ndirs],"%s",buff);
                        ndirs++;
                    }
                }
            }
        }
    }
    (*dirs) = malloc(ndirs * sizeof(char*));
    i = 0;
    while(tempDirs[i] != NULL){
        (*dirs)[i] = calloc(1,sizeof(tempDirs[i]));
        sprintf((*dirs)[i],"%s",tempDirs[i]);
        i++;
    }
    for ( i = 0; i < nfiles; i++)
    {
        free(tempDirs[i]);
    }
    free(tempDirs);
    return ndirs;
}

void getDirSelection(char **dirs, int ndirs,int **dirSelection,int *nDirSelection){
    
    int sel, buff[ndirs];

    int i;

    for (i = 0 ; i < ndirs; i++){
        buff[i] = -1;
    }

    printf("\n\n ****************************************************************");
    printf("\n AVAILABLE DIRECTORIES FOR REPORT\n");
    printf(" ****************************************************************\n\n");

    for ( i = 0 ; i < ndirs; i++){
        printf("    %d) %s\n",i+1,dirs[i]);
    }

    printf("\n Type the numbers of the desired directories one at a time followed by ENTER, or 0 to exit the selection\n\n");

    i = 0;
    do{
        printf("> ");
        sel = getUserOption(0,ndirs);

        if(sel){

            if(!alreadySelectedDirectory(sel-1,buff,ndirs)){
                buff[i] = sel-1;
                i++;
            }

        }
        
    }while(sel != 0 && i < ndirs);

    (*nDirSelection) = i;
    (*dirSelection) = malloc((*nDirSelection) * sizeof(int));

    i = 0;
    while(buff[i] != -1 && i <= ndirs){
        (*dirSelection)[i] = buff[i];
        i++;
    }
}

int alreadySelectedDirectory(int n, int buff[], int size){

    int i;
    for ( i = 0; i < size; i++)
    {
        if (buff[i] == n)
        {
            return 1;
        }
        
    }
    
    return 0;
}

void printDirectoryReports(int **reports, char **fileNames, int nfiles, char **dirs, int ndirs, int **dirSelection, int nDirSelection, int percentage){

    int i;
    for (i = 0; i < nfiles ; i++){

        if(inSelectedDirs(fileNames[i],dirs,(*dirSelection),nDirSelection)){   
            printf("\n\n ****************************************************************");
            printf("\n FILE: %s\n",fileNames[i]);
            printf(" ****************************************************************\n\n");

            int j; 
            printf("\n  **EXTENDED ASCII TABLE CHARS (0-32)**\n\n\n");
            for ( j = 0; j < ASCII_START; j++)
            {
                if(percentage){
                    printf("| %4d : %.2f%c   ",j,getPerc(reports[i][j],getTotalChar(reports[i])),'%');
                }else{
                    printf("| %4d : %4d  ",j,(reports[i][j]));
                }
                if(((j+1)%COLS)==0 && j!=0){
                    printf("|\n\n");
                }
            }
        printf("\n\n");
        printf("\n  **PRINTABLE ASCII TABLE CHARS**\n\n\n");
            for ( j = ASCII_START; j < ALPHABET_SIZE ; j++){

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
    freeDirSelection(dirSelection,nDirSelection);
}

int inSelectedDirs(char *fileName, char **dirs, int *dirSelection, int nDirSelection){

    int i;
    for ( i = 0; i < nDirSelection; i++)
    {
        if(strstr(fileName,dirs[dirSelection[i]]) != NULL){
            return 1;
        }
    }
    return 0;
}


void getCategoriesSelection(int *categoriesSelection){

    int sel;  

    printf("\n\n ****************************************************************");
    printf("\n AVAILABLE CATEGORIES FOR REPORT\n");
    printf(" ****************************************************************\n\n");

    printf("\n    1) LETTERS");
    printf("\n    2) UPPERCASE LETTERS");
    printf("\n    3) LOWERCASE LETTERS");
    printf("\n    4) NUMBERS");
    printf("\n    5) PUNCTUATION");
    printf("\n    6) SYMBOLS");
    printf("\n    7) EXTENDED ASCII TABLE");

    printf("\n\n Type the numbers of the desired category one at a time followed by ENTER, or 0 to exit the selection\n\n");

    do{
        printf("> ");
        sel = getUserOption(0,7);

        if(sel){

            categoriesSelection[sel-1] = 1;

        }
    }while(sel != 0);
}

void freeDirSelection(int **dirSelection, int nDirSelection){

    free((*dirSelection));

}

void freeDirs(char ***dirs, int ndirs){

    int i;
    for ( i = 0; i < ndirs; i++)
    {
        free((*dirs)[i]);
    }
    free((*dirs));

}
