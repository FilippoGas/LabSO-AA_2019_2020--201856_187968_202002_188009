#include "processQfunc.h"

int main(int argc, char *argv[]){
  signal(SIGTERM, SIG_DFL);
  char **argv1 = calloc(argc + 1, sizeof(char *));
  int z = 0;
  while(z < argc){
  	argv1[z] = calloc(strlen(argv[z]) + 1, sizeof(char));
	sprintf(argv1[z], "%s", argv[z]);
	z++;
  }
  argv1[z] = NULL;

  int parte, denominatore, pipeRead, pipeWrite, pipeReadOnTheFly, pipeWriteOnTheFly;
  int *writtenFiles = (int *)calloc(argc-ARGS_Q_START_FILE_OFFSET,sizeof(int));
  int *removedFiles = (int *)calloc(argc-ARGS_Q_START_FILE_OFFSET,sizeof(int));
  char message[PIPE_BUF+1]="";
  readInput(argc, argv1, &parte, &denominatore, &pipeRead, &pipeWrite, &pipeReadOnTheFly, &pipeWriteOnTheFly);

  printf("\n");
  close(pipeRead);
  //Salva i file descriptor in un array
  int i=0;
  //sleep(3);
  while(i<argc - ARGS_Q_START_FILE_OFFSET){
	  int z = 0;
	  printf("DEVO STAMPARE LA RIGA, argc vale %d\n", argc);
	  while(z < argc){
	  	printf("\t %s", argv1[z]);
		z++;
	  }
	  printf("\n");
    //CONTROLLER SULLA PIPE DEI MESSAGGI DA P
    int byteRead = read(pipeReadOnTheFly,message,PIPE_BUF);
    if(byteRead>0){
      printf("%s\n",message);
      if(!strcmp(message,MOD_ADD)){
        addHandler(pipeReadOnTheFly,pipeWrite,parte,denominatore,message,&argc,&argv1);
        writtenFiles = realloc(writtenFiles,argc*sizeof(int));
        removedFiles = realloc(removedFiles,argc*sizeof(int));
      }
      else if(!strcmp(message,MOD_REMOVE)){
        removeHandler(pipeReadOnTheFly,removedFiles,writtenFiles,message,argc,argv1);
      }
      strcpy(message,"");
    }

    if(!removedFiles[i]){
	    int fd  = openFile(argv1[i + ARGS_Q_START_FILE_OFFSET]);
      int size = computeSize(fd);
      //Per ogni file vado a calcolarmi l'offset, l'end e la stringa formato che andrò a scrivere nella pipe
      int offset = computeOffset(parte,denominatore,size);
      int end = computeEnd(parte,denominatore,size);
      char *format = computeCountingOnFile(fd,i + ARGS_P_START_FILE_OFFSET,offset,end);	//mi serve indice
      //printf("Scrivo nella pipe: %s\n", format);
      //Scrivo nella pipe la stringa formato
      //if(!removedFiles[i]){
      if(errorSysCall(write(pipeWrite,format, PIPE_BUF))>-1){
	      writtenFiles[i] = 1;
      }
      errorSysCall(close(fd));
      free(format);
    }
    //Stampo a video la stringa formato
    //printFormatString(format);

    i++;
  }
  errorSysCall(close(pipeWrite));
  free(writtenFiles);
  free(removedFiles);
	//FREE INPUT DATA
  return 0;
}
