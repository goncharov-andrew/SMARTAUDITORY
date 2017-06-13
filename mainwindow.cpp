#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    reqdata = new RequestGetData(true, this);

    connect(reqdata, &RequestGetData::logmessage, this, &MainWindow::log_message_received);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_DBPath_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open DataBase"), "",
            tr("DB Files (*.db)"));

        if (fileName != "")
        {
            ui->lineEdit_DBPath->setText(fileName);

            DBPath::setDBPath(fileName);

            ui->pushButton_auditories->setEnabled(true);
            ui->pushButton_workers->setEnabled(true);
            ui->pushButton_GetData->setEnabled(true);
            ui->pushButton_auditorysettings->setEnabled(true);
        }
}

void MainWindow::on_pushButton_workers_clicked()
{
    fw = new fWorkers();

    fw->show();
}

void MainWindow::on_pushButton_auditories_clicked()
{
    fc = new fClimate();

    fc->show();
}

void MainWindow::on_pushButton_GetData_clicked()
{
    reqdata->Handle("getdata", Q_NULLPTR);
}

void MainWindow::log_message_received(QString logmes)
{
    ui->textEdit_log->append(logmes);
}

void MainWindow::on_pushButton_auditorysettings_clicked()
{
    fas = new fAuditorySettings();

    fas->show();
}
