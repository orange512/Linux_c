/*************************************************************************
	> File Name: test.cpp
	> Author:    orange
	> Mail:      huiyi950512@gmail.com
	> Created Time: 2018年04月29日 星期日 16时49分44秒
 ************************************************************************/

#include <iostream>
#include "mymsg.pb.h"
#include <string>
using namespace std;

int main()
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    mypack::Student student;
    //给消息Student对象student赋值
    
    student.set_id(3150931032);
    *student.mutable_name() = "orange";
    student.set_email("282652254@qq.com");
    //增加一个号码对象
    mypack::Student::PhoneNumber *phone_number = student.add_phone();
    phone_number->set_number("13709227058");
    phone_number->set_type(mypack::Student::MOBILE);

    //再增加一个号码对象
    mypack::Student::PhoneNumber *phone_number2 = student.add_phone();
    phone_number2->set_number("0917677777");
    phone_number2->set_type(mypack::Student::HOME);

    //将消息序列化到string容器
    string my_data;
    student.SerializeToString(&my_data);
    cout<<"序列化的字符串为:"<<my_data<<endl;
    cout<<"string size:"<<my_data.size()<<endl;


    //将消息反序列化
    mypack::Student out_res;

    if(!out_res.ParseFromString(my_data))
    {
        cerr<<"解析失败"<<endl;
        return -1;
    }
    cout<<"--------反序列化的结果---------"<<endl;

    cout<<"ParseFromString debug string"<<out_res.DebugString();

    cout<<"自己反序列化结果"<<endl;
    cout<<endl<<"student ID:"<<out_res.id()<<endl;
    cout<<"name:"<<out_res.name()<<endl;
    if(out_res.has_email())
    {
        cout<<"email:"<<out_res.email()<<endl;
    }
    for(int i = 0 ; i < out_res.phone_size();i++)
    {
        const mypack::Student::PhoneNumber &phone_number = out_res.phone(i);
        
        switch(phone_number.type())
        {
            case mypack::Student_PhoneType_HOME:
                cout<<"HOME PHONE"<<endl;
                break;
            case mypack::Student_PhoneType_MOBILE:
                cout<<"MOBILE PHONE"<<endl;
                break;
        }
        cout<<phone_number.number()<<endl;

        google::protobuf::ShutdownProtobufLibrary();
    }
    return 0; 
}
