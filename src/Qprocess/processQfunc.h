#include "../macro_libglob.h"


char *computeCountingOnFile(int fileDescriptor, int idFile, int offset, int end);

int fileSize(int fileDescriptor);

void printFormatString(char **format);

int computeOffset(int parte, int denominatore, int size);

int computeEnd(int parte, int denominatore, int size);

int computeSize(int fileDescriptor);
