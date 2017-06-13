#include "xmlwriter.h"

XmlWriter::XmlWriter()
{

}

QString XmlWriter::GetXmlPasswords(QStringList passlist)
{
    QDomDocument doc;

    QDomElement root = doc.createElement("Passwords");

    doc.appendChild(root);

    for(int i = 0; i < passlist.count(); i++)
    {
        QDomElement pass = doc.createElement("password");

        root.appendChild(pass);

        QDomText passText = doc.createTextNode(passlist[i]);

        pass.appendChild(passText);
    }

    return doc.toString();
}

QString XmlWriter::GetXmlDateTime(QDateTime dt)
{
    QDomDocument doc;

    QDomElement root = doc.createElement("Datetime");

    QDomElement hour = doc.createElement("hour");
    QDomElement minute = doc.createElement("minute");
    QDomElement day = doc.createElement("day");
    QDomElement month = doc.createElement("month");
    QDomElement year = doc.createElement("year");

    QDomText hourText = doc.createTextNode(QString::number(dt.time().hour()));
    QDomText minuteText = doc.createTextNode(QString::number(dt.time().minute()));
    QDomText dayText = doc.createTextNode(QString::number(dt.date().day()));
    QDomText monthText = doc.createTextNode(QString::number(dt.date().month()));
    QDomText yearText = doc.createTextNode(QString::number(dt.date().year()));

    doc.appendChild(root);

    root.appendChild(hour);
    root.appendChild(minute);
    root.appendChild(day);
    root.appendChild(month);
    root.appendChild(year);

    hour.appendChild(hourText);
    minute.appendChild(minuteText);
    day.appendChild(dayText);
    month.appendChild(monthText);
    year.appendChild(yearText);

    return doc.toString();
}
