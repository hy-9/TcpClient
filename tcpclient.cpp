#include "tcpclient.h"
#include "protocol.h"
#include "opewidget.h"
#include <qfile.h>
#include <qdebug.h>
#include <QTcpSocket>
#include <qstringlist.h>
#include <qmessagebox.h>
#include <qhostaddress.h>
#include "./ui_tcpclient.h"

TcpClient::TcpClient(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TcpClient)
{
    ui->setupUi(this);
    m_tcpSocket = new QTcpSocket;
    connect(m_tcpSocket,SIGNAL(connected())
            ,this,SLOT(showConnect()));

    connect(m_tcpSocket,SIGNAL(readyRead())
            ,this,SLOT(rescvMsg()));

    loadConfig();
    m_tcpSocket->connectToHost(QHostAddress(m_strIP),m_usPort);
}

TcpClient::~TcpClient()
{
    delete ui;
}

TcpClient *TcpClient::getInstance()
{
    static TcpClient instance;
    return &instance;
}

void TcpClient::loadConfig()
{
    QFile file(":/client.config");
    if(file.open(QIODevice::ReadOnly)){
        QString strData = file.readAll();
        file.close();

        strData.replace("\r\n"," ");
        QStringList strlist = strData.split(" ");
        m_strIP = strlist.at(0);
        m_usPort = strlist.at(1).toUShort();
        qDebug()<<"IP:"<<m_strIP<<" 端口:"<<m_usPort;
    }else{
        QMessageBox::critical(this, "打开配置文件", "打开配置文件失败");
    }
}

QTcpSocket *TcpClient::getTcpSocket()
{
    return m_tcpSocket;
}

void TcpClient::showConnect()
{
    QMessageBox::information(this,"连接服务器","连接服务器成功");
}

void TcpClient::rescvMsg()
{
    qDebug() << m_tcpSocket->bytesAvailable();
    uint uiPDULen = 0;
    m_tcpSocket->read((char*)&uiPDULen, sizeof(uint));
    uint uiMsgLen = uiPDULen-sizeof(PDU);
    PDU *pdu =mkPDU(uiMsgLen);
    m_tcpSocket->read((char*)pdu+sizeof(uint), uiPDULen-sizeof(uint));

    switch (pdu->uiMsgType) {
    case ENUM_MSG_TYPE_REGIST_RESPOND:
    {
        if (strcmp(pdu->caData, REGIST_OK) == 0) {
            QMessageBox::information(this, "注册", "注册成功");
        }else if(strcmp(pdu->caData, REGIST_FAILED) == 0){
            QMessageBox::warning(this, "注册", "注册失败,以存在用户名。");
        }
        break;
    }
    case ENUM_MSG_TYPE_LOGIN_RESPOND:
    {
        if (strcmp(pdu->caData, LOGIN_OK) == 0) {
            m_strCurPuath = QString("./%1").arg(m_strName);
            QMessageBox::information(this, "登录", "登录成功");
            OpeWidget::getInstance().show();
            emit showFriend();
            // emit showFlie();
            hide();
        }else if(strcmp(pdu->caData, LOGIN_FAILED) == 0){
            QMessageBox::warning(this, "登录", "登录失败,用户名密码错误或重复登录。");
            m_strName = NULL;
        }
        break;
    }
    case ENUM_MSG_TYPE_ALL_ONLINE_RESPOND:{
        OpeWidget::getInstance().pFriend()
            ->pOnline()->showOnlie(pdu);
        break;
    }
    case ENUM_MSG_TYPE_SEARCH_USR_RESPOND:{
        if (strcmp(pdu->caData, SEARCH_USR_NO) == 0) {
            QMessageBox::information(this, "搜索"
                , OpeWidget::getInstance().pFriend()->m_strSearName+"不存在");
        }else if (strcmp(pdu->caData, SEARCH_USR_ONLINE) == 0) {
            QMessageBox::information(this, "搜索"
                , OpeWidget::getInstance().pFriend()->m_strSearName+"在线");
        }else if (strcmp(pdu->caData, SEARCH_USR_OFFLINE) == 0) {
            QMessageBox::information(this, "搜索"
                , OpeWidget::getInstance().pFriend()->m_strSearName+"不在线");
        }
        break;
    }
    case ENUM_MSG_TYPE_ADD_FRIEND_RESPOND:{
        if (strcmp(pdu->caData, ADD_FRIEND_FAILED) == 0) {
            QMessageBox::information(this, "添加好友", "添加好友失败");
        }else if (strcmp(pdu->caData, ADD_FRIEND_EXIST) == 0) {
            QMessageBox::information(this, "添加好友", "添加好友失败，已经为好友");
        }else if (strcmp(pdu->caData, ADD_FRIEND_OK) == 0) {
            QMessageBox::information(this, "添加好友", "添加好友成功");
        }
        break;
    }
    case ENUM_MSG_TYPE_SHOW_FRIEND_RESPOND:{
        OpeWidget::getInstance().pFriend()->showFriend(pdu);
        break;
    }
    case ENUM_MSG_TYPE_DELETE_FRIEND_RESPOND:{
        if (strcmp(pdu->caData, DELETE_FRIEND_OK) == 0) {
            QMessageBox::information(this, "删除好友", "删除好友成功");
        }else if (strcmp(pdu->caData, DELETE_FRIEND_OK) == 0) {
            QMessageBox::information(this, "删除好友", "删除好友失败，已不为好友");
        }
        emit showFriend();
        break;
    }case ENUM_MSG_TYPE_SHOW_CHAR_RESPOND:{
        OpeWidget::getInstance().pFriend()
            ->showFriendChar(pdu);
        break;
    }case ENUM_MSG_TYPE_SENDER_CHAR_RESPOND:{
        if (strcmp(pdu->caData, SENDER_CHAR_FAILED) == 0) {
            QMessageBox::information(this, "发送信息", "发送失败");
            break;
        }
        emit showChar();
        break;
    }case ENUM_MSG_TYPE_CREAT_DIR_RESPOND:{
        if (strcmp(pdu->caData, CREAT_DIR_PATH_NO) == 0) {
            QMessageBox::information(this, "创建文件夹", "路径不存在");
        }else if (strcmp(pdu->caData, CREAT_DIR_PATH_REP) == 0) {
            QMessageBox::information(this, "创建文件夹", "文件夹已存在");
        }
        break;
    }case ENUM_MSG_TYPE_SHOW_FLIE_RESPOND:{
        OpeWidget::getInstance().pResource()->showFlie(pdu);
        break;
    }case ENUM_MSG_TYPE_DELETE_FLIE_RESPOND:{
        if (strcmp(pdu->caData, DELETE_FLIE_OK) == 0) {
            QMessageBox::warning(this, "文件删除", "删除成功");
            emit showFlie();
        }else if(strcmp(pdu->caData, DELETE_FLIE_FAILED) == 0){
            QMessageBox::warning(this, "文件删除", "删除失败");
            emit showFlie();
        }
        break;
    }
    default:
        break;
    }

    free(pdu);
    pdu = NULL;
}

void TcpClient::on_pushButton_login_clicked()
{
    QString strName = ui->lineEdit_userName->text();
    QString strPwd = ui->lineEdit_password->text();
    if (!strName.isEmpty() && !strPwd.isEmpty()) {
        m_strName = strName;
        PDU *pdu = mkPDU(0);
        pdu->uiMsgType = ENUM_MSG_TYPE_LOGIN_REQUEST;
        strncpy(pdu->caData, strName.toStdString().c_str(), 32);
        strncpy(pdu->caData+32, strPwd.toStdString().c_str(), 32);
        m_tcpSocket->write((char *)pdu, pdu->uiPDULen);
        free(pdu);
        pdu = NULL;
    }else{
        QMessageBox::critical(this,"登录失败","用户名与密码不能为空");
    }
}


void TcpClient::on_pushButton_register_clicked()
{
    QString strName = ui->lineEdit_userName->text();
    QString strPwd = ui->lineEdit_password->text();
    if (!strName.isEmpty() && !strPwd.isEmpty()) {
        PDU *pdu = mkPDU(0);
        pdu->uiMsgType = ENUM_MSG_TYPE_REGIST_REQUEST;
        strncpy(pdu->caData, strName.toStdString().c_str(), 32);
        strncpy(pdu->caData+32, strPwd.toStdString().c_str(), 32);

        m_tcpSocket->write((char *)pdu, pdu->uiPDULen);
        free(pdu);
        pdu = NULL;
    }else{
        QMessageBox::critical(this,"注册失败","用户名与密码不能为空");
    }
}
