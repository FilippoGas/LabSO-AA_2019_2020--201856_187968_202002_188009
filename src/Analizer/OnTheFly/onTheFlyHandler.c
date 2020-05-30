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



void execChangeOnTheFly(int pipe_from_M, int n, int m, char ***p_argv_matrix, char ***files, int *nfiles, int *finished, int *n_files_for_P, int ***data){
	char mod_type[PIPE_BUF + 1];
	int byte = read(pipe_from_M, mod_type, PIPE_BUF);
	if(byte > 0){
		char **mods;
		int realsize;
		int nmods = getModContent(pipe_from_M, &mods, &realsize);
		if(!strcmp(mod_type, MOD_ADD)){
			printf("DEVO AGGIUNGERE FILE\n");
			removeFiles(mods, nmods, files, nfiles, data, p_argv_matrix, n_files_for_P, finished, n, m);
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
		freeModContent(mods, nmods); //DA CONTROLLARE SE CI VA REALSIZE O NMODS + 1
	}
}

int *getNFilesForP(char ***p_argv_matrix, int n){
	int *res = (int *)calloc(n, sizeof(int));
	int i = 0;
	while(i < n){
		int j = ARGS_P_START_FILE_OFFSET;
		while(p_argv_matrix[i][j] != NULL){
			res[i]++;
			j++;
		}
		i++;
	}
	return res;
}

void removeFiles(char **mods, int nmods, char ***files, int *nfiles, int ***data, char ***p_argv_matrix, int *n_files_for_P, int *finished, int n, int m){
	int i = 0;
	int *stopped = (int *)calloc(n, sizeof(int));
	int *pipes = (int *)calloc(n, sizeof(int));
	while(i < nmods){
		removeFile(mods[i], files, *nfiles, data);
		int index = getPWithFile(p_argv_matrix, n, mods[i], pipes);
		if(notFinished(n_files_for_P[index], finished[index], m)){
			if(!stopped[index]){
				write(pipes[index], MOD_REMOVE, strlen(MOD_REMOVE));
				stopped[index] = 1;
			}
			write(pipes[index], mods[i], strlen(mods[i]));
		}
		(*nfiles)--;
		i++;
	}
	i = 0;
	while(i < n){
		if(notFinished(n_files_for_P[i], finished[i], m)){
			if(stopped[i]){
				write(pipes[i], MOD_END, strlen(MOD_END));
			}
		}
		i++;
	}
	free(pipes);
	free(stopped);
}

void removeFile(char *to_remove, char ***files, int nfiles, int ***data){
	int i = findFile(to_remove, *files, nfiles);
	int j = i;
	if(i != -1){
		free(files[i]);
		free(data[i]);
		while(j < nfiles - 1){
			(*files[i]) = (*files)[i + 1];
			(*data[i]) = (*data)[i + 1];
		}
		(*files)[nfiles - 1] = NULL;
		(*data)[nfiles - 1] = NULL;
		(*files) = (char **)realloc((*files), (nfiles * sizeof(char *)) - sizeof(char *));
		(*data) = (int **)realloc((*data), (nfiles * sizeof(int *)) - sizeof(int *));
	}
	else{
		fprintf(stderr, "Cannot find file to remove\n");
	}

}

int findFile(char *in, char **files, int nfiles){
	int i = 0;
	int res = -1;
	while(i < nfiles){
		if(!strcmp(in, files[i])){
			res = i;
		}
		i++;
	}
	return i;
}

int getPWithFile(char ***p_argv_matrix, int n, char *in, int *pipe){
	int res = -1;
	int i = 0;
	while(i < n){
		int j = 0; 
		while(p_argv_matrix[i][j] != NULL){
			if(!strcmp(p_argv_matrix[i][j], in)){
				res = i;
				pipe[i] = atoi(p_argv_matrix[i][PIPE_CONTROL_WRITE_IN_P]);
			}
			j++;
		}
		i++;
	}
	return res;
}

int notFinished(int nfiles, int value, int m){
	return (nfiles * m) <= value;
}

