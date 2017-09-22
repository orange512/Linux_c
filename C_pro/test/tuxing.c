/*************************************************************************
	> File Name: tuxing.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月04日 星期一 21时56分09秒
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
        for(int j = 1 ; j <= 2 * i - 1;j++)
        {
            printf("*");
        }
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
