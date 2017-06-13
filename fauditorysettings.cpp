#include "fauditorysettings.h"
#include "ui_fauditorysettings.h"

fAuditorySettings::fAuditorySettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::fAuditorySettings)
{
    ui->setupUi(this);

    ui->listWidget_auditories->addItems(ClientDataBase::GetListAuditories(DBPath::getDBPath()));

    QStack<QListWidgetItem*> sw = ClientDataBase::GetListWorkers(DBPath::getDBPath());

    while(!sw.isEmpty())
    {
        ui->listWidget_allWorkers->addItem(sw.pop());
    }

    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());

    reqdata = new RequestSetDateTime(true, this);

    reqgetpass = new RequestGetPasswords(true, this);

    reqsetpass = new RequestSetPasswords(true, this);


    connect(reqdata, &RequestSetDateTime::logmessage, this, &fAuditorySettings::log_message_received);

    connect(reqgetpass, &RequestGetPasswords::logmessage, this, &fAuditorySettings::log_message_received);

    connect(reqgetpass, &RequestGetPasswords::message_received, this, &fAuditorySettings::on_message_passwords_received);

    connect(reqsetpass, &RequestSetPasswords::logmessage, this, &fAuditorySettings::log_message_received);


}

fAuditorySettings::~fAuditorySettings()
{
    delete ui;
}

void fAuditorySettings::on_pushButton_setDateTime_clicked()
{    
    QString AuditoryAddress = ClientDataBase::GetAuditoryAddress(DBPath::getDBPath(),
                                                                 ui->listWidget_auditories->currentItem()->text());

    QString XMLDateTime = XmlWriter::GetXmlDateTime(ui->dateTimeEdit->dateTime());

    reqdata->Handle("setdatetime", (QObject*)(new QPair<QString, QString>(AuditoryAddress, XMLDateTime)));
}

void fAuditorySettings::log_message_received(QString logmes)
{
    ui->textEdit_log->append(logmes);
}

void fAuditorySettings::on_pushButton_getWorkers_clicked()
{
    QString AuditoryAddress = ClientDataBase::GetAuditoryAddress(DBPath::getDBPath(),
                                                                 ui->listWidget_auditories->currentItem()->text());

    reqgetpass->Handle("getpasswords", (QObject*)(new QPair<QString, QString>(AuditoryAddress, NULL)));
}

void fAuditorySettings::on_pushButton_setWorkers_clicked()
{
    QStringList passlist;

    for(int i = 0; i < ui->listWidget_WorkersInAud->count(); ++i)
    {
        QVariant data = ui->listWidget_WorkersInAud->item(i)->data(Qt::UserRole);

        passlist << ClientDataBase::GetWorkerPassword(DBPath::getDBPath(),
                                                      data.toStringList()[1],
                                                      data.toStringList()[0]);
    }

    QString xmlpasswords = XmlWriter::GetXmlPasswords(passlist);

    qDebug() << xmlpasswords;

    QString AuditoryAddress = ClientDataBase::GetAuditoryAddress(DBPath::getDBPath(),
                                                                 ui->listWidget_auditories->currentItem()->text());

    reqsetpass->Handle("setpasswords", (QObject*)(new QPair<QString, QString>(AuditoryAddress, xmlpasswords)));

}

void fAuditorySettings::on_listWidget_WorkersInAud_doubleClicked(const QModelIndex &index)
{
    if( !index.isValid() )
    {
       return;
    }

    if( QListWidget* listWgt = dynamic_cast< QListWidget* >( sender() ) )
    {
        if( QListWidgetItem* item = listWgt->takeItem( index.row() ) )
        {
            delete item;
        }
    }
}

void fAuditorySettings::on_message_passwords_received(QVariant qv)
{
   QStack<QListWidgetItem*> sw = ClientDataBase::GetListWorkers(DBPath::getDBPath(), qv.toStringList());

   while(!sw.isEmpty())
   {
       ui->listWidget_WorkersInAud->addItem(sw.pop());
   }
}
