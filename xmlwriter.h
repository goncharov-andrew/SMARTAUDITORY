#ifndef XMLWRITER_H
#define XMLWRITER_H

#include<QtXml>

class XmlWriter
{
public:
    XmlWriter();
    static QString GetXmlDateTime(QDateTime dt);
    static QString GetXmlPasswords(QStringList passlist);
};

#endif // XMLWRITER_H
