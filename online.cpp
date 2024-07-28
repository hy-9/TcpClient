#include "online.h"
#include "ui_online.h"
#include "protocol.h"
#include "tcpclient.h"
#include <QMessageBox>

Online::Online(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Online)
{
    ui->setupUi(this);
}

Online::~Online()
{
    delete ui;
}

void Online::showOnlie(PDU *pdu)
{
    if (NULL == pdu) {
        return;
    }
    ui->online->clear();
    char caTmp[32];
    for (int i = 0; i < pdu->uiMsgLen/32; ++i) {
        memcpy(caTmp, (char *)pdu->caMsg+i*32, 32);
        ui->online->addItem(caTmp);
    }
}

void Online::on_AddFriend_bd_clicked()
{
    QListWidgetItem *item = ui->online->currentItem();
    if (item == nullptr) {
        return;
    }
    if (strcmp(item->text().toStdString().c_str(),TcpClient::getInstance()->m_strName.toStdString().c_str()) == 0) {
        QMessageBox::information(this, "添加好友", "不能添加自己为好友");
        return;
    }
    PDU *pdu = mkPDU(0);
    memcpy(pdu->caData, TcpClient::getInstance()->m_strName.toStdString().c_str()
           , TcpClient::getInstance()->m_strName.size());
    memcpy(pdu->caData+32, item->text().toStdString().c_str()
           , item->text().size());
    pdu->uiMsgType = ENUM_MSG_TYPE_ADD_FRIEND_REQUEST;
    TcpClient::getInstance()->getTcpSocket()->write((char *)pdu,pdu->uiPDULen);
    free(pdu);
    pdu = NULL;
}

