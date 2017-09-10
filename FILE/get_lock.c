/*************************************************************************
	> File Name: f_lock.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月08日 星期五 19时13分23秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>


int main()
{
    int fd = open("a.txt",O_CREAT|O_RDWR|O_TRUNC,0666);
    if(fd == -1)
    {
        perror("open"),exit(-1);
    }
    struct flock lock;
    lock.l_type = F_WRLCK;//写锁
    lock.l_whence = SEEK_SET;
    lock.l_start = 2;
    lock.l_len = 12;
    lock.l_pid = -1;
    int ret = fcntl(fd,F_GETLK,&lock);
    if(ret == -1)perror("lock");
    printf("%d  %d\n",lock.l_type,lock.l_pid);
    sleep(10);
}
