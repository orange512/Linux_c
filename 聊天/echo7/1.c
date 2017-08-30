/*************************************************************************
	> File Name: 1.c
	> Author: 
	> Mail: 
	> Created Time: 2017年08月28日 星期一 16时47分43秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct p_info
{
    char name[20];
    char friend[2][20];
}p[10];

void f()
{
   strcpy(p[0].name,"jake");
   strcpy(p[1].name,"lisa");
   strcpy(p[2].name,"tom");
   strcpy(p[0].friend[0],"lisa");
   strcpy(p[1].friend[0],"jake");
   strcpy(p[0].friend[1],"tom");
}
void fun(int choose,int id)
{
    char buff[1024];
    switch(choose)
    {
       case 1:
        {
            for(int i = 0 ; i < 2; i++)
            {
              // sprintf(buff,"%s  ",p[id].friend[i]);
              // send(conn,buff,sizeof(buff),0);
               printf("%s",p[id].friend[i]);
            }
            break;
        }
       /* case 2:
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
                    sprintf(buff,"创建成功\n");
                    send(conn,buff,sizeof(buff),0);
                    break;
                }
            }
            if(i > 4)
            {
                sprintf(buff,"您的群列表已满\n");
                send(conn,buff,sizeof(buff),0);
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
                    sprintf(buff,"删除成功\n");
                    send(conn,buff,sizeof(buff),0);
                    break;
                }
            }
            if(i > 4)
            {
                sprintf(buff,"没有这个群号\n");
                send(conn,buff,sizeof(buff),0);
            }
            break;

        }*/
    }
}
void Chat(int choose,int id)
{
    switch(choose)
    {
        case 1:
            fun(choose,id);
            break;
       // case 2:

            
    }
}
int main()
{
    f();
    int n;
    scanf("%d",&n);
    Chat(n,1);
    return 0;
}
