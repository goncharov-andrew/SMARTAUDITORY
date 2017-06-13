#ifndef REQUESTSETPASSWORDS_H
#define REQUESTSETPASSWORDS_H

#include <QObject>
#include "requestmessage.h"

class RequestSetPasswords : public RequestMessage
{   
    Q_OBJECT
public:
    RequestSetPasswords();
    RequestSetPasswords(bool debug, QObject *parent = Q_NULLPTR);
    void Handle(QString message, QObject* param);

protected Q_SLOTS:
    virtual void onOpened();
    virtual void onConnected();
    virtual void onError(QAbstractSocket::SocketError error);
    virtual void onTextMessageReceived(QString message);

private:
    const QString request = "setpasswords";
    QPair<QString, QString>* auditorydata;
    bool m_debug;
};

#endif // REQUESTSETPASSWORDS_H
