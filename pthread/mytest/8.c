/*************************************************************************
	> File Name: 8.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月22日 星期五 10时15分46秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
unsigned int remainMoney;
unsigned int left_MoneyPacksize;
int RAND(int n,int m)
{
    return rand()%(m-n+1)+n; 
}
int getRandomMoney()
{
    if(remainMoney/left_MoneyPacksize == 1)
    {
        return remainMoney/left_MoneyPacksize;
    }
    unsigned int money;
    if(left_MoneyPacksize == 1)
    {
        return  remainMoney;
    }
    money = remainMoney*RAND(1,199)/100/left_MoneyPacksize;
    remainMoney -= money;
    left_MoneyPacksize--;
    return money;
}
int main()
{
    int n;
    int k;
    while(1)
    {
        scanf("%d %d",&remainMoney,&left_MoneyPacksize);
        if(remainMoney/left_MoneyPacksize >= 1)
        {
            k = left_MoneyPacksize;
            break;
        }
        else
        printf("对不起，您的红包金额过少，请重新输入\n");
    }
    srand((unsigned)time(0));
    for(int i = 0; i<k ;i++  )
    {
        n = getRandomMoney();
        printf("left money = %d.%d%d\n",n/100,(n/10)%10,n%10);
        
    }
}
