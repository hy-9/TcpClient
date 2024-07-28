#include "friend.h"
#include "protocol.h"
#include "tcpclient.h"
#include <QInputDialog>
#include <QMessageBox>

Friend::Friend(QWidget *parent)
    : QWidget{parent}
{

    m_pShowMsgTE = new QTextEdit;
    m_pFriendListWidget = new QListWidget;
    m_pInputMsgLE = new QLineEdit;

    m_pDelFriendPB = new QPushButton("删除好友");
    m_pFlushFrienPB = new QPushButton("刷新好友");
    m_pShowOnlineUsrPB = new QPushButton("显示在线用户");
    m_pSearchUsrPB = new QPushButton("查找用户");
    m_pMsgSendPB = new QPushButton("发送");
    m_pPrivateChatPB = new QPushButton("私聊");

    QVBoxLayout *pRightPBVBL = new QVBoxLayout;
    pRightPBVBL->addWidget(m_pDelFriendPB);
    pRightPBVBL->addWidget(m_pFlushFrienPB);
    pRightPBVBL->addWidget(m_pShowOnlineUsrPB);
    pRightPBVBL->addWidget(m_pSearchUsrPB);
    pRightPBVBL->addWidget(m_pPrivateChatPB);

    QHBoxLayout *pTopHBL = new QHBoxLayout;
    pTopHBL->addWidget(m_pShowMsgTE);
    pTopHBL->addWidget(m_pFriendListWidget);
    pTopHBL->addLayout(pRightPBVBL);

    QHBoxLayout *pMsgHBL = new QHBoxLayout;
    pMsgHBL->addWidget(m_pInputMsgLE);
    pMsgHBL->addWidget(m_pMsgSendPB);

    m_pOnline = new Online;

    QVBoxLayout *pMain = new QVBoxLayout;
    pMain->addLayout(pTopHBL);
    pMain->addLayout(pMsgHBL);
    pMain->addWidget(m_pOnline);
    m_pOnline->hide();

    setLayout(pMain);

    connect(m_pShowOnlineUsrPB, SIGNAL(clicked(bool))
            , this, SLOT(showOnline()));
    connect(m_pSearchUsrPB, SIGNAL(clicked())
            , this, SLOT(searchUsr()));
    connect(m_pFlushFrienPB, SIGNAL(clicked())
            , this, SLOT(searchFriend()));
    connect(m_pDelFriendPB, SIGNAL(clicked())
            , this, SLOT(deleteFeriend()));
    connect(TcpClient::getInstance(),SIGNAL(showFriend())
            ,this,SLOT(searchFriend()));

}

Online *Friend::pOnline() const
{
    return m_pOnline;
}

void Friend::showFriend(PDU *pdu)
{
    if (NULL == pdu) {
        return;
    }
    m_pFriendListWidget->clear();
    char caTmp[32];
    for (int i = 0; i < pdu->uiMsgLen/32; ++i) {
        memcpy(caTmp, (char *)pdu->caMsg+i*32, 32);
        m_pFriendListWidget->addItem(caTmp);
    }
}

void Friend::showOnline()
{
    if (m_pOnline->isHidden()) {
        m_pOnline->show();
        PDU *pdu = mkPDU(0);
        pdu->uiMsgType = ENUM_MSG_TYPE_ALL_ONLINE_REQUEST;
        TcpClient::getInstance()->getTcpSocket()
            ->write((char *)pdu, pdu->uiPDULen);
        free(pdu);
        pdu = NULL;

    }else{
        m_pOnline->hide();
    }
}

void Friend::searchUsr()
{
    m_strSearName = QInputDialog::getText(this, "搜索", "用户名");
    if (!m_strSearName.isEmpty()) {
        PDU *pdu = mkPDU(0);
        pdu->uiMsgType = ENUM_MSG_TYPE_SEARCH_USR_REQUEST;
        memcpy(pdu->caData, m_strSearName.toStdString().c_str(), m_strSearName.size());
        TcpClient::getInstance()->getTcpSocket()
            ->write((char *)pdu,pdu->uiPDULen);
        free(pdu);
        pdu = NULL;
    }
}

void Friend::searchFriend()
{
    PDU *pdu = mkPDU(0);
    pdu->uiMsgType = ENUM_MSG_TYPE_SHOW_FRIEND_REQUEST;
    memcpy(pdu->caData, TcpClient::getInstance()->m_strName.toStdString().c_str()
           , TcpClient::getInstance()->m_strName.size());
    TcpClient::getInstance()->getTcpSocket()
        ->write((char *)pdu,pdu->uiPDULen);
    free(pdu);
    pdu = NULL;
}

void Friend::deleteFeriend()
{
    if (m_pFriendListWidget->currentItem()==NULL) {
        return;
    }
    QMessageBox::StandardButton btn;
    btn = QMessageBox::question(this, "提示", "确实要好友"+m_pFriendListWidget->currentItem()->text()+"删除吗?"
                                , QMessageBox::Yes|QMessageBox::No);
    if (btn == QMessageBox::No) {
        return;
    }
    PDU *pdu = mkPDU(0);
    pdu->uiMsgType = ENUM_MSG_TYPE_DELETE_FRIEND_REQUEST;
    memcpy(pdu->caData, TcpClient::getInstance()->m_strName.toStdString().c_str()
           , TcpClient::getInstance()->m_strName.size());
    memcpy(pdu->caData+32, m_pFriendListWidget->currentItem()->text().toStdString().c_str()
           , m_pFriendListWidget->currentItem()->text().size());
    TcpClient::getInstance()->getTcpSocket()
        ->write((char *)pdu,pdu->uiPDULen);
    free(pdu);
    pdu = NULL;
}
