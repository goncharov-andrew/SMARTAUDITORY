#ifndef REQUESTMESSAGE_H
#define REQUESTMESSAGE_H

#include <QObject>
#include "QtWebSockets/qwebsocket.h"

class RequestMessage : public QObject
{
    Q_OBJECT
public:
    virtual ~RequestMessage(){}
    virtual void Handle(QString message, QObject* param) = 0;

Q_SIGNALS:
    void logmessage(QString logmes);
    void closed();
    void message_received(QVariant qv);

protected:
    RequestMessage* Successor;
    QWebSocket m_webSocket;

protected Q_SLOTS:
    virtual void onOpened() = 0;
    virtual void onConnected() = 0;
    virtual void onError(QAbstractSocket::SocketError error) = 0;
    virtual void onTextMessageReceived(QString message) = 0;

};

#endif // REQUESTMESSAGE_H
