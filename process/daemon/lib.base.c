/*************************************************************************
	> File Name: lib.base.c
	> Author: 
	> Mail: 
	> Created Time: 2017年10月30日 星期一 20时29分14秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>

int daemon(int nochdir,int noclose)
{
    pid_t pid;
    pid = fork();

    if(pid < 0)
    {
        perror("fork");
        return -1;
    }
    //父进程则退出
    if(pid != 0)
        exit(0);
    //子进程
    pid = setsid();//成为会话领头进程

    if(pid < -1)
    {
        perror("setsid");
        return -1;
    }
    //改变工作目录
    if(!nochdir)
        chdir("/");
    //关闭文件描述符
    if(!noclose)
    {
        int fd;
        fd = open("dev/null",O_RDWR,0);
        if(fd != -1)
        {
            dup2(fd,STDIN_FILENO);
            dup2(fd,STDOUT_FILENO);
            dup2(fd,STDERR_FILENO);
            if(fd > 2)
                close(2);
        }
    }
    umask(0027);
    return 0;
}
void* signal_set(int signo,void(*func)(int))
{
    int ret;
    struct sigaction sig;
    struct sigaction osig;

    sig.sa_handler = func;
    sigemptyset(&sig.sa_mask);
    sig.sa_flags = 0;
#ifdef SA_RESTART
    sig.sa_flags |= SA_RESTART;
#endif
    ret = sigaction(signo,&sig,&osig);
    if(ret < 0)
        return (SIG_ERR);
    else
        return (osig.sa_handler);
}
//SIGINT信号处理
void sigint(int sig)
{
    //完成某项工作，例如给syslogd发送消息
}
//SIGTSTP信号处理
void sigtstp(int sig)
{
    //完成某项工作，例如给syslogd发送消息
}
//初始化SIGINT和SIGTSTP信号
void signal_init()
{
    signal_set(SIGINT,sigint);
    signal_set(SIGTSTP,sigtstp);
}
