#include "tcpclient.h"
#include "protocol.h"
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
            QMessageBox::information(this, "登录", "登录成功");
        }else if(strcmp(pdu->caData, LOGIN_FAILED) == 0){
            QMessageBox::warning(this, "登录", "登录失败,用户名密码错误或重复登录。");
        }
        break;
    }
    default:
        break;
    }

    free(pdu);
    pdu = NULL;
}

// void TcpClient::on_But_sender_clicked()
// {
//     QString strMsg = ui->lineEdit->text();
//     if (!strMsg.isEmpty()) {
//         PDU *pdu = mkPDU(strMsg.size());
//         pdu->uiMsgType = 8888;
//         memcpy(pdu->caMsg, strMsg.toStdString().c_str(), strMsg.size());
//         m_tcpSocket->write((char *)pdu, pdu->uiPDULen);
//         free(pdu);
//         pdu = NULL;
//     }else{
//         QMessageBox::warning(this, "发送信息", "发送信息为空");
//     }
// }


void TcpClient::on_pushButton_login_clicked()
{
    QString strName = ui->lineEdit_userName->text();
    QString strPwd = ui->lineEdit_password->text();
    if (!strName.isEmpty() && !strPwd.isEmpty()) {
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

