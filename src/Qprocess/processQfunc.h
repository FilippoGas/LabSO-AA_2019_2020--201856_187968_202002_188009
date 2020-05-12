#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char **computeCountingOnFile(int fileDescriptor, int idFile, int offset);

int fileSize(int fileDescriptor);

void printFormatString(char **format);
