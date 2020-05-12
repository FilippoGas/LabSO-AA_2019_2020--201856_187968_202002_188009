#include "processQfunc.h"

//Per ora legge tutto il file
//Effettua il conteggio dei caratteri del file e ritorna la stringa formato
char **computeCountingOnFile(int fileDescriptor, int idFile, int offset, int end){
  int *ASCII = (int *)calloc(256,sizeof(int));
  char *carattere = (char*)malloc(sizeof(char));
  char **datiParziali = (char **)malloc(258*sizeof(char*));

  lseek(fileDescriptor,offset,SEEK_SET);
  int counterChar = 0;
  while(read(fileDescriptor,carattere,1) && counterChar<(end-offset)){
    int ascii = (int)(carattere[0]);
    ASCII[ascii]++;
    counterChar++;
  }
  free(carattere);
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
  free(ASCII);

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

//Calcola l'offset
int computeOffset(int parte, int denominatore, int size){
  int offset = ((double)(parte-1)/((double)denominatore)*size);
  return offset;
}

//Calcola la posizione dell'ultimo carattere che Q non deve leggere
int computeEnd(int parte, int denominatore, int size){
  int termine;
  if(parte<denominatore){
    termine = ((double)(parte)/((double)denominatore)*size);
  }else{
    termine = size;
  }
  return termine;
}

//Calcola la dimensione del file
int computeSize(int fileDescriptor){
  return lseek(fileDescriptor,0,SEEK_END);
}
