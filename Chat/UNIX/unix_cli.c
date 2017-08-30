/*************************************************************************
	> File Name: unix_cli.c
	> Author: 
	> Mail: 
	> Created Time: 2017年08月30日 星期三 21时18分52秒
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
void chat(int sock)
{
    char sendbuff[1024];
    char recvbuff[1024];
    int n;
    while(fgets(sendbuff,sizeof(sendbuff),stdin) != NULL)
    {
        send(sock,sendbuff,sizeof(sendbuff),0);
        read(sock,recvbuff,sizeof(recvbuff));
        fputs(recvbuff,stdout);
        memset(sendbuff,0,sizeof(sendbuff));
        memset(recvbuff,0,sizeof(recvbuff));

    }
}
int main()
{
    int sock;
    if((sock = socket(PF_UNIX,SOCK_STREAM,0)) < 0)
        perror("sock");

    struct sockaddr_un serveraddr;
    memset(&serveraddr,0,sizeof(serveraddr));

    serveraddr.sun_family = AF_UNIX;
    strcpy(serveraddr.sun_path,"test_socket");//路径
    if(connect(sock,(struct sockaddr*)&serveraddr,sizeof(serveraddr)) < 0)
        perror("connet");
    chat(sock);
    return 0;
}
