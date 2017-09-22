/*************************************************************************
	> File Name: atexit.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月09日 星期六 17时11分45秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
void  fa()
{
    printf("你好\n");
}
int main()
{
    atexit(fa);
    printf("hello world\n");
    _exit(0);
    //exit(0);

    return 0;
}
