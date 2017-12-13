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

int main()
{
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
    int i;
    for(i = 0;i < FD_SETSIZE; i++)
    {
        cli[i] = -1;
    }
    fd_set rset,allset;
    FD_ZERO(&rset);
    FD_ZERO(&allset);
    int maxfd  = listenfd;
    int nready = 0;    
    while(1)
    {
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
                int ret = recv(conn,buf,sizeof(buf),0);
                if(ret == -1)
                {
                    perror("read");
                }
                if(ret == 0)
                {
                    cli[i] = -1;
                    char s[1024];
                    sprintf(s,"%sclient close\n",s);
                    for(i = 0 ; i < FD_SETSIZE;i++)
                    {
                        if(cli[i] > 0)
                        {
                            send(cli[i],s,sizeof(s),0);
                        }
                    }

                    FD_CLR(conn,&allset);
                }
                //fputs(buf,stdout);
                printf("recv cli data:%s\n",buf);
                for(i = 0;i < FD_SETSIZE;i++)
                {
                    if(cli[i] != conn)
                    {
                        send(cli[i],buf,ret-1,0);

                    }
                }
                if( --nready <= 0)
                    break;
            }
        }
    }
    return 0;
}
