/*************************************************************************
	> File Name: 1.c
	> Author: 
	> Mail: 
	> Created Time: 2017年11月25日 星期六 15时06分29秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
int main()
{
    close(STDIN_FILENO);
    close(STDERR_FILENO);

    int fd1 = open("1.txt",O_CREAT|O_RDONLY|O_TRUNC,0);
    if(fd1<0)
        printf("open error\n");
    printf("fd1= %d\n",fd1);
    int fd2 = open("2.txt",O_CREAT|O_RDONLY|O_TRUNC,0);
    if(fd2<0)
        printf("open error\n");
    printf("fd2= %d\n",fd2);
    int fd3 = open("3.txt",O_CREAT|O_RDONLY|O_TRUNC,0);
    if(fd3<0)
        printf("open error\n");
    printf("fd3= %d\n",fd3);

    close(fd1);
    close(fd2);
    close(fd3);
    return 0;
}
