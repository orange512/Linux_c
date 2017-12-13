/*************************************************************************
	> File Name: link_redis.c
	> Author: 
	> Mail: 
	> Created Time: 2017年12月01日 星期五 20时34分46秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<stddef.h>
#include<stdarg.h>
#include<string.h>
#include<assert.h>
#include<hiredis/hiredis.h>
void doTest()
{
    redisContext *c = redisConnect("127.0.0.1",6379);
    if(c->err)
    {
        redisFree(c);
        printf("连接redis失败\n");
        return;
    }
    printf("连接redis成功\n");

    const char* command1 = "set k1 hello";
    redisReply *r = (redisReply *)redisCommand(c,command1);
    if(NULL == r)
    {
        printf("执行命令1失败\n");
        redisFree(c);
        return;
    }
    if(!(r->type == REDIS_REPLY_STATUS && strcasecmp(r->str,"OK") ==0))
    {
        printf("执行command1%s failed\n",command1);
        freeReplyObject(r);
        redisFree(c);
        return;
    }
    freeReplyObject(r);
    printf("成功执行command1:%s\n",command1);

    const char *command2 = "strlen k1";
    r = (redisReply *)redisCommand(c,command2);
    if(r->type != REDIS_REPLY_INTEGER)
    {
        printf("执行command2%s failed\n",command2);
        freeReplyObject(r);
        redisFree(c);
        return;
    }
    int length = r->integer;
    freeReplyObject(r);
    printf("the length of 'k1'is%d\n",length);
    printf("成功执行command2:%s\n",command2);


    const char *command3 = "get k1";
    r = (redisReply *)redisCommand(c,command3);
    if(r->type != REDIS_REPLY_STRING)
    {
        printf("执行command3%s failed\n",command3);
        freeReplyObject(r);
        redisFree(c);
        return;
    }
    printf("the value of'k1'is%s\n",r->str);
    freeReplyObject(r);
    printf("成功执行command3:%s\n",command3);

    const char *command4 = "get f1";
    r = (redisReply *)redisCommand(c,command4);
    if(r->type != REDIS_REPLY_NIL)
    {
        printf("执行command4%s failed\n",command4);
        freeReplyObject(r);
        redisFree(c);
        return;
    }
    freeReplyObject(r);
    printf("成功执行command3:%s\n",command3);

    redisFree(c);

    
}
int main()
{
    doTest();
    return 0;
}
