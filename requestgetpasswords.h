#ifndef REQUESTGETPASSWORDS_H
#define REQUESTGETPASSWORDS_H

#include <QObject>
#include "requestmessage.h"
#include "dbpath.h"
#include "clientdatabase.h"
#include "xmlreader.h"

class RequestGetPasswords : public RequestMessage
{    
    Q_OBJECT
public:
    RequestGetPasswords();
    RequestGetPasswords(bool debug, QObject *parent = Q_NULLPTR);
    void Handle(QString message, QObject* param);

protected Q_SLOTS:
    virtual void onOpened();
    virtual void onConnected();
    virtual void onError(QAbstractSocket::SocketError error);
    virtual void onTextMessageReceived(QString message);

private:
    const QString request = "getpasswords";
    const QString endmessage = "endmessage";
    QPair<QString, QString>* auditorydata;
    QString data;
    QStringList xmlpasswords;
    bool m_debug;
};

#endif // REQUESTGETPASSWORDS_H
