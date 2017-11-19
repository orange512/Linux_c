/*************************************************************************
	> File Name: malloc2.c
	> Author: 
	> Mail: 
	> Created Time: 2017年11月06日 星期一 21时32分23秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
    char *p = malloc(1024*512);
    printf("%d\n",getpid());

    pause();
    free(p);
}
