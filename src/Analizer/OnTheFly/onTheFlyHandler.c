#include "onTheFlyHandler.h"

void execChangeOnTheFly(int pipe_from_M, int n){
	char *message[PIPE_BUF + 1];
	int byte = read(pipe_from_M, message, PIPE_BUF);
	if(byte > 0){
		//HANDLE ON THE FLY MOD
	}
}
