/*************************************************************************
	> File Name: shm_unlink.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月27日 星期三 21时24分49秒
 ************************************************************************/

#include<stdio.h>
#include"shm.h"
int main(int argc,char * argv[1])
{
    if(2 != argc)
    {
        printf("请输入删除的共享内存名\n");
        exit(EXIT_FAILURE);
    }
    char buf[20];
    sprintf(buf,"/%s",argv[1]);
    shm_unlink(buf);
    return 0;
}
