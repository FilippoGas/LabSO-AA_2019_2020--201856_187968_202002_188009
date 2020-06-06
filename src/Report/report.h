#include "../macro_libglob.h"
/*
 *Print the report menu for user interaction 
*/
void printMenu();

/**
 * Read the user input and validate it, return the selected option
 * min and max value the selection can have
 * number selected from user
*/
int getUserOption(int min, int max);

/*
 *generate random reports. For debbugging puropse only
 *arg: pointer to string array and number of reports to be generated  
*/
void generateRandomReports(int ***reports, int nfiles);

/*
 *Read the list of file names from argv and saves it into ***fileNames. For debugging purpose only 
*/
void getFileNames(char *** fileNames, int nfiles, char* argv[]);

/*
 *Ask user if the operation has to be performed for all files or just some 
*/
void printFileSelection();

/**
 *Let the user choose wich files in fileNames will be printed in the report
 The list of all the filenames, the number of files, the reference to the list of selected files that has to be initialized,
 *the reference of the variable holding the number of new files
*/
void getFileSelection(char **fileNames, int nfiles, int **selection, int *nselection);

/*
 *Print the report of the files specified by selection (index of files to report), if selection il NULL, print all reports, percentage = 1 to print percentage
 *instead of absolute values
*/
void printReports(int **reports, char **filenames, int nfiles, int *selection, int nselection, int percentage);

/*
 *Return the total number of characters of a given report 
*/
int getTotalChar(int *report);

/**
 * Calculate percentage of x and y
*/
float getPerc(int x, int y);

/*
 *Remove unselected reports from the reports list 
*/
void removeUnselectedReports(int ***reports, int *selection, int nselection);

/*
 *Remove unselected file names from the filenames list 
*/
void removeUnselectedNames(char ***fileNames, int *selection, int nselection);

/*
 *Open the FIFO related to the path and return the fd, creates it if not existing
*/
int openFIFO();

/*
 *Read the pipe and fills reports and filenames 
*/
void readPipe(int fd, int ***reports, char ***fileNames, int *nfiels, int *lastUpdate, int stopRecursion);

/*
 *Fill a report row from received message 
*/
void fillReports(int *report,char *buff);

/**
 * Generate a report file, fac-simile to the one produced by analizer, for debugging purpose only
*/
void generateRandomReportFile(int **reports, char **fileNames, int nfiles);

/**
 *Print statistic for different categories of char  
 */
void printCategoriesReports(int **reports, char **fileNames, int nfiles, int *selection,int nselection, int *categoriesSelection);

/**
 * free memory used by reports
*/
void freeReports(int ***reports, int size);

/**
 * free memory used by fileNames
*/
void freeFileNames(char ***fileNames, int size);

/**
 * get all the available directories from file names and save them into dirs, return the number of dirs
*/
int getDirs(char **fileNames, int nfiles, char ***dirs);

/**
 * get the selection of directories to print
*/
void getDirSelection(char **dirs, int ndirs,int **dirSelection,int *nDirSelection);

/**
 * print reports for the selected directories
*/
void printDirectoryReports(int **reports, char **fileNames, int nfiles, char **dirs, int ndirs, int **dirSelection, int nDirSelection, int percentage);

/**
 * check if a file is in one of the selected directories
*/
int inSelectedDirs(char *fileName,char **dirs, int *dirSelection,int nDirSelection);


/**
 * get the selection of categories to report
*/
void getCategoriesSelection(int *categoriesSelection);

/**
 * free memory used by directory selection
*/
void freeDirSelection(int **dirSelection, int nDirSelection);

/**
 * free memory used by dirs
*/
void freeDirs(char ***dirs, int ndirs);

/**
 * check if the file has already been selected
*/
int alreadySelectedFile(int file,int buff[], int size);

/**
 * check if directory has already been selected
*/
int alreadySelectedDirectory(int n, int buff[], int size);