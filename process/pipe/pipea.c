/*************************************************************************
	> File Name: pipea.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月11日 星期一 22时13分19秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{
    int fd = open("./a.pipe",O_WRONLY);
    if(fd == -1) 
        perror("open"),exit(-1);
    for(int i = 0 ; i < 100;i++)
    {
        write(fd,&i,4);
        usleep(100000);
    }
    close(fd);
}
