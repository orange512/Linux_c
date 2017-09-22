/*************************************************************************
> File Name: mmap.c
> Author: 
> Mail: 
> Created Time: 2017年09月07日 星期四 20时43分57秒
************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<sys/mman.h>
int main()
{
    //0首地址 代表内核指定
    void *p = mmap(0,//0首地址 代表内核指定
                   4,//分配4字节，实际分配4096字节（一页）
                   PROT_READ|PROT_WRITE,//权限
                   MAP_PRIVATE|MAP_ANONYMOUS,//私有 匿名 针对物理内存
                   0,0);
    if(p == MAP_FAILED)
    {
        perror("mmap");
        return -1;
    }
    int *pi =(int *)p;
    *pi = 100;
    char *str = p+10;
    strcpy(str,"abcd");

    char *ch = p;
    for(int i = 0 ; i < 20;i++)
    {
        printf("%d\n",ch[i]);
    }
    munmap(p,4);

}
