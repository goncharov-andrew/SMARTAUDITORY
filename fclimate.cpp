#include "fclimate.h"
#include "ui_fclimate.h"

fClimate::fClimate(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::fClimate)
{
    ui->setupUi(this);
    ui->comboBox_auditories->addItems(ClientDataBase::GetListAuditories(DBPath::getDBPath()));
    ui->comboBox_measures->addItems(ClientDataBase::GetListMeasures(DBPath::getDBPath()));

    // Инициализируем полотно для графика функции
    prepareQCustomPlot();
    // Инициализируем график и привязываем его к Осям
    graphic = new QCPGraph(ui->customPlot->xAxis, ui->customPlot->yAxis);
    // Устанавливаем цвет графика
    QPen pen(Qt::red);
    pen.setWidth(4);
    graphic->setPen(pen);
    // Устанавливаем график на полотно
    ui->customPlot->addPlottable(graphic);
}

fClimate::~fClimate()
{
    delete ui;
}

void fClimate::prepareQCustomPlot()
{
    ui->customPlot->setInteraction(QCP::iRangeZoom,true);   // Включаем взаимодействие удаления/приближения
    ui->customPlot->setInteraction(QCP::iRangeDrag, true);  // Включаем взаимодействие перетаскивания графика
    ui->customPlot->axisRect()->setRangeDrag(Qt::Horizontal);   // Включаем перетаскивание только по горизонтальной оси
    ui->customPlot->axisRect()->setRangeZoom(Qt::Horizontal);   // Включаем удаление/приближение только по горизонтальной оси
    ui->customPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);   // Подпись координат по Оси X в качестве Даты и Времени
    ui->customPlot->xAxis->setDateTimeFormat("hh:mm");  // Устанавливаем формат даты и времени
    ui->customPlot->xAxis->setLabel("Time");

    // Настраиваем шрифт по осям координат
    ui->customPlot->xAxis->setTickLabelFont(QFont(QFont().family(), 8));
    ui->customPlot->yAxis->setTickLabelFont(QFont(QFont().family(), 8));

    // Автоматическое масштабирование тиков по Оси X
    ui->customPlot->xAxis->setAutoTickStep(true);

    ui->customPlot->yAxis->setTickLabelColor(QColor(Qt::red)); // Красный цвет подписей тиков по Оси Y
    ui->customPlot->legend->setVisible(true);   //Включаем Легенду графика
    // Устанавливаем Легенду в левый верхний угол графика
    ui->customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft|Qt::AlignTop);
}

void fClimate::on_pushButton_getdata_clicked()
{
    QPair<QVector<double>, QVector<double> > * pair = ClientDataBase::GetListMeasuresInAuditory(DBPath::getDBPath(),
                                                                    ui->comboBox_auditories->currentText(),
                                                                    ui->calendarWidget->selectedDate(),
                                                                    ui->comboBox_measures->currentIndex() + 1);

    graphic->clearData();                                    // Очищаем данные
    graphic->setName(ui->comboBox_measures->currentText());  // Устанавливаем название легенды
    graphic->setData(pair->first, pair->second);             // Устанавливаем данные


    ui->customPlot->rescaleAxes();      // Масштабируем график по данным
    ui->customPlot->replot();           // Отрисовываем график

    pair->first.clear();
    pair->second.clear();
    delete pair;
}
