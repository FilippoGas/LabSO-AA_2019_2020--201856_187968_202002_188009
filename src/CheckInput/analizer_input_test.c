#include "inputcheck.h"
#include "../Debug/utility.h"

void printIdfileArray(struct idfile **in, int size){
	int i = 0;
	while(i < size){
		printf("\t%d:\n", i);
		printf("\t\tName: %s\n", in[i]->name);
		printf("\t\tPath: %s\n", in[i]->path);
		i++;
	}

}

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
	
	//Recupera i contenuti delle directory
	int dir_content_size;
	char **dir_content = getContentOfDirs(dir_list, ndirs, recursive, &dir_content_size);
	freeStringArray(dir_list, ndirs);	//libero dir_list
	printf("Files in directories:\n");
	printStringArray(dir_content, dir_content_size);
	
	//Unisce i file in file_list e in dir_content e salva in un array tutti i percorsi reali;	
	int def_file_list_size;
	char **def_file_list = getAllFullPath(file_list, nfiles, dir_content, dir_content_size, &def_file_list_size);
	freeStringArray(file_list, nfiles);	//libero file_list
	freeStringArray(dir_content, dir_content_size);		//libero dir_content
	printf("Definitive file list:\n");	
	printStringArray(def_file_list, def_file_list_size);
	
	//cambia i file da string a idfile e li mette in un array
	int file_size = def_file_list_size;
	struct idfile **files = polishFileList(def_file_list, def_file_list_size);
	printIdfileArray(files, file_size);
	freeStringArray(def_file_list, def_file_list_size); 		//libero def_file_list
	
	//genero n processi P

	//genero m processi Q

	//Libero memoria allocata dinamicamente
	freeIdfileArray(files, file_size);
	return ret;

}
