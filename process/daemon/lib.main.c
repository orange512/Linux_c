/*************************************************************************
	> File Name: lib.main.c
	> Author: 
	> Mail: 
	> Created Time: 2017年10月30日 星期一 21时03分59秒
 ************************************************************************/

#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<signal.h>
#include<syslog.h>

//每次查询间隔
#define SLEEP_TIME 5

//获得文件信息大小
long get_file_size(const char *filename)
{
    struct stat status;
    long size;
    if(stat(filename,&status)==-1)
    {
        perror("stat");
        return -1;
    }
    size = status.st_size;
    return size;
}
//显示邮件到达信息
void mail_log(const char *progname,const char *mail_pos)
{
    fprintf(stderr,"%s notice:you have new mail in %s\n",progname,mail_pos);
}
int check_mail(const char *filename,const char *progname)
{
    long old_mail_size;
    old_mail_size = get_file_size(filename);
    
    long mail_size;
    if(old_mail_size == -1)
        return 1;
    if(old_mail_size > 0)
        mail_log(progname,filename);
    sleep(SLEEP_TIME);

    while(1)
    {
        mail_size = get_file_size(filename);

        if(mail_size != old_mail_size)
        {
            mail_log(progname,filename);
        }
        old_mail_size = mail_size;
        sleep(SLEEP_TIME);
    }
}
