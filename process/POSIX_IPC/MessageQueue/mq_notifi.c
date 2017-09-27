/*************************************************************************
	> File Name: mq_notifi.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月27日 星期三 19时13分35秒
 ************************************************************************/

#include<stdio.h>
#include"mq.h"
#include<signal.h>
mqd_t mqid;
size_t size;
struct sigevent sigev;
struct stu
{
    char name[20];
    int age;
};
void handle(int sig)
{
    mq_notify(mqid,&sigev);//重复注册，消息有空变到有会已信号通知
    unsigned int prio;
    struct stu p1;
    mq_receive(mqid,(char*)&p1,size,&prio);
    printf("name = %s\tage = %d\tprio = %u\n",p1.name,p1.age,prio);
}
int main()
{
    mqid = mq_open("/abc",O_RDONLY);
    if(mqid < 0)
        perror("mq_open"),exit(-1);

    signal(SIGUSR1,handle);//注册信号
    struct mq_attr attr;
    mq_getattr(mqid,&attr);
    size = (size_t)attr.mq_msgsize;
    sigev.sigev_notify = SIGEV_SIGNAL;//注册到notify信号发送
    sigev.sigev_signo = SIGUSR1;

    mq_notify(mqid,&sigev);
    for(;;)
        pause();
    mq_close(mqid);

}
