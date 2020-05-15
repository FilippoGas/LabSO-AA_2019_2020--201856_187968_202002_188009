#include "processQfunc.h"
int main(int argc, char *argv[]){
  int parte = atoi(argv[1]);
  int denominatore = atoi(argv[2]);
  int pipeRead = atoi(argv[3]);
  int pipeWrite = atoi(argv[4]);
  int fileDescriptors[argc - ARGS_Q_START_FILE_OFFSET];
  int sizes[argc - ARGS_Q_START_FILE_OFFSET];

  //Salva i file descriptor in un array
  int i=0;
  while(i<argc - ARGS_Q_START_FILE_OFFSET){
    char test[PATH_MAX + 1];
    strncpy(test, argv[i + ARGS_Q_START_FILE_OFFSET], strlen(argv[i + ARGS_Q_START_FILE_OFFSET]) - 1); //NON SO COSA METTE ALLA FINE
    printf("\ntest: %sx\n",test);
    fileDescriptors[i] = errorOpenInQ(open(test,O_RDONLY),test);
    sizes[i] = computeSize(fileDescriptors[i]);
    i++;
  }
  //Per ogni file vado a calcolarmi l'offset, l'end e la stringa formato che andrò a scrivere nella pipe
  i = 0;
  errorSysCall(close(pipeRead));
  while(i<argc - ARGS_Q_START_FILE_OFFSET){
    int offset = computeOffset(parte,denominatore,sizes[i]);
    int end = computeEnd(parte,denominatore,sizes[i]);
    char *format = computeCountingOnFile(fileDescriptors[i],i + ARGS_P_START_FILE_OFFSET,offset,end);	//mi serve indice
    //Scrivo nella pipe la stringa formato
    errorSysCall(write(pipeWrite,format, PIPE_BUF));
    //Stampo a video la stringa formato
    //printFormatString(format);
    errorSysCall(close(fileDescriptors[i]));
    i++;
  }
  char endm[PIPE_BUF];
  sprintf(endm, "%s", END);
  errorSysCall(write(pipeWrite, endm, PIPE_BUF));
  errorSysCall(close(pipeWrite));

  return 0;
}
