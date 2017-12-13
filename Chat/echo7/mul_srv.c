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
    int friend[2];
    int cliid;
}p[10];
void fun(int conn,int id)
{
    char buff[1024];
    for(int i = 0 ; i < 2; i++)
    {
        sprintf(buff,"%s  ",p[p[id].friend[i]].name);
        send(conn,buff,sizeof(buff),0);
    }
}
void Chat(int conn,int choose,int id)
{
    switch(choose)
    {
        case 1:
            fun(conn,id);
            break;
        case 2:
           // group_chat(conn,id,cli,name,buf);
            break;
    }
}
void f()
{
   strcpy(p[0].name,"jake");
   strcpy(p[1].name,"lisa");
   strcpy(p[2].name,"tom");
   p[0].friend[0] = 1;
   p[0].friend[1] = 2;
   p[1].friend[0] = 0;
   p[1].friend[1] = 2;
   p[2].friend[0] = 0;
   p[2].friend[0] = 1;
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
    int cli[FD_SETSIZE];//客户端数组
    int mark[FD_SETSIZE];//标记用户输入模式 -1是
    int id[FD_SETSIZE];//标记登录人的id
    int obj[FD_SETSIZE];
    int i;
    int count = 0;
    for(i = 0;i < FD_SETSIZE; i++)
    {
        cli[i] = -1;
        id[i] = -1;
        mark[i] = -2;
        obj[i] = -1;
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
        //监听客户端连接
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
                    for(int k = 0 ; k < 10;k++)
                    {
                        if(p[k].cliid == i)
                        {
                            p[k].cliid = -1;
                        }
                    }
                    char s[1024];
                    sprintf(s,"%sclient close\n",p[i].name);
                    printf("当前连接的人数有%d\n",count);
                    for(i = 0 ; i < FD_SETSIZE;i++)
                    {
                        if(cli[i] > 0)
                        {
                            send(cli[i],s,sizeof(s),0);
                        }
                    }

                    FD_CLR(conn,&allset);
                    break;
                }
                if(mark[i] == 1)
                {
                    char *p3 = buf;
                    while(*p3 != '\n')p3++;
                    *p3 = '\0';
                    if(!strcmp(buf,"exit"))
                    {
                        mark[i] = -1;
                    }
                    char n[1024];
                    sprintf(n,"%s:privacy message--->",p[id[i]].name);
                    strcat(n,buf);
                    send(cli[obj[i]],n,sizeof(n),0);
                }
                if(mark[i] == 0)
                {
                    char *p3 = buf;
                    while(*p3 != '\n')p3++;
                    *p3 = '\0';
                    if(!strcmp(buf,"exit"))
                    {
                        mark[i] = -1;
                    }
                    printf("%s:public message---->%s\n",p[id[i]].name,buf);
                    for(int k  = 0;k < FD_SETSIZE;k++)
                    {
                        if(cli[k] != conn && cli[k] > 0)
                        {
                            char n[1024];
                            sprintf(n,"%s:public message----->",p[id[i]].name);
                            strcat(n,buf);
                            send(cli[k],n,sizeof(n),0);
                        }
                    }
                    if( --nready <= 0)
                        break;
                }
               if(mark[i] == -1)
                {
                    char *p1 = strtok(buf," ");
                    int k = 0;
                    if(p1 != NULL)
                    {
                        k  = atoi(p1);
                    }

                    if( k == 2)
                    {
                        mark[i] = 0;
                    }
                    if( k == 3 )
                    {
                        char *p2 = strtok(NULL," ");
                        if(p2 == NULL)
                        {
                            send(conn,"error",10,0);
                            continue;

                        }
                        char *p3 = p2;
                        while(*p3 != '\n')p3++;
                        *p3 = '\0';
                        int j = 0;
                        while(j < 2)
                        {
                            if(!strcmp(p[p[i].friend[j]].name,p2))
                            {
                                obj[i] = p[p[i].friend[j]].cliid;
                                break;
                            }
                            j++;

                        }
                        if(j >= 2)
                        {
                            send(conn,"对不起你没有这个好友",20,0);
                            continue;

                        }
                        mark[i] = 1;
                    }

                    Chat(conn,k,id[i]);
                }
                //验证连接客户是否正确
                if(mark[i] == -2)
                {
                    int j;
                    for( j = 0 ; j < 10; j++)
                    {
                        if(!strcmp(p[j].name,buf))
                        {
                            p[j].cliid = i;
                            id[i] = j;
                            mark[i] = -1;
                            break;
                        }
                    }
                    if( j > 10)
                    {
                        send(conn,"error",20,0);
                    }
                }
            }
        }
    }
    return 0;
}
