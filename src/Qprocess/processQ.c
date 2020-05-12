#include "processQfunc.h"

int main(int argc, char *argv[]){
  int parte = atoi(argv[1]);
  int denominatore = atoi(argv[2]);
  int pipeRead = atoi(argv[3]);
  int pipeWrite = atoi(argv[4]);
  int fileDescriptors[argc-5];
  int sizes[argc-5];

  //Salva i file descriptor in un array
  int i=0;
  while(i<argc-5){
    fileDescriptors[i] = open(argv[i+5],O_RDONLY);
    sizes[i] = computeSize(fileDescriptors[i]);
    i++;
  }

  //Per ogni file vado a calcolarmi l'offset, l'end e la stringa formato che andrò a scrivere nella pipe
  i=0;
  while(i<argc-5){
    int offset = computeOffset(parte,denominatore,sizes[i]);
    int end = computeEnd(parte,denominatore,sizes[i]);
    char **format = computeCountingOnFile(fileDescriptors[i],i+5,offset,end);

    //Scrivo nella pipe la stringa formato
    close(pipeRead);
    write(pipeWrite,format,MAX_LENGTH_FORMAT);

    //Stampo a video la stringa formato
    //printFormatString(format);
    close(fileDescriptors[i]);
    i++;
  }
  close(pipeWrite);

  //CODICE DI TEST DI Q

  /*int offset, end, size;

  int fd = open("/home/giuseppe/prova1.txt", O_RDONLY);
  printf("%ld \n",sizeof(int));
  size = computeSize(fd);
  offset = computeOffset(parte,denominatore,size);
  end = computeEnd(parte,denominatore,size);
  printf("%d %d \n",offset, end);
  char **format = computeCountingOnFile(fd,10,offset,end);
  printFormatString(format);

  //simulo la comunicazione unidirezionale tra q e p
  char **msg=(char **)malloc(259*sizeof(char*));
  int i=0;
  while(i<258){
    msg[i] = (char *)malloc(10*sizeof(char));
    i++;
  }
  int p[2];
  pipe(p);
  if(fork()>0){
    close(p[0]);
    write(p[1],format,2590);
    printf("Sto scrivendo... \n");
    close(p[1]);
  }
  else{
    close(p[1]);
    int bRead=read(p[0],msg,2590);
    printf("Ho letto %d byte\n",bRead);
    printFormatString(msg);
    printf("\n");
    close(p[0]);
  }*/

  return 0;
}
