#include "processQfunc.h"
//Per ora legge tutto il file
//Effettua il conteggio dei caratteri del file e ritorna la stringa formato
char *computeCountingOnFile(int fileDescriptor, int idFile, int offset, int end){
  int *ASCII = (int *)calloc(ALPHABET_SIZE, sizeof(int));
  char carattere[1];
  char *datiParziali = (char *)calloc(PIPE_BUF + 1,  sizeof(char*));

  errorSysCall(lseek(fileDescriptor,offset,SEEK_SET));
  int counterChar = 0;
  while(errorSysCall(read(fileDescriptor,carattere,1)) && counterChar<(end-offset)){
    int ascii = (int)(carattere[0]);
    ASCII[ascii]++;
    counterChar++;
  }
  sprintf(datiParziali,"%d ",idFile);
  int i=0;
  while(i< ALPHABET_SIZE){
    sprintf(datiParziali,"%s %d ", datiParziali, ASCII[i]);
    i++;
  }
  sprintf(datiParziali, "%s\n", datiParziali);
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
	int offset = ((double)(parte)/((double)denominatore)*size);
  return offset;
}

//Calcola la posizione dell'ultimo carattere che Q non deve leggere
int computeEnd(int parte, int denominatore, int size){
  int termine;
  if(parte<denominatore){
    termine = ((double)(parte + 1)/((double)denominatore)*size); //MODIFICATO
  }else{
    termine = size;
  }
  return termine;
}

//Calcola la dimensione del file
int computeSize(int fileDescriptor){
	 return errorSysCall(lseek(fileDescriptor,0,SEEK_END));
}

void readInput(int argc, char *argv[], int *parte, int *denominatore, int *pipeRead, int *pipeWrite){
	(*parte) = atoi(argv[1]);
  (*denominatore) = atoi(argv[2]);
  (*pipeRead) = atoi(argv[3]);
  (*pipeWrite) = atoi(argv[4]);
}

int openFile(char *name){
	int last = strlen(name) - 1;
	char temp[PATH_MAX + 1] = "";
	strncpy(temp, name, last);
	return errorOpenInQ(open(temp, O_RDONLY), temp);
}
