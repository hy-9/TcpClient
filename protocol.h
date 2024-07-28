#ifndef PROTOCOL_H
#define PROTOCOL_H

typedef unsigned int uint;

#define REGIST_OK "regist ok"
#define REGIST_FAILED "regist failed : name existed"
#define LOGIN_OK "login ok"
#define LOGIN_FAILED "login failed : name error or pwd error or relogin"
#define SEARCH_USR_NO "search usr no"
#define SEARCH_USR_ONLINE "search usr online"
#define SEARCH_USR_OFFLINE "search usr offline"
#define ADD_FRIEND_FAILED "add friend failed"
#define ADD_FRIEND_OK "add friend ok"
#define ADD_FRIEND_EXIST "add friend exist"
#define DELETE_FRIEND_OK "delete friend ok"
#define DELETE_FRIEND_FAILED "delete friend failed"

enum ENUM_MSG_TYPE{
    ENUM_MSG_TYPE_MIN=0,
    //注册请求
    ENUM_MSG_TYPE_REGIST_REQUEST,
    //注册回复
    ENUM_MSG_TYPE_REGIST_RESPOND,
    //登录
    ENUM_MSG_TYPE_LOGIN_REQUEST,
    ENUM_MSG_TYPE_LOGIN_RESPOND,
    // 在线用户
    ENUM_MSG_TYPE_ALL_ONLINE_REQUEST,
    ENUM_MSG_TYPE_ALL_ONLINE_RESPOND,
    // 搜索用户
    ENUM_MSG_TYPE_SEARCH_USR_REQUEST,
    ENUM_MSG_TYPE_SEARCH_USR_RESPOND,
    // 加好友
    ENUM_MSG_TYPE_ADD_FRIEND_REQUEST,
    ENUM_MSG_TYPE_ADD_FRIEND_RESPOND,
    // 显示好友
    ENUM_MSG_TYPE_SHOW_FRIEND_REQUEST,
    ENUM_MSG_TYPE_SHOW_FRIEND_RESPOND,

    // 删除好友
    ENUM_MSG_TYPE_DELETE_FRIEND_REQUEST,
    ENUM_MSG_TYPE_DELETE_FRIEND_RESPOND,

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
