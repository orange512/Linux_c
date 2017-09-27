/*************************************************************************
	> File Name: mq_unlink.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月27日 星期三 19时56分51秒
 ************************************************************************/

#include<stdio.h>
#include"mq.h"

int main(int argc,char* argv[])
{
    char buff[20];
    sprintf(buff,"/%s",argv[1]);
    mq_unlink((const char *)buff);
    return 0;
}
