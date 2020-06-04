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
		if(!strcmp(mod_type, MOD_REMOVE)){
			printf("DEVO TOGLIERE FILE\n");
			removeFiles(mods, nmods, files, nfiles, data, p_argv_matrix, n_files_for_P, finished, n, m);
		}
		else if(!strcmp(mod_type, MOD_ADD)){
			printf("DEVO AGGIUNGERE FILE\n");
			addFiles(mods, nmods, files, nfiles, data, p_argv_matrix, n_files_for_P, n);
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

void addFiles(char **mods, int nmods, char ***files, int *nfiles, int ***data, char ***p_argv_matrix, int *n_files_for_P, int n){
	int i = 0;
	int *stopped = (int *)calloc(n, sizeof(int));

	while(i < nmods){
		int index_P_min = findPMinFile(n_files_for_P, n);
		if(!stopped[index_P_min]){
			write((*p_argv_matrix)[index_P_min][PIPE_CONTROL_WRITE_IN_P], MOD_ADD, strlen(MOD_ADD));
			i++;
		}
		write((*p_argv_matrix)[index_P_min][PIPE_CONTROL_WRITE_IN_P], mods[i], strlen(mods[i]));
		n_files_for_P[index_P_min]++;
		addFileToPArgv(p_argv_matrix + index_P_min, mods[i]);
		addToFiles(files, nfiles, data, mods[i]);
		i++;
	}
	i = 0;
	while(i < n){
		if(stopped[i]){
			write((*p_argv_matrix)[i][PIPE_CONTROL_WRITE_IN_P], MOD_END, strlen(MOD_END));	
		}
		i++;
	}

}

int findPMinFile(int *n_files_for_P, int n){
	int res = 0, min = INT_MAX;
	int i = 0;
	while(i < n){
		if(n_files_for_P[i] < min){
			res = i;
			min = n_files_for_P[i];
		}
		i++;
	}
	return res;
}
void addFileToPArgv(char ***p_argv, char *name){
	int i = ARGS_P_START_FILE_OFFSET;
	while((*p_argv)[i] != NULL)
		i++;
	(*p_argv) = (char **)realloc((*p_argv), (i + 2) * sizeof(char *));
	(*p_argv)[i] = (char *)calloc(PATH_MAX + 1, sizeof(char)); 
	sprintf((*p_argv)[i], "%s", name);
	(*p_argv[i + 1]) = NULL;
}

void addToFiles(char ***files, int *nfiles, int ***data, char *name){
	(*files) = (char **)realloc((*files), ((*nfiles) + 1) * sizeof(char *));
	(*files)[*nfiles] = (char *)calloc(PATH_MAX + 1, sizeof(char));
	sprintf((*files)[*nfiles], "%s", name);
	(*data) = (int **)realloc((*data), ((*nfiles) + 1) * sizeof(int *));
	(*data)[*nfiles] = (int *)calloc(ALPHABET_SIZE, sizeof(int));
	(*nfiles)++;
}

int dataEmpty(int *data){
	int i = 0;
	while(i < ALPHABET_SIZE){
		if(data[i] != 0)
			return 1;
		i++;
	}
	return 0;
}


int getFileMissingData(char **def_file_list, int def_file_list_size, int **data, char ***file_list){
	int i = 0;
	int res = 0;
	(*file_list) = (char **)calloc(def_file_list_size, sizeof(char *));
	while(i < def_file_list_size){
		if(dataEmpty(data[i])){
			(*file_list)[res] = (char *)calloc(strlen(def_file_list[i]) + 1, sizeof(char));
			sprintf((*file_list)[res], "%s", def_file_list[i]);
			res++;
		}
		i++;
	}
	return res;
}
