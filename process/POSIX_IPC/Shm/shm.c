/*************************************************************************
	> File Name: shm.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月27日 星期三 20时48分18秒
 ************************************************************************/

#include<stdio.h>
#include"shm.h"
struct stu
{
    char name[20];
    int age;
};
int main()
{
    int shmid = shm_open("/xyz",O_CREAT|O_RDWR,0666);
    if(shmid < 0 )
        perror("shm_open"),exit(-1);
    ftruncate(shmid,sizeof(struct stu));
    struct stat buf;
    if(fstat(shmid,&buf) == -1)
        perror("fstat"),exit(-1);
    printf("size=%ld mode = %o\n",buf.st_size,buf.st_mode&07777);

    close(shmid);
    return 0;
}
