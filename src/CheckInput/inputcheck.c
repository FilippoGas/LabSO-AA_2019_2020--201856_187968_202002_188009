#include "inputcheck.h"

int typeOfArgument(char *value){
	int res;	
	if(value[0] == '-' && strlen(value) == 2)	
		res = COMMAND;
	else
		res = NOTCOMMAND;
	return res;
}

int typeOfCommand(char *value){
	int res = -1;
	if(strlen(value) == 2){
		if(value[1] == 'n')
			res = SETN;
		else if(value[1] == 'm')
			res = SETM;
		else if(value[1] == 'h')
			res = HELP;
		else if(value[1] == 'r')
			res = SETREC;
	}
	return res;
}

void optionN(int *n, char *value){
	(*n) = atoi(value);
	if((*n) < 1){
		fprintf(stderr, "n has to be a positive value, resetting default (n = 4)\n");
		(*n) = 4;
	}
}

void optionM(int *m, char *value){
	(*m) = atoi(value);
	if((*m) < 1){
		fprintf(stderr, "m has to be a positive value, resetting default (m = 3)\n");
		(*m) = 3;
	}
}

void changeNOrM(int type, int *n, int *m, char *value){
	if(type == SETN)
		optionN(n, value);
	else
		optionM(m, value);
}

int executeCommand(int type, int *n, int *m, int argc, int i, char *value, int *recursive){
	int res = 0;
	char errorFile[WSIZE] = MANPATH;
	strcat(errorFile, "analizer_usage.txt");
	char *args[] = {"more", errorFile, NULL};
	if(type == -1){
		fprintf(stderr, "Syntax error\n");
		if(execvp("/bin/more", args)){
			fprintf(stderr, "Cannot open man file %s\n", errorFile);
			exit(-1);
		}

	}
	else if(type == HELP){
		if(execvp("/bin/more", args)){	//fare in modo che continui esecuzione ?  Finezza controllare alla fine magari
			fprintf(stderr, "Cannot open man file %s\n", errorFile);
			exit(-1);
		}
	}
	else if(type == SETREC){
		(*recursive) = 1;
	}
	else{
		if(i == argc - 1){
			char *dummy = "0";
			changeNOrM(type, n, m, dummy);
		}
		else{
			changeNOrM(type, n, m, value);
			res = isNumber(value);
		}
	}
	return res;
}

int isNumber(char *value){
	int res = 1;
	int i = 1;
	if(value[0] == '-' || (value[0] <= '9' && value[0] >= '0'))
		while(i < strlen(value)){
			if(!(value[i] <= '9' && value[i] >= '0'))
				res = 0;
			i++;	
		}
	else
		res = 0;
	return res;

}

char **getNames(char *argv[], int *pos, int n){
	int i = 0;
	char **res = malloc(n * sizeof(char *));
	while(i < n){
		int j = pos[i];
		res[i] = malloc(sizeof(char) * WSIZE);
		strcpy(res[i], argv[j]);
		i++;
	}
	return res;
}

void readInput(int argc, char *argv[], char ***input, int *ninput, int *n, int *m, int *recursive){
	(*recursive) = 0;
	int i = 1;
	int pos[argc];
	(*ninput)= 0;
	while(i < argc){
		int type = typeOfArgument(argv[i]);
		if(type == COMMAND){
			int command = typeOfCommand(argv[i]);
			if(executeCommand(command, n, m, argc, i, argv[i + 1], recursive))
				i++;
		}	
		else{
			pos[(*ninput)] = i;
			(*ninput)++;
		}
		i++;
	}
	(*input) = getNames(argv, pos, *ninput);
}

void validateInput(char **input, int ninput, char ***files, char ***dirs, int *nfiles, int *ndirs){
	int file_pos[ninput], dir_pos[ninput];
	(*nfiles) = 0;
	(*ndirs) = 0;
	int i = 0;
	while(i < ninput){
		int type = inputType(input[i]);
		if(type == DIRECTORY){
			dir_pos[(*ndirs)] = i;
			(*ndirs)++;	
		}
		else if(type == FILES){
			file_pos[(*nfiles)] = i;
			(*nfiles)++;	
		}
		i++;
	}
	(*files) = getNames(input, file_pos, *nfiles);
	(*dirs) = getNames(input, dir_pos, *ndirs);
	freeStringArray(input, ninput);
}

int inputType(char *in){
	struct stat s;
	int res = stat(in, &s);
	
	if(res == -1){
		if(errno == ENOENT){
			fprintf(stderr, "Object %s doesn't, exist, ignored.\n", in);
		}
		else{
			perror("stat");
			exit(1);
		}
	}
	else{
		if(S_ISDIR(s.st_mode))
			res = DIRECTORY;
		else if(S_ISREG(s.st_mode))
			res = FILES;
		else{
			res = 10;
			fprintf(stderr, "Object %s is neither a file nor a directory, ignored.\n", in);
		}
	}
	return res;
}

void freeStringArray(char **in, int n){
	int i = 0;
	while(i < n){
		free(in[i]);
		i++;
	}
	free(in);
}

struct idfile getfile(char *in){
	char *abspath = realpath(in, NULL);
	char *path, *name;
	int i = strlen(abspath) - 1;
	while(abspath[i] != '/')
		i--;
	strncat(path, abspath, i);
	strcat(name, (abspath + i +1));
	struct idfile res;
	res.nomefile = name;
	res.pathfile = path;
	return res;

}
//ALLOCAZIONE DINAMICA DI TUTTO PORCO DIOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
void getfiles(char **file_list, int nfiles, struct idfile **files, int *filesize){
	int i = 0;
	(*filesize) = nfiles;
	(*files) = malloc((*filesize) * sizeof(struct idfile));
	while(i < nfiles){
		(*files)[i] = getfile(file_list[i]);
	}
}
