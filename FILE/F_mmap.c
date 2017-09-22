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
    int fd = open("emp.dat",O_CREAT|O_RDWR|O_TRUNC,0666);
    if(fd == -1) perror("open"),exit(-1);
    ftruncate(fd,sizeof(struct emp)*2);//如果映射的文件不设大小将会出现总线错误，无法存进去数据
    void *pi = mmap(0,sizeof(struct emp)*2,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);//如果换成MAP_PRIVATE，则不会往文件里存数据

    struct emp *p = pi;
    p[0].id = 1;
    strcpy(p[0].name,"zhangsan");
    p[0].salary = 120.0;
    p[1].id = 2;
    strcpy(p[1].name,"lisi");
    p[1].salary = 160.0;

    munmap(p,sizeof(p));
    printf("write success\n");

}
