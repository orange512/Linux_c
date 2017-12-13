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
    p = malloc(45);
    printf("%d\n",*(p-8));
    free(p);
    char *p1; 
    p1 = malloc(20);
    printf("%d\n",*(p1-8));
    free(p1);
    return 0;
}
