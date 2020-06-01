#include "../../macro_libglob.h"

int execChangeOnTheFly(int pipe_from_A, int m, int **pipe_control_for_Q);

int getModContent(int pipe_d, char ***content, int *realsize);

void removeFiles(char **mods, int nmods, int **pipe_control_for_Q, int m);

void addFiles(char **mods, int nmods, int **pipe_control_for_Q, int m);

void relayMod(char **mods, int nmods, int **pipe_control_for_Q, int m, char *type);
