/*************************************************************************
	> File Name: 1.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月24日 星期日 10时28分39秒
 ************************************************************************/

#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

void *task(void* arg)
{
    printf("hello\n");
}

int main()
{
    int n;
    int err;
    scanf("%d",&n);
    pthread_t *pi = malloc(sizeof(pthread_t)*n);
    for(int i = 0 ; i < n;i++)
    if((err = pthread_create(&pi[i],0,task,0)) != 0)
    {
        printf("error\n");
    }
    for(int i = 0 ; i > n; i++)
    {
        pthread_join(pi[i],0);
    }
}
