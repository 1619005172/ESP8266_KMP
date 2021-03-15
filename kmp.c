#include "osapi.h"
#include "mem.h"
#define ERROR_KMP 0;
#define TRUE_KMP 1;



int GetValue(char * target, int *value){

    char *head,*tail;
    int temp;

    int i = 1,j = 0;
    head = (char *)os_malloc(sizeof(char) *100);
    tail = (char *)os_malloc(sizeof(char) *100);
    if(!head || !tail)
    	return ERROR_KMP;

    for(i = 1;i<os_strlen(target);i++){

        j = 0;
        while(target[j]!='\0'){
            head[j] = target[j];
            tail[j] = target[j];
            j++;
            head[j]='\0';
            tail[j] = '\0';
        }

        head[i] = '\0';
        tail[i+1] = '\0';

        for(j = 0;j<i;j++){
            if(os_strcmp(head,tail+1+j)==0){
                value[i] = os_strlen(head);
                break;
            }
            temp = os_strlen(head) - 1;
            head[temp] = '\0';
        }
    }
    return TRUE_KMP;
}

int KMP(char *source,char *target,int *value){

    int i = 0,j = 0;

    while(i < os_strlen(source)){

        if(source[i] == target[j] && j<os_strlen(target)){
            i++;
            j++;
        }else if(j>=os_strlen(target)){
            return TRUE_KMP;

        }else if(source[i]!=target[j]){
            if(j==0){
                j=0;
                i++;
            }else{
                j =  value[j-1];
            }
        }
    }
    if(i >=os_strlen(source) && j>=os_strlen(target)){
    	return TRUE_KMP;
    }
    else{
    	return ERROR_KMP;
    }

}


int KMP_start(char *source,char *target)
{
	int value[100];
	int i = 0;
	os_memset(value,0,100);
	GetValue(target,value);
	int data =  KMP(source,target,value);
	os_free(value);
	return data;
}