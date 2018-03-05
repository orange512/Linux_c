/*************************************************************************
	> File Name: mysql.c
	> Author: 
	> Mail: 
	> Created Time: 2017年10月17日 星期二 21时28分06秒
 ************************************************************************/
#include<stdio.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<mysql/mysql.h>
#include"cJSON.h"
int main()
{
    int ret=0;
    MYSQL mysql;
    MYSQL *connect = NULL;
    connect = mysql_init(&mysql);
    if(connect == NULL)
    {
        ret = mysql_errno(&mysql);
        printf("mysql_init error,%s\n",mysql_error(&mysql));
        return ret;
    }
    printf("mysql_init ok...\n");
    connect = mysql_real_connect(connect,"localhost","root","950512","student",0,NULL,0);
    if(connect == NULL)
    {
        ret = mysql_errno(&mysql);
        printf("mysql_real_connect error,err is:%s\n",mysql_error(&mysql));
        return ret;
    }
    printf("mysql_real_connect ok...\n");
    cJSON *json = cJSON_CreateObject();

    //向文档中增加一个键值对{"name":"王大锤"}
    cJSON_AddItemToObject(json,"name",cJSON_CreateString("王大锤"));
    //向文档中添加一个键值对
    //cJSON_AddItemToObject(json,"age",cJSON_CreateNumber(29));
    cJSON_AddNumberToObject(json,"age",29);

    /*cJSON *array = NULL;
    cJSON_AddItemToObject(json,"love",array=cJSON_CreateArray());
    cJSON_AddItemToArray(array,cJSON_CreateString("LOL"));
    cJSON_AddItemToArray(array,cJSON_CreateString("NBA"));
    cJSON_AddItemToArray(array,cJSON_CreateString("Go shopping"));*/

    cJSON_AddNumberToObject(json,"score",59);
    cJSON_AddStringToObject(json,"address","beijing");

    //将json结构格式化到缓冲区
    char *buf = cJSON_Print(json);
    printf("%s\n",buf);
    char query[1024];
    sprintf(query,"insert into redpacket(username) values %s",buf);
    ret = mysql_query(connect,query);
    if(ret != 0)
    {
        printf("mysql_query error\n");
        return ret;
    }
    MYSQL_RES *result = mysql_store_result(&mysql);
    if(result == NULL)
    {
        printf("mysql_store_result error\n");
        return -1;
    }
    int field_num = mysql_field_count(&mysql);
    MYSQL_FIELD *fields = mysql_fetch_fields(result);//列名
    printf("-------------------------------------\n");
    for(int i = 0 ; i < field_num;i++)
    {
        printf("%s \t",fields[i].name);
    }
    printf("\n------------------------------------\n");
    //表内容
    MYSQL_ROW row = NULL;
    while(row = mysql_fetch_row(result))
    {
        for(int i = 0 ; i < field_num;i++)
        {
            printf("%s \t",row[i]);
        }
        putchar(10);
    }
    mysql_free_result(result);
    mysql_close(connect);
    printf("mysql_close\n");
    return ret;
}
