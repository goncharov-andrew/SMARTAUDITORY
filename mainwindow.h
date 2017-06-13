#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>

#include "clientdatabase.h"
#include "dbpath.h"
#include "fworkers.h"
#include "fclimate.h"
#include "requestgetdata.h"
#include "requestmessage.h"
#include "fauditorysettings.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_DBPath_clicked();

    void on_pushButton_workers_clicked();

    void on_pushButton_auditories_clicked();

    void on_pushButton_GetData_clicked();

    void log_message_received(QString logmes);

    void on_pushButton_auditorysettings_clicked();

private:
    Ui::MainWindow *ui;

    RequestMessage *reqdata;

    fWorkers *fw;

    fClimate *fc;

    fAuditorySettings *fas;
};

#endif // MAINWINDOW_H
