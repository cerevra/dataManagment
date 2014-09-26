
#include <QLabel>
#include <QRect>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow  (parent                  )
    , ui           (new Ui::MainWindow      )
    , m_kpCount    (0                       )
    , m_scrollValue(0                       )
    , m_scene      (new QGraphicsScene(this))
{
    ui->setupUi(this);

    // !!! Здесь добавляем в использование свой алгоритм !!!
    m_algoritms.append(new CalcUniform());
    //m_algoritms.append(new yourCalc());

    onKpCountSpinChanged(ui->spinBox_kpCount->value());
    connect(ui->spinBox_kpCount  , SIGNAL(valueChanged        (int)) ,
            this                 , SLOT  (onKpCountSpinChanged(int)));
    connect(ui->verticalScrollBar, SIGNAL(valueChanged(int)),
            this                 , SLOT  (scrollDock  (int)));

    connect(ui->pushButton       , SIGNAL(clicked  ()),
            this                 , SLOT  (calculate()));

    ui->graphicsView->setScene(m_scene);

    connect(ui->comboBox         , SIGNAL(currentIndexChanged(int)),
            this                 , SLOT  (displayBrief(int)));

    for (int i = 0; i < m_algoritms.size(); ++i)
    {
        ui->comboBox->addItem(m_algoritms[i]->name(), i);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onKpCountSpinChanged(int count)
{
    if (count < m_kpCount)
    {
        for(int i = m_kpCount - 1; i > count - 1; --i)
        {
            QDoubleSpinBox* spinBox = m_kpCapacitiesSpins[i];
            ui->formLayout->labelForField(spinBox)->deleteLater();
            spinBox->deleteLater();
            m_kpCapacitiesSpins.removeAt(i);
        }
    }
    else if (count > m_kpCount)
    {
        for(int i = m_kpCount; i < count; ++i)
        {
            QDoubleSpinBox* spinBox = new QDoubleSpinBox(this);
            spinBox->setValue  (2);
            spinBox->setMinimum(0.01);
            ui->formLayout->addRow(QString("№%1").arg(i+1),spinBox);
            m_kpCapacitiesSpins.append(spinBox);
        }
    }

    QRect geometry = ui->widget_kpCapacities->geometry();
    ui->widget_kpCapacities->setGeometry(
        QRect(geometry.topLeft(),
              QSize(geometry.width(),
                    (  ui->spinBox_kpCount->height         ()
                     + ui->formLayout     ->verticalSpacing())*count
                     + 20 // из-за разницы размеров виджета и formLayout
                                       )));

    m_kpCount = count;

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

void MainWindow::calculate()
{
//    Calculator calc();


    QBrush greenBrush(Qt::green);
    QBrush blueBrush(Qt::blue);
    QPen outlinePen(Qt::black);
    outlinePen.setWidth(2);

    QGraphicsRectItem *rectangle = m_scene->addRect(100, 0, 80, 100, outlinePen, blueBrush);

}

void MainWindow::displayBrief(int index)
{
    ui->plainTextEdit->clear();
    ui->plainTextEdit->insertPlainText(m_algoritms[index]->brief());
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
