#ifndef FCLIMATE_H
#define FCLIMATE_H

#include <QWidget>
#include "clientdatabase.h"
#include "dbpath.h"
#include "qcustomplot.h"

namespace Ui {
class fClimate;
}

class fClimate : public QWidget
{
    Q_OBJECT

public:
    explicit fClimate(QWidget *parent = 0);
    ~fClimate();

private slots:
    void on_pushButton_getdata_clicked();

private:
    Ui::fClimate *ui;
    void prepareQCustomPlot();
    QCPGraph *graphic;          // Объявляем график
};

#endif // FCLIMATE_H
