/*************************************************************************
	> File Name: test2.cpp
	> Author:    orange
	> Mail:      huiyi950512@gmail.com
	> Created Time: 2018年04月29日 星期日 20时09分47秒
 ************************************************************************/

#include <iostream>
using namespace std;
#include <string>
#include <fstream>
//包含rapidjson必要头文件,rapidjson文件夹拷贝到工程目录，或者设置include路径，或者加入到工程树
#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
using namespace std;
using namespace rapidjson;  //引入rapidjson命名空间

//写json文件
void json_write()
{
	Document doc;
	doc.SetObject();
	Document::AllocatorType &allocator=doc.GetAllocator(); //获取分配器
	//1.添加字符串对象
	doc.AddMember("author","tashaxing",allocator); 
	//2.添加数组对象
	Value array1(kArrayType);
	for(int i=0;i<3;i++)
	{
		Value int_object(kObjectType);
		int_object.SetInt(i);
		array1.PushBack(int_object,allocator);
	}
	doc.AddMember("number",array1,allocator);
	//3.添加复合对象
	Value object(kObjectType);
	object.AddMember("language1","C++",allocator);
	object.AddMember("language2","java",allocator);
	doc.AddMember("language",object,allocator);
	//4.添加对象数组和复合对象的组合
	Value array2(kArrayType);
	Value object1(kObjectType);
	object1.AddMember("hobby","drawing",allocator);
	array2.PushBack(object1,allocator);
	Value object2(kObjectType);
	object2.AddMember("height",1.71,allocator);
	array2.PushBack(object2,allocator);
	doc.AddMember("information",array2,allocator);
	StringBuffer buffer;
	PrettyWriter<StringBuffer> pretty_writer(buffer);  //PrettyWriter是格式化的json，如果是Writer则是换行空格压缩后的json
	doc.Accept(pretty_writer);
	//打印到屏幕
	cout<<"the json output:"<<endl;
	cout<<buffer.GetString()<<endl;
	//输出到文件
	ofstream fout;
	fout.open("test");    //可以使绝对和相对路径，用\\隔开目录，test, test.json, test.txt 都行，不局限于文件格式后缀，只要是文本文档
	fout<<buffer.GetString();
	fout.close();
}

//读json文件
void json_read()
{
	cout<<"the json read:"<<endl;
	ifstream fin;
	fin.open("test");
	string str;
	string str_in="";
	while(getline(fin,str))    //一行一行地读到字符串str_in中
	{
		str_in=str_in+str+'\n';
	}
	//解析并打印出来
	Document document;
	document.Parse<0>(str_in.c_str());

	Value &node1=document["author"];
	cout<<"author: "<<node1.GetString()<<endl;

	Value &node2=document["number"];
	cout<<"number: "<<endl;
	if(node2.IsArray())
	{
		for(unsigned int  i=0;i<node2.Size();i++)
			cout<<'\t'<<node2[i].GetInt()<<endl;
	}

	Value &node3=document["language"];
	cout<<"language: "<<endl;
	Value &tmp=node3["language1"];
	cout<<'\t'<<"language1: "<<tmp.GetString()<<endl;
	tmp=node3["language2"];
	cout<<'\t'<<"language2: "<<tmp.GetString()<<endl;

	Value &node4=document["information"];
	cout<<"information: "<<endl;
	if(node4.IsArray())
	{
		int i=0;
		Value &data=node4[i];   //注意，此处下表索引只能用变量，不能用常量，例如node[0]编译错误
		cout<<'\t'<<"hobby: "<<data["hobby"].GetString()<<endl;
		i=1;
		data=node4[i];
		cout<<'\t'<<"height: "<<data["height"].GetDouble()<<endl;
	}

}
int main()
{
	//写、读 测试
	json_write();
	json_read();
	return 0;
}
