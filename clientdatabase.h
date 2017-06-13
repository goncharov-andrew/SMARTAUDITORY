#ifndef CLIENTDATABASE_H
#define CLIENTDATABASE_H

#include <QObject>
#include <QMap>
#include "QtSql/QSqlDatabase"
#include "QtSql"
#include "QSqlQuery"
#include "xmlstructs.h"
#include <QListWidget>

class ClientDataBase
{
public:
    explicit ClientDataBase();

    static QStringList GetListAuditories(QString dbpath);//запрос на получение списка всех номеров аудиторий

    static QString GetWorkerPassword(QString dbpath, QString first_name, QString last_name);// по фамилии и имени получить пароль

    static QString GetAuditoryAddress(QString dbpath, QString AudNum);// получить по номеру аудитории ее ip-адресс

    static QStack<QListWidgetItem*> GetListWorkers(QString dbpath);// получить список всех работников

    static QStack<QListWidgetItem*> GetListWorkers(QString dbpath, QStringList passwords);// ???

    static QStringList GetListMeasures(QString dbpath);// получить список id показателей аудитории

    static void WriteLog(QString dbpath, QPair<QStack<Measure>, QStack<Sequrity> >* log, QString auditory);// записать показания в лог аудитории

    static QStack<QPair<QString, QString> >* GetListIPAddrAuditories(QString dbpath);// получить список аудиторий с их ip адресами

    static QSqlQueryModel* GetListWorkersInAuditory(QString dbpath, QString AudNum, QDate d);// получить список всех работкников, которые побывали в аудитории за выбранный день

    static QSqlQueryModel* GetWorkersSchedule(QString dbpath, QString first_name, QString last_name, QDate d);// получить список аудиторий, в которых побывал работник

    static QPair<QVector<double>, QVector<double> >* GetListMeasuresInAuditory(QString dbpath, QString AudNum, QDate d, int measure);//
};

#endif // CLIENTDATABASE_H
