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
    lock.l_type = F_RDLCK;//读锁
    lock.l_whence = SEEK_SET;
    lock.l_start = 2;
    lock.l_len = 10;
    lock.l_pid = -1;
    int ret = fcntl(fd,F_SETLK,&lock);
    if(ret == -1)perror("lock");
    else printf("加锁成功");
    lock.l_type = F_UNLCK;
    fcntl(fd,F_SETLK,&lock);
    printf("释放成功\n");

    sleep(10);
    close(fd);
}
