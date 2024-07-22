#include "tcpclient.h"
#include <qfile.h>
#include <qdebug.h>
#include <qstringlist.h>
#include <qmessagebox.h>
#include "./ui_tcpclient.h"

TcpClient::TcpClient(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TcpClient)
{
    ui->setupUi(this);
    loadConfig();
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
