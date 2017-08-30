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
    int sock;
    if((sock = socket(PF_INET,SOCK_STREAM,0)) < 0)
        perror("socket");

    struct sockaddr_in serveraddr;
    memset(&serveraddr,0,sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(51880);
//    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    //inet_aton("127.0.0.1",&serveraddr.sin_addr);
    if(connect(sock,(struct sockaddr*)&serveraddr,sizeof(serveraddr))< 0)
        perror("connect");
    char sendbuff[1024] = {0};
    char recvbuff[1024] = {0};

    while(fgets(sendbuff,sizeof(sendbuff),stdin) != NULL)
    {
        send(sock,sendbuff,sizeof(sendbuff),0);   
        recv(sock,recvbuff,sizeof(recvbuff),0);   

        fputs(recvbuff,stdout);
        memset(sendbuff,0,sizeof(sendbuff));
        memset(recvbuff,0,sizeof(recvbuff));
    }
    close(sock);
    return 0;



}
