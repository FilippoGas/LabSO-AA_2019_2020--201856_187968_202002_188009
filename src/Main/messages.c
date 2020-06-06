#include"messages.h"

void sms_addfile(char *file,int pipe[2]){
  write(pipe[WRITE],MOD_ADD, strlen(MOD_ADD));
  write(pipe[WRITE],file, strlen(file));
  sms_endmessage(pipe);
}

void sms_rmfile(char *file,int pipe[2]){
  write(pipe[WRITE],MOD_REMOVE, strlen(MOD_REMOVE));
  write(pipe[WRITE],file, strlen(file));
  sms_endmessage(pipe);
}
void sms_change_mn(char *num,char selec,int pipe[2]){
  if( selec == 'm' ){
    write(pipe[WRITE],MOD_CHANGE_M, strlen(MOD_CHANGE_M));
  }
  else if( selec == 'n' ){
    write(pipe[WRITE],MOD_CHANGE_N, strlen(MOD_CHANGE_N));
  }
  else{
    exit(-1);
  }
  write(pipe[WRITE],num, strlen(num));
  sms_endmessage(pipe);

}
void sms_endmessage(int pipe[2]){
  write(pipe[WRITE],MOD_END, strlen(MOD_END));
}
