#include "opewidget.h"
#include "protocol.h"

#include <QListWidget>

OpeWidget::OpeWidget(QWidget *parent)
    : QWidget{parent}
{
    m_pListW = new QListWidget(this);
    m_pListW->addItem("好友");
    m_pListW->addItem("资源");

    m_pFriend = new Friend;
    m_pResource = new Resource;

    m_pSW = new QStackedWidget;
    m_pSW->addWidget(m_pFriend);
    m_pSW->addWidget(m_pResource);

    QHBoxLayout *pMain = new QHBoxLayout;
    pMain->addWidget(m_pListW);
    pMain->addWidget(m_pSW);

    setLayout(pMain);

    // emit showFlie();
    connect(m_pListW, SIGNAL(currentRowChanged(int))
            , m_pSW, SLOT(setCurrentIndex(int)));
    // connect(m_pListW, SIGNAL(currentRowChanged(int))
    //         , this, SLOT(showFlie()));
}

OpeWidget &OpeWidget::getInstance()
{
    static OpeWidget instance;
    return instance;
}

Friend *OpeWidget::pFriend() const
{
    return m_pFriend;
}

Resource *OpeWidget::pResource() const
{
    return m_pResource;
}
