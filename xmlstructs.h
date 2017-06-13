#ifndef XMLSTRUCTS_H
#define XMLSTRUCTS_H

#include <QString>

struct Measure
{
    QString id_measure;
    QString readings;
    QString hour;
    QString minute;
    QString day;
    QString month;
    QString year;
};

struct Sequrity
{
    QString password;
    QString result;
    QString hour;
    QString minute;
    QString day;
    QString month;
    QString year;
};

#endif // XMLSTRUCTS_H
