/*************************************************************************
	> File Name: mq_send.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月27日 星期三 18时44分22秒
 ************************************************************************/

#include<stdio.h>
#include"mq.h"
struct stu
{
    char name[20];
    int age;
}STU;
int main(int argc,char* argv[])
{
    if(2 != argc)
    {
        printf("请输入发送消息的优先级\n");
        exit(EXIT_FAILURE);
    }
    mqd_t mq;
    mq = mq_open("/abc",O_WRONLY);
    if(mq < 0 )
        perror("mq_open"),exit(-1);
    struct stu  p1;
    strcpy(p1.name,"lizuhuo");
    p1.age = 22;
    unsigned int prio;
    prio = atoi(argv[1]);

    mq_send(mq,(const char *)&p1,sizeof(p1),prio);//发送时必须强制转换成const类型
    mq_close(mq);
}
