#ifndef FWORKERS_H
#define FWORKERS_H

#include <QWidget>
#include "clientdatabase.h"
#include "dbpath.h"

namespace Ui {
class fWorkers;
}

class fWorkers : public QWidget
{
    Q_OBJECT

public:
    explicit fWorkers(QWidget *parent = 0);
    ~fWorkers();

private slots:

    void on_pushButton_auditorylog_clicked();

    void on_pushButton_workerslog_clicked();

private:
    Ui::fWorkers *ui;
};

#endif // FWORKERS_H
