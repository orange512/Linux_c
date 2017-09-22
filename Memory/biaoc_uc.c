/*************************************************************************
	> File Name: biaoc_uc.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月06日 星期三 21时50分26秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{
   /* FILE *fp = fopen("a.txt","w");
    if(fp == NULL)
        perror("fopen");
    int i = 0;
    for(i = 0 ; i < 1000000;i++)
    {
        fwrite(&i,4,1,fp);
    }*/
    int fd = open("b.txt",O_CREAT|O_TRUNC|O_RDWR,0666);
    if(fd == -1)
        perror("open");
    int i = 0;
    int arr[10000];
    for(i = 0; i < 1000000;i++)
    {
        arr[i%10000] = i;
        if((i%10000) == 9999)
        write(fd,arr,sizeof(arr));
    }
    close(fd);
    return 0;

}
