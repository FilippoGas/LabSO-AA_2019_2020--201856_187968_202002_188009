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
	char errorFile[PATH_MAX] = MANPATH;
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
		res[i] = malloc(sizeof(char) * (PATH_MAX + 1));
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

char **concatStringArray(char **first, char **second, int nfirst, int nsecond, int *resdim){
	(*resdim) = nfirst + nsecond;
	char **res = malloc((*resdim) * sizeof(char *));
	int i = 0;
	while(i < (*resdim)){
		res[i] = malloc((PATH_MAX + 1) * sizeof(char));
		if(i < nfirst)
			strcpy(res[i], first[i]);
		else
			strcpy(res[i], second[i-nfirst]);
		i++;
	} 
	return res;
}

char **initStringArray(int dimArray, int dimString){
	char **res = malloc(dimArray * sizeof(char *));
	int i = 0;
	while(i < dimArray){
		res[i] = calloc(dimString, sizeof(char));
		i++;
	}
	return res;
}

int isNotParOrSameDir(char *in){
	return strcmp(in, "..") && strcmp(in, ".");
}

int file_select(struct dirent   *entry) {
	if ((strcmp(entry->d_name, ".") == 0) ||(strcmp(entry->d_name, "..") == 0))
		 return 0;
	else
		return 1;
}


char **lsDir(char *dir, int rec, int *n){
	struct dirent **test;
	int sizedir = scandir(dir, &test, file_select, 0);		
	(*n) = sizedir;
	char **res = initStringArray((*n), PATH_MAX + 1);

	
	int i = 0;
	int j = 0;
	while(j < sizedir){
		char temp[PATH_MAX + 1];
		sprintf(temp, "%s%s", dir, test[j]->d_name);
		int type = inputType(temp);
		if(type == DIRECTORY && rec && isNotParOrSameDir(test[j]->d_name)){
			addSlashToDir(temp);	
			int tempdim, tempresdim = *n;
			char **newfiles = lsDir(temp, rec, &tempdim);
			char **tempres = concatStringArray(res, newfiles, tempresdim, tempdim, n);
			freeStringArray(res, tempresdim);
			res = tempres;
		}
		else  if(type == FILES){
			sprintf(res[i], "%s", temp);
			i++;
		}
		j++;	
	}
	return res;
}

void addSlashToDir(char *dir){
	int last = strlen(dir) - 1;
	if(dir[last] != '/'){
		dir[last + 1] = '/';
		dir[last + 2] = '\0';
	}
}

void addSlashToDirs(char **dirs, int ndirs){
	int i = 0;
	while(i < ndirs){
		addSlashToDir(dirs[i]);
		i++;
	}
}


char **getContentOfDirs(char **dirs, int ndirs, int rec, int *resdim){
	addSlashToDirs(dirs, ndirs);
	int i = 0;
	char **res = initStringArray(1, 1);
	(*resdim) = 1;
	while(i < ndirs){
		int ndir;
		char **dir_content = lsDir(dirs[i], rec, &ndir);
		int ntemp;
		int dimtemp = (*resdim);
		char **temp = concatStringArray(res, dir_content, *resdim, ndir, &ntemp);
		freeStringArray(res, dimtemp);
		freeStringArray(dir_content, ndir);
		res = temp;
		(*resdim) = ntemp;
		i++;
	}
	return res;
}

char **getAllFullPath(char **file_list, int nfiles, char **dir_content, int dir_content_size, int *res_dim){
	(*res_dim) = nfiles;
	int file_in_dir[dir_content_size];
	int i = 0;
	while(i < dir_content_size){
		if(strcmp(dir_content[i], "\0")){
			file_in_dir[(*res_dim) - nfiles] = i;
			(*res_dim)++;
		}
		i++;
	}
	char **res = initStringArray((*res_dim), PATH_MAX + 1);
	i = 0;
	while(i < nfiles){
		sprintf(res[i], "%s", realpath(file_list[i], NULL));
		i++;
	}
	while(i < (*res_dim)){
		sprintf(res[i], "%s", realpath(dir_content[file_in_dir[i - nfiles]], NULL));
		i++;
	}
	return res;
}

void getPathAndName(char *file, char **path, char **name){
	int j = strlen(file) - 1;
	while(file[j] != '/')
		j--;
	(*path) = calloc((j + 2),  sizeof(char));
	(*name) = calloc(((strlen(file) - j) + 1),  sizeof(char));
	strncat((*path), file, j + 1);
	strcat((*name), (file + j + 1));
}

struct idfile *initIdFile(char *path, char *name){
	struct idfile *res = malloc(sizeof(struct idfile *));
	res->name = malloc((strlen(name) + 1) * sizeof(char));
	sprintf(res->name, "%s", name);
	res->path = malloc((strlen(path) + 1) * sizeof(char));
	sprintf(res->path, "%s", path);
	return res;
}

struct idfile **polishFileList(char **file_list, int size){
	struct idfile **res = malloc(size * sizeof(struct idfile *));
	int i = 0; 
	while(i < size){
		char *path, *name;
		getPathAndName(file_list[i], &path, &name);
		res[i] = initIdFile(path, name);
		free(path);
		free(name);
		i++;
	}
	return res;
}

void freeIdFile(struct idfile *in){
	free(in->name);
	free(in->path);
	free(in);
}

void freeIdfileArray(struct idfile **in, int n){
	int i = 0;
	while(i < n){
		freeIdFile(in[i]);
		i++;
	}
	free(in);
}
int manageInput(char ***def_file_list, int argc, char *argv[],  int *m, int *n, int *recursive){
	int nfiles, ndirs, ninput;
	char **input, **dir_list, **file_list;
	readInput(argc, argv, &input, &ninput, n, m, recursive);

	validateInput(input, ninput, &file_list, &dir_list, &nfiles, &ndirs);
	int dir_content_size;
	char **dir_content = getContentOfDirs(dir_list, ndirs, *recursive, &dir_content_size);
	freeStringArray(dir_list, ndirs);
	int res;
	(*def_file_list) = getAllFullPath(file_list, nfiles, dir_content, dir_content_size, &res);
	freeStringArray(file_list, nfiles);
	freeStringArray(dir_content, dir_content_size);
	return res;
}
