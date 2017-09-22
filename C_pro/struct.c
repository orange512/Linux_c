/*************************************************************************
	> File Name: struct.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月02日 星期六 09时47分34秒
 ************************************************************************/

#include<stdio.h>
#include<stdbool.h>
#include<string.h>
enum Edu{primary,middle,high,university};//创建枚举类型
struct Student;
struct Person
{
    char name[20];
    _Bool isMale;//C中的bool
    int age;
};
struct Student
{
    struct Person p;
    enum Edu type;
    enum Edu (*getEdu)(struct Student s);//获取学历
    void(*setEdu)(struct Student *s,int choose);
    void(*printStudent)(struct Student s);
};
enum Edu getEdu(struct Student s)
{
    return s.type;

}
void setEdu(struct Student *s,int choose)//设置学历
{
    s->type = (enum Edu)choose;
}
void printStudent(struct Student s)//打印信息
{
    char sex[20];
    if(s.p.isMale)
    {
        strcpy(sex,"male");
    }
    else
        strcpy(sex,"male");
    char edu[20];
    switch(s.type)
    {
        case 0:
            strcpy(edu,"primary");
            break;
        case 1:
            strcpy(edu,"middle");
            break;
        case 2:
            strcpy(edu,"high");
            break;
        case 3:
            strcpy(edu,"university");
            break;
    }

    printf("name:%s\tsex:%s\tage:%d\tEdu:%s\n",s.p.name,sex,s.p.age,edu);
}
int main()
{
    struct Student stu1;
    strcpy(stu1.p.name,"liuzhuo");
    stu1.p.isMale = 1;
    stu1.p.age = 20;

    stu1.setEdu = setEdu;
    stu1.setEdu(&stu1,3);
   // stu1.type = (enum Edu)3;

    stu1.getEdu = getEdu;
   // enum Edu n = stu1.getEdu(stu1);
    printf(" edu = %d\n",stu1.getEdu(stu1));

    stu1.printStudent = printStudent;
    stu1.printStudent(stu1);
    
    stu1.setEdu = setEdu;
    stu1.setEdu(&stu1,2);

    stu1.getEdu = getEdu;
   // enum Edu n = stu1.getEdu(stu1);
    printf(" edu = %d\n",stu1.getEdu(stu1));

    stu1.printStudent = printStudent;
    stu1.printStudent(stu1);
    return 0;

}
