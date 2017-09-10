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

int main()
{
    DIR *dir = opendir("../Chat");
    if(dir == NULL)perror("opendir"),exit(-1);
    while(1)
    {
        struct dirent *ent = readdir(dir);
        if(ent ==NULL)
        break;
        printf("type = %d\tname = %s\n",ent->d_type,ent->d_name);
    }
}
