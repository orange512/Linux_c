/*************************************************************************
	> File Name: 3.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月16日 星期六 14时43分54秒
 ************************************************************************/

#include<stdio.h>
#line 1000
int main()
{
    printf("__DATE__: %s\n",__DATE__);
    printf("__FILE__ : %s\n",__FILE__);
    printf("__LINE__:%d\n",__LINE__);
    printf("__STDC__:%d\n",__STDC__);
    printf("__func__: %s\n",__func__);
    printf("__TIME__: %s\n",__TIME__);
    printf("STDC_HOSTED__%d\n",__STDC_HOSTED__);
    printf("__STDC_VERSION__:%ld\n",__STDC_VERSION__);
    return 0;
}
