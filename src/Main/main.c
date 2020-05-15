#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<limits.h>
#define AZIONI 3
#define AANAL 5


void printOptions(){
	int i=0;
	printf("\nAZIONI:\n");
	char *laz[AZIONI]={"Analazer Menu'", "Reporter", "Lista Azioni"};
	for(i=0;i<AZIONI; i++){
		printf("%d. %s\n",i+1,laz[i]);
	}
	printf("q/quit/exit  EXIT\n");
}



void printOpAnal(){
	int i=0;
	char *lazAnal[AANAL]={"Iniziare Analazer","Aggiungere cartella","Impostare ricorsione su cartelle", "Impostare m", "Impostare n"};
	printf("\nANALIZER:\n");
	printf("AZIONI:\n");
	for(i=0;i<AANAL;i++){
		printf("%d. %s\n",i+1,lazAnal[i]);
	}
	printf("q/quit/exit  EXIT\n");
}


void enterAnalMenu(){
	char **exrcAnal;

	printOpAnal();


}

void startReporter(){
	printf("Faccio partire il reporter\n");
	int f=fork();
	while(f<0)
		f=fork();
	if(f==0){
		execp("./TestArea/report");
	}
	int status;
	wait(f,&status,0);
}

void ending(){
	printf("Grazie per aver utilizzato il programma di analisi di GGEF&co.\n");
	printf("Arrivederci e buona giornata.\n\n");
	exit(0);
}


char *getIn(){
	int i=1;
	char *ret=malloc(1);
	char car_in=getc(stdin);
	ret[0]='\0';
	while(car_in != '\n'){
		i++;
		char tmp[i];
		strcpy(tmp,ret);
		tmp[i-2]=car_in;
		tmp[i-1]='\0';
		free(ret);
		ret=malloc(i);
		strcpy(ret,tmp);
		car_in=getc(stdin);
        }
        return ret;
}



int main(){
	printf("Grazie per aver scelto il programma di analisi dati di GGEF&co.\n\n");
	sleep(1);
	printf("Con che azione volete cominciare?\n");
	printOptions();

	int option;
	while(option >= 0){
		char *input=getIn();
		option=atoi(input);
		if(!(strcmp(input,"q")&&strcmp(input,"quit")&&strcmp(input,"exit"))){
			free(input);
			ending();
		}
		free(input);
		printf("\n");
		switch(option){
			case 1:
				enterAnalMenu();
				printf("Siete nel menu' principale.\n");
			case 3:
				printOptions();
				break;

			case 2:
				startReporter();
				printf("Siete nel menu' principale.\n");
				printOptions();
				break;
			default:
				printf("L'opzione inserita non e' valida\n\n");
				printf("Prego digitare il numero di un azione in elenco:\n\n");
				printOptions();
				option=0;
		}
	}
	return 0;
}
