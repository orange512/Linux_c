/*************************************************************************
	> File Name: get_info.c
	> Author: 
	> Mail: 
	> Created Time: 2017年10月31日 星期二 20时03分19秒
 ************************************************************************/
//获取系统网络设备和网络地址信息
#include<stdio.h>
#include<pcap.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int main()
{
    char *net_dev;
    char *ip_addr;
    char *net_mask;
    char errbuf[PCAP_ERRBUF_SIZE];

    bpf_u_int32 netp;
    bpf_u_int32 maskp;
    struct in_addr addr;

    //获得系统中的网络设备名称
    net_dev = pcap_lookupdev(errbuf);
    if(net_dev == NULL)
    {
        printf("不能获取网络设备：%s\n",errbuf);
        return 1;
    }
    printf("网络设备名称为:%s\n",net_dev);

    //获得改设备的IP地址信息和子网掩码信息
    if(pcap_lookupnet(net_dev,&netp,&maskp,errbuf) == -1)
    {
        printf("不能获取设备IP和掩码:%s\n",errbuf);
        return 1;
    }

    //转换获得的地址的格式，将其转换成字符串
    addr.s_addr = netp;
    ip_addr = inet_ntoa(addr);

    if(ip_addr == NULL)
    {
        printf("转换地址失败\n");
        return 1;
    }

    printf("设备的IP地址为:%s\n",ip_addr);

    addr.s_addr = maskp;
    net_mask  = inet_ntoa(addr);
    if(net_mask == NULL)
    {
        printf("转换掩码失败\n");
        return 1;
    }
    printf("设备的掩码为:%s\n",net_mask);

    return 0;

}
