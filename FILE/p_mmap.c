/*************************************************************************
	> File Name: F_mmap.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月08日 星期五 20时17分05秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<sys/mman.h>
struct emp
{
    int id;
    char name[20];
    double salary;
};

int main()
{
    int fd = open("emp.dat",O_RDWR);
    if(fd == -1) perror("open"),exit(-1);
    void *pi = mmap(0,sizeof(struct emp)*2,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    //mmap主要用来映射文件，不是用来读数据
    struct emp *p = pi;
    for(int i = 0 ; i < 2; i++)
    {
        printf("id = %d\tname = %s\tsalary = %lf\n",p[i].id,p[i].name,p[i].salary);
    }
    close(fd);
    return 0;

}
