/*************************************************************************
	> File Name: link_list.h
	> Author: 
	> Mail: 
	> Created Time: 2017年09月23日 星期六 19时08分52秒
 ************************************************************************/

#ifndef _LINK_LIST_H
#define _LINK_LIST_H
char* string;
typedef struct node
{
    char *name;
    int money;
    struct Node *next;
}Node;

char* getRandomString(int length);
Node* init();
Node* tail_Insert(Node* N,char *na,int m);
void print(Node* p);
void Max(Node* p);

#endif
