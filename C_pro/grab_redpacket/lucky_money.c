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
#include"api_redis.h"
#include"api_mysql.h"
int remainMoney;//剩余红包钱
int left_MoneyPacksize;//剩余红包个数
int total_num;
pthread_cond_t cond;
pthread_mutex_t lock;
int getMoney;//获取的钱
double Lucky_money = 0.0;
redisContext *c;
struct send_redpacket
{
    char name[16];
    double send_money;
    int packet_num;
};
struct grab_redpacket
{
    char red_uid[16];
    char myname[16];
};
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
void destroy(pthread_t tid)//销毁抢完红包的线程
{
    pthread_join(tid,0);
    printf("%ld exit\n",tid);
}
void* task(void *p)//抢红包
{
    struct grab_redpacket *grab_redpacket;
    grab_redpacket = (struct grab_redpacket*)p;
 //      printf("start %s\n",grab_redpacket->myname);
    /*if(remainMoney == -1)
        pthread_cond_wait(&cond,&lock);*/
        
    char buff[1024];
    sprintf(buff,"hmget %s total_money num left_num",grab_redpacket->red_uid);
    
    redisReply *r = (redisReply *)redisCommand(c,buff);
    sscanf(r->element[0]->str,"%d",&remainMoney);
    sscanf(r->element[1]->str,"%d",&total_num);
    sscanf(r->element[2]->str,"%d",&left_MoneyPacksize);
 
    //printf("remainMoney = %d\ntotal_money = %d\nle = %d\n",remainMoney,total_num,left_MoneyPacksize);
    pthread_mutex_lock(&lock);
    if(remainMoney == 0)
    {
        pthread_mutex_unlock(&lock);
        destroy(pthread_self());
    }
    else
    {
        getMoney = getRandomMoney();//获取金额
        printf("%s---取走%d.%d%d元\n",grab_redpacket->myname,getMoney/100,(getMoney/10)%10,getMoney%10);
        pthread_mutex_unlock(&lock);
        destroy(pthread_self());//先抢完的人先结束
    }
}
double check_money_enough(char *name)
{
    //GString *search;
    //search = g_string_new("hget");
    char buff[1024];
    char val[1024];
    sprintf(buff,"select usermoney from usermoney where UId = '%s';",name);
    MYSQL *mysql;
    mysql = init_mysql(mysql);
    mysql = connect_mysql(mysql,"127.0.0.1","root","950512","test");
    query_mysql(mysql,buff);
    MYSQL_RES* result =  import_result(mysql);
    MYSQL_ROW row = NULL;
    while(row = mysql_fetch_row(result))
    {
       sprintf(val,"%s",row[0]); 
    }
    double a;
    sscanf(val,"%lf",&a);
    if(a > 0.0)
        return a;
    else
        return 0;

}
void* creat_money(void *p)//生产红包
{
    double total;
    struct send_redpacket *mysend = (struct send_redpacket*)p;
    pthread_mutex_lock(&lock);
    if(total = check_money_enough(mysend->name))
    {
        char send_buf[1024];
        sprintf(send_buf,"hmset red001 total_money %d num %d left_num %d",(int)mysend->send_money*100,mysend->packet_num,mysend->packet_num);
        
        set_redis(c,send_buf);
        printf("红包已放入\n");
        usleep(100);
        remainMoney = mysend->send_money;
        pthread_cond_broadcast(&cond);
    }
    pthread_mutex_unlock(&lock);
    return NULL;

}

int main()
{
    int k;
    remainMoney = -1;
    c = connect_redisContext("127.0.0.1",6379);
    double user_money;
    int err;
    pthread_mutex_init(&lock,0);
    pthread_cond_init(&cond,0);
    pthread_t tid;
    srand((unsigned)time(0));

    while(1)
    {
        printf("请输入红包金额和红包数量(注：红包数量最多3000个)\n");
        scanf("%lf %d",&user_money,&left_MoneyPacksize);
        if(user_money*100/left_MoneyPacksize >= 1)
        {
            k = left_MoneyPacksize;
            break;
        }
        else
        printf("对不起，您的红包金额过少，请重新输入\n");
    }

    struct send_redpacket redpacket;
    sprintf(redpacket.name,"haha123");
    redpacket.send_money = user_money;
    redpacket.packet_num = left_MoneyPacksize;
    pthread_create(&tid,0,creat_money,(void *)(&redpacket));
    pthread_join(tid,0);

    printf("\n1秒后开抢.....\n");
    sleep(1);

    struct grab_redpacket cli_grab[k*2];

    pthread_t *p_id =(pthread_t *) malloc(sizeof(pthread_t) * k * 2);
    memset(p_id,0,sizeof(p_id));
    for(int i = 0 ; i  < k*2;i++)//创建抢红包人数
    {
        sprintf(cli_grab[i].red_uid,"red001");
        sprintf(cli_grab[i].myname,"haha%d",i);
        pthread_create(&p_id[i],0,task,(void*)(&cli_grab[i]));
    }

    sleep(3);
    /*for(int i = 0 ;i<4;i++)//检验生成红包钱
    {
        printf("getMoney = %d\n",getRandomMoney(&cli_grab));
    }*/

    //free(p_id);
    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&lock);
    return 0;
}
