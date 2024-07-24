#ifndef PROTOCOL_H
#define PROTOCOL_H

typedef unsigned int uint;

#define REGIST_OK "regist ok"
#define REGIST_FAILED "regist failed : name existed"
#define LOGIN_OK "login ok"
#define LOGIN_FAILED "login failed : name error or pwd error or relogin"

enum ENUM_MSG_TYPE{
    ENUM_MSG_TYPE_MIN=0,
    //注册请求
    ENUM_MSG_TYPE_REGIST_REQUEST,
    //注册回复
    ENUM_MSG_TYPE_REGIST_RESPOND,

    ENUM_MSG_TYPE_LOGIN_REQUEST,
    ENUM_MSG_TYPE_LOGIN_RESPOND,

    ENUM_MSG_TYPE_REQUEST,
    ENUM_MSG_TYPE_RESPOND,
    ENUM_MSG_TYPE_MAX=0x00ffffff,
};

struct PDU
{
    //总的协议数据单元大小
    uint uiPDULen;
    //消息类型
    uint uiMsgType;
    char caData[64];
    //实际消息长度
    uint uiMsgLen;
    //实际消息
    int caMsg[];
};

PDU *mkPDU(uint uiMsglen);
#endif // PROTOCOL_H
