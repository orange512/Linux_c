/*************************************************************************
	> File Name: mutex.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月14日 星期四 22时33分04秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<signal.h>
#include<string.h>
#include<time.h>
int remainMoney = -1;//剩余红包钱
int left_MoneyPacksize;//剩余红包个数

pthread_t g_id[20];
pthread_cond_t cond;
pthread_mutex_t lock;
int getMoney;//获取的钱

int RAND(int n,int m)//生成n到m之内的随机数
{
    return rand()%(m-n+1)+n; 
}

int getRandomMoney()//获取随机金额红包
{
    if(remainMoney/left_MoneyPacksize == 1)
    {
        return remainMoney/left_MoneyPacksize;
    }
    int money;
    if(left_MoneyPacksize == 1)
    {
        money =   remainMoney;
        remainMoney -= money;
        return money;
    }
    money = remainMoney*RAND(1,199)/100/left_MoneyPacksize;
    remainMoney -= money;
    left_MoneyPacksize--;
    return money;
}
void destroy(pthread_t tid)
{
    pthread_join(tid,0);
    //printf("%ld exit\n",tid);
}
void* task(void *p)//抢红包
{
    int n = *(int *)p;
    pthread_mutex_lock(&lock);
    printf("%d准备好抢红包\n",n);
    if(remainMoney == -1)
        pthread_cond_wait(&cond,&lock);
    if(remainMoney == 0)
    {
        pthread_mutex_unlock(&lock);
        destroy(pthread_self());
    }
    else
    {
        getMoney = getRandomMoney();
        printf("线程%d取走%d.%d%d元\n",n,getMoney/100,(getMoney/10)%10,getMoney%10);
        printf("剩余红包钱%d\n",remainMoney);
        pthread_mutex_unlock(&lock);
        destroy(pthread_self());
    }
}
void* creat_money(void *p)//生产红包
{
    remainMoney =(int)(*(double*)p * 100);
    pthread_mutex_lock(&lock);
    remainMoney = remainMoney;
    printf("红包已放入\n");
    usleep(100);
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&lock);
    return NULL;

}

int main()
{
    int k;
    double user_money;
    int err;
    pthread_mutex_init(&lock,0);
    pthread_cond_init(&cond,0);
    pthread_t tid;
    srand((unsigned)time(0));

    while(1)
    {
        printf("请输入红包金额和红包数量\n");
        scanf("%lf %d",&user_money,&left_MoneyPacksize);
        if(user_money*100/left_MoneyPacksize >= 1)
        {
            k = left_MoneyPacksize;
            break;
        }
        else
        printf("对不起，您的红包金额过少，请重新输入\n");
    }

    for(int i = 0 ; i  < 100;i++)//创建抢红包人数
    {
        p = (int*)malloc(sizeof(int));
        p = &i;
        if(err = pthread_create(&g_id[i],0,task,(void *)&p)!= 0)
            printf("error");
    }

    pthread_create(&tid,0,creat_money,(void *)(&user_money));
    pthread_join(tid,0);
   /* for(int j = 0 ; j < 10000;j++)
    {
        pthread_join(g_id[j],0);
   //    printf("%djoin\n",j);
    }*/

    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&lock);
    return 0;
}
