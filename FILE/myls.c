/*************************************************************************
	> File Name: DIR.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月08日 星期五 20时38分08秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<dirent.h>
#include<sys/stat.h>
#include<time.h>
void myls(char *name)
{
    struct stat st = {};
    int ret = stat(name,&st);//文件状态放入st
    if(ret == -1)
    {
        perror("stat"),exit(-1);
    }
    printf("%d\t",st.st_ino);
    //printf("mode:%o\t",st.st_mode);//类型加权限
    printf("%o\t",st.st_mode&0777);
    printf("%d\t",st.st_nlink);
    printf("%d\t",st.st_size);
    printf("%s",ctime(&st.st_mtime));

}
int main()
{
    DIR *dir = opendir("../Chat");
    if(dir == NULL)perror("opendir"),exit(-1);
    while(1)
    {
        struct dirent *ent = readdir(dir);
        if(ent ==NULL)
        break;
        char buf[1024];
        sprintf(buf,"../Chat/%s",ent->d_name);
        myls(buf);
        if(ent->d_type == 4)
        {
            printf("[%s]\t\t",ent->d_name);
        }
        else
        {
            printf("%s\t\t",ent->d_name);
        }

    }
}
