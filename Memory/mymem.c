/*************************************************************************
	> File Name: string.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月06日 星期三 17时06分56秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <unistd.h>


int i1 = 1;//全局
int i2 = 2;//全局
int i3;//BSS段
static int i4 = 4;//全局
const int i5 = 5;//只读常量区
int main(int i6)//i6栈
{
    int i7;//栈
    static int i8 = 8;//全局
    const int i9 = 9;//只读常量区
    int *pi = malloc(4);//堆
    char *str = "abc";//只读常量区
    char str2[]= "abc";//栈
   /* printf("形参i6 = %p\n",&i6);
    printf("函数内变量的i7 = %p\n",&i7);
    printf("函数内静态常量i8 = %p\n",&i8);
    printf("函数内const常量i9 = %p\n",&i9);
    printf("malloc申请的pi = %p\n",pi);
    printf("*str = %p\n",str);
    printf("str2[] = %p\n",str2);*/
}
/*int main()
{
    printf("pid = %d\n",getpid());
    printf("全局i1 = %p\n",&i1); 
    printf("全局i2 = %p\n",&i2); 
    printf("未初始化全局i3 = %p\n",&i3); 
    printf("静态全局i4 = %p\n",&i4); 
    printf("const全局i5 = %p\n",&i5); 
    printf("fa = %p\n",fa);
    fa(100);
    while(1);
    return 0;
}*/
