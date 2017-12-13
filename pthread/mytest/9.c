/*************************************************************************
	> File Name: 9.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月22日 星期五 17时32分30秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

char *name[1024];
int Random(int n,int m)
{
    return rand()%(m-n+1)+n;
}
int create_name()
{
    int n = Random(65,90);
    printf("%d\n",n);
    char a = '0' + n;
    printf("%\n",'a');
}
int main()
{
    srand((unsigned)time(0));
    create_name();
}
