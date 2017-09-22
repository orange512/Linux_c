/*************************************************************************
	> File Name: pipe.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月11日 星期一 22时24分37秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>


int main()
{
    int fd[2];//fd[0]为写  fd[1]为读
    pipe(fd);
    pid_t pid = fork();
    if(pid == 0)
    {
        close(fd[0]);//关闭写管道
        for(int i = 0 ; i < 100;i++)
        {
            read(fd[1],&i,4);
            printf("%d ",i);
            fflush(0);
        }
        close(fd[1]);
        exit(0);
    }
    close(fd[1]);//父进程关闭写管道
    for(int i = 0 ; i < 100;i++)
    {
        write(fd[0],&i,4);
    }
    close(fd[0]);
    return 0;
    
}
