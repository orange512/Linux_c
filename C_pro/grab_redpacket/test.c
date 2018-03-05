/*************************************************************************
	> File Name: test.c
	> Author: 
	> Mail: 
	> Created Time: 2018年03月05日 星期一 17时39分07秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<hiredis/hiredis.h>
int main()
{
    redisContext *c = redisConnect("127.0.0.1",6379);
    char buff[1024];
    sprintf(buff,"hmget red001 total_money num left_num");

    redisReply *r = (redisReply *)redisCommand(c,buff);
    printf("%d\n",(int)r->elements);
    while(r->elements--)
    {
        printf("%s\n",r->element[r->elements]->str);
    }

}
