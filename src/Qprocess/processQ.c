#include "processQfunc.h"
int main(int argc, char *argv[]){
  int parte, denominatore, pipeRead, pipeWrite;
  readInput(argc, argv, &parte, &denominatore, &pipeRead, &pipeWrite);
  close(pipeRead);

  //Salva i file descriptor in un array
  int i=0;
  while(i<argc - ARGS_Q_START_FILE_OFFSET){
    int fd  = openFile(argv[i + ARGS_Q_START_FILE_OFFSET]);
    int size = computeSize(fd);
  //Per ogni file vado a calcolarmi l'offset, l'end e la stringa formato che andrò a scrivere nella pipe
    int offset = computeOffset(parte,denominatore,size);
    int end = computeEnd(parte,denominatore,size);
    char *format = computeCountingOnFile(fd,i + ARGS_P_START_FILE_OFFSET,offset,end);	//mi serve indice
    //printf("Scrivo nella pipe: %s\n", format);
    //Scrivo nella pipe la stringa formato
    errorSysCall(write(pipeWrite,format, PIPE_BUF));
    //Stampo a video la stringa formato
    //printFormatString(format);
   errorSysCall(close(fd));
    free(format);
    i++;
  }
  errorSysCall(close(pipeWrite));
	//FREE INPUT DATA
  return 0;
}
