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
Node* init()
{
    Node* p = (Node*)malloc(sizeof(Node));
    p -> name = NULL;
    p -> money = 0.0;
    p -> next = NULL;
    return p;
}
Node* tail_Insert(Node* N,char *na,double m)
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
    return N;
}
void print(Node* p)
{
   while(p->next != NULL)
    {
        printf("%s抢到红包金额:%.2lf\n",p->name,p->money);
        p = p->next;
    }
   printf("%s抢到红包金额:%.2lf\n",p->name,p->money);
}
void Max(Node* p)
{
    double Max_money = 0.0;
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
    printf("运气王为%s----抢到的红包金额为%.2lf\n",M_person,Max_money);
}
char* getRandomString(int length)
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
