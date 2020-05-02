#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/errno.h>

#define SETN 0		//Code of command to set n
#define SETM 1		//Code of command to set m
#define HELP 2		//Code of command for help
#define COMMAND 0	//Code of argument as command
#define FILES 1		//Code of argument as file
#define DIRS 2		//Code of argument as directory
#define WSIZE 81	//Dimension of word
#define FILE 1      //boolean check used in checkExistance()
#define MANPATH "/LabSO-AA_2019_2020--201856_187968_202002_188009/src/ManFiles/"	//Path of the help files

/* Read the input (n = argc, arguments = argv)for the Analizer process, changes the value 
 * for n and m and save files in array files (nfiles = dim) and directory in dirs
 * (ndirs = dim)
 */
void readInput(int argc, char *argv[], char ***files, char ***dirs, int *nfiles, int *ndir, int *n, int *m);

/* Changes the value for the option n with number contained in string value
*/
void optionN(int *n, char *value);

/* Changes the value for the option m with number contained in string value
*/
void optionM(int *m, char *value);

/* Recognize the type of argument: option, file or directory
 */
int typeOfArgument(char *value);

/* Recognize the type of command: set-n, set-m, help
 */
int typeOfCommand(char *value);

/* Execute the command, already recognized by typeOfCommand in case of unrecognised command
 * prints the help file and exit
 */
int executeCommand(int type, int *n, int *m, int argc, int i, char *value);

/* Recognize if string is completely a number
 */
int isNumber(char *value);

/* According to command type changes n or m
 */
void changeNOrM(int type, int *n, int *m, char *value);

/* takes argv and the index chosen previously in pos and save them in an array of string
 * (the return value), n is the dimension of pos
 */
char **getNames(char *argv[], int *pos, int n);


/*Check consistency of input, existency of files and dirs
*args: list of file and dirs
*/
void validateInput(char ***files, char ***dirs, int *nfiles, int *ndirs);

/*
*checks existance of files and directories
*args: the list of file, the list of dir, and te option (0 or 1) to specify if i'm checking a file or a dir, and a pointer to variable
*holding the number of existing files/dirs
*returns an int array with the position of existing files/dirs in the original array
*/
int *checkExistance(char **list, int n, int option, int *newcount);