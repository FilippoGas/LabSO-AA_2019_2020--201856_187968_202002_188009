//raggruppare per lettere, numeri, maiuscole,minuscole....


#include "report.h"

int main(int argc, char *argv[]){

    int ret = 0, reporting = 1, control;
    char *option, **fileNames;
    int **reports, nfiles/* = argc - 1*/, lastUpdate;

    //getFileNames(&fileNames,nfiles,argv);
    //generateRandomReports(&reports,nfiles);
    

    int fd = openFIFO();

    readPipe(fd,&reports,&fileNames,&nfiles,&lastUpdate);

    while(reporting){

        printMenu();

        control = getUserOption(0,5);

        int *selection = NULL;
        int nselection = 0;
        
        switch (control){
            case 1:
                printFileSelection();
                control = getUserOption(0,1);
                if(control){
                    getFileSelection(fileNames,nfiles,&selection, &nselection);
                }
                printReports(reports,fileNames,nfiles,selection,nselection,0);
                
            break;

            case 2:
                printFileSelection();
                control = getUserOption(0,1);
                if(control){
                    getFileSelection(fileNames,nfiles,&selection, &nselection);
                }
                printReports(reports,fileNames,nfiles,selection,nselection,1);
            break;

            case 3:
                printFileSelection();
                control = getUserOption(0,1);
            break;

            case 4:
                printFileSelection();
                control = getUserOption(0,1);  
            break;

            case 5:
                readPipe(fd,&reports,&fileNames,&nfiles,&lastUpdate);
            break;

            case 0:
                printf("Exiting...\n");
                reporting = 0;
            break;

        }

    }

    close(fd);
    unlink(FIFO_NAME);

    printf("Quitting report\n\n");
    return ret;

}
