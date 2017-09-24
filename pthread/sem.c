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
#include <semaphore.h>

int size = 0;
char *arr[5];
sem_t sem;
void* task(void *p)
{
    sem_wait(&sem);
    arr[size] = (char *)p;
    sleep(1);
    size++;
    sem_post(&sem);
}


int main()
{
    sem_init(&sem,0,1);
    arr[size] = "zhangsan";
    size++;
    pthread_t id1,id2;
    pthread_create(&id1,0,task,"lisi");
    pthread_create(&id2,0,task,"wangwu");
    pthread_join(id1,0);
    pthread_join(id2,0);
    for(int i = 0 ; i < size;i++)
        printf("%s\n",arr[i]);

    sem_destroy(&sem);

}
