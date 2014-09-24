
#include <QLabel>
#include <QRect>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow  (parent            )
    , ui           (new Ui::MainWindow)
    , m_scrollValue(0                 )
{
    ui->setupUi(this);

    onKpCountSpinChanged(ui->spinBox_kpCount->value());

    connect(ui->spinBox_kpCount, SIGNAL(valueChanged        (int)) ,
            this               , SLOT  (onKpCountSpinChanged(int)));

    connect(ui->verticalScrollBar, SIGNAL(valueChanged(int)),
            this                 , SLOT  (scrollDock  (int)));
    ui->verticalScrollBar->setMinimum(0);
    ui->verticalScrollBar->setMaximum(0);
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
        QRect(geometry.topLeft(),
              QSize(geometry.width(),
                    (  ui->spinBox_kpCount->height         ()
                     + ui->formLayout     ->verticalSpacing())*count
                     + 20 // из-за разницы размеров виджета и formLayout
                                       )));

    resizeScroll();
}

void MainWindow::scrollDock(int value)
{
    ui->frame->scroll(0, m_scrollValue - value);
    m_scrollValue = value;
}

void MainWindow::resizeEvent(QResizeEvent *)
{
    resizeScroll();
}

void MainWindow::resizeScroll()
{
    ui->verticalScrollBar->setMinimum(0);

    int max = ui->widget_kpCapacities->y     () - ui->frame->y     ()
            + ui->widget_kpCapacities->height() - ui->frame->height();
    if (max < 0)
        max = 0;

    ui->verticalScrollBar->setMaximum(max);
}
