/*************************************************************************
	> File Name: mypro_con.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月17日 星期日 15时53分56秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#define PRODUCE_COUNT 1
#define CONSUM_COUNT 3
#define BUFFSIZE 4
int g_buff[BUFFSIZE];
pthread_t g_pthread[PRODUCE_COUNT+CONSUM_COUNT];
int in = 0;
int out = 0;
unsigned short  int produce_id = 0;
unsigned short int consumer_id = 0 ; 

sem_t semfull;
sem_t semempty;
pthread_mutex_t lock;

void* pro(void *p)
{
    int i;
    int num = (int)p;
    while(1)
    {
        printf("%d 等待数组满\n",num);
        sem_wait(&semfull);
        pthread_mutex_lock(&lock);
        for(i = 0 ; i <BUFFSIZE;i++ )
        {
            printf("%02d ",i);
            if(g_buff[i] == -1)
                printf("NULL\n");
            else
                printf("%d",g_buff[i]);
            if(i == in)
                printf("\t<--------produce");
            putchar(10);
        }
        printf("%d 开始生产产品%d\n",num,produce_id);
        g_buff[in] = produce_id;
        in = (in + 1) % BUFFSIZE;
        printf("%d结束生产产品%d\n",num,produce_id++);

        pthread_mutex_unlock(&lock);
        sem_post(&semempty);
        sleep(5);
        
    }
    return NULL;
}
void* con(void *p)
{
    int i;
    int num = (int)p;
    while(1)
    {
        printf("%d 等待数组空\n",num);
        sem_wait(&semempty);
        pthread_mutex_lock(&lock);
        for(i = 0 ; i <BUFFSIZE;i++ )
        {
            printf("%02d ",i);
            if(g_buff[i] == -1)
                printf("NULL\n");
            else
                printf("%d",g_buff[i]);
            if(i == in)
                printf("\t<--------consume");
            putchar(10);
        }
        printf("%d 开始消费产品%d\n",num,consumer_id);
        g_buff[out] = consumer_id;
        out = (out + 1) % BUFFSIZE;
        printf("%d结束消费产品%d\n",num,consumer_id++);

        pthread_mutex_unlock(&lock);
        sem_post(&semfull);
        sleep(1);
        
    }
    return NULL;
}





int main()
{
    sem_init(&semfull,0,PRODUCE_COUNT);
    sem_init(&semempty,0,CONSUM_COUNT);
    pthread_mutex_init(&lock,0);
    for(int i = 0 ; i < PRODUCE_COUNT;i++)
    {
        pthread_create(&g_pthread[i],0,pro,(void *)i);
        
    }
    for(int j = 0 ; j < CONSUM_COUNT;j++)
    {
        pthread_create(&g_pthread[j],0,con,(void *)j);
        
    }
    for(int k = 0;k < PRODUCE_COUNT+CONSUM_COUNT;k++)
    {
        pthread_join(g_pthread[k],0);
    }
}
