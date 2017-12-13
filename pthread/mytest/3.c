/*************************************************************************
	> File Name: 3.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月19日 星期二 21时08分37秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main()
{
    srand((unsigned)time(NULL));
    double a[4];
    a[0] = rand();
    a[1] = rand();
    a[2] = rand();
    a[3] = rand();
    double total = 0.0;
    for(int i = 0 ; i < 4;i++)
    {
        total += a[i];
    }
    double b = a[0]/total;
    double c = a[1]/total;
    double d = a[2]/total;
    double e = a[3]/total;
    a[0] = ((int)((b* 10000)))/100.0;
    a[1] = ((int)((c* 10000)))/100.0;
    a[2] = ((int)((d* 10000)))/100.0;
    a[3] = 100.0 - a[0] - a[1] - a[2];
    printf("%lf\t%lf\t%lf\t%lf\n",b,c,d,e);
    for(int i = 0 ; i < 4; i++)
    printf("%lf\n",a[i]);
}
