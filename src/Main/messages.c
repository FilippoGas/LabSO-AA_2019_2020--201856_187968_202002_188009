#include"messages.h"

void sms_addfile(char *file,int pipe[2]){
  printf("prima del write\n" );
  write(pipe[WRITE],MOD_ADD,PIPE_BUF);
  perror("\t");
  printf("Dopo il write\n" );
  write(pipe[WRITE],file,PIPE_BUF);
  sms_endmessage(pipe);
}

void sms_rmfile(char *file,int pipe[2]){
  write(pipe[WRITE],MOD_REMOVE,PIPE_BUF);
  write(pipe[WRITE],file,PIPE_BUF);
  sms_endmessage(pipe);
}
void sms_change_mn(char *num,char selec,int pipe[2]){
  if(selec=='m'){
    write(pipe[WRITE],MOD_CHANGE_M,PIPE_BUF);
  }
  else if(selec == 'n'){
    write(pipe[WRITE],MOD_CHANGE_N,PIPE_BUF);
  }
  else{
    exit(-1);
  }
  write(pipe[WRITE],num,PIPE_BUF);
  sms_endmessage(pipe);

}
void sms_endmessage(int pipe[2]){
  write(pipe[WRITE],MOD_END,PIPE_BUF);
}
