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
#include<pthread.h>

void mulchat(int conn)
{
    char buf[1024];
    while(1)
    {
        memset(buf,0,sizeof(buf));
        int ret = recv(conn,buf,sizeof(buf),0);
        if(ret == -1)
        {
            perror("read");
        }
        if(ret == 0)
        {
            printf("client close\n");
            break;
        }
        {        //fputs(buf,stdout);
        printf("recv cli data[%d]:%s\n", ret,buf);
        send(conn,buf,ret-1,0);}

    }
}
void * posix(void *arg)
{
    pthread_detach(pthread_self());
    int conn = *(int *)arg;
    mulchat(conn);
    printf("exiting thread ...\n");
    return NULL;
}

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
    socklen_t peer_len = sizeof(peeraddr);

    int conn;
    while(1)
    {
        conn = accept(listenfd,(struct sockaddr *)&peeraddr,&peer_len);
        printf("IP = %s PORT = %d\n",inet_ntoa(peeraddr.sin_addr),ntohs(peeraddr.sin_port));
        int *p =malloc(sizeof(int));
        *p = conn;
        pthread_t tid;
        int ret;
        if(ret = pthread_create(&tid,NULL,posix,p) != 0)
        {
            fprintf(stderr,"pthread_create%s\n",strerror(ret));
            exit(EXIT_FAILURE);
        }
    }
    return 0;
}
