#include "requestsetpasswords.h"

RequestSetPasswords::RequestSetPasswords(bool debug, QObject *parent) : m_debug(debug)
{
    this->setParent(parent);

    Successor = nullptr;

    connect(&m_webSocket, &QWebSocket::connected, this, &RequestSetPasswords::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &RequestSetPasswords::closed);
    connect(&m_webSocket, &QWebSocket::textMessageReceived, this, &RequestSetPasswords::onTextMessageReceived);
    connect(&m_webSocket, static_cast<void(QWebSocket::*)(QAbstractSocket::SocketError)>(&QWebSocket::error),
            this, &RequestSetPasswords::onError);
}

void RequestSetPasswords::Handle(QString message, QObject *param)
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

void RequestSetPasswords::onOpened()
{

}

void RequestSetPasswords::onConnected()
{
    QString lm = "WebSocket connected to auditory";

    emit logmessage(lm);

    m_webSocket.sendTextMessage(auditorydata->second);
}

void RequestSetPasswords::onTextMessageReceived(QString message)
{
    QString lm = "Message received from auditory: " + message;

    emit logmessage(lm);

    m_webSocket.close();
}

void RequestSetPasswords::onError(QAbstractSocket::SocketError error)
{
    emit logmessage(m_webSocket.errorString());

    m_webSocket.close();
}

