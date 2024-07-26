#include "online.h"
#include "ui_online.h"
#include "protocol.h"

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
