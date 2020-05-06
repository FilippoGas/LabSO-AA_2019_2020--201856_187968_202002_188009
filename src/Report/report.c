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

void printNumericReports(int **reports, char **fileNames, int nfiles, int *selection, int nselection){

    if(selection){

        
        int i = 0;
        for (i ; i < nselection ; i++){

            printf("\n\n ****************************************************************");
            printf("\n FILE NAME: %s    FILE PATH: un giorno ci sarà\n",fileNames[selection[i]]);
            printf(" ****************************************************************\n\n");

            int j = ASCII_START; //i primi 31 caratteri ASCII non sono stampabili, difficile riuscire a scriverli...
            for ( j ; j < 256 ; j++){

                if(j == 127){
                    printf("| %4c : %4d  ",32,(reports[selection[i]][j]));
                    if(((j-ASCII_START+1)%COLS)==0 && j!=0){
                        printf("|\n\n");
                    }
                }else{

                    printf("| %4c : %4d  ",j,(reports[selection[i]][j]));
                    if(((j-ASCII_START+1)%COLS)==0 && j!=0){
                        printf("|\n\n");
                    }
                }
            }

            printf("\n\n");

        }

    }else{

        int i = 0;
        for (i ; i < nfiles ; i++){

            printf("\n\n ****************************************************************");
            printf("\n FILE NAME: %s    FILE PATH: un giorno ci sarà\n",fileNames[i]);
            printf(" ****************************************************************\n\n");

            int j = ASCII_START; //i primi 31 caratteri ASCII non sono stampabili, difficile riuscire a scriverli...
            for ( j ; j < 256 ; j++){

                if(j == 127){
                    printf("| %4c : %4d  ",32,(reports[i][j]));
                    if(((j-ASCII_START+1)%COLS)==0 && j!=0){
                        printf("|\n\n");
                    }
                }else{

                    printf("| %4c : %4d  ",j,(reports[i][j]));
                    if(((j-ASCII_START+1)%COLS)==0 && j!=0){
                        printf("|\n\n");
                    }
                }
            }

            printf("\n\n");

        }
        

    }

}

int getTotalChar(int *report){

    int totalChar= 0;

    int i = 0;
    for( i ; i < 256 ; i++){
        totalChar+=report[i];
    }

    return totalChar;

}

float getPerc(int x, int y){

        return (float)(100.0*x)/(float)y;
        
}

void printPercentReports(int **reports, char **fileNames, int nfiles, int *selection, int nselection){

    if(selection){

        
        int i = 0;
        for (i ; i < nselection ; i++){

            printf("\n\n ****************************************************************");
            printf("\n FILE NAME: %s    FILE PATH: un giorno ci sarà\n",fileNames[selection[i]]);
            printf(" ****************************************************************\n\n");

            int j = ASCII_START; //i primi 31 caratteri ASCII non sono stampabili, difficile riuscire a scriverli...
            for ( j ; j < 256 ; j++){

                if(j == 127){
                    printf("| %4c : %.2f%c   ",32,getPerc(reports[i][j],getTotalChar(reports[selection[i]])),'%');
                    if(((j-ASCII_START+1)%COLS)==0 && j!=0){
                        printf("|\n\n");
                    }
                }else{

                    printf("| %4c : %.2f%c   ",j,getPerc(reports[i][j],getTotalChar(reports[selection[i]])),'%');
                    if(((j-ASCII_START+1)%COLS)==0 && j!=0){
                        printf("|\n\n");
                    }
                }
            }

            printf("\n\n");

        }

    }else{

        int i = 0;
        for (i ; i < nfiles ; i++){

            printf("\n\n ****************************************************************");
            printf("\n FILE NAME: %s    FILE PATH: un giorno ci sarà\n",fileNames[i]);
            printf(" ****************************************************************\n\n");

            int j = ASCII_START; //i primi 31 caratteri ASCII non sono stampabili, difficile riuscire a scriverli...
            for ( j ; j < 256 ; j++){

                if(j == 127){
                    printf("| %4c : %.2f%c   ",32,getPerc(reports[i][j],getTotalChar(reports[i])),'%');
                    if(((j-ASCII_START+1)%COLS)==0 && j!=0){
                        printf("|\n\n");
                    }
                }else{

                    printf("| %4c : %.2f%c   ",j,getPerc(reports[i][j],getTotalChar(reports[i])),'%');
                    if(((j-ASCII_START+1)%COLS)==0 && j!=0){
                        printf("|\n\n");
                    }
                }
            }

            printf("\n\n");

        }
    }

}