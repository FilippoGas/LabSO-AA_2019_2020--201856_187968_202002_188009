#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define ASCII_SIZE 256
#define ASCII_START 32
#define COLS 10

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
 *Print the numeric report of the files specified by selection (index of files to report), if selection il NULL, print all reports 
 * 
*/
void printNumericReports(int **reports, char **filenames, int nfiles, int *selection, int nselection);

/*
 *Print the percent report of the files specified by selection (index of files to report), if selection il NULL, print all reports 
 * 
*/
void printPercentReports(int **reports, char **filenames, int nfiles, int *selection, int nselection);

/*
 *Return the total number of characters of a given report 
*/
int getTotalChar(int *report);

/**
 * Calculate percentage of x and y
*/
float getPerc(int x, int y);