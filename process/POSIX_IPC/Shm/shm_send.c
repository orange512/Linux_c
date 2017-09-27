/*************************************************************************
	> File Name: shm_send.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月27日 星期三 20时58分14秒
 ************************************************************************/

#include<stdio.h>
#include"shm.h"
struct stu
{
    char name[20];
    int age;
};
int main()
{
    int shimd = shm_open("/xyz",O_RDWR,0);
    if(shimd < 0)
        perror("shm_open"),exit(EXIT_FAILURE);
    
    struct stu *p;//定义结构体指针  同时将内存映射到shimd
    p = mmap(0,sizeof(struct stu),PROT_WRITE,MAP_SHARED,shimd,0);//注意当保护为write，shared，shimd要指定为RDWR
    if(p == MAP_FAILED)
        perror("mmap"),exit(EXIT_FAILURE);

    strcpy(p->name,"liuzhuo");
    p->age = 22;
    return 0;
    
}
