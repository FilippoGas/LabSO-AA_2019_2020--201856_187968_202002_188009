//raggruppare per lettere, numeri, maiuscole,minuscole....


#include <stdio.h>
#include <stdlib.h>
#include "report.h"

int main(int argc, char *argv[]){

    int ret = 0, reporting = 1, control;
    char *option, **fileNames;
    int **reports, nfiles = argc - 1;

    getFileNames(&fileNames,nfiles,argv);
    generateRandomReports(&reports,nfiles);
    
    while(reporting){

        printMenu();

        control = getUserOption(0,4);

        int *selection = NULL;
        int nselection = 0;
        
        switch (control){
            case 1:
                printFileSelection();
                control = getUserOption(0,1);
                if(control){
                    getFileSelection(fileNames,nfiles,&selection, &nselection);
                }
                printNumericReports(reports,fileNames,nfiles,selection,nselection);
                
            break;

            case 2:
                printFileSelection();
                control = getUserOption(0,1);
                if(control){
                    getFileSelection(fileNames,nfiles,&selection, &nselection);
                }
                printPercentReports(reports,fileNames,nfiles,selection,nselection);
            break;

            case 3:
                printFileSelection();
                control = getUserOption(0,1);
            break;

            case 4:
                printFileSelection();
                control = getUserOption(0,1);  
            break;

            case 0:
                printf("Exiting...\n");
                reporting = 0;
            break;

        }

    }

    printf("Quitting report\n\n");
    return ret;

}