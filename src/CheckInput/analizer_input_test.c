#include "inputcheck.h"
#include "../Debug/utility.h"


int main(int argc, char *argv[]){

	int m = 3, n = 4, ninput, recursive, nfiles, ndirs, ret = 0;
	char **input, **dir_list, **file_list;

	//legge l'input, alloca dinamicamente **input
	readInput(argc, argv, &input, &ninput, &n, &m, &recursive);
	
	printInput(m, n, input, ninput, recursive);
	
	//recupera vere cartelle e file nell'input, libera **input, alloca dinamicamente **dir_list e **file_list
	validateInput(input, ninput, &file_list, &dir_list, &nfiles, &ndirs);
	
	printf("Directories:\n");
	printStringArray(dir_list, ndirs);
	printf("Files:\n");
	printStringArray(file_list, nfiles);
	
	//cambia i file da string a idfile e li mette in un array
	struct idfile *files;
	int filesize = 0;
	getfiles(file_list, nfiles, &files, &filesize);	
	
	
	//genero n processi P

	//genero m processi Q

	//Libero memoria allocata dinamicamente
	freeStringArray(file_list, nfiles);
	freeStringArray(dir_list, ndirs);
	return ret;

}
