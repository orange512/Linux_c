/*************************************************************************
	> File Name: link_list.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月23日 星期六 14时21分35秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef int ElementType;
typedef struct node
{
    ElementType data;
    struct Node *next;
}Node;
typedef Node* list;
list init()
{
    list p = (list)malloc(sizeof(Node));
    p -> data = 0;
    p -> next = NULL;
    return p;
}
Node* tail_Insert(Node* N,ElementType elem)
{
    Node *tmp = N;
    while(tmp->next != NULL)
    {
        tmp = tmp->next;
    }
    Node* p  = (Node*)malloc(sizeof(Node));
    tmp -> next = p;
    p -> data = elem;
    p -> next = NULL;
    return N;
}
/*Node* Delete(Node *p,ElementType elem)
{
    Node *tmp = p;
    tmp = tmp -> next;
    while(tmp -> next != NULL)
    {
        if(tmp -> data == elem)
            break;
        tmp = tmp -> next;
    }
    Node* m = tmp;
    tmp = tmp -> next;
    free(m);
    return p;
}*/
Node* head_Insert(Node* p,ElementType elem)
{
    Node* tmp = (Node*)malloc(sizeof(Node));
    tmp -> data = elem;
    tmp -> next = p;
    return tmp;
}
void print(Node* p)
{
   while(p->next != NULL)
    {
        printf("%d\n",p->data);
        p = p->next;
    }
    printf("%d\n",p->data);
}
int main()
{
    list a = init();
    a = tail_Insert(a,3);
    a = head_Insert(a,4);
    print(a);
    printf(".................\n");
    a = Delete(a,3);
    print(a);


    return 0;
}
