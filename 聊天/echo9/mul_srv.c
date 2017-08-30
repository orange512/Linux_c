/*************************************************************************
	> File Name: t_server.c
	> Author: 
	> Mail: 
	> Created Time: Sun 16 Jul 2017 09:19:34 AM CST
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<sys/types.h>  /* See NOTES */
#include<sys/socket.h>
#include<stdlib.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
struct p_info
{
    char name[20];
    int p_group[4];
    char friend[2][20];
}p[10];
struct cli
{
    int sock;
    char name[1024];
    int opt;
}cli[FD_SETSIZE];
void fun(int choose,int conn,int id)
{
    char *buff;
    switch(choose)
    {
        case 1:
        {
            for(int i = 0 ; i < 4; i++)
            {
               sprintf(buff,"%d  ",p[id].p_group[i]);
               send(conn,buff,sizeof(buff),0);
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

        }
    }
}
void Chat(int conn,int choose,int id)
{
    switch(choose)
    {
        case 1:
            fun(conn,choose,id);
            break;
       // case 2:

            
    }
}
void f()
{
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
}
int main()
{
    f();
    int listenfd;
    if((listenfd = socket(PF_INET,SOCK_STREAM,0)) < 0)
        perror("socket");

    struct sockaddr_in serveraddr;
    memset(&serveraddr,0,sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(51880);
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    //serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    //inet_aton("127.0.0.1",&serveraddr.sin_addr);

    int on = 1;

    if(setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on))< 0)//地址重复利用
       perror("setsockopt");
    if(bind(listenfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr)) < 0)
       perror("bind");
    if(listen(listenfd,SOMAXCONN) < 0)
       perror("listen");

    struct sockaddr_in peeraddr;
    socklen_t peer_len;
    char buf[1024];

    int conn;
    int cli[FD_SETSIZE];
    int opt[FD_SETSIZE];
    int i;
    int count = 0;
    for(i = 0;i < FD_SETSIZE; i++)
    {
        cli[i] = -1;
        opt[i] = -1;
    }
    fd_set rset,allset;
    FD_ZERO(&rset);
    FD_ZERO(&allset);
    int maxfd  = listenfd;
    int nready = 0;    
    while(1)
    {
        char name[1024];
        rset = allset;
        FD_SET(listenfd,&rset);

        nready = select(maxfd + 1,&rset,NULL,NULL,NULL);
        if(nready < 0)
            perror("select");
        if(nready = 0)
            continue;
        if(FD_ISSET(listenfd,&rset))
        {
            peer_len = sizeof(peeraddr);
            conn = accept(listenfd,(struct sockaddr *)&peeraddr,&peer_len);
        
            for(i = 0; i < FD_SETSIZE;i++)
            {
                if(cli[i] < 0)
                {
                    cli[i] = conn;
                    break;
                }
            }
            if( i == FD_SETSIZE)
            {
                fprintf(stderr,"超出连接数量");
                exit(EXIT_FAILURE);
            }
            printf("IP = %s PORT = %d\n",inet_ntoa(peeraddr.sin_addr),ntohs(peeraddr.sin_port));
            count++;
            printf("当前连接的人数有%d\n",count);
            FD_SET(conn,&allset);
            if(opt[i] = -1)
            {
                recv(conn,name,sizeof(name),0);
                int j;
                for( j = 0 ; j < 10; j++)
                {
                    if(!strcmp(p[j].name,name))
                    {
                        send(conn,"right",20,0);
                        break;
                    }
                }
                if( j >= 10)
                {
                    send(conn,"error",20,0);
                }
            }
            if(conn > maxfd)
                maxfd = conn;
            if(--nready <= 0)
                continue;
        }
        for(i =0; i < FD_SETSIZE;i++)
        {
            conn = cli[i];
            if(conn == -1)
                continue;
            if(FD_ISSET(conn,&rset))
            {
                memset(buf,0,sizeof(buf));
                int ret = recv(conn,buf,sizeof(buf),0);
                if(ret == -1)
                {
                    perror("read");
                }
                if(ret == 0)
                {
                    count--;
                    cli[i] = -1;
                    char s[1024];
                    sprintf(s,"%sclient close\n",p[i].name);
                    for(i = 0 ; i < FD_SETSIZE;i++)
                    {
                        if(cli[i] > 0)
                        {
                            send(cli[i],s,sizeof(s),0);
                        }
                    }

                    FD_CLR(conn,&allset);
                }
                if(ret > 0)
                {
                    printf("%s:message---->%s\n",name,buf);
                    for(i = 0;i < FD_SETSIZE;i++)
                    {
                        if(cli[i] != conn && cli[i] > 0)
                        {
                            char n[1024];
                            sprintf(n,"%s:message----->",name);
                            strcat(n,buf);
                            send(cli[i],n,sizeof(n),0);
                        }
                    }
                    if( --nready <= 0)
                        break;
                }
            }
        }
    }
    return 0;
}
