/*************************************************************************
	> File Name: get_stat.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月12日 星期二 16时59分22秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/shm.h>
#define ERR_EXIT(m)\
    do{\
        perror(m),exit(-1);\
    }while(0)


int main()
{
    key_t key = ftok(".",100);//找家里钥匙
    if(key == -1)
        ERR_EXIT("ftok");
    int shmid = shmget(key,0,0);//用钥匙找房间
    if(shmid == -1)
       ERR_EXIT("shmid");
    struct shmid_ds ds;
    shmctl(shmid,IPC_STAT,&ds);//获取状态
    printf("key = %x\n",ds.shm_perm.__key);
    printf("mode = %o\n",ds.shm_perm.mode);
    printf("size = %d\n",ds.shm_segsz);
    printf("cpid = %d\n",ds.shm_cpid);
    printf("nattch = %d\n",ds.shm_nattch);

    ds.shm_perm.mode = 0640;
    ds.shm_segsz = 40;//不可修改
    shmctl(key,IPC_SET,&ds);//修改
    //shmctl(key,IPC_RMID,0);
}
