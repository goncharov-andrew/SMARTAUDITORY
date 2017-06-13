#include "requestgetdata.h"

RequestGetData::RequestGetData(bool debug, QObject *parent) : m_debug(debug)
{
    this->setParent(parent);

    Successor = nullptr;

    data.clear();

    connect(&m_webSocket, &QWebSocket::connected, this, &RequestGetData::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &RequestGetData::closed);
    connect(&m_webSocket, &QWebSocket::textMessageReceived, this, &RequestGetData::onTextMessageReceived);
    connect(&m_webSocket, static_cast<void(QWebSocket::*)(QAbstractSocket::SocketError)>(&QWebSocket::error), this, &RequestGetData::onError);
    connect(this, &RequestGetData::nextauditory, this, &RequestGetData::onOpened);
}

void RequestGetData::Handle(QString message, QObject *param)
{
    if(request.compare(message) == 0)
    {
       Auditaddresses = ClientDataBase::GetListIPAddrAuditories(DBPath::getDBPath());
       emit nextauditory();
    }
    else
    {
        if(Successor != nullptr)
        {
            Successor->Handle(message, param);
        }
    }
}

void RequestGetData::onOpened()
{
    if(!Auditaddresses->isEmpty())
    {
        QString lm = "Connecting to %1 auditory...";

        emit logmessage(lm.arg(Auditaddresses->top().first));

        m_webSocket.open(QUrl(Auditaddresses->top().second));
    }
    else
    {
        QString lm = "The end!";

        emit logmessage(lm);
    }
}

void RequestGetData::onConnected()
{
    QString lm = "WebSocket connected to %1 auditory";

    emit logmessage(lm.arg(Auditaddresses->top().first));

    m_webSocket.sendTextMessage(request);
}

void RequestGetData::onTextMessageReceived(QString message)
{
    if(message.startsWith(endmessage) == true)
    {
        if (m_debug)
            qDebug() << "Message received:" << message;

        QString lm = "Message received from %1 auditory";

        emit logmessage(lm.arg(Auditaddresses->top().first));

        m_webSocket.close();

        QPair<QStack<Measure>, QStack<Sequrity> >* log = XmlReader::GetLogs(data);

        ClientDataBase::WriteLog(DBPath::getDBPath(), log, Auditaddresses->top().first);

//        QFile file("someTxt.txt");
//        if(file.open(QIODevice::WriteOnly))
//        {
//            QDataStream str(&file);
//            str << data;
//            file.close();
//        }

        Auditaddresses->pop();

        data.clear();

        emit nextauditory();
    }
    else
    {
        data += message;
    }
}

void RequestGetData::onError(QAbstractSocket::SocketError error)
{
    emit logmessage(m_webSocket.errorString());

    Auditaddresses->pop();

    emit nextauditory();
}
