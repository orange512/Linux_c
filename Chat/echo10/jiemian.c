/*************************************************************************
	> File Name: jiemian.c
	> Author: 
	> Mail: 
	> Created Time: Mon 21 Aug 2017 10:41:01 AM CST
 ************************************************************************/

#include<stdio.h>
#include<string.h>
struct p_info
{
    char name[20];
    int p_group[4];
    char friend[2][20];
}p[10];
void menu(int id);
int my_printf();
void group_chating(int id);
int main()
{
   int id = 0;
   strcpy(p[0].name,"jake");
   strcpy(p[1].name,"lisa");
   strcpy(p[2].name,"tom");
   p[1].p_group[0] = 1;
   p[1].p_group[1] = 2;
   p[0].p_group[0] = 1;
   p[2].p_group[0] = 2;
   strcpy(p[0].friend[0],"lisa");
   strcpy(p[1].friend[0],"jake");
   strcpy(p[0].friend[1],"tom");
   id = my_printf(); 
   if(id > 0)
   {
       menu(id);
   }
}
void watch( int id)
{
    for(int j = 0 ; j < 2; j++)
    {
        printf("%s ",p[id].friend[j]);
    }
    putchar(10);
    
}
void peer_chating(int id)
{
    char *name;
    for(int j = 0 ; j < 2; j++)
    {
        printf("%s ",p[id].friend[j]);
    }
    putchar(10);
    printf("请输入你想聊天的好友\n");
    scanf("%s",name);
    int j = 0;
    for(j = 0 ; j < 2; j++)
    {
        if(strcmp(name,p[id].friend[j]))
        {

        }
    }
    if(j > 2)
    {
        printf("没有你要找的用户\n");
    }
    

    
}
int my_printf()
{
    char info[1024];
    printf("请输入你的姓名\n");
    scanf("%s",info);
    int id = 0;
    for( id = 0 ; id < 10;id++)
    {
       if(strcmp(info,p[id].name) == 0)
       {
           printf("欢迎登录\n");
           printf("您的信息如下：\n");
           printf("您的群组号为：%d\n",p[id].p_group[0]);
           printf("好友列表：\n");
           for(int j = 0 ; j < 2; j++)
           {
               printf("%s ",p[id].friend[j]);
           }
           putchar(10);
           return id;
       }
    }
    if(id > 10)
    {
        printf("登录失败\n");
        menu(id);
        return -1;
    }
}
void menu(int id)
{
    int choose = 0;
    printf("\n请输入你的选项\n");
    printf("\n1:群聊\n2:查看好友列表\n3:向跟好友聊天\n4:查看自己未接受到的信息\n");
    scanf("%d",&choose);

    switch(choose)
    {
        case 1:
        {
            group_chating(id);
            break;
        }
        case 2:
        {
            watch(id);
            break;
        }
        case 3:
        {
            peer_chating(id);
            break;
        }
        case 4:
        {
         //   history();
            break;
        }
    }
    if(id > 10)
    {
        printf("\n请您先进行注册\n");
    }
}


void group_chating(int id)
{
    int n = 0;
    printf("\n1:查看自己拥有的群组\n2:创建自己的群组\n3:删除群聊号\n4:加入群聊\n");
    scanf("%d",&n);
    switch(n)
    {
        case 1:
        {
            for(int i = 0 ; i < 4; i++)
            {
                printf("%d  ",p[id].p_group[i]);
            }
            putchar(10);
            break;
        }
        case 2:
        {
            int group_id;
            int i = 0 ;
            printf("请输入你想创建的群聊号:");
            scanf("%d",&group_id);
            for(i = 0;i < 4;i++)
            {
                if(p[id].p_group[i] == 0)
                {
                    p[id].p_group[i] = group_id;
                    printf("创建成功");
                    break;
                }
            }
            if(i > 4)
            {
                printf("您的群列表已满\n");
            }
            break;

        }
        case 3:
        { 
            int group_id;
            int i = 0;
            printf("请输入你想删除的群聊号:");
            scanf("%d",&group_id);
            for(i = 0;i < 4;i++)
            {
                if(p[id].p_group[i] == group_id)
                {
                    p[id].p_group[i] = 0;
                    printf("删除成功");
                    break;
                }
            }
            if(i > 4)
            {
                printf("没有这个群号\n");
            }
            break;
               
        }
        case 4:
        {
            int group_id;
            int i = 0;
            printf("请输入你想进入的群聊:");
            scanf("%d",&group_id);
            for(i = 0;i < 4;i++)
            {
                if(p[id].p_group[i] == group_id)
                {
                }
            }
            if(i > 4)
            {
                printf("没有这个群号\n");
            }
        }
    }
    menu(id);

}
