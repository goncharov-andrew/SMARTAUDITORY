#ifndef ECHOCLIENT_H
#define ECHOCLIENT_H

#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>
#include <QStack>
#include "xmlreader.h"
#include "dbpath.h"
#include "clientdatabase.h"

class EchoClient : public QObject
{
    Q_OBJECT
public:
    explicit EchoClient(bool debug = false, QObject *parent = Q_NULLPTR);
    void GetDataFromAuditories(QStack<QPair<QString, QString>>* addr);

Q_SIGNALS:
    void closed();

private Q_SLOTS:
    void onOpened();
    void onConnected();
    void onTextMessageReceived(QString message);

private:
    QString request;
    QWebSocket m_webSocket;
    QStack<QPair<QString, QString>>* Auditaddresses;
    bool m_debug;
};

#endif // ECHOCLIENT_H
