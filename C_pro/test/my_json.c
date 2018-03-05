/*************************************************************************
	> File Name: my_json.c
	> Author: 
	> Mail: 
	> Created Time: 2018年02月26日 星期一 20时13分15秒
 ************************************************************************/

/*#include<stdio.h>
#include<stdlib.h>
#include"cJSON.h"

int main(void)
{
    char *data = "{\"love\":[\"LOL\",\"Go shopping\"]}";
    //从缓冲区中解析出JSON结构
    cJSON * json= cJSON_Parse(data);

    //将传入的JSON结构转化为字符串 并打印
    char *json_data = NULL;
    printf("data:%s\n",json_data = cJSON_Print(json));

    free(json_data);
    //将JSON结构所占用的数据空间释放
    cJSON_Delete(json);
    return 0;

}*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"cJSON.h"

int main(void)
{
    //创建一个空的文档（对象）
    cJSON *json = cJSON_CreateObject();

    //向文档中增加一个键值对{"name":"王大锤"}
    cJSON_AddItemToObject(json,"name",cJSON_CreateString("王大锤"));
    //向文档中添加一个键值对
    //cJSON_AddItemToObject(json,"age",cJSON_CreateNumber(29));
    cJSON_AddNumberToObject(json,"age",29);

    cJSON *array = NULL;
    cJSON_AddItemToObject(json,"love",array=cJSON_CreateArray());
    cJSON_AddItemToArray(array,cJSON_CreateString("LOL"));
    cJSON_AddItemToArray(array,cJSON_CreateString("NBA"));
    cJSON_AddItemToArray(array,cJSON_CreateString("Go shopping"));

    cJSON_AddNumberToObject(json,"score",59);
    cJSON_AddStringToObject(json,"address","beijing");

    //将json结构格式化到缓冲区
    char *buf = cJSON_Print(json);
    printf("data = %s \n",buf);
    //打开文件写入json内容
/*    FILE *fp = fopen("create.json","w");
    fwrite(buf,strlen(buf),1,fp);*/
    free(buf);
//    fclose(fp);
    //释放json结构所占用的内存
    cJSON_Delete(json);
    return 0;

}
