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
void menu()
{
    printf("\t\t----请输入你的选项：(退出选择请输入exit)\n\n");
    printf("\t\t\t----1:查看自己的好友列表--\n\n");
    printf("\t\t\t----2:发起群聊---\n\n");
    printf("\t\t\t----3:发信息给好友(输入格式：3 好友名字)---\n\n");
}

int main(int argc,char *argv[])
{
    printf("\t\t------这是一个简单的聊天程序\n--------");
    
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
    fd_set rset;
    FD_ZERO(&rset);
    int nready = 0;
    int maxfd;
    int std = fileno(stdin);
    if(std > sock)
        maxfd = std;
    else
        maxfd = sock;
    char name[1024];
    char enter[1024];
    printf("请输入你的姓名:\n");
    scanf("%s",name);
    getchar();
    send(sock,name,sizeof(name),0);
    recv(sock,enter,sizeof(enter),0);
    if(!strcmp(enter,"error"))
    {
        printf("对不起，你的信息有误，请重新启动\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("登录成功\n");
        menu();
    }

    while(1)
    {
        FD_SET(sock,&rset);
        FD_SET(std,&rset);

        nready = select(maxfd + 1,&rset,NULL,NULL,NULL);
        if(nready < 0)
            perror("select");
        if(nready = 0)
            continue;
        if(FD_ISSET(sock,&rset))
        {
            int ret = recv(sock,recvbuff,sizeof(recvbuff),0);
            if(ret == -1)
                perror("recv");
            if(ret == 0)
            {
                printf("server close\n");
                exit(EXIT_SUCCESS);
            }
            fputs(recvbuff,stdout);
            putchar(10);
            fflush(stdout);
            memset(recvbuff,0,sizeof(recvbuff));
        }
        if(FD_ISSET(std,&rset))
        {
           if(fgets(sendbuff,sizeof(sendbuff),stdin) == NULL)
                break;
            send(sock,sendbuff,sizeof(sendbuff),0);
            memset(sendbuff,0,sizeof(sendbuff));
            
        }
    }
    close(sock);
    return 0;

}
