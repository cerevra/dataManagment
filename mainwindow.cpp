#include <QStyleFactory>
#include <QLabel>
#include <QRect>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QApplication::setStyle("Fusion");
    onKpCountSpinChanged(ui->spinBox_kpCount->value());

    connect(ui->spinBox_kpCount, SIGNAL(valueChanged        (int)) ,
            this               , SLOT  (onKpCountSpinChanged(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onKpCountSpinChanged(int count)
{
    m_kpCount = count;

    for(int i = 0; i < m_kpCapacitiesSpins.size(); ++i)
    {
        QDoubleSpinBox* spinBox = m_kpCapacitiesSpins[i];
        ui->formLayout->labelForField(spinBox)->deleteLater();
        spinBox->deleteLater();
    }
    m_kpCapacitiesSpins.clear();

    for(int i = 0; i < count; ++i)
    {
        QDoubleSpinBox* spinBox = new QDoubleSpinBox();
        spinBox->setValue(2);
        ui->formLayout->addRow(QString("№%1").arg(i+1),spinBox);
        m_kpCapacitiesSpins.append(spinBox);
    }

    QRect geometry = ui->widget_kpCapacities->geometry();
    ui->widget_kpCapacities->setGeometry(
        QRect(geometry.topLeft(),QSize(geometry.width(),
            (ui->spinBox_kpCount->height()+ui->formLayout->verticalSpacing()
              +20 // из-за разницы размеров виджета и formLayout
              )*count)));
}
//ui->scrollArea->scroll(0,500);
