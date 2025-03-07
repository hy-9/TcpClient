#ifndef OPEWIDGET_H
#define OPEWIDGET_H

#include <QWidget>
#include <QStackedWidget>

#include "friend.h"
#include "resource.h"

class QListWidget;

class OpeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OpeWidget(QWidget *parent = nullptr);
    static OpeWidget& getInstance();
    Friend *pFriend() const;

    Resource *pResource() const;

signals:
    void showFlie();
private:
    QListWidget *m_pListW;
    Friend *m_pFriend;
    Resource *m_pResource;
    QStackedWidget *m_pSW;

signals:
};

#endif // OPEWIDGET_H
