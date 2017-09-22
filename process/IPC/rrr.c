/*************************************************************************
	> File Name: msgtypea.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月12日 星期二 18时28分55秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/msg.h>
#define ERR_EXIT(m)\
        do{\
            perror(m),exit(-1);\
        }while(0)
struct msg
{
    long mtype;
    char buf[1024];
};
int main()
{
    key_t key = ftok(".",200);
    if(key == -1)
        ERR_EXIT("ftok");
    int msgid = msgget(key,0);
    if(msgid == -1)
        ERR_EXIT("msgget");
    struct msg msg2 = {};
    int ret = msgrcv(msgid,&msg2,sizeof(msg2) -4,-2,0);
    printf("buf = %s\n",msg2.buf);



}
