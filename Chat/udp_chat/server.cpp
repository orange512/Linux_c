/*************************************************************************
	> File Name: server.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年08月25日 星期五 10时47分17秒
 ************************************************************************/

#include<iostream>
#include<stdio.h>
#include<string.h>
#include<sys/types.h>  
#include<sys/socket.h>
#include<stdlib.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<errno.h>
//#include"pub.h"
#include<list>
#include<algorithm>
using namespace std;

//客户到服务器
#define C2S_LOGIN                     0x01
#define C2S_LOGOUT                    0x02
#define C2S_ONLINE_USER               0x03

#define MSG_LEN                        512

//服务器到客户端
#define S2C_LOGIN_OK                   0x01
#define S2C_ALREADY_LOGINED            0x02
#define S2C_SOMEONE_LOGIN              0x03
#define S2C_SOMEONE_LOGOUT             0x04
#define S2C_ONLINE_USER                0x05

//客户端到客户端
#define C2C_CHAT                      0x06

typedef struct message
{
    int cmd;
    char body[MSG_LEN];
}MESSAGE;

typedef struct user_info
{
    char username[16];
    char msg[100];
}CHAT_MSG;

typedef list<USER_INFO> USER_LIST

USER_LIST client_list;
void do_login(MESSAGE& msg,int sock,struct sockaddr_in *cliaddr)
{
    USER_INFO user;
    strcpy(user.username,msg.body);
    user.ip = cliaddr->sin_addr_s.addr;
    user.port = cliaddr->sin_port;

    //查找用户
    USER_LIST::iterator it;
    for(it = clilen_list.begin();it != clilent_list.end();++it)
    {
        if(strcmp(it->username,msg.body) == 0)
        {
            break;
        }
    }
    if(it = client_list.end())//没找到用户
    {
        printf("有一个用户登录user:%s <------>%s:%d\n",msg.body,inet_ntoa(cliaddr),ntohs(cliaddr->sin_port));
        client_list.push_back(user);


        //登录成功应答
        MESSAGE reply_msg;
        memset(&reply_msg,0,sizeof(reply_msg));
        reply_msg.cmd = htonl(S2C_LOGIN_OK);
        sendto(sock,&reply_msg,sizeof(msg),0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));

        int count = htonl((int)client_list.size());
        //发送在线人数
        sendto(sock,&count,sizeof(int),0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));

        printf("发送用户信息到：%s<----->%s:%d\n",msg.body,inet_ntoa(cliaddr),ntohl(cliaddr->sin_port));
        //发送在线列表
        for(it = clilen_list.begin();it != clilent_list.end();++it)
        {
            sendto(sock,&*it,sizeof(USER_INFO),0,(struct sockaddr*)&cliaddr,sizeof(cliaddr));
        }
        //想其他用户通知新用户登录
        for(it = client_list.begin();it  != clilent_list.end();++it)
        {
            if(strcmp(it->username,msg.body) == 0)
            {
                continue;
            }

            struct sockaddr_in peeraddr;
            memset(&peeraddr,0,sizeof(peeraddr));

            peeradd.sin_family = AF_INET;
            peeraddr.sin_port = it->port;
            peeraddr.sin_add.s_addr = it->ip;

            msg.cmd = htonl(S2C_SOMEONE_LOGIN);
            memcpy(msg.body,&user,sizeof(user));

            if(sendto(sock,&msg,sizeof(msg),0,(struct sockaddr*)&peeraddr,sizeof(peeraddr)))
            {
                perror("sendto");
            }
        }
        else //找到用户
        {
            printf("用户 %s已经登录了\n",msg.body);

            MESSAGE
        }
    }
}
void chat_srv(int sock)
{
    struct sockaddr_in cliaddr;
    socklen_t clilen;
    int n;
    MESSAGE msg;
    while(1)
    {
        memset(&msg,0,sizeof(msg));
        clilen = sizeof(cliaddr);
        n = recvfrom(sock,&msg,sizeof(msg),0,(struct sockaddr *)&cliaddr,&clilen);
        if(n < 0 )
        {
            if(errno == EINTR)
                continue;
            perror("recvfrom");
            exit(EXIT_FAILURE);
        }
        int cmd = ntohl(msg.cmd);
        switch(cmd)
        {
            case C2S_LOGIN:
                do_login(msg,sock,&cliaddr);
                break;
            case C2S_LOGOUT:
                do_logout(msg,sock,&cliaddr);
                break;
            case C2S_ONLINE_USER:
             do_sendlist(sock,&cliaddr);
                break;
            default:
                break;
        }
                
    }
}





















int main()
{
    int sock;
    if((sock = socket(PF_INET,SOCK_DGRAM,0)) < 0)
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
    if(bind(sock,(struct sockaddr*)&serveraddr,sizeof(serveraddr)) < 0)
       perror("bind");

    chat_srv(sock);
    return 0;

}
