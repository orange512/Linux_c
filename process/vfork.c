/*************************************************************************
	> File Name: vfork.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月10日 星期日 13时53分49秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>

int main()
{
    pid_t pid1 = vfork();
    if(pid1 == 0)
    {
        printf("子进程%d开始运行\n",getpid());
         //execl("./test","test",NULL);
        execl("/bin/ls","ls","-l",NULL);
        exit(100);//这里的代码不会执行
    }
    int status;
    pid_t pid = waitpid(-1,&status,0);
    if(WIFEXITED(status))
    {
        printf("exitcode = %d\n",WEXITSTATUS(status));
    }
    printf("父进程结束运行\n");
}
