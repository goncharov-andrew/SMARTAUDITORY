#include "xmlreader.h"

QPair<QStack<Measure>, QStack<Sequrity> > *XmlReader::GetLogs(QString log)
{
    QPair<QStack<Measure>, QStack<Sequrity>> * p = new QPair<QStack<Measure>, QStack<Sequrity>>();

    QXmlStreamReader sr(log);

    do
    {
        sr.readNext();

        if(sr.isStartElement() && sr.name() == "measure")
        {
            Measure m;

            while(!(sr.isEndElement() && sr.name() == "measure"))
            {
                if(sr.isStartElement() && sr.name() == "id")
                {
                    while(!sr.isCharacters())
                    {
                        sr.readNext();
                    }
                    m.id_measure = sr.text().toString();
                }
                else if(sr.isStartElement() && sr.name() == "readings")
                {
                    while(!sr.isCharacters())
                    {
                        sr.readNext();
                    }
                    m.readings = sr.text().toString();
                }
                else if(sr.isStartElement() && sr.name() == "hour")
                {
                    while(!sr.isCharacters())
                    {
                        sr.readNext();
                    }
                    m.hour = sr.text().toString();
                }
                else if(sr.isStartElement() && sr.name() == "minute")
                {
                    while(!sr.isCharacters())
                    {
                        sr.readNext();
                    }
                    m.minute = sr.text().toString();
                }
                else if(sr.isStartElement() && sr.name() == "day")
                {
                    while(!sr.isCharacters())
                    {
                        sr.readNext();
                    }
                    m.day = sr.text().toString();
                }
                else if(sr.isStartElement() && sr.name() == "month")
                {
                    while(!sr.isCharacters())
                    {
                        sr.readNext();
                    }
                    m.month = sr.text().toString();
                }
                else if(sr.isStartElement() && sr.name() == "year")
                {
                    while(!sr.isCharacters())
                    {
                        sr.readNext();
                    }
                    m.year = sr.text().toString();
                }

                sr.readNext();
            }
            p->first.push(m);
        }
        else if(sr.isStartElement() && sr.name() == "sequrity")
        {
            Sequrity s;

            while(!(sr.isEndElement() && sr.name() == "sequrity"))
            {
                if(sr.isStartElement() && sr.name() == "password")
                {
                    while(!sr.isCharacters())
                    {
                        sr.readNext();
                    }
                    s.password = sr.text().toString();
                }
                else if(sr.isStartElement() && sr.name() == "result")
                {
                    while(!sr.isCharacters())
                    {
                        sr.readNext();
                    }
                    s.result = sr.text().toString();
                }
                else if(sr.isStartElement() && sr.name() == "hour")
                {
                    while(!sr.isCharacters())
                    {
                        sr.readNext();
                    }
                    s.hour = sr.text().toString();
                }
                else if(sr.isStartElement() && sr.name() == "minute")
                {
                    while(!sr.isCharacters())
                    {
                        sr.readNext();
                    }
                    s.minute = sr.text().toString();
                }
                else if(sr.isStartElement() && sr.name() == "day")
                {
                    while(!sr.isCharacters())
                    {
                        sr.readNext();
                    }
                    s.day = sr.text().toString();
                }
                else if(sr.isStartElement() && sr.name() == "month")
                {
                    while(!sr.isCharacters())
                    {
                        sr.readNext();
                    }
                    s.month = sr.text().toString();
                }
                else if(sr.isStartElement() && sr.name() == "year")
                {
                    while(!sr.isCharacters())
                    {
                        sr.readNext();
                    }
                    s.year = sr.text().toString();
                }

                sr.readNext();
            }
            p->second.push(s);
        }

    }while(!sr.isEndDocument());

    return p;
}


QStringList XmlReader::GetPasswords(QString xmlpasswords)
{
     QStringList passwords;

     QXmlStreamReader sr(xmlpasswords);

     do
     {
         if(sr.isStartElement() && sr.name() == "password")
         {
            while(!sr.isCharacters())
            {
               sr.readNext();
            }

            passwords << sr.text().toString();
          }

          sr.readNext();

     }while(!sr.isEndDocument());

     return passwords;
}
