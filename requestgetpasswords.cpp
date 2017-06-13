#include "requestgetpasswords.h"

RequestGetPasswords::RequestGetPasswords(bool debug, QObject *parent) : m_debug(debug)
{
    this->setParent(parent);

    Successor = nullptr;

    connect(&m_webSocket, &QWebSocket::connected, this, &RequestGetPasswords::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &RequestGetPasswords::closed);
    connect(&m_webSocket, &QWebSocket::textMessageReceived, this, &RequestGetPasswords::onTextMessageReceived);
    connect(&m_webSocket, static_cast<void(QWebSocket::*)(QAbstractSocket::SocketError)>(&QWebSocket::error),
            this, &RequestGetPasswords::onError);
}

void RequestGetPasswords::Handle(QString message, QObject *param)
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

void RequestGetPasswords::onOpened()
{

}

void RequestGetPasswords::onConnected()
{
    QString lm = "WebSocket connected to auditory";

    emit logmessage(lm);

    m_webSocket.sendTextMessage(request);
}

void RequestGetPasswords::onTextMessageReceived(QString message)
{
    if(message.startsWith(endmessage) == true)
    {
        if (m_debug)
            qDebug() << "Message received:" << data;

        QString lm = "Message received from auditory";

        emit logmessage(lm);

        m_webSocket.close();

        QVariant qv(XmlReader::GetPasswords(data));

        emit message_received(qv);
    }
    else
    {
        data += message;
    }


}

void RequestGetPasswords::onError(QAbstractSocket::SocketError error)
{
    emit logmessage(m_webSocket.errorString());

    m_webSocket.close();
}

