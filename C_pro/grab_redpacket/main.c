/*************************************************************************
> File Name: main.c
> Author: 
> Mail: 
> Created Time: 2018年01月15日 星期一 18时35分36秒
************************************************************************/

#include"api_redis.h"
#include"cJSON.h"
#include<glib.h>

GString *get_redis_result(redisContext *c,char *command,GString* str)
{
    redisReply *r = (redisReply *)redisCommand(c,command);
    if(r->type != REDIS_REPLY_STRING)
    {
        printf("执行%s failed\n",command);
        freeReplyObject(r);
        redisFree(c);
        return NULL;
    }
    if(r->type == REDIS_REPLY_NIL)
    {
        freeReplyObject(r);
        redisFree(c);
        return NULL;
    }
    str = g_string_new(r->str);
    freeReplyObject(r);
    return str;
}
int main()
{
    cJSON *json = cJSON_CreateObject();
    cJSON *array = NULL;
    cJSON *obj = NULL;
    cJSON_AddItemToObject(json,"red1",obj=cJSON_CreateObject());
    //cJSON_AddItemToArray(array,obj=cJSON_CreateObject());
    cJSON_AddItemToObject(obj,"total_money",cJSON_CreateString("200"));
    cJSON_AddStringToObject(obj,"num","10");
    cJSON_AddStringToObject(obj,"left_num","4");

    GString *my_buf;
    //将json结构格式化到缓冲区
    my_buf = g_string_new(cJSON_Print(json));
    printf("%s\n",my_buf->str);


    //从缓冲区中解析出JSON结构
    cJSON *json2 = cJSON_Parse(my_buf->str);
    cJSON *node = NULL;
    //cJOSN_GetObjectItem 根据key来查找json节点 若果有返回非空
    node = cJSON_GetObjectItem(json2,"red1");
    if(node == NULL)
    {
        printf("red1 node == NULL\n");
    }
    else
    {
        printf("found red1 node\n");
        if(1 == cJSON_HasObjectItem(node,"total_money"))
        {
            printf("found family node\n");
            node = cJSON_GetObjectItem(node,"total_money");
            if(node->type == cJSON_String)
            {
                printf("buff = %s\n",node->valuestring);
                int money  = atoi(node->valuestring);
                money -= 20;
                sprintf(node->valuestring,"%d",money);
                printf("modifi = %s\n",node->valuestring);
            }
        }
        else
        {
            printf("not found family node\n");
        }
    }

    GString *modify_buf;
    GString *out;
    //将json结构格式化到缓冲区
    modify_buf = g_string_new(cJSON_Print(json2));
    printf("%s\n",modify_buf->str);
    char *set_string = "set red1 ";
    modify_buf = g_string_prepend(modify_buf,set_string);
    printf("%s\n",modify_buf->str);
    printf("%ld\n",modify_buf->len);
    
    redisContext *c = connect_redisContext("127.0.0.1",6379);
    set_redis(c,modify_buf->str);
    out = get_redis_result(c,"get red1",out);
    printf("get red1 %s\n",out->str);
    redis_free(c);
    return 0;
}
