/*************************************************************************
	> File Name: pthread1.c
	> Author: 
	> Mail: 
	> Created Time: Mon 21 Aug 2017 09:41:54 PM CST
 ************************************************************************/

#include<stdio.h>
#include<pthread.h>
#include <unistd.h>
#include<string.h>
#include<stdlib.h>
void* thread_routine(void* arg)
{
    for(int i = 0 ; i < 20;i++)
    {
        printf("B");
        fflush(stdout);
        //if( i == 3 )
         //    pthread_exit("OPI");
        usleep(20);
    }
    sleep(3);
    return "EDF\n";
}
int main()
{
    pthread_t tid;
    int ret;
    if(ret = pthread_create(&tid,NULL,thread_routine,NULL) != 0)
    {
        fprintf(stderr,"pthread_create error%s",strerror(ret));//创建失败返回的错误为错误码
        exit(EXIT_FAILURE);
    }

    for(int i = 0 ; i < 20;i++)
    {
        printf("A");
        fflush(stdout);
        usleep(20);//让主进程和创建到的进程并行运行
    }
    putchar(10);
    void *value;
    if(ret = pthread_join(tid,&value) != 0)//等待创建的进程退出在结束程序，进程结束时返回的字符保存载alue里
    {
        fprintf(stderr,"pthread_join%s",strerror(ret));//创建失败返回的错误为错误码
        exit(EXIT_FAILURE);
        
    }
    printf("recv msg %s\n",(char *)value);
    return 0;
}
