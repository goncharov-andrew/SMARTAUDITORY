#include "clientdatabase.h"

ClientDataBase::ClientDataBase()
{

}

QStringList ClientDataBase::GetListAuditories(QString dbpath)
{
    QStringList strlist;
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName (dbpath);

        if (!db.open())
        {
            qDebug() << db.lastError().text();
        }
        else
        {
            QSqlQuery query;

            if (!query.exec("SELECT id FROM Auditories"))
            {
               qDebug() << "UnaЫe to make operation";
               qDebug() << query.lastError();
            }

            while (query.next())
            {
               QSqlRecord rec = query.record();
               strlist << query.value(rec.indexOf("id")).toString();
            }
         }
     }

     QSqlDatabase::removeDatabase(dbpath);

     return strlist;
}

QString ClientDataBase::GetAuditoryAddress(QString dbpath, QString AudNum)
{
    QString audaddr;

    QString pattern = "ws://%1:%2";

    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName (dbpath);

        if (!db.open())
        {
            qDebug() << db.lastError().text();
        }
        else
        {
            QSqlQuery query;

            QString strF = "SELECT * FROM Auditories WHERE  Auditories.id = '%1'";
            QString str = strF.arg(AudNum);


            if (!query.exec(str))
            {
               qDebug() << "UnaЫe to make operation";
               qDebug() << query.lastError();
            }

            while (query.next())
            {
               QSqlRecord rec = query.record();
               audaddr = pattern.arg(query.value(rec.indexOf("ip")).toString())
                                .arg(query.value(rec.indexOf("port")).toString());
            }
         }
     }

     QSqlDatabase::removeDatabase(dbpath);

     return audaddr;
}

QStack<QListWidgetItem*> ClientDataBase::GetListWorkers(QString dbpath, QStringList passwords)
{
    QStack<QListWidgetItem *> swi;
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName (dbpath);

        if (!db.open())
        {
            qDebug() << db.lastError().text();
        }
        else
        {
            QSqlQuery query;

            for(int i = 0; i < passwords.count(); i++)
            {
                QString strF = "SELECT first_name, last_name FROM Workers "
                               "WHERE Workers.password = '%1' ";

                QString str = strF.arg(passwords[i]);

                if (!query.exec(str))
                {
                   qDebug() << "UnaЫe to make operation";
                   qDebug() << query.lastError();
                }

                QString firstname = "";
                QString lastname = "";


                while (query.next())
                {
                   QSqlRecord rec = query.record();
                   firstname = query.value(rec.indexOf("first_name")).toString();
                   lastname = query.value(rec.indexOf("last_name")).toString();

                   QStringList namedata;
                   namedata.append(lastname);
                   namedata.append(firstname);

                   QListWidgetItem* item = new QListWidgetItem();
                   item->setText(lastname + " " + firstname);
                   item->setData (Qt::UserRole, namedata);
                   swi.push(item);
                }
            }
         }
     }

     QSqlDatabase::removeDatabase(dbpath);

     return swi;
}

QStack<QListWidgetItem *> ClientDataBase::GetListWorkers(QString dbpath)
{
    QStack<QListWidgetItem *> swi;

    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName (dbpath);

        if (!db.open())
        {
            qDebug() << db.lastError().text();
        }
        else
        {
            QSqlQuery query;

            if (!query.exec("SELECT last_name, first_name FROM Workers"))
            {
               qDebug() << "UnaЫe to make operation";
               qDebug() << query.lastError();
            }

            QString firstname = "";
            QString lastname = "";


            while (query.next())
            {
               QSqlRecord rec = query.record();
               firstname = query.value(rec.indexOf("first_name")).toString();
               lastname = query.value(rec.indexOf("last_name")).toString();

               QStringList namedata;
               namedata.append(lastname);
               namedata.append(firstname);

               QListWidgetItem* item = new QListWidgetItem();
               item->setText(lastname + " " + firstname);
               item->setData (Qt::UserRole, namedata);
               swi.push(item);
            }
         }
     }

     QSqlDatabase::removeDatabase(dbpath);

     return swi;
}

QStringList ClientDataBase::GetListMeasures(QString dbpath)
{
    QStringList strlist;
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName (dbpath);

        if (!db.open())
        {
            qDebug() << db.lastError().text();
        }
        else
        {
            QSqlQuery query;

            if (!query.exec("SELECT name FROM Measures"))
            {
               qDebug() << "UnaЫe to make operation";
               qDebug() << query.lastError();
            }

            while (query.next())
            {
               QSqlRecord rec = query.record();
               strlist << query.value(rec.indexOf("name")).toString();
            }
         }
     }

     QSqlDatabase::removeDatabase(dbpath);

     return strlist;
}

QSqlQueryModel* ClientDataBase::GetListWorkersInAuditory(QString dbpath, QString AudNum, QDate d)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName (dbpath);

        if (!db.open())
        {
            qDebug() << db.lastError().text();
        }
        else
        {

            QString strF = "SELECT Workers.last_name, Workers_Log.password, hour, minute, result FROM Workers_Log LEFT JOIN Workers "
                           "ON Workers_Log.password = Workers.password "
                           "WHERE Workers_Log.auditory = '%1' AND "
                           "Workers_Log.day = '%2' AND Workers_Log.month = '%3' AND Workers_Log.year = '%4'";

            QString str = strF.arg(AudNum)
                              .arg(QString::number(d.day()))
                              .arg(QString::number(d.month()))
                              .arg(QString::number(d.year()));

            model->setQuery(str);

            if (model->lastError().isValid())
            {
                qDebug () << model->lastError();
            }
         }
     }

     QSqlDatabase::removeDatabase(dbpath);

     return model;
}

QSqlQueryModel* ClientDataBase::GetWorkersSchedule(QString dbpath, QString first_name, QString last_name, QDate d)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName (dbpath);

        if (!db.open())
        {
            qDebug() << db.lastError().text();
        }
        else
        {

            QString strF = "SELECT Workers.last_name, Workers.first_name, auditory, hour, minute FROM Workers_Log LEFT JOIN Workers "
                           "ON Workers_Log.password = Workers.password "
                           "WHERE Workers.first_name = '%1' AND Workers.last_name = '%2' AND "
                           "Workers_Log.day = '%3' AND Workers_Log.month = '%4' AND Workers_Log.year = '%5'";

            QString str = strF.arg(first_name)
                              .arg(last_name)
                              .arg(QString::number(d.day()))
                              .arg(QString::number(d.month()))
                              .arg(QString::number(d.year()));

            model->setQuery(str);

            if (model->lastError().isValid())
            {
                qDebug () << model->lastError();
            }
         }
     }

     QSqlDatabase::removeDatabase(dbpath);

     return model;
}

QString ClientDataBase::GetWorkerPassword(QString dbpath, QString first_name, QString last_name)
{
    QString password;
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName (dbpath);

        if (!db.open())
        {
            qDebug() << db.lastError().text();
        }
        else
        {

            QString strF = "SELECT Workers.password FROM Workers "
                           "WHERE Workers.first_name = '%1' AND Workers.last_name = '%2' ";

            QString str = strF.arg(first_name)
                              .arg(last_name);

            QSqlQuery query;

            if (!query.exec(str))
            {
               qDebug() << "UnaЫe to make operation";
               qDebug() << query.lastError();
            }

            while (query.next())
            {
               QSqlRecord rec = query.record();

               password = query.value(rec.indexOf("password")).toString();
            }
         }
     }

     QSqlDatabase::removeDatabase(dbpath);

     return password;
}

QPair<QVector<double>, QVector<double> >* ClientDataBase::GetListMeasuresInAuditory(QString dbpath, QString AudNum, QDate d, int measure)
{
    QPair<QVector<double>, QVector<double> > *pair = new QPair<QVector<double>, QVector<double> >();

    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName (dbpath);

        if (!db.open())
        {
            qDebug() << db.lastError().text();
        }
        else
        {
            QString strF = "SELECT readings, hour, minute FROM Measures_Log "
                           "WHERE measure = '%1' AND auditory = '%2' AND "
                           "Measures_Log.day = '%3' AND Measures_Log.month = '%4' "
                           "AND Measures_Log.year = '%5' "
                           "ORDER BY hour ASC, minute ASC";

            QString str = strF.arg(QString::number(measure))
                              .arg(AudNum)
                              .arg(QString::number(d.day()))
                              .arg(QString::number(d.month()))
                              .arg(QString::number(d.year()));

            QSqlQuery query;

            if (!query.exec(str))
            {
               qDebug() << "UnaЫe to make operation";
               qDebug() << query.lastError();
            }

            while (query.next())
            {
               QSqlRecord rec = query.record();
               QTime time(query.value(rec.indexOf("hour")).toInt(),
                          query.value(rec.indexOf("minute")).toInt());

               QDateTime dt(d, time);
               pair->first.push_back(dt.toTime_t());
               pair->second.push_back(query.value(rec.indexOf("readings")).toDouble());
            }
         }
     }

     QSqlDatabase::removeDatabase(dbpath);

     return pair;
}

QStack<QPair<QString, QString>>* ClientDataBase::GetListIPAddrAuditories(QString dbpath)
{
    QStack<QPair<QString, QString>>*Auditories = new QStack<QPair<QString, QString>>();
    QString pattern = "ws://%1:%2";

    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName (dbpath);

        if (!db.open())
        {
            qDebug() << db.lastError().text();
        }
        else
        {
            QSqlQuery query;

            if (!query.exec("SELECT * FROM Auditories"))
            {
               qDebug() << "UnaЫe to make operation";
               qDebug() << query.lastError();
            }

            while (query.next())
            {
               QSqlRecord rec = query.record();
               QString str = pattern.arg(query.value(rec.indexOf("ip")).toString())
                                    .arg(query.value(rec.indexOf("port")).toString());

               Auditories->push(QPair<QString, QString>(query.value(rec.indexOf("id")).toString(), str));
            }
         }
     }

     QSqlDatabase::removeDatabase(dbpath);

     return Auditories;
}

void ClientDataBase::WriteLog(QString dbpath, QPair<QStack<Measure>, QStack<Sequrity> >* log, QString auditory)
{

    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName (dbpath);

        if (!db.open())
        {
            qDebug() << db.lastError().text();
        }
        else
        {
            QSqlQuery query;
            QString strF = "";
            QString str = "";

            strF = "INSERT INTO Measures_Log (auditory, readings, measure, hour, minute, day, month, year) "
                   "VALUES('%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8')";

            while(!log->first.isEmpty())
            {
                str = strF.arg(auditory)
                          .arg(log->first.top().readings)
                          .arg(log->first.top().id_measure)
                          .arg(log->first.top().hour)
                          .arg(log->first.top().minute)
                          .arg(log->first.top().day)
                          .arg(log->first.top().month)
                          .arg(log->first.top().year);

                if (!query.exec(str))
                {
                   qDebug() << "UnaЫe to make operation";
                   qDebug() << query.lastError();
                }

                log->first.pop();
            }

            strF = "INSERT INTO Workers_Log (auditory, password, result, hour, minute, day, month, year) "
                   "VALUES('%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8')";

            while(!log->second.isEmpty())
            {
                str = strF.arg(auditory)
                          .arg(log->second.top().password)
                          .arg(log->second.top().result)
                          .arg(log->second.top().hour)
                          .arg(log->second.top().minute)
                          .arg(log->second.top().day)
                          .arg(log->second.top().month)
                          .arg(log->second.top().year);

                if (!query.exec(str))
                {
                   qDebug() << "UnaЫe to make operation";
                   qDebug() << query.lastError();
                }

                log->second.pop();
            }
         }
     }

     QSqlDatabase::removeDatabase(dbpath);
}
