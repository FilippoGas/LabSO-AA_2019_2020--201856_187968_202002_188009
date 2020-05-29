#include "./onTheFlyHandler.h"

int execChangeOnTheFly(int pipe_from_A, int m){
	char message[PIPE_BUF + 1];
	int byte = read(pipe_from_A, message, PIPE_BUF);
	if(byte > 0){
		//gestione cambi on the fly
	}

}
