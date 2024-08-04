#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QWidget>
#include "QTcpSocket"

QT_BEGIN_NAMESPACE
namespace Ui {
class TcpClient;
}
QT_END_NAMESPACE

class QTcpSocket;

class TcpClient : public QWidget
{
    Q_OBJECT

public:
    TcpClient(QWidget *parent = nullptr);
    ~TcpClient();
    static TcpClient* getInstance();
    void loadConfig();
    QTcpSocket* getTcpSocket();
    QString m_strName;
    QString m_strCurPuath;
    QString m_strIP;
    quint16 m_usPort;

signals:
    void showFriend();
    void showChar();
    void showFlie();
    void upLoadFile();

public slots:
    void showConnect();
    void rescvMsg();

private slots:

    void on_pushButton_login_clicked();

    void on_pushButton_register_clicked();

private:
    Ui::TcpClient *ui;


    QTcpSocket *m_tcpSocket;
};
#endif // TCPCLIENT_H
