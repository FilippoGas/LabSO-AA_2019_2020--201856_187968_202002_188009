#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>



#define ASCII_SIZE 256
#define ASCII_START 32
#define COLS 10



#define FIFO_NAME "LabSO-AA_2019_2020--201856_187968_202002_188009/TestExe/Fifo/AtoR"
#define FILE_NAME "LabSO-AA_2019_2020--201856_187968_202002_188009/TestExe/Report/data.txt"

/*
 *Print the report menu for user interaction 
*/
void printMenu();

/*
 * Read the user input and validate it, return the selected option
 * args: min and max value the selection can have
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

/*
 *Let the user choose wich files in fileNames will be printed in the report
 *args: The list of all the filenames, the number of files, the reference to the list of selected files that has to be initialized,
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
void readPipe(int fd, int ***reports, char ***fileNames, int *nfiels, int *lastUpdate);

/*
 *Fill a report row from received message 
*/
void fillReports(int *report,char *buff);