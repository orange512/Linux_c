/*************************************************************************
	> File Name: download.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月25日 星期一 20时55分13秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<dirent.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{
    char server[1024] = {0};
    char buf[128];
    char file_name[1024];
    char down_file[1024];
    int src_fd = 0;
    int des_fd = 0;
    DIR *dp = NULL;
    int ret = 0;
    struct dirent  *dir;
start:
    printf("请输入服务器的路径和文件名\n");
    scanf("%s",server);
    dp = opendir(server);
    if(dp == NULL)
    {
        printf("open server:%s failure\n",server);
        goto start;
    }
    printf("打开服务器%s成功\n",server);
    while(1)
    {
        dir = readdir(dp);
        if(dir == NULL)
            break;
        else
        {
            printf("inode = %ld\t file_name = %s\n",dir->d_ino,dir->d_name);
        }
    }
    printf("请输入你要下载文件\n");
    scanf("%s",file_name);
    sprintf(down_file,"%s/%s",server,file_name);

    src_fd = open(down_file,O_RDONLY,0);
    if(src_fd < 0)
    {
        printf("打开文件失败:%s",down_file);
        return -1;
    }
    printf("打开文件%s成功\n",down_file);

    des_fd = open(file_name,O_CREAT|O_WRONLY,0777);
    if(des_fd < 0)
    {
        printf("创建%s失败\n",file_name);
        return -1;
    }
    while(1)
    {
        ret = read(src_fd,buf,128);
        if(ret < 128)
        {
            printf("下载成功\n");
            break;
        }
        write(des_fd,buf,ret);
    }
    write(des_fd,buf,ret);



    close(src_fd);
    close(des_fd);
    closedir(dp);
    return 0;

}
