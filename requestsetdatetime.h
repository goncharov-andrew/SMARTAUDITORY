#ifndef REQUESTSETDATETIME_H
#define REQUESTSETDATETIME_H

#include <QObject>
#include "requestmessage.h"
#include "dbpath.h"
#include "clientdatabase.h"
#include "xmlreader.h"

class RequestSetDateTime : public RequestMessage
{    
    Q_OBJECT
public:
    RequestSetDateTime();
    RequestSetDateTime(bool debug, QObject *parent = Q_NULLPTR);
    void Handle(QString message, QObject* param);

protected Q_SLOTS:
    virtual void onOpened();
    virtual void onConnected();
    virtual void onError(QAbstractSocket::SocketError error);
    virtual void onTextMessageReceived(QString message);

private:
    const QString request = "setdatetime";
    QPair<QString, QString>* auditorydata;
    bool m_debug;
};

#endif // REQUESTSETDATETIME_H
