#include "requestsetdatetime.h"

RequestSetDateTime::RequestSetDateTime(bool debug, QObject *parent) : m_debug(debug)
{
    this->setParent(parent);

    Successor = nullptr;

    connect(&m_webSocket, &QWebSocket::connected, this, &RequestSetDateTime::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &RequestSetDateTime::closed);
    connect(&m_webSocket, &QWebSocket::textMessageReceived, this, &RequestSetDateTime::onTextMessageReceived);
    connect(&m_webSocket, static_cast<void(QWebSocket::*)(QAbstractSocket::SocketError)>(&QWebSocket::error),
            this, &RequestSetDateTime::onError);
}

void RequestSetDateTime::Handle(QString message, QObject *param)
{
    if(request.compare(message) == 0)
    {
        auditorydata = (QPair<QString, QString>*)param;

        QString lm = "Connecting to auditory with address %1 ...";

        emit logmessage(lm.arg(auditorydata->first));

        m_webSocket.open(QUrl(auditorydata->first));//взять данные из параметров
    }
    else
    {
        if(Successor != nullptr)
        {
            Successor->Handle(message, param);
        }
    }
}

void RequestSetDateTime::onOpened()
{

}

void RequestSetDateTime::onConnected()
{
    QString lm = "WebSocket connected to auditory";

    emit logmessage(lm);

    m_webSocket.sendTextMessage(auditorydata->second);
}

void RequestSetDateTime::onTextMessageReceived(QString message)
{
    if (m_debug)
       qDebug() << "Message received:" << message;

    QString lm = "Message received from auditory: " + message;

    emit logmessage(lm);

    m_webSocket.close();
}

void RequestSetDateTime::onError(QAbstractSocket::SocketError error)
{
    emit logmessage(m_webSocket.errorString());

    m_webSocket.close();
}
