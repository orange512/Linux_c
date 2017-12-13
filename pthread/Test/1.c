/*************************************************************************
	> File Name: 1.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月23日 星期六 20时00分00秒
 ************************************************************************/

#include<stdio.h>
#include"link_list.h"
int main()
{
    Node *p;
    p = init();
    tail_Insert(p,"liuzhuo",2.3);
    tail_Insert(p,"ddddd",2.5);
    print(p);
    Max(p);
}
