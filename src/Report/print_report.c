//raggruppare per lettere, numeri, maiuscole,minuscole....


#include "report.h"

int main(int argc, char *argv[]){

    int ret = 0;

    if(argc == 2 && strcmp(argv[1],"-h") == 0){
        execl("/bin/cat","cat","../ManFiles/report_usage.txt",0);
    }else{

        int reporting = 1, control;
        char **fileNames = NULL, **dirs = NULL;
        int **reports = NULL, nfiles = 0, lastUpdate, ndirs = 0;

        //FIFO opening for Analizer-Report comunication
        int fd = openFIFO();
        printf("\nafter openFIFO()\n");

        readPipe(fd,&reports,&fileNames,&nfiles,&lastUpdate,0);
        while(reporting){

            printMenu();

            //get user operation
            control = getUserOption(0,6);

            int categoriesSelection[7] = {0,0,0,0,0,0,0};
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
                    getCategoriesSelection(categoriesSelection);
                    int i;
                    for ( i = 0; i < 5; i++)
                    {
                        printf("%d ",categoriesSelection[i]);
                    }
                    
                    printCategoriesReports(reports,fileNames,nfiles,selection,nselection,categoriesSelection);
                break;

                case 4:
                    ndirs = getDirs(fileNames,nfiles,&dirs);
                    getDirSelection(dirs,ndirs,&dirSelection,&nDirSelection);
                    printDirectoryReports(reports,fileNames,nfiles,dirs,ndirs,&dirSelection,nDirSelection,0);
                break;

                case 5:
                    ndirs = getDirs(fileNames,nfiles,&dirs);
                    getDirSelection(dirs,ndirs,&dirSelection,&nDirSelection);
                    printDirectoryReports(reports,fileNames,nfiles,dirs,ndirs,&dirSelection,nDirSelection,1);
                break;

                case 6:
                    readPipe(fd,&reports,&fileNames,&nfiles,&lastUpdate,0);
                break;

                case 0:
                    printf("    EXITING...\n");
                    if(reports != NULL){
                        freeReports(&reports,nfiles);
                    }
                    if(fileNames != NULL){
                        freeFileNames(&fileNames,nfiles);
                    }
                    if(dirs != NULL){
                        freeDirs(&dirs,ndirs);
                    }
                    reporting = 0;
                break;
            }   
        }

        close(fd);
        unlink(FIFO_NAME);

        sleep(1);
        printf("    QUITTING REPORT.\n\n");
    }
    return ret;

}
