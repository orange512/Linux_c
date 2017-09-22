/*************************************************************************
	> File Name: 5.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月16日 星期六 15时24分25秒
 ************************************************************************/

#include<stdio.h>
#define MAX(a,b)  (a>b)?a:b
#define MAX2(a,b,c) (a>((b>c)?b:c))?a:((b>c)?b:c)  
int main()
{
    printf("%d\n",MAX(2,3));
    printf("%d\n",MAX2(1,2,3));
}
