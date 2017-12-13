/*************************************************************************
	> File Name: 1.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月19日 星期二 19时20分20秒
 ************************************************************************/

#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
int num;
pthread_mutex_t mutex;

void *task1(void *p)
{
    printf("I am thread1\n");
   // pthread_mutex_lock(&mutex);
    printf("1before num = %d\n",num);
    num++;
    printf("1after num = %d\n",num);
  //  pthread_mutex_unlock(&mutex);
}

void *task2(void *p)
{
    printf("I am thread2\n");
    pthread_mutex_lock(&mutex);
    printf("2before num = %d\n",num);
    num++;
    sleep(2);
    printf("2 after num = %d\n",num);
    pthread_mutex_unlock(&mutex);
}
int main()
{
    pthread_t tid1,tid2;
    pthread_mutex_init(&mutex,0);
    pthread_create(&tid1,0,task1,NULL);
    pthread_create(&tid2,0,task2,NULL);
    pthread_join(tid1,0);
    pthread_join(tid2,0);
    printf("num = %d\n",num);
    pthread_mutex_destroy(&mutex);
}
