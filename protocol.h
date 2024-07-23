#ifndef PROTOCOL_H
#define PROTOCOL_H

typedef unsigned int uint;

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
