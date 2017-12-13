/*************************************************************************
	> File Name: 7.c
    > Author: 
    > Mail: 
    > Created Time: 2017年09月20日 星期三 22时41分54秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

/*
 *  * 函数说明： 第一次调用传入N和money，其余调用所传参数无用
 *   * N : 所分红包的总数目
 *    * money : 红包的总钱数，保留两位小数，其余小数位数忽略
 *     * return 下一个红包的钱数，单位为分，总和为money
 *      */
int getLuckyMoney( int N, double money)
{
    static int money_amount;/* = money * 100;*/
    static int left_money ;/* money_amount;*/
    static int counter ;/* N*/;
    money_amount = money*100;
    left_money = money_amount;
    counter = N;
    int lucky_rand = 0;    
    if(counter > 1)
    {
        if(left_money > counter - 1)
        {
            do
            {
                lucky_rand = rand() % (money_amount / counter) + 1;

            }while(left_money - lucky_rand < counter - 1);

        }
        else
        {
            lucky_rand = 1;

        }

        left_money -= lucky_rand;

    }
    else if(counter == 1)
    {
        lucky_rand = left_money;
        left_money = 0;

    }
    else
    {
        // Do nothing. There is a error, because you are not supposed to invoke the function more than N times after one initialization.
        //     
    }
    printf("lucky_rand = %i\tmoney = %i\n", lucky_rand, money_amount);
    counter--;

    return lucky_rand;


}
int main()
{
    srand((unsigned)time(NULL));

    int sum = 0;
    for(int i = 0; i < 20; i++)
    {
        sum += getLuckyMoney(20, 100);

    }
    printf("sum = %d\n", sum);

}
