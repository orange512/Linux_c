/*************************************************************************
	> File Name: recv_msg.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月12日 星期二 17时58分37秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/msg.h>
#include<sys/types.h>
#define ERR_EXIT(m)\
        do{\
            perror(m),exit(-1);\
        }while(0)
int main()
{
    key_t key = ftok(".",200);
    if(key == -1)
        ERR_EXIT("ftok");
    int msgid = msgget(key,0);
    if(msgid == -1)
        ERR_EXIT("msgget");
    char buf[1024];
    int ret = msgrcv(msgid,buf,sizeof(buf),0,0);
    printf("buf = %s\n",buf);
    if(ret == -1)
        ERR_EXIT("msgrcv");
}
