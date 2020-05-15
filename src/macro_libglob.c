#include "macro_libglob.h"

int errorSysCall(int res){
	if(res == -1){
		perror("Error on syscall: ");
	}
	return res;
}

int errorOpenInQ(int res, char path[]){
	if(res==-1){
		switch(errno){
			case ENOENT:
				printf("Il file %s non esiste oppure il percorso specificato non è corretto\n",path);
				break;
			case EACCES:
				printf("Permesso negato: non è possibile aprire il file %s in lettura\n",path);
				break;
			default:
				perror("Fatal error: ");
				break;
		}
	}
	return res;
}
