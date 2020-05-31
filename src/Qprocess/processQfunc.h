#include "../macro_libglob.h"


char *computeCountingOnFile(int fileDescriptor, int idFile, int offset, int end);

int fileSize(int fileDescriptor);

void printFormatString(char **format);

int computeOffset(int parte, int denominatore, int size);

int computeEnd(int parte, int denominatore, int size);

int computeSize(int fileDescriptor);

int openFile(char *name);

void readInput(int argc, char *argv[], int *parte, int *denominatore, int *pipeRead, int *pipeWrite, int *pipeReadOnTheFly, int *pipeWriteOnTheFly);

int isWrittenFile(int *writtenFiles,int idFile);

void addHandler(int pipeReadOnTheFly, int pipeWrite, int counterFilesOnTheFly, int parte, int denominatore, char *message);

void removeHandler(int pipeReadOnTheFly, int *removedFiles, int *writtenFiles, char *message, int argc, char *argv[]);

int idFile(char *file, int argc, char *argv[]);
