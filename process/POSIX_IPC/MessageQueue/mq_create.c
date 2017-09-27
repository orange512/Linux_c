/*************************************************************************
	> File Name: mq_create.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月27日 星期三 18时21分40秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

int main()
{
    //注意创建POSIX消息队列时名字前加/
    mqd_t mq;
    mq = mq_open("/abc",O_CREAT|O_RDONLY,0666,NULL);//mq_open使用和open函数差不多
    if(mq < 0)
        perror("mq_open"),exit(-1);
    return 0;
}
