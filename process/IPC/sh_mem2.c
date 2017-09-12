/*************************************************************************
	> File Name: sh_mem.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月11日 星期一 22时58分03秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/shm.h>
#include<unistd.h>

int main()
{
    key_t key = ftok(".",100);//生成key
    if(key == -1)
        perror("ftok"),exit(-1);
    int shmid = shmget(key,0,0);//获取共享内存
    if(shmid == -1)
        perror("shmget"),exit(-1);
    void  *p = shmat(shmid,0,0);
    int *p1 = p;
    printf("p = %d\n",*p1);
    int ret = shmdt(p);
    if(ret == -1)
        perror("shmdl"),exit(-1);
    printf("OK");
}

