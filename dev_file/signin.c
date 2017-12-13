/*************************************************************************
	> File Name: curses.c
	> Author: 
	> Mail: 
	> Created Time: 2017年10月25日 星期三 17时52分26秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<termios.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#define ECHOFLAGS (ECHO | ECHOE | ECHOK | ECHONL)
//函数set_disp_mode用于控制是否开启输入回显功能
//如果option为0则关闭回显，为1打开回显
char buf[] = {'*','#','.','&','(',')','+','-','$','=','-','~'};
int set_disp_mode(int fd,int option)
{
    int err;
    struct termios term;

    if(tcgetattr(fd,&term) == -1)
    {
        printf("不能获取终端的属性\n");
        return 1;
    }
    if(option)
        term.c_lflag |= ECHOFLAGS;
    else
        term.c_lflag &= ~ECHOFLAGS;
    err = tcsetattr(fd,TCSAFLUSH,&term);
    if(err == -1 && err == EINTR)
    {
        printf("不能设置终端的属性\n");
        return 1;
    }
    return 0;
}
int getpasswd(char *passwd,int size)
{
    int c;
    int n = 0;
    printf("请输入密码:");
    do{
        c = getchar();
        if(c != '\n' | c != '\r')
        {
            passwd[n++] = c;
        }
    }while(c != '\n' && c != '\r' && n < size -1);
    passwd[n] = '\0';
    return n;
}

int main()
{
    char passwd[20];
 //首先关闭回显功能
    set_disp_mode(STDIN_FILENO,0);

    int n = getpasswd(passwd,sizeof(passwd));
    if(n == -1)
    { 
        return -1;
    }
    printf("\n你的密码为%s\n",passwd);
    for(int i = 0 ; i<n;i++)
    {
        if(passwd[i] == '@' || passwd[i] == '#' || passwd[i] == '\\' || passwd[i] == '`')
        { 
            printf("\n你输入的密码有非法字符\n");
            return -1;
        }
    }
    printf("请按任意键继续...\n");
//打开回显
    set_disp_mode(STDIN_FILENO,1);
    getchar();

    return 0;
}
