#include "./onTheFlyHandler.h"

int getModContent(int pipe_d, char ***content, int *realsize){
	int size = 10;
	(*content) = (char **)malloc(size * sizeof(char *));
	int i = 0;
	int byte = -1;
	do{
		char message[PIPE_BUF + 1] = "";
		byte = read(pipe_d, message, PIPE_BUF);
		if(byte > 0){
			(*content)[i] = (char *)calloc((PIPE_BUF + 1), sizeof(char));
			sprintf((*content)[i], "%s", message);
			i++;
			if(i >= size){
				size *= 2;
				(*content) = realloc((*content), size * sizeof(char *));
			}
		}
	}while(strcmp(MOD_END, (*content)[i-1]) && byte != 0);
	(*realsize) = size;
	return i - 1;
}



int execChangeOnTheFly(int pipe_from_A, int m, int **pipe_control_for_Q){
	char mod_type[PIPE_BUF + 1] = "";
	int byte = read(pipe_from_A, mod_type, PIPE_BUF);
	if(byte > 0){
		char **mods;
		int realsize;
		int nmods = getModContent(pipe_from_A, &mods, &realsize);
		if(!strcmp(mod_type, MOD_ADD)){
			addFiles(mods, nmods, pipe_control_for_Q, m);
		}
		else if(!strcmp(mod_type, MOD_REMOVE)){
			removeFiles(mods, nmods, pipe_control_for_Q, m);
		}
		else{
			fprintf(stderr, "Cannot recognize modifiyng command\n");
		}
		//gestione cambi on the fly
	}

}

void removeFiles(char **mods, int nmods, int **pipe_control_for_Q, int m){
	relayMod(mods, nmods, pipe_control_for_Q, m, MOD_REMOVE);
}

void addFiles(char **mods, int nmods, int **pipe_control_for_Q, int m){
	relayMod(mods, nmods, pipe_control_for_Q, m, MOD_ADD);
}


void relayMod(char **mods, int nmods, int **pipe_control_for_Q, int m, char *type){
	int i = 0;
	while(i < m){
		int out = write(pipe_control_for_Q[i][WRITE], type, strlen(type));
		//perror("");
		if(out>0)
		i++;
	}
	i = 0;
	while(i < nmods){
		int j = 0;
		while(j < m){
			int out = write(pipe_control_for_Q[j][WRITE], mods[i], strlen(mods[i]));
			//perror("");
			if(out>0)
			j++;
		}
		i++;
	}
	i = 0;
	while(i < m){
		int  out = write(pipe_control_for_Q[i][WRITE], MOD_END, strlen(MOD_END));
		//perror("");
		if(out>0)
		i++;
	}
}
