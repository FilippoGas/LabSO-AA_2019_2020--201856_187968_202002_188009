#include "../../macro_libglob.h"

void execChangeOnTheFly(int pipe_from_M, int n, int m, char ***p_argv_matrix, char ***files, int *nfiles, int *finished, int *n_files_for_P, int ***data);

int getModContent(int pipe_d, char ***content, int *realsize);

int *getNFilesForP(char ***p_argv_matrix, int n);

void removeFiles(char **mods, int nmods, char ***files, int *nfiles, int ***data, char ***p_argv_matrix, int *n_files_for_P, int *finished, int n, int m);

void removeFile(char *to_remove, char ***files, int nfiles, int ***data);

int findFile(char *in, char **files, int nfiles);