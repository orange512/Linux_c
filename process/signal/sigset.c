/*************************************************************************
	> File Name: sigset.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月10日 星期日 21时08分11秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<signal.h>

void handle(int sig)
{
    printf("捕获的信号为%d\n",sig);
}
int main()
{
    printf("sizeof(sigset_t) = %d\n",sizeof(sigset_t));
    sigset_t set;
    sigemptyset(&set);
    printf("set = %d\n",set);
    sigaddset(&set,5);
    printf("sig 2 = %d\n",set);
    sigaddset(&set,3);
    printf("sig 3 = %d\n",set);
    sigaddset(&set,10);
    printf("sig 50 = %d\n",set);
    sigdelset(&set,3);
    printf(" del sig 3 = %d\n",set);
    if(sigismember(&set,2))
        printf("信号2在set里\n");

}
