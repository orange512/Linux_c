/*************************************************************************
	> File Name: mq_attr.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月27日 星期三 18时37分02秒
 ************************************************************************/

#include<stdio.h>
#include"mq.h"

int main()
{
    mqd_t mqid;
    mqid = mq_open("/abc",O_RDONLY);
    if(mqid < 0)
        perror("mq_open"),exit(-1);
    struct mq_attr attr;
    mq_getattr(mqid,&attr);

    printf("mq_maxmsg = %lu\tmq_msgsize = %lu\tmq_curmsgs = %lu\n",attr.mq_maxmsg,attr.mq_msgsize,attr.mq_curmsgs);
    mq_close(mqid);
    return 0;
}
