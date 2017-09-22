/*************************************************************************
	> File Name: 2.c
	> Author: 
	> Mail: 
	> Created Time: 2017年08月29日 星期二 10时34分00秒
 ************************************************************************/

#include<stdio.h>
int a;
static int b =100;
extern int c;
extern void print();
extern void s_print();

int main()
{
    print();
   // extern s_print();
    printf("3333333  a = %d\t b = %d\tc=%d\n",a,b,c);
    return 0;
}
