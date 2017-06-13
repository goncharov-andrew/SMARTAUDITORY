#include "fworkers.h"
#include "ui_fworkers.h"

fWorkers::fWorkers(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::fWorkers)
{
    ui->setupUi(this);

    ui->listWidget_auditories->addItems(ClientDataBase::GetListAuditories(DBPath::getDBPath()));

    QStack<QListWidgetItem*> sw = ClientDataBase::GetListWorkers(DBPath::getDBPath());

    while(!sw.isEmpty())
    {
        ui->listWidget_workers->addItem(sw.pop());
    }
}

fWorkers::~fWorkers()
{
    delete ui;
}

void fWorkers::on_pushButton_auditorylog_clicked()
{
    QSqlQueryModel *model = ClientDataBase::GetListWorkersInAuditory(DBPath::getDBPath(),
                                                                    ui->listWidget_auditories->currentItem()->text(),
                                                                    ui->calendarWidget->selectedDate());
    ui->tableView->setModel(model);
}

void fWorkers::on_pushButton_workerslog_clicked()
{
    QVariant data = ui->listWidget_workers->currentItem()->data(Qt::UserRole);

    QSqlQueryModel *model = ClientDataBase::GetWorkersSchedule(DBPath::getDBPath(),
                                                                data.toStringList()[1],
                                                                data.toStringList()[0],
                                                                ui->calendarWidget->selectedDate());

    ui->tableView->setModel(model);
}
