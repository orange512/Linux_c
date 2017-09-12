/*************************************************************************
	> File Name: msg.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月12日 星期二 17时45分23秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/msg.h>
#define ERR_EXIT(m)\
        do{\
            perror(m),exit(-1);\
        }while(0)

int main()
{
    key_t key = ftok(".",200);
    int msgid = msgget(key,0666|IPC_CREAT);
    if(msgid== -1)
        ERR_EXIT("msgget");
    int ret = msgsnd(msgid,"hell0",5,0);
    if(ret == 1)
        ERR_EXIT("msgsnd");
    printf("send ok\n");

}
