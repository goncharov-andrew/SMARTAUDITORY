#ifndef FAUDITORYSETTINGS_H
#define FAUDITORYSETTINGS_H

#include <QWidget>
#include "xmlwriter.h"
#include "clientdatabase.h"
#include "requestmessage.h"
#include "requestsetdatetime.h"
#include "dbpath.h"
#include "requestgetpasswords.h"
#include "requestsetpasswords.h"

namespace Ui {
class fAuditorySettings;
}

class fAuditorySettings : public QWidget
{
    Q_OBJECT

public:
    explicit fAuditorySettings(QWidget *parent = 0);
    ~fAuditorySettings();

private slots:
    void on_pushButton_setDateTime_clicked();

    void log_message_received(QString logmes);

    void on_pushButton_getWorkers_clicked();

    void on_pushButton_setWorkers_clicked();

    void on_listWidget_WorkersInAud_doubleClicked(const QModelIndex &index);

    void on_message_passwords_received(QVariant qv);

private:
    Ui::fAuditorySettings *ui;

    RequestMessage *reqdata;

    RequestMessage *reqgetpass;

    RequestMessage *reqsetpass;
};

#endif // FAUDITORYSETTINGS_H
