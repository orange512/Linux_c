/*************************************************************************
	> File Name: create_pipe.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月24日 星期日 09时48分08秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>

int main()
{
    mkfifo("b.pipe",O_CREATE|O_RDWR,0666);
    return 0;
}
