/*************************************************************************
	> File Name: mq_open.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月27日 星期三 18时33分54秒
 ************************************************************************/

#include<stdio.h>
#include"mq.h"

int main()
{
    mqd_t mq;
    mq = mq_open("/abc",O_RDONLY);
    if(mq < 0)
        perror("mq_open"),exit(-1);
    printf("打开成功\n");
    mq_close(mq);
}
