/*************************************************************************
	> File Name: protobuf_test.cc
	> Author:    orange
	> Mail:      huiyi950512@gmail.com
	> Created Time: 2018年04月29日 星期日 15时47分25秒
 ************************************************************************/

#include "msg.pb.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
    demo::msg msg_test;   //先创建一个对象
    msg_test.set_msgtype(1);
    msg_test.set_msginfo("I am liuzhuo");
    msg_test.set_msgfrom("127.0.0.1");

    //将信息格式化到字符串中（写操作）
    string in_data;
    msg_test.SerializeToString(&in_data);
    cout<<"format:"<<in_data<<endl;

    //将信息从字符串中反序列中反格式化出来（读操作）
    demo::msg msg_encoding;//解码对象

    msg_encoding.ParseFromString(in_data);
    cout<<"msg type:"<<msg_encoding.msgtype()<<endl;
    cout<<"msg info:"<<msg_encoding.msginfo()<<endl;
    cout<<"msg from:"<<msg_encoding.msgfrom()<<endl;
    return 0;
}
