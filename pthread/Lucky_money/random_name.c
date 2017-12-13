/*************************************************************************
	> File Name: 10.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月22日 星期五 18时48分56秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
char* string;
char* genRandomString(int length)
{
    int flag, i;
    srand((unsigned) time(0)*rand());
    if ((string = (char*) malloc(sizeof(char)*length)) == NULL )
    {
        printf("Malloc failed!\n");
        return NULL ;

    }
    for (i = 0; i < length - 1; i++)
    {
        flag = rand() % 4;
        switch (flag)
        {
            case 0:
            string[i] = 'A' + rand() % 26;
            break;
            case 1:
            string[i] = 'a' + rand() % 26;
            break;
            case 2:
            string[i] = 'A' + rand() % 26;
            break;
            case 3:
            string[i] = 'b' + rand() % 25;
            default:
            string[i] = 'x';
            break;

        }

    }
    string[length - 1] = '\0';
    return string;

}
int main()
{
    for(int i = 0; i < 200;i++)
    printf("%s\n",genRandomString(5));
    free(string);
}
