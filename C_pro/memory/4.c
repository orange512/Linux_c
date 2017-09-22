/*************************************************************************
	> File Name: 4.c
	> Author: 
	> Mail: 
	> Created Time: 2017年08月29日 星期二 10时36分20秒
 ************************************************************************/

#include<stdio.h>
int a = 6;
static int b = 10;
int c = 5;
void print()
{
    printf("a=%d\tb=%d\tc= %d\n",a,b,c);
}
static void s_print()
{
    printf("a=%d\tb=%d\tc= %d\n",a,b,c);

}
