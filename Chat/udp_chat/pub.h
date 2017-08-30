/*************************************************************************
	> File Name: pub.h
	> Author: 
	> Mail: 
	> Created Time: 2017年08月25日 星期五 10时26分19秒
 ************************************************************************/

#ifndef _PUB_H
#define _PUB_H


#include<list>
#include<algorithm>
using namespace std;

//客户到服务器
#define C2S_LOGIN                     0x01
#define C2S_LOGOUT                    0x02
#define C2S_ONLINE_USER               0x03

#define MSG_LEN                        512

//服务器到客户端
#define S2C_LOGIN_OK                   0x01
#define S2C_ALREADY_LOGINED            0x02
#define S2C_SOMEONE_LOGIN              0x03
#define S2C_SOMEONE_LOGOUT             0x04
#define S2C_ONLINE_USER                0x05

//客户端到客户端
#define C2C——CHAT                      0x06

typedef struct message
{
    int cmd;
    char body[MSG_LEN];
}MESSAGE;

typedef struct user_info
{
    char username[16];
    char msg[100];
}CHAT_MSG;

typedef list<USER_INFO> USER_LIST

#endif
