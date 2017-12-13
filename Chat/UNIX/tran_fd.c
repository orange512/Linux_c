/*************************************************************************
	> File Name: sockpair.c
	> Author: 
	> Mail: 
	> Created Time: 2017年08月30日 星期三 21时51分20秒
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
//socketpair是一个全双工的管道不同于pipe
//用他进行父子进程之间的通信
void send_to(int sock_fd,int send_fd)
{
    int ret;
    struct msghdr msg;
    struct cmsghdr *p_cmsg;
    struct iovec vec;
    char cmsgbuf[CMSG_SPACE(sizeof(send_fd))];
    int *p_fds;
    char sendchar=0;
    msg.msg_control = cmsgbuf;
    msg.msg_controllen = sizeof(cmsgbuf);
    p_cmsg = CMSG_FIRSTHDR(&msg);
    p_cmsg->cmsg_level = SOL_SOCKET;
    p_cmsg->cmsg_type = SCM_RIGHTS;
    p_cmsg->cmsg_len= CMSG_LEN(sizeof(send_fd));
    p_fds = (int *)CMSG_DATA(p_cmsg);
    *p_fds = send_fd;

    msg.msg_name = NULL;
    msg.msg_namelen = 0;
    msg.msg_iov = &vec;
    msg.msg_iovlen = 1;
    msg.msg_flags = 0;

    vec.iov_base = &sendchar;
    vec.iov_len = sizeof(sendchar);
    ret = sendmsg(sock_fd,&msg,0);
    if(ret != 1)
        perror("sendmsg");
}
int main()
{
    int sockfds[2];

    if(socketpair(PF_UNIX,SOCK_STREAM,0,sockfds) < 0)
        perror("socketpair");
    pid_t pid;
    pid = fork();
    if(pid == -1)
    {
        perror("fork");
    }
    if(pid > 0)
    {
        int val = 0;
        close(sockfds[1]);
        while(1)
        {
            ++val;
            printf("send data : %d\n",val);
            write(sockfds[0],&val,sizeof(val));
            read(sockfds[0],&val,sizeof(val));
            printf("data received :%d \n",val);
            sleep(1);
        }
    }
    else if(pid == 0)
    {
        int val;
        close(sockfds[0]);
        while(1)
        {
            read(sockfds[1],&val,sizeof(val));
            ++val;
            write(sockfds[1],&val,sizeof(val));
        }
    }
    return 0;
}
