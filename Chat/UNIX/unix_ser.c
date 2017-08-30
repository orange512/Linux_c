/*************************************************************************
	> File Name: unix_ser.c
	> Author: 
	> Mail: 
	> Created Time: 2017年08月30日 星期三 20时27分57秒
 ************************************************************************/
#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/un.h>
//unix域协议在同一个主机上传递速度是TCP的两倍，同时也可以传递描述符
void chat(int conn)
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
        printf("recv cli data:%s\n",buf);
        send(conn,buf,ret-1,0);}

    }

/*void chat(int conn)
{
    char buff[1024];
    int n;
    while(1)
    {
        memset(buff,0,sizeof(buff));
        n = read(conn,buff,sizeof(buff));
        if(n == -1)
            perror("read");
        if(n == 0)
        {
            printf("client close\n");
            exit(EXIT_SUCCESS);
        }
        fputs(buff,stdout);
        send(conn,buff,sizeof(buff),0);

    }
    close(conn);
}*/
int main()
{
    int listenfd;
    if((listenfd = socket(PF_UNIX,SOCK_STREAM,0)) < 0)
        perror("sock");

    struct sockaddr_un serveraddr;
    memset(&serveraddr,0,sizeof(serveraddr));

    unlink("test_socket");//解决重复绑定问题
    serveraddr.sun_family = AF_UNIX;
    strcpy(serveraddr.sun_path,"test_socket");//路径
    if(bind(listenfd,(struct sockaddr *)&serveraddr,sizeof(serveraddr)) < 0)
        perror("bind");
    if(listen(listenfd,SOMAXCONN) < 0)
        perror("listen");
    
    int conn;
    pid_t pid;
    while(1)
    {
        conn = accept(listenfd,NULL,NULL);
        if(conn == -1)
        {
            if(conn == EINTR)
                continue;
            perror("accept");
        }
        pid =fork();
        if(pid == -1)
            perror("fork");
        if(pid == 0)
        {
            close(listenfd);
            chat(conn);
            exit(EXIT_SUCCESS);
        }
        else
        {
            close(conn);
        }
    }

}
