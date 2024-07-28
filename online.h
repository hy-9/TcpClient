#ifndef ONLINE_H
#define ONLINE_H

#include <QWidget>

namespace Ui {
class Online;
}
class  PDU;
class Online : public QWidget
{
    Q_OBJECT

public:
    explicit Online(QWidget *parent = nullptr);
    ~Online();
    void showOnlie(PDU *pdu);

private slots:
    void on_AddFriend_bd_clicked();

private:
    Ui::Online *ui;
};

#endif // ONLINE_H
