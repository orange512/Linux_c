/*************************************************************************
	> File Name: client.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月12日 星期二 22时53分00秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<signal.h>
#include<sys/ipc.h>
#include<string.h>
#include<sys/msg.h>
#define ERR_EXIT(m)\
        do{\
            perror(m),exit(-1);\
        }while(0)
struct account
{
    int id;
    char name[20];
    double money;
};
struct msg
{
    long mtype;
    struct account acc;
};

int main(int argc,char *argv[])
{
    int i;
    sscanf(argv[1],"%d",&i);
    printf("%d\n",i);
    key_t key2 = ftok(".",200);
    if(key2 == -1)
        ERR_EXIT("ftok");;
    int msgid2 = msgget(key2,0);
    if(msgid2 == -1)
        ERR_EXIT("msgid2");

    struct msg msg1;
    msg1.mtype = 1;
    strcpy(msg1.acc.name,"liuzhuo");
    msg1.acc.money = 200.0;
    int ret = msgsnd(msgid2,&msg1,sizeof(msg1)-8,0);
    if(ret == -1)
        ERR_EXIT("msgsnd");
    printf("写如成功\n");
    kill(i,30);
    while(1);

}

