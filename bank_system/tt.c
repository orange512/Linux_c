/*************************************************************************
	> File Name: msgtypeb.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月12日 星期二 18时39分01秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
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
    int n;
};
struct msg
{
    long mtype;
    struct account acc;
};

int main()
{
    key_t key = ftok(".",200);
    if(key == -1)
        ERR_EXIT("ftok");
    int msgid = msgget(key,0);
    if(msgid == -1)
        ERR_EXIT("msgget");
    struct msg msg1;
    int ret = msgrcv(msgid,&msg1,sizeof(msg1)-4,-2,0);
    if(ret == -1)
        ERR_EXIT("msgrcv");
    printf("mtype = %ld\tid = %d\tbuf = %s\tmoney = %lf\n",msg1.mtype,msg1.acc.id,msg1.acc.name,msg1.acc.money);
    return 0;
}
