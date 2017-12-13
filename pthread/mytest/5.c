/*************************************************************************
	> File Name: 5.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月20日 星期三 14时36分33秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
double lucky_rand =0.0;
int flag = 0;
int fun(int n,double money)
{
    int lucky_money =(int)(money * 100);
    printf("%d\n",lucky_money);
    if(lucky_money == (n-flag)*1)
    {
        lucky_money = 1;
        return 1;
    }
    lucky_rand =((int)rand()%7*+1)/100.0;
    printf("rand = %lf\n",lucky_rand);
    /*while(lucky_money < lucky_money * lucky_rand - (n-flag)*1)
    {
   //     printf("middle %lf\n",lucky_rand);
        lucky_rand =((int)rand()%7000+1)/100.0;
    }*/
    lucky_money = lucky_money*lucky_rand;
    flag++;
    printf("n = %lf\tmoney = %d\n",lucky_rand,lucky_money);
    return money;

}
int main()
{
    srand((unsigned)time(NULL));
    for(int i = 0; i < 20;i++)
    fun(10,1);
}
