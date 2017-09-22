/*************************************************************************
	> File Name: sigaction2.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月10日 星期日 22时04分27秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>

void handle(int sig,siginfo_t *info,void *p)
{
    printf("进程%d发送信号%d，外带数据%d\n",info->si_pid,sig,info->si_value);
}
int main()
{
    struct sigaction action = {};
    action.sa_flags = SA_SIGINFO;//设置执行第二个函数
    action.sa_sigaction = handle;//处理函数的掉用
    sigaction(SIGINT,&action,NULL);
    printf("pid = %d\n",getpid());
    union sigval v;   //发送外带数据
    v.sival_int = 10;
    sigqueue(getpid(),2,v);
    while(1);
    return 0;
}
