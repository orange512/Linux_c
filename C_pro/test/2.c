/*************************************************************************
	> File Name: 2.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月16日 星期六 14时32分20秒
 ************************************************************************/

#include<stdio.h>
#define A 3

#if(A < 2)
    #error "版本低"
#else
    #warning "版本高"
#endif
int main()
{
    printf("hello\n");
    return 0;
}
