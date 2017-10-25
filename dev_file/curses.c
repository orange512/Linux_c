/*************************************************************************
	> File Name: curses.c
	> Author: 
	> Mail: 
	> Created Time: 2017年10月25日 星期三 17时52分26秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<curses.h>
#include<unistd.h>

void init()
{
    initscr();
    cbreak();//接受除“Del”和“Ctrl”键外，接受其他所有字符
    nl();//nl将换行作为回车符
    echo();//打开回显功能
    noecho();//关闭回显功能
    intrflush(stdscr,FALSE);
    refresh();//重绘屏幕显示内容。在调用initscr函数后，第一次调用refresh函数会清除屏幕显示
}

int getpasswd(char *passwd,int size)
{
    int c;
    int n = 0;
    printw("请输入密码:");
    do{
        c = getch();
        if(c != '\n')
        {
            echochar('*');
            passwd[n++] = c;
        }
    }while(c != '\n' && n < size -1);
    passwd[n] = '\0';
    return n;
}

int main()
{
    char passwd[20];
    int n;
    init();
    n = getpasswd(passwd,sizeof(passwd));

    printw("\n你的密码为%s\n",passwd);
    printw("请按任意键继续...\n");
    refresh();
    getchar();
    endwin();

    return 0;
}
