#include "processQfunc.h"

int main(int argc, char *argv[]){
  /*int *parte = atoi(argv[1]);
  int *denominatore = atoi(argv[2]);
  int *piperead = atoi(argv[3]);
  int *pipewrite = atoi(argv[4]);*/

  int fd = open("/home/giuseppe/prova.txt", O_RDONLY);
  char **format = computeCountingOnFile(fd,10,0);
  printFormatString(format);
  /*char **message;
  int p[2];
  pipe(p);

  if(fork()>0){
    close(p[0]);
    write(p[1],formato,strlen(formato)+1);
    printf("dati scritti... \n");
    close(p[1]);
  }
  else{
    close(p[1]);
    read(p[0],message,strlen(message)+1);
    close(p[0]);
  }*/

  return 0;
}
