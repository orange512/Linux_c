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
    int shimd = shm_open("/xyz",O_RDONLY,0);
    if(shimd < 0)
        perror("shm_open"),exit(EXIT_FAILURE);
    struct stu *p;
    p = mmap(0,sizeof(struct stu),PROT_READ,MAP_SHARED,shimd,0);//将共享内存映射到进程
    if(p == MAP_FAILED)
        perror("mmap"),exit(EXIT_FAILURE);

    printf("name = %s\tage = %d\n",p->name,p->age);
    close(shimd);
    return 0;
    
}
