/*************************************************************************
	> File Name: attr.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月16日 星期六 09时36分28秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<limits.h>
#include<pthread.h>
pthread_attr_t attr;

void* task(void *p)
{
    printf("I'm new thread 1\n");
    size_t stacksize;
#ifdef _POSIX_THREAD_ATTR_STACKSIZE
    pthread_attr_getstacksize(&attr,&stacksize);
    printf("before stack size = %d\n",(int)stacksize);
    pthread_attr_setstacksize(&attr,16389);
    pthread_attr_getstacksize(&attr,&stacksize);
    printf("after stack size = %d\n",(int)stacksize);
#endif

}
int main()
{
    pthread_t tid;
    int err;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
#ifdef _POSIX_THREAD_ATTR_STACKSIZE   //检查系统是否支持线程栈属性
    pthread_attr_setstacksize(&attr,PTHREAD_STACK_MIN);//设置栈最小
#endif
    err = pthread_create(&tid,&attr,task,NULL);
    if(err)
    {
        printf("create thread1 failed\n");
        return -1;
    }
    else
        printf("create thread1 success\n");
    pthread_join(tid,NULL);
    return 0;


}
