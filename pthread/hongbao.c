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
double a[100];
double b[100];
double c[100];
int k = 0;
void fun2(int n,double money)//随机生成红包个数
{
    c[n] = 0;
    srand((unsigned)time(NULL));
    for(int i = 0; i < n;i++)
    {
        a[i] = rand();
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
}
double  money;
pthread_t mainid;
pthread_t g_id[20];
struct info{//个人信息
    int id;
    int m;
    int mark;//用于标记只能抢一次
    char name[20];
}person[20];

pthread_mutex_t lock;
void* task(void *p)//抢红包
{
    int n = *(int*)p;
    pthread_mutex_lock(&lock);
    if(money > 0 && person[n].mark == -1)
    {
        money = money - c[k];
        printf("线程%d取走%.2lf元\n",n,c[k]);
        printf("剩余%.2lf\n",money);
        person[n].id = n;
        person[n].m = c[k];
        k++;
        person[n].mark = 1;
    }
    pthread_mutex_unlock(&lock);

}
void * creat_money(void *p)//生产红包
{

    double num = *(double*)p;
    pthread_mutex_lock(&lock);
    money = num;
    pthread_mutex_unlock(&lock);
    return "红包已放入";

}
void fun()//备注名字
{
    strcpy(person[0].name,"jake");
    strcpy(person[1].name,"tom");
    strcpy(person[2].name,"lisa");
    strcpy(person[3].name,"zhangsan");
    strcpy(person[4].name,"lisi");
    strcpy(person[5].name,"wangwu");
    strcpy(person[6].name,"xiaoliu");
    strcpy(person[7].name,"qianba");
    strcpy(person[8].name,"liu");
    strcpy(person[9].name,"zhao");
    strcpy(person[10].name,"qian");
    strcpy(person[11].name,"sun");
    strcpy(person[12].name,"li");
    strcpy(person[13].name,"zhou");
    strcpy(person[14].name,"wu");
    strcpy(person[15].name,"zhen");
    strcpy(person[16].name,"wang");
    strcpy(person[17].name,"xing");
    strcpy(person[18].name,"rou");
    strcpy(person[19].name,",mercy");

}
int main()
{
    fun();
    int err;
    for(int i = 0 ; i < 20;i++)//初始化
    {
        person[i].mark = -1;
        person[i].id = -1;
    }
    pthread_mutex_init(&lock,0);

    pthread_t tid;
    char *buff;
    double qian;
    int num;
    printf("请输入你的红包金额\n");
    scanf("%lf",&qian);
    printf("请输入红包个数\n");
    scanf("%d",&num);
    fun2(num,qian);
    pthread_create(&tid,0,creat_money,(void *)&qian);
    pthread_join(tid,(void **)&buff);
    printf("%s\n",buff);
    sleep(1);

   /* pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);*/
    for(int i = 0 ; i  < 20;i++)
    {
        if(person[i].mark == -1)
        {
            if(err = pthread_create(&g_id[i],0,task,(void *)&i)!= 0)
                   
                printf("error");
        }
    }
    for(int j = 0 ; j < 20;j++)
    {
        pthread_join(g_id[j],0);
    }
    for(int i = 0 ;i < 20;i++)
    {
        if(person[i].id != -1)
        {
            printf("name = %s\t money = %d\n",person[i].name,person[i].m);
        }
    }

    pthread_mutex_destroy(&lock);
    return 0;
}
