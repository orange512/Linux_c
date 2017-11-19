/*************************************************************************
	> File Name: thread_stack.c
	> Author: 
	> Mail: 
	> Created Time: 2017年11月07日 星期二 17时04分00秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#define N 2
void *thread_proc(void *param)
{
    int first = 0;
    int *p = malloc(1024);
    printf("(0x%x):first = %p\n",pthread_self(),&first);
    printf("(0x%x):p = %p\n",pthread_self(),p);
    return NULL;
}
int main()
{
    int first = 0;
    int i = 0 ;
    void *ret = NULL;
    pthread_t tid[N] = {0};
    printf("main->first:%p\n",&first);
    for(int i = 0; i < N;i++)
    {
        pthread_create(&tid[i],NULL,thread_proc,NULL);
    }
    pause();
    return 0;
}
