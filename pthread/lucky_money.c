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
int remainMoney;
int left_MoneyPacksize;
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
    printf("%destroy \n",(unsigned int)tid);
    pthread_join(tid,0);
}
pthread_t mainid;
pthread_t g_id[20];
struct info{//个人信息
    int id;
    double m;
    _Bool mark;//用于标记只能抢一次
    char name[20];
}person[20];
void mutex_clean(void *mutex)
{
    pthread_mutex_unlock((pthread_mutex_t *)mutex);
}
pthread_cond_t cond;
pthread_mutex_t lock;
void* task(void *p)//抢红包
{
    int n = (int)p;
    pthread_mutex_lock(&lock);
    //printf("%d准备好抢红包\n",n);
    pthread_cleanup_push(mutex_clean,&lock);
    pthread_cond_wait(&cond,&lock);
   // printf("剩余%d\n",remainMoney);
    if(remainMoney == 0)
    {
        pthread_mutex_unlock(&lock);
        printf("%d exit\n",n);
        
    //    pthread_mutex_unlock(&lock);
        pthread_exit(0);
       // destroy(pthread_self());
    }
    int getMoney = getRandomMoney();
    //printf("线程%d取走%d.%d%d元\n",n,getMoney/100,(n/10)%10,n%10);
    printf("线程%d取走%d分\n",n,getMoney);
    //printf("剩余%d\n",remainMoney);
   /* person[n].id = n;
    person[n].m = getMoney;
    person[n].mark = 1;*/
    pthread_cleanup_pop(0);
    pthread_mutex_unlock(&lock);
    pthread_exit(0);
//    destroy(pthread_self());

}
void * creat_money(void *p)//生产红包
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
    int n;
    int k;
    double user_money;
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

    int err;
    for(int i = 0 ; i < 20;i++)//初始化
    {
        person[i].mark = 0;
        person[i].id = -1;
    }
    pthread_mutex_init(&lock,0);
    pthread_cond_init(&cond,0);
    pthread_t tid;
    char *buff;

    srand((unsigned)time(0));

    /*pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);*/
    for(int i = 0 ; i  < 20;i++)
    {
        if(err = pthread_create(&g_id[i],0,task,(void *)i)!= 0)
            printf("error");
    }
    pthread_create(&tid,0,creat_money,(void *)(&user_money));
    pthread_join(tid,(void **)&buff);
   // printf("%s\n",buff);
    for(int j = 0 ; j < 20;j++)
    {
        pthread_join(g_id[j],0);
    //    printf("%djoin\n",j);
    }
   /* for(int i = 0 ;i < 20;i++)
    {
        if(person[i].mark == 1)
        printf("id = %d\t money = %.2lf\n",person[i].id,person[i].m);
    }*/

    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&lock);
    return 0;
}
