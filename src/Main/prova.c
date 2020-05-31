#include <stdio.h>
#include <stdlib.h>

#include <string.h>

int main(){
	char *pnum="";
	int ret=0;
	if(strlen(pnum)>0)
	if(strlen(pnum) == strspn(pnum,"0123456789")){
		ret=1;
	}
	printf("ret=%d\n",ret);
	return 0;
}
