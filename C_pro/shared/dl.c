/*************************************************************************
	> File Name: dl.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月04日 星期一 20时37分02秒
 ************************************************************************/

#include<stdio.h>
#include<dlfcn.h>
int main()
{
    void * handle = dlopen("./myku.so",RTLD_LAZY);

    char * error = dlerror();
    if(error)//返回不为空时出错
    {
        printf("open error");
    }
    double (*f)(double,double);
    f = dlsym(handle,"add2");
    printf("add2 = %lf\n",f(2.0,4.0));
    return 0;
}
