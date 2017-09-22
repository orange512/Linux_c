/*************************************************************************
	> File Name: wait.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月09日 星期六 17时03分45秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>

int main()
{
    printf("进入fork\n");
    pid_t pid = fork();
    if(pid == 0)
    {
        printf("子进程%d\n",getpid());
        sleep(5);
        printf("结束子进程\n");
        exit(100);
    }
    printf("父进程运行\n");
    sleep(3);
    int status;
    pid_t pid2 = wait(&status);
    if(WIFEXITED(status))
    {
        printf("子进程%d退出成功\n",pid2);
        printf("退出码为%d\n",WEXITSTATUS(status));
    }
}
