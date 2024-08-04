#ifndef RESOURCE_H
#define RESOURCE_H

#include "protocol.h"
#include <QWidget>
#include <QLabel>
#include <QThread>
#include <QTcpSocket>
#include <QListWidget>
#include <QPushButton>
class MyThread : public QThread
{
    Q_OBJECT
public:
    MyThread(QObject *parent = nullptr);
    QTcpSocket m_tcpSocket;
    QString m_strUploadFliePath;
signals:
    void sigShowMsg();
    void senderPDU(PDU *pdu);

protected:
    void run();
};
class Resource : public QWidget
{
    Q_OBJECT
public:
    explicit Resource(QWidget *parent = nullptr);
    void showFlie(PDU *pdu);

    QString m_strUploadFliePath;

signals:

public slots:
    void createDir();
    void flushFile();
    void deleteFlie();
    void renNameFlie();
    void enterDir(QListWidgetItem* item);
    void returnSuperior();
    void uploadFlie();
    void upLoadFileData();
    void showErr();
    void senderPDU(PDU *pdu);


private:
    MyThread *m_pthread;
    QLabel *m_pPathLb;
    QListWidget *m_pResListW;
    QPushButton *m_pReturnPB;
    QPushButton *m_pCreateDirPB;
    // QPushButton *m_pDelDirPB;
    QPushButton *m_pRenamePB;
    QPushButton *m_pFlushFilePB;
    QPushButton *m_pUploadPB;
    QPushButton *m_pDownLoadPB;
    QPushButton *m_pDelFilePB;
    QPushButton *m_pShareFilePB;
};

#endif // RESOURCE_H
