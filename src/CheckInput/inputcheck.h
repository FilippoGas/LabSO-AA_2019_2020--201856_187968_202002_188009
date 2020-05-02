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
#define SETREC 3	//Code for setting recursive search in directories
#define COMMAND 0	//Code of argument as command
#define NOTCOMMAND 1
#define WSIZE 81	//Dimension of word
#define FILES 0      	//Code for a found file in input
#define DIRECTORY 1	//Code for a found directory in input
#define MANPATH "/LabSO-AA_2019_2020--201856_187968_202002_188009/src/ManFiles/"	//Path of the help files

struct idfile{

	char* nomefile;
	char* pathfile;

};

/* Read the input (n = argc, arguments = argv)for the Analizer process, changes the value 
 * for n and m and save files not command argument in input (size = ninput), set if the
 * search in listed directory has to be recursive
 */
void readInput(int argc, char *argv[], char ***input, int *ninput, int *n, int *m, int *recursive);

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
int executeCommand(int type, int *n, int *m, int argc, int i, char *value, int *recursive);

/* Recognize if string is completely a number
 */
int isNumber(char *value);

/* According to command type changes n or m
 */
void changeNOrM(int type, int *n, int *m, char *value);

/* Takes argv and the index chosen previously in pos and save them in an array of string
 * (the return value), n is the dimension of pos
 */
char **getNames(char *argv[], int *pos, int n);

/* Free the array of string dynamically allocated in of size n
 */
void freeStringArray(char **in, int n);

/* Check consistency of input, existency of files and dirs
*/
void validateInput(char **input, int ninput, char ***files, char ***dirs, int *nfiles, int *ndirs);

/*Check type of in: if exists, if file, directory or other
 */
int inputType(char *in);

void getfiles(char **file_list, int nfiles, struct idfile **files, int *filesize);	

struct idfile getfile(char *in);
