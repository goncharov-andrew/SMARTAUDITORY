#ifndef REQUESTGETDATA_H
#define REQUESTGETDATA_H

#include <QObject>
#include "requestmessage.h"
#include "dbpath.h"
#include "clientdatabase.h"
#include "xmlreader.h"

class RequestGetData : public RequestMessage
{
    Q_OBJECT
public:
    RequestGetData();
    RequestGetData(bool debug, QObject *parent = Q_NULLPTR);
    void Handle(QString message, QObject* param);

Q_SIGNALS:
    void nextauditory();

private:
    const QString request = "getdata";
    const QString endmessage = "endmessage";
    QString data;
    QStack<QPair<QString, QString>>* Auditaddresses;
    bool m_debug;

protected Q_SLOTS:
    virtual void onOpened();
    virtual void onConnected();
    virtual void onError(QAbstractSocket::SocketError error);
    virtual void onTextMessageReceived(QString message);
};

#endif // REQUESTGETDATA_H
