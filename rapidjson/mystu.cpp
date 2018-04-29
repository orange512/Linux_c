/*************************************************************************
	> File Name: mystu.cpp
	> Author:    orange
	> Mail:      huiyi950512@gmail.com
	> Created Time: 2018年04月29日 星期日 20时19分43秒
 ************************************************************************/

#include <iostream>
#include <rapidjson/allocators.h>
#include <rapidjson/rapidjson.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/prettywriter.h>
#include <string>
#include <fstream>
using namespace std;
using namespace rapidjson;

void json_write()
{
    Document doc;
    doc.SetObject();
    Document::AllocatorType &allocator = doc.GetAllocator();
    //添加字符串对象
    doc.AddMember("name","orange",allocator);
    doc.AddMember("id","3150931032",allocator);

    Value array1(kArrayType);
    for(int i = 0;i < 2;i++)
    {
        Value int_obj(kObjectType);
        int_obj.SetInt(i);
        array1.PushBack(int_obj,allocator);
    }
    doc.AddMember("number",array1,allocator);

    Value obj(kObjectType);
    obj.AddMember("school1","ligong",allocator);
    obj.AddMember("school2","guozhong",allocator);
    doc.AddMember("school",obj,allocator);

	Value array2(kArrayType);
	Value object1(kObjectType);
	object1.AddMember("hobby","drawing",allocator);
	array2.PushBack(object1,allocator);
	Value object2(kObjectType);
	object2.AddMember("height",1.71,allocator);
	array2.PushBack(object2,allocator);
	doc.AddMember("information",array2,allocator);

    StringBuffer buffer;
    PrettyWriter<StringBuffer> pretty_write(buffer);
    doc.Accept(pretty_write);
    cout<<"myjson out_put"<<endl;
    cout<<buffer.GetString()<<endl;

	ofstream fout;
	fout.open("test2");    
	fout<<buffer.GetString();
	fout.close();
}

void json_read()
{
    cout<<"my json read:"<<endl;
    ifstream fin;
    fin.open("test2");
    string str;
    string str_in = "";
    while(getline(fin,str))
    {
        str_in = str_in + str + '\n';
    }

    cout<<str_in<<endl;
    Document out_doc;
    out_doc.Parse<0>(str_in.c_str());

    Value &node1 = out_doc["name"];
    cout<<"name :"<<node1.GetString()<<endl;
    Value &node2 = out_doc["id"];
    cout<<"name :"<<node2.GetString()<<endl;

    Value &node3 = out_doc["number"];
    cout<<"number:"<<endl;
    if(node3.IsArray())
    {
        for(unsigned int i = 0 ; i < node3.Size();i++)
            cout<<'\t'<<node3[i].GetInt()<<endl;
    }
    Value &node4 = out_doc["school"];
    cout<<"school :"<<endl;
    Value &tmp = node4["school1"];
    cout<<'\t'<<"school1:"<<tmp.GetString()<<endl;
    tmp = node4["school2"];
    cout<<'\t'<<"school2:"<<tmp.GetString()<<endl;

	Value &node5=out_doc["information"];
	cout<<"information: "<<endl;
	if(node5.IsArray())
	{
		//int i=0;
		Value &data=node5[0];
		cout<<'\t'<<"hobby: "<<data["hobby"].GetString()<<endl;
		/* i=1; */
		data=node5[1];
		cout<<'\t'<<"height: "<<data["height"].GetDouble()<<endl;
	}
}

int main()
{
    json_write();
    json_read();
    return 0;
}
