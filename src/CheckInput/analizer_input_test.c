#include "inputcheck.h"
#include "../Debug/utility.h"
int main(int argc, char *argv[]){
	int m = 3, n = 4, nfiles, ndir;
	char **files, **dirs;
	readInput(argc, argv, &files, &dirs, &nfiles, &ndir, &n, &m);
	printInput(m, n, files, dirs, nfiles, ndir);

}
