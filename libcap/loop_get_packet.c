/*************************************************************************
	> File Name: get_info.c
	> Author: 
	> Mail: 
	> Created Time: 2017年10月31日 星期二 20时03分19秒
 ************************************************************************/
//捕获单个数据包调用实例
#include<stdio.h>
#include<pcap.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netinet/if_ether.h>

//数据包处理函数
void deal_with_packet(u_char *user,const struct pcap_pkthdr* hdr,const u_char *packet)
{
    static int count = 0;
    struct ether_header *ether_header;
    u_char *ptr;

    printf("数据包长度为:%d\n",hdr->len);
    //printf("捕获时间:%s\n",ctime((const time_t*)&hdr->ts.tv_sec));
    printf("portion present 长度为%d\n",hdr->caplen);
    //给出捕获数据包中的信息
    ether_header = (struct ether_header*)packet;
    if(ntohs(ether_header->ether_type)!=ETHERTYPE_IP)
    {
        printf("不是网络数据包\n");
    }
    ptr = ether_header->ether_dhost;
    int i = 0;
    printf("目地MAC地址：");
    while(i < ETHER_ADDR_LEN)
    {
        printf("  %x",*ptr++);
        i++;
    }
    printf("\n源MAC地址：");
    ptr = ether_header->ether_shost;
    i = 0;
    while(i < ETHER_ADDR_LEN)
    {
        printf("  %x",*ptr++);
        i++;
    }
    putchar(10);

    printf("处理了%d个数据包\n",count);
    count++;
}
int main()
{
    char *net_dev;
    char *ip_addr;
    char *net_mask;
    char errbuf[PCAP_ERRBUF_SIZE];
    
    pcap_t *sniffer_des;
    struct bpf_program fp;
    const u_char *packet;
    struct pcap_pkthdr hdr;
    char filter_exp[] = "port 80";

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

    //获取用于捕获网络数据包的数据包描述字
    sniffer_des = pcap_open_live(net_dev,65535,1,1000,errbuf);
    if(sniffer_des == NULL)
    {
        printf("不能获取数据包描述字:%s\n",errbuf);
        return 1;
    }
    //设置包过滤条件
    if(pcap_compile(sniffer_des,&fp,filter_exp,0,maskp) == -1)
    {
        printf("设置包过滤条件失败\n");
        return 1;
    }
    if(pcap_setfilter(sniffer_des,&fp) == -1)
    {
        printf("不能设置网络设备\n");
        return 1;
    }
    //捕获数据包
   /* packet = pcap_next(sniffer_des,&hdr);
    if(packet == NULL)
    {
        printf("不能获取数据包\n");
        return 1;
    }*/
    int ret = pcap_loop(sniffer_des,3,deal_with_packet,NULL);
    if(ret == -1 || ret == -2)
    {
        printf("不能获取包\n");
        return 1;
    }
    printf("完成包获取\n");

    
    return 0;

}
