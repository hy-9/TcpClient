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
#define SENDER_CHAR_OK "sender char ok"
#define SENDER_CHAR_FAILED "sender char failed"
#define CREAT_DIR_OK "creat dir ok"
#define CREAT_DIR_PATH_NO "creat dir failed path no"
#define CREAT_DIR_PATH_REP "creat dir failed path repetition"
#define DELETE_FLIE_OK "delete dlie ok"
#define DELETE_FLIE_FAILED "delete dlie failed"
#define RENNAME_FLIE_OK "ren name flie ok"
#define RENNAME_FLIE_FAILED "ren name flie failed"
#define DIR_ENTER_OK "dir enter ok"
#define DIR_ENTER_FAILED "dir enter failed"
#define DIR_INEXISTENCE "dir inexistence"
#define FILE_CREAT_OK "file creat ok"
#define FILE_CREAT_FAILED "file creat failed"
#define UPLOAD_DATA_OK "upload data ok"
#define UPLOAD_DATA_FAILED "upload data failed"

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

    // 显示对话
    ENUM_MSG_TYPE_SHOW_CHAR_REQUEST,
    ENUM_MSG_TYPE_SHOW_CHAR_RESPOND,

    // 发送信息
    ENUM_MSG_TYPE_SENDER_CHAR_REQUEST,
    ENUM_MSG_TYPE_SENDER_CHAR_RESPOND,

    // 创建文件夹
    ENUM_MSG_TYPE_CREAT_DIR_REQUEST,
    ENUM_MSG_TYPE_CREAT_DIR_RESPOND,

    // 显示文件
    ENUM_MSG_TYPE_SHOW_FLIE_REQUEST,
    ENUM_MSG_TYPE_SHOW_FLIE_RESPOND,

    // 删除文件
    ENUM_MSG_TYPE_DELETE_FLIE_REQUEST,
    ENUM_MSG_TYPE_DELETE_FLIE_RESPOND,

    // 重命名文件
    ENUM_MSG_TYPE_RENNAME_FLIE_REQUEST,
    ENUM_MSG_TYPE_RENNAME_FLIE_RESPOND,

    // 进入文件夹
    ENUM_MSG_TYPE_ENTER_DIR_REQUEST,
    ENUM_MSG_TYPE_ENTER_DIR_RESPOND,

    // 上传文件
    ENUM_MSG_TYPE_UPLOAD_FILE_REQUEST,
    ENUM_MSG_TYPE_UPLOAD_FILE_RESPOND,

    // 上传数据
    ENUM_MSG_TYPE_UPLOAD_DATA_REQUEST,
    ENUM_MSG_TYPE_UPLOAD_DATA_RESPOND,

    // 路径
    ENUM_MSG_TYPE_PATH,

    ENUM_MSG_TYPE_REQUEST,
    ENUM_MSG_TYPE_RESPOND,
    ENUM_MSG_TYPE_MAX=0x00ffffff,
};

struct FLIE
{
    //文件名
    char flieName[32];
    // 文件类型
    int isDir;
    // 文件大小
    int flieSize;
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
