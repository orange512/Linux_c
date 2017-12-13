/*************************************************************************
	> File Name: test.c
	> Author: 
	> Mail: 
	> Created Time: 2017年10月31日 星期二 20时01分15秒
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pcap/pcap.h>
int main(int argc,char *argv[]){
    char *dev, errbuf[PCAP_ERRBUF_SIZE];
    dev=pcap_lookupdev(errbuf);
    if(dev==NULL){
        fprintf(stderr,"couldn't find default device: %s\n",errbuf);
        return(2);

    }
    printf("Device: %s\n",dev);
    return(0);
}


