#include "processQfunc.h"

//Per ora legge tutto il file
//Effettua il conteggio dei caratteri del file e ritorna la stringa formato
char **computeCountingOnFile(int fileDescriptor, int idFile, int offset){
  char *ASCII = (char *)calloc(256,sizeof(char));
  char *carattere = (char*)malloc(sizeof(char));
  char **datiParziali = (char **)malloc(258*sizeof(char*));

  lseek(fileDescriptor,offset,SEEK_SET);
  while(read(fileDescriptor,carattere,1)){
    int ascii = (int)(carattere[0]);
    ASCII[ascii]++;
  }

  datiParziali[0]=(char *)malloc(10*sizeof(char));
  sprintf(datiParziali[0],"%d ",idFile);
  int i=1;
  while(i<257){
    datiParziali[i]=(char *)malloc(10*sizeof(char));
    sprintf(datiParziali[i],"%d ",ASCII[i-1]);
    i++;
  }
  datiParziali[257]=(char *)malloc(10*sizeof(char));
  sprintf(datiParziali[257],"\n");

  return datiParziali;
}

//Ritorna la dimensione del file
int fileSize(int fileDescriptor){
  char *carattere = (char*)malloc(sizeof(char));
  int count=0;
  while(read(fileDescriptor,carattere,1)){
    count++;
  }
  return count;
}

//Stampa la stringa formato
void printFormatString(char **format){
  int i=0;
  while(i<258){
    printf("%s",format[i]);
    i++;
  }
}
