#ifndef RESOURCE_H
#define RESOURCE_H

#include "protocol.h"
#include <QWidget>
#include <QListWidget>
#include <QPushButton>

class Resource : public QWidget
{
    Q_OBJECT
public:
    explicit Resource(QWidget *parent = nullptr);
    void showFlie(PDU *pdu);

signals:

public slots:
    void createDir();
    void flushFile();
    void deleteFlie();
    void renNameFlie();
    void enterDir(QListWidgetItem* item);

private:
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
