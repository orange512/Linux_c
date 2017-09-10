/*************************************************************************
	> File Name: stat.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月08日 星期五 20时04分55秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>
#include<time.h>

int main()
{
    struct stat st = {};
    int ret = stat("a.txt",&st);//文件状态放入st
    if(ret == -1)
    {
        perror("stat"),exit(-1);
    }
    printf("inode:%d\n",st.st_ino);
    printf("mode:%o\n",st.st_mode);//类型加权限
    printf("权限:%o\n",st.st_mode&0777);
    printf("硬连接数:%d\n",st.st_nlink);
    printf("size = %d\n",st.st_size);
    printf("mtime= %s\n",ctime(&st.st_mtime));
    if(S_ISREG(st.st_mode))
    {
        printf("普通文件\n");
    }
    if(S_ISDIR(st.st_mode))
    {
        printf("目录文件\n");
    }

}
    

