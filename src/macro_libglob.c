#include "macro_libglob.h"

int errorSysCall(int res){
	if(res == -1){
		perror("Error on syscall: ");
	}
	return res;
}
