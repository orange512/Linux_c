/*************************************************************************
	> File Name: string2.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月06日 星期三 17时41分50秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
    char *s1 = "abc";//s1是地址 指向“abc“只读常量区
    char s2[] = "abc";//s2是数组 在栈中分配空间 把"abc"的值复制到了栈中，指向栈区

    char *s3 = s2;//s3指向了栈，不是常指针

   // strcpy(s1,"123");//错，s1指向只读区不能修改
    s1 = "123";//对  =是地址元算

    strcpy(s2,"123");//对  strcpy是值运算
  //  s2 = "123";//错 s2是常指针不能改变地址

    char *s4 =(char *) malloc(4);//s4是指向堆区的非常指针
  //  s4 = "abc";//s4 指向只读区
    strcpy(s4,"abc");//对 改值
    printf("s1 = %s\ns2 = %s\n",s1,s2);
}
