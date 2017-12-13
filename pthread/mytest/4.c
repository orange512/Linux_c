/*************************************************************************
	> File Name: 4.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月19日 星期二 23时59分36秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
double a[100];
double b[100];
int* fun(int n,double money)
{
    double c[100];
    c[n] = 0;
    srand((unsigned)time(NULL));
    for(int i = 0; i < n;i++)
    {
        a[i] = rand()*0.000000001;
        if(a[i] > 1 && a[i] < 2)
        {
            a[i]-= 1;
        }
        if(a[i] > 2)
        {
            a[i] -= 2;
        }
    }
    for(int i = 0 ; i < n;i++)
    {
        printf("%lf\n ",a[i]);
    }
    double total = 0.0;
    for(int i = 0 ; i < n;i++)
    {
        total += a[i];
    }
    for(int i = 0 ; i < n;i++)
    {
        b[i] = a[i]/total;
    }
    for(int j = 0 ; j < n -1 ; j++)
    {
        c[j] = ((int)((b[j]* 10000)))/100.0;
    }
    c[n-1] = money;
    for(int k = 0; k < n-1;k++)
    {
        c[n-1] -= c[k];
    }
   // for(int i = 0 ; i < 4; i++)
    //printf("%.2lf\n",c[i]);
}
int main()
{
    fun(100,100);
}
