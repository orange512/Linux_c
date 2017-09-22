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
#include<string.h>
void mytree(char *name)
{
    DIR *dir = opendir(name);
    if(dir == NULL)perror("opendir"),exit(-1);
    struct dirent *ent;
    while(ent = readdir(dir))
    {
        if(ent->d_type == 4)
        {
            if(strcmp(ent->d_name,".") == 0 || strcmp(ent->d_name,"..") == 0)
                continue;
            printf("[%s]\t",ent->d_name);
            char path[1024];
            sprintf(path,"%s/%s",name,ent->d_name);
            mytree(path);
            putchar(10);
        }
        else
        {
            printf("%s\t",ent->d_name);
        }
    }
    
}
int main()
{
    mytree("../Chat");
    putchar(10);

}
