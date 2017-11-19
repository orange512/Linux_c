/*************************************************************************
	> File Name: mallopt.c
	> Author: 
	> Mail: 
	> Created Time: 2017年11月06日 星期一 21时14分47秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

int main()
{
    mallopt(M_MXFAST,0);
    char *p = malloc(10);
    char *p1 = malloc(10);
    char *p2 = malloc(20);
    printf("%p    %p     %p\n",p,p1,p2);
    free(p);
    free(p1);
    char *p3 = malloc(10);
    printf("%p\n",p3);
    return 0;
}
