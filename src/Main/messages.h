#include"../macro_libglob.h"
#ifndef MESSAGES_H
#define MESSAGES_H


void sms_addfile(char *file,int pipe[2]);
void sms_rmfile(char *file,int pipe[2]);
void sms_change_mn(char *num,char selec,int pipe[2]);
void sms_endmessage(int pipe[2]);


#endif
