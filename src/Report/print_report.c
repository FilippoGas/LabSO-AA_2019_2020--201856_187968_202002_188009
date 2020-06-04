//raggruppare per lettere, numeri, maiuscole,minuscole....


#include "report.h"

int main(int argc, char *argv[]){

    int ret = 0, reporting = 1, control;
    char *option, **fileNames, **dirs;
    int **reports, nfiles = argc-1, lastUpdate, ndirs = 0;

    //getFileNames(&fileNames,nfiles,argv);
    //generateRandomReports(&reports,nfiles);
    
    
    //generateRandomReportFile(reports,fileNames,nfiles);


    int fd = openFIFO();

    readPipe(fd,&reports,&fileNames,&nfiles,&lastUpdate,0);

    while(reporting){

        printMenu();

        control = getUserOption(0,8);

        int *selection = NULL;
        int nselection = 0;
        int *dirSelection = NULL;
        int nDirSelection = 0;
        
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
                if(control){
                    getFileSelection(fileNames,nfiles,&selection, &nselection);
                }
                printCategoriesReports(reports,fileNames,nfiles,selection,nselection);
            break;

            case 4:
                ndirs = getDirs(fileNames,nfiles,&dirs);
                getDirSelection(dirs,ndirs,&dirSelection,&nDirSelection);
                printDirectoryReports(reports,fileNames,nfiles,dirs,ndirs,dirSelection,nDirSelection,0);
            break;

            case 5:
                ndirs = getDirs(fileNames,nfiles,&dirs);
                getDirSelection(dirs,ndirs,&dirSelection,&nDirSelection);
                printDirectoryReports(reports,fileNames,nfiles,dirs,ndirs,dirSelection,nDirSelection,1);
            break;

            case 6:
                printFileSelection();
                control = getUserOption(0,1);
            break;

            case 7:
                printFileSelection();
                control = getUserOption(0,1);  
            break;

            case 8:
                readPipe(fd,&reports,&fileNames,&nfiles,&lastUpdate,0);
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
