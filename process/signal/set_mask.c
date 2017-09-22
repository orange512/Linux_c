/*************************************************************************
	> File Name: set_mask.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月10日 星期日 21时19分25秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>

void handle(int sig)
{
    printf("接受的信号为%d\n",sig);
}
int main()
{
    signal(SIGINT,handle);
    signal(SIGQUIT,handle);
    signal(50,handle);
    printf("pid = %d\n",getpid());
    printf("执行普通代码，不屏蔽信号\n");
    sleep(15);
    printf("执行重要代码，屏蔽信号\n");

    sigset_t set,old;
    sigemptyset(&set);
    sigaddset(&set,2);
    sigaddset(&set,3);
    sigaddset(&set,50);
    sigprocmask(SIG_SETMASK,&set,&old);
    sleep(20);
    printf("关键代码结束，结束代码\n");
    sigprocmask(SIG_SETMASK,&old,NULL);

}
