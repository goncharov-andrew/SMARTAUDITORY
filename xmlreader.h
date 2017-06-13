#ifndef XMLREADER_H
#define XMLREADER_H

#include<QtXml>
#include "xmlstructs.h"

class XmlReader
{
public:
    XmlReader();
    static QPair<QStack<Measure>, QStack<Sequrity> > *GetLogs(QString log);
    static QStringList GetPasswords(QString xmlpasswords);
};

#endif // XMLREADER_H
