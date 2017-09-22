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
#include<string.h>
#define ERR_EXIT(m)\
        do{\
            perror(m),exit(-1);\
        }while(0)
struct msg
{
    long mtype;
    char buf[256];
};
int main()
{
    key_t key = ftok(".",200);
    if(key == -1)
        ERR_EXIT("ftok");
    int msgid = msgget(key,0666|IPC_CREAT);
    if(msgid == -1)
        ERR_EXIT("msgget");
    struct msg msg1 = {1,"hello1"};
    struct msg msg2 = {2,"hello2"};

    int res1 = msgsnd(msgid,(void *)&msg1,sizeof(msg1)-8,0);
    //printf("size = %ld\n",sizeof(struct msg));
    int res2 = msgsnd(msgid,(void *)&msg2,sizeof(msg2)-8,0);
    printf("size =%ld\n",sizeof(long));
    if(res1 == -1&&res2 == -1)
        ERR_EXIT("msgsnd");
    printf("send ok\n");
}
