/*************************************************************************
	> File Name: pwd.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年10月25日 星期三 17时14分44秒
 ************************************************************************/

#include<iostream>
#include<unistd.h>
#include<limits.h>
using namespace std;
int main()
{
    long cur_path_len;
    char cur_work_dir[PATH_MAX];
    std::cout<<"当前路径最大的长度为"<<PATH_MAX<<std::endl;
    //获取当前目录
    if(getcwd(cur_work_dir,PATH_MAX) == NULL)
    {
        cout<<"不能获取当前的目录";
        return 1;
    }
    //获取目录最大长度
    if((cur_path_len = pathconf(".",_PC_PATH_MAX)) == -1)
    {
        cout<<"不能获取最大长度";
        return 1;
    }

    std::cout<<"当前工作目录:"<<cur_work_dir<<std::endl;
    std::cout<<"当前工作目录的最大长度:"<<cur_path_len<<std::endl;
    //更改当前目录到上一级目录
    if(chdir("..") == -1)
    {
        cout<<"不能切换";
        return 1;
    }
    if(getcwd(cur_work_dir,PATH_MAX) == NULL)
    {
        cout<<"不能获取当前的目录";
        return 1;
    }
    std::cout<<"当前工作目录:"<<cur_work_dir<<std::endl;
    return 0;
}
