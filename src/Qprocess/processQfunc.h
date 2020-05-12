#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_LENGTH_FORMAT 2590

char **computeCountingOnFile(int fileDescriptor, int idFile, int offset, int end);

int fileSize(int fileDescriptor);

void printFormatString(char **format);

int computeOffset(int parte, int denominatore, int size);

int computeEnd(int parte, int denominatore, int size);

int computeSize(int fileDescriptor);
