/*************************************************************************
	> File Name: kongxin.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月04日 星期一 22时18分35秒
 ************************************************************************/

#include<stdio.h>

int main()
{
    for(int i = 1;i <= 5;i++)
    {
        for(int k = 5 - i;k>0;k--)
        {
            printf(" ");
        }
        printf("*");
        for(int m = 1;m <= 2 * i  -3;m++)
            printf(" ");
        printf("*");

        printf("\n");
    }
    for(int i = 4;i >= 1;i--)
    {
        for(int k = 5 - i;k>0;k--)
        {
            printf(" ");
        }
        for(int j = 1 ; j <= 2 * i - 1;j++)
        {
            printf("*");
        }
        printf("\n");
    }
}
