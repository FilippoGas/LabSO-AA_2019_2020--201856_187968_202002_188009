#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#define FIFO_NAME "/LabSO-AA_2019_2020--201856_187968_202002_188009/TestExe/Fifo/AtoR"

#define REPORT_FILE "/LabSO-AA_2019_2020--201856_187968_202002_188009/TestExe/Report/AtoR"

void writeToReport(int **data, char **file_list, int file_list_size, int fd);

int openFIFO();
