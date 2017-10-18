/*************************************************************************
	> File Name: main.c
	> Author: 
	> Mail: 
	> Created Time: 2017年10月18日 星期三 20时13分01秒
 ************************************************************************/

#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include"thread_pool.h"
void *mytask(void *arg)
{
    printf("thread 0x%0x is working on task %d\n",(int)pthread_self(),*(int*)arg);
    sleep(1);
    free(arg);
    return NULL;
}
int main()
{
    threadpool_t pool;
    threadpool_init(&pool,3);

    int i;
    for(i = 0 ; i < 10;i++)
    {
        int *arg = (int *)malloc(sizeof(int));
        *arg = i;
        threadpool_add_task(&pool,mytask,arg);
    }
    threadpool_destroy(&pool);
    return 0;
}

