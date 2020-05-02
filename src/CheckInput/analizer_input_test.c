#include "inputcheck.h"
#include "../Debug/utility.h"

typedef struct idfile{

	char* nomefile;
	char* pathfile;

};

int main(int argc, char *argv[]){

	int m = 3, n = 4, nfiles, ndir, ret = 0;
	char **files, **dirs;

	//lettura riga di comando, popolazione della lista delle cartelle, file, n, m.
	readInput(argc, argv, &files, &dirs, &nfiles, &ndir, &n, &m);
	printInput(m, n, files, dirs, nfiles, ndir);
	validateInput();
	printInput(m, n, files, dirs, nfiles, ndir);

	//genero n processi P

	//genero m processi Q

	return ret;

}