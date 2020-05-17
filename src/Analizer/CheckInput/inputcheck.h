#include "../../macro_libglob.h"
/* Struttura che contiene percorso e nome del file (DEPRECATA), forse da spostare in report?
 */
struct idfile{

	char* name;
	char* path;

};

/* struct per la scansione della cartella
 */
struct dirent {
    ino_t          d_ino;       /* inode number */
    off_t          d_off;       /* offset to the next dirent */
    unsigned short d_reclen;    /* length of this record */
    unsigned char  d_type;      /* type of file; not supported
                                   by all file system types */
    char           d_name[256]; /* filename */
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

/* Concatenate second array of string onto the first, saving new array dynamically 
 * allcated and new size in resdim
 */
char **concatStringArray(char **first, char **second, int nfirst, int nsecond, int *resdim);
 
/* Get all files in dir and concatenate them, returning a new allocated array of string
 */
char **getContentOfDirs(char **dirs, int ndirs, int rec, int *resdim);

/* Save content of directory in array of string of dimension n, rec decides if the search
 * is recursive
 */
char **lsDir(char *dir, int rec, int *n);

/* Takes a string and if there isn't add to it a terminal /
 */
void addSlashToDir(char *dir);

/* Takes an array of string and if there isn't add to each string a terminal /
 */
void addSlashToDirs(char **dirs, int ndirs);

/* Takes a directory and return an array of string containing all files in it
 * (if rec analize also subdirectories
 */
char **lsDir(char *dir, int rec, int *n);

/* Check if string is not . (same directory) and not .. (parent directory)
 */
int isNotParOrSameDir(char *in);

/* dynamically allocate an array of string containing null values of dimension dimArray, 
 * with string long dimString
 */
char **initStringArray(int dimArray, int dimString);

/* Dalla lista dei file ritorna una nuova lista con i file con i percorsi completi
 */
char **getAllFullPath(char **file_list, int nfiles, char **dir_content, int dir_content_size, int *res_dim);

/* Takes the list of file definitive and form them in an array of idfile
 */
struct idfile **polishFileList(char **file_list, int size);

/* Takes a full path for a file and dynamically allocate its path and name
 */
void getPathAndName(char *file, char **path, char **name);

/* Takes a path and a name for a file and returns the corrispondent struct idfile
 */
struct idfile *initIdFile(char *path, char *name);

/* Free a dynamically allocated struct idfile
 */
void freeIdFile(struct idfile *in);

/* Free a dynamically allocated arrau of struct idfile
 */
void freeIdfileArray(struct idfile **in, int n);

int manageInput(char ***def_file_list, int argc, char *argv[],  int *m, int *n, int *recursive);
