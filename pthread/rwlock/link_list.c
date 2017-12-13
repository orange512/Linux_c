/*************************************************************************
	> File Name: link_list.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月23日 星期六 14时21分35秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"link_list.h"
Node* init()//初始化
{
    Node* p = (Node*)malloc(sizeof(Node));
    p -> name = NULL;
    p -> money = 0;
    p -> next = NULL;
    return p;
}
Node* tail_Insert(Node* N,char *na,int m)//插入信息
{
    if(N != NULL)
    {
        Node *tmp = N;
        while(tmp->next != NULL)
        {
            tmp = tmp->next;
        }
        Node* p  = (Node*)malloc(sizeof(Node));
        tmp -> next = p;
        p -> name = na;
        p -> money = m;
        p -> next = NULL;
    }
    return N;
}
void print(Node* p)//打印信息
{
   while(p->next != NULL)
    {
        p = p->next;
        printf("\n%s抢到红包金额:%d.%d%d元\n",p->name,p->money/100,(p->money/10)%10,p->money%10);
    }
}
void Max(Node* p)//最大抢到的红包
{
    int  Max_money = 0;
    char *M_person;
    while(p -> next != NULL)
    {
        if(p->money > Max_money)
        {
            Max_money = p->money;
            M_person = p -> name;
        }
        p = p -> next;
    }
    if(p->money > Max_money)
    {
        Max_money = p->money;
        M_person = p -> name;
    }
    printf("\n运气王为%s----抢到的红包金额为%d.%d%d元\n",M_person,Max_money/100,(Max_money/10)%10,Max_money%10);
}
char* getRandomString(int length)//生成随机字符串
{
    int flag, i;
    srand((unsigned) time(0)*rand());
    if ((string = (char*) malloc(sizeof(char)*length)) == NULL )
    {
        printf("Malloc failed!\n");
        return NULL ;

    }
    for (i = 0; i < length - 1; i++)
    {
        flag = rand() % 4;
        switch (flag)
        {
            case 0:
            string[i] = 'A' + rand() % 26;
            break;
            case 1:
            string[i] = 'a' + rand() % 26;
            break;
            case 2:
            string[i] = 'A' + rand() % 26;
            break;
            case 3:
            string[i] = 'b' + rand() % 25;
            default:
            string[i] = 'x';
            break;

        }

    }
    string[length - 1] = '\0';
    return string;
}
