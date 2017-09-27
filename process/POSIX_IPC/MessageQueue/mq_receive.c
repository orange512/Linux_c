/*************************************************************************
	> File Name: mq_receive.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月27日 星期三 18时55分33秒
 ************************************************************************/

#include<stdio.h>
#include"mq.h"
struct stu
{
    char name[20];
    int age;
};
int main()
{
    mqd_t mq;
    mq = mq_open("/abc",O_RDONLY);
    if(mq < 0)
        perror("mq_open"),exit(-1);
    
    struct mq_attr attr;
    mq_getattr(mq,&attr);
    struct stu p1;
    unsigned int prio;
    size_t size = (size_t)attr.mq_msgsize;//接受时的大小必须是消息队列的大小
    mq_receive(mq,(char *)&p1,size,&prio);
    printf("name = %s\tage = %d\tprio = %u\n",p1.name,p1.age,prio);
    mq_close(mq);
}
