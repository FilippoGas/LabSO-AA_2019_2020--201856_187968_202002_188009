#include "./onTheFlyHandler.h"

int getModContent(int pipe_d, char ***content, int *realsize){
	int size = 10;
	(*content) = (char **)malloc(size * sizeof(char *));
	int i = 0;
	int byte = -1;
	printf("SONO P E HO LETTO I DATI IN ARRIVO\n");
	do{
		char message[PIPE_BUF + 1] = "";
		byte = read(pipe_d, message, PIPE_BUF);
		if(byte > 0){
			printf("BYTE LETTI: %d",byte);
			printf("%s\n",message);
			(*content)[i] = (char *)calloc((PIPE_BUF + 1), sizeof(char));
			sprintf((*content)[i], "%s", message);
			i++;
			if(i >= size){
				size *= 2;
				(*content) = realloc((*content), size * sizeof(char *));
			}
			printf("%s\n",(*content)[i-1]);
		}
	}while(strcmp(MOD_END, (*content)[i-1]) && byte != 0);
	printf("HO FINITO DI LEGGERE IL CASINO\n");
	(*realsize) = size;
	return i - 1;
}



int execChangeOnTheFly(int pipe_from_A, int m, int **pipe_control_for_Q){
	char mod_type[PIPE_BUF + 1] = "";
	int byte = read(pipe_from_A, mod_type, PIPE_BUF);
	if(byte > 0){
		printf("SONO P E MI SONO ARRIVATI I COMANDI DI CAMBIO \n");
		char **mods;
		int realsize;
		int nmods = getModContent(pipe_from_A, &mods, &realsize);
		if(!strcmp(mod_type, MOD_ADD)){
			printf("DEVO AGGIUNGERE FILE\n");
			addFiles(mods, nmods, pipe_control_for_Q, m);
		}
		else if(!strcmp(mod_type, MOD_REMOVE)){
			printf("DEVO TOGLIERE FILE\n");
			removeFiles(mods, nmods, pipe_control_for_Q, m);
		}
		else if(!strcmp(mod_type, MOD_CHANGE_M)){
			printf("DEVO CAMBIARE M\n");
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
		printf("\t%d\n",pipe_control_for_Q[i][WRITE]);
		//perror("");
		if(out>0)
			printf("TYPE VALE: %s\n",type);
		printf("%d\n", pipe_control_for_Q[i][WRITE]);
		i++;
	}
	i = 0;
	while(i < nmods){
		int j = 0;
		while(j < m){
			int out = write(pipe_control_for_Q[j][WRITE], mods[i], strlen(mods[i]));
			printf("\t%d\n",pipe_control_for_Q[j][WRITE]);
			//perror("");
			if(out>0)
				printf("MODS[I] VALE: %s\n",mods[i]);
			j++;
		}
		i++;
	}
	i = 0;
	while(i < m){
		int  out = write(pipe_control_for_Q[i][WRITE], MOD_END, strlen(MOD_END));
		//perror("");
		printf("\t%d\n",pipe_control_for_Q[i][WRITE]);
		if(out>0)
			printf("MESSAGGIO DI FINE: %s\n",MOD_END);
		i++;
	}
}
