#include"processPfunc.h"




//conto le cofre di un numero intero
int cifre_int(int n){
        int i=0;
        if(i!=0){
                while(n/10!=0)
                i++;
                return i;
                }
        else return 1;
}



int lettura_numero(char **str_in){
        char *temp = strchr(*str_in,' ');

        if(( (long) temp ) == 0){
                return atoi(*str_in);
        }

        int ntemp = (int)(temp - *str_in);
        char numero[ntemp+1];

        strncpy(numero, *str_in, ntemp);
        *str_in=temp+1;
        numero[ntemp]='\0';
        return atoi(numero);
}



int main(int argc, char *argv[]){
	printf("Sono Q e mi hanno creato\n");
	char *mess="13 89 14 32 \n";
	int i=0;
	int pipe_write=atoi(argv[4]);
	int pipe_read=atoi(argv[3]);
	close(pipe_read);
	printf("mando mess\n");
	write(pipe_write,mess,80);
	printf("mando %s\n",ENDQ);
	write(pipe_write,ENDQ,30);
	return 0;
}
