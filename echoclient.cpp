#include "echoclient.h"
#include <QtCore/QDebug>


QT_USE_NAMESPACE

EchoClient::EchoClient(bool debug, QObject *parent) :
    QObject(parent), m_debug(debug)
{
    connect(&m_webSocket, &QWebSocket::connected, this, &EchoClient::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &EchoClient::closed);
    connect(&m_webSocket, &QWebSocket::textMessageReceived, this, &EchoClient::onTextMessageReceived);
}

void EchoClient::GetDataFromAuditories(QStack<QPair<QString, QString> > *addr)
{
    EchoClient::Auditaddresses = addr;
    this->onOpened();
}

void EchoClient::onOpened()
{
    m_webSocket.open(QUrl(Auditaddresses->top().second));
}

void EchoClient::onConnected()
{
    if (m_debug)
        qDebug() << "WebSocket connected";
    m_webSocket.sendTextMessage(QStringLiteral("getdata"));
}

void EchoClient::onTextMessageReceived(QString message)
{
    if (m_debug)
        qDebug() << "Message received:" << message;

    m_webSocket.close();

    QPair<QStack<Measure>, QStack<Sequrity> >* log = XmlReader::GetLogs(message);

    ClientDataBase::WriteLog(DBPath::getDBPath(), log, Auditaddresses->top().first);

    //запись в БД с учетом аудитории, потом выталкиваем из стека аудиторию и emit сигнал в onOpened
}


