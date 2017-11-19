/*************************************************************************
	> File Name: malloc.c
	> Author: 
	> Mail: 
	> Created Time: 2017年11月06日 星期一 19时05分03秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
int main()
{
    char *p; 
    p = malloc(20);
    strcpy(p,"123");
    printf("p=%p\n",p);
   // printf("0x%x\n",*(p-4));
    pid_t pid = getpid();
    printf("pid = %d\n",pid);
    pause();
    free(p);
    return 0;
}
