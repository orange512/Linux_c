/*************************************************************************
	> File Name: waitpid.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月10日 星期日 13时34分19秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main()
{
    pid_t pid1,pid2;
    pid1 = fork();
    if(pid1 > 0)
        pid2 = fork();
    if(pid1 == 0)
    {
        printf("子进程%d开始运行\n",getpid());
        sleep(3);
        printf("子进程%d结束运行\n",getpid());
        exit(100);
    }
    if(pid2 == 0)
    {
        printf("子进程%d开始运行\n",getpid());
        sleep(1);
        printf("子进程%d结束运行\n",getpid());
        exit(200);
    }
    int status;
    pid_t pid = waitpid(-1,&status,0);
    if(WIFEXITED(status))
    {
        printf("exitcode = %d\n",WEXITSTATUS(status));
    }
    printf("end\n");

}
