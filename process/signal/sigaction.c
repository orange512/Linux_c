/*************************************************************************
	> File Name: signation.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月10日 星期日 21时45分30秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
void handle(int sig)
{
    printf("捕获信号为%d\n",sig);
    sleep(5);
}//在信号处理函数的执行期间，会屏蔽相同信号
int main()
{
    struct sigaction action = {};
    action.sa_handler= handle;//设置信号处理函数
    sigemptyset(&action.sa_mask);
    sigaddset(&action.sa_mask,3);//在信号处理期间会屏蔽到来的3信号
    //action.sa_flags = SA_RESETHAND;//设置信号第一次是处理函数，然后恢复为默认处理
    sigaction(SIGINT,&action,NULL);
    while(1);
}

