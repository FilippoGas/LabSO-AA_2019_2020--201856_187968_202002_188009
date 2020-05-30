#include "onTheFlyHandler.h"

int getModContent(int pipe_d, char ***content, int *realsize){
	int size = 10;
	(*content) = (char **)malloc(size * sizeof(char *));
	int i = 0;
	int byte = -1;
	do{
		char message[PIPE_BUF + 1];
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
	}while(strcmp(MOD_END, (*content)[i]) && byte != 0);
	(*realsize) = size;
	return i - 1;
}

void freeModContent(char **content, int size){
	int i = 0;
	while(i < size){
		free(content[i]);
		i++;
	}
	free(content);
}



void execChangeOnTheFly(int pipe_from_M, int n){
	char mod_type[PIPE_BUF + 1];
	int byte = read(pipe_from_M, mod_type, PIPE_BUF);
	if(byte > 0){
		char **mods;
		int realsize;
		int nmods = getModContent(pipe_from_M, &mods, &realsize);
		if(!strcmp(mod_type, MOD_ADD)){
			printf("DEVO AGGIUNGERE FILE\n");
		}
		else if(!strcmp(mod_type, MOD_REMOVE)){
			printf("DEVO TOGLIERE FILE\n");
		}
		else if(!strcmp(mod_type, MOD_CHANGE_M)){
			printf("DEVO CAMBIARE M\n");
		}
		else if(!strcmp(mod_type, MOD_CHANGE_N)){
			printf("DEVO CAMBIARE N\n");
		}
		else{
			fprintf(stderr, "I cannot recognize mod command %s\n", mod_type);
		}
		freeModContent(mods, realsize); //DA CONTROLLARE SE CI VA REALSIZE O NMODS + 1
	}
}


