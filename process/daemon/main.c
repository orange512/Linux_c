/*************************************************************************
	> File Name: main.c
	> Author: 
	> Mail: 
	> Created Time: 2017年10月30日 星期一 21时19分14秒
 ************************************************************************/

#include<stdio.h>

#define USER_ACCOUNT "var/mail/orange"

extern void signal_int();
extern int daemon(int nochdir,int noclose);

int check_mail(const char* filename,char *progname);

int main(int argc,char* argv[])
{
    char *p;
    int opt;
    int daemon_mode = 1;
    char *progname;

    signal_init();

    if(daemon_mode)
        daemon(0,1);
    check_mail(USER_ACCOUNT,argv[0]);
    return 0;
}
