#include "utility.h"

void printInput(int m, int n, char **files, char **dirs, int nfiles, int ndir){
	printf("m ha valore: %d\nn ha valore: %d\n", m, n);
	printf("Ci sono %d files\nFILES:\n", nfiles);
	printStringArray(files, nfiles);
	printf("Ci sono %d directory\nDIRECTORIES\n", ndir);
	printStringArray(dirs, ndir);


}

void printStringArray(char **in, int n){
	int i = 0;
	while(i < n){
		printf("\t %d:\t%s\n", i, in[i]);
		i++;
	}

}
