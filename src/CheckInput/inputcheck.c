#include "inputcheck.h"

int typeOfArgument(char *value){
	int res;
	if(value[0] == '-')
		res = COMMAND;
	else if(value[strlen(value) - 1] == '/')
		res = DIRS;
	else
		res = FILES;
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

int executeCommand(int type, int *n, int *m, int argc, int i, char *value){
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
		execvp("/bin/more", args);
		{
			fprintf(stderr, "Cannot open man file %s\n", errorFile);
			char *argstest[] = {"ls"};
			execvp("/bin/ls", argstest);
			exit(-1);
		}
	}
	else{
		if(i == argc){
			char dummy[2] = "0";
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

void readInput(int argc, char *argv[], char ***files, char ***dirs, int *nfiles, int *ndir, int *n, int *m){
	int i = 1;
	int pos_files[argc];
	int pos_dir[argc];
	(*nfiles) = 0;
	(*ndir) = 0;
	while(i < argc){
		int type = typeOfArgument(argv[i]);
		if(type == COMMAND){
			int command = typeOfCommand(argv[i]);
			if(executeCommand(command, n, m, argc, i, argv[i + 1]))
				i++;
		}	
		else if(type == DIRS){
			pos_dir[(*ndir)] = i;
			(*ndir)++;
		}
		else if(type == FILES){
			pos_files[(*nfiles)] = i;
			(*nfiles)++;
		}
		i++;
	}
	*files = getNames(argv, pos_files, *nfiles);
	*dirs = getNames(argv, pos_dir, *ndir);
}

