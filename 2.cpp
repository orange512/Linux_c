/*************************************************************************
	> File Name: 2.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年08月24日 星期四 09时41分58秒
 ************************************************************************/

#include<iostream>
using namespace std;
class People
{
    private:
        string name;
        string height;
        int age;
        string data;
        string address;
        static int count;
    public:
        People();
        People(string n,double h,int a,string d,string add)
        {
            count++;
            name = n;
            age = a;
            data = d;
            address = add;
        }
        ~People();
        People(const People &obj);//拷贝构造函数
        People &operator=(const People &obj);//赋值运算符重载
        //static int count;
        void print()
        {
            cout<<"name = "<<name<<"height = "<<height<< "age= " <<age<<"data= "<<data<<"add= "<<address<<endl;
        }
        static void Init_count()
        {
            count = 0;
        }
        static  void printcount()
        {
            cout<<count<<endl;

        }
};
People::People()
{
    count++;
    cout<<"构造函数1"<<endl;
}
int People::count = 0;
People::People(const People &obj)//拷贝构造函数
{
    cout<<"拷贝构造函数"<<endl;
    name = obj.name;
    height = obj.height;
    age = obj.age;
    data = obj.data;
    address = obj.address;
}
People::~People()
{
    cout<<"析构函数"<<endl;
}
People& People::operator =(const People &obj)
{
    cout<<"赋值运算符重载"<<endl;
    if(this == &obj)
        return *this;
    name = obj.name;
    height = obj.height;
    age = obj.age;
    data = obj.data;
    address = obj.address;
}
int main()
{
   //People::Init_count();
    People a;
    People p1("liuzhuo",170,21,"19950512","xian");
    p1.print();
    People p2(p1);//拷贝构造函数
    People p3 = p1;//拷贝构造函数
    People e;
    e = p1;//赋值运算符重载
    e.print();
    /*People *pt = new People();
    pt = NULL;
    delete pt;*/
    //cout<<"count="<<e.count<<endl; 
    People::printcount();
}
