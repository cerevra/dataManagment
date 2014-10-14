
#include <QLabel>
#include <QRect>
#include <QScopedPointer>
#include <QGraphicsTextItem>

#include "mainwindow.h"
#include "ui_mainwindow.h"

const QString MainWindow::m_bankName = "Хранилище №";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow  (parent                  )
    , ui           (new Ui::MainWindow      )
    , m_kpCount    (0                       )
    , m_scrollValue(0                       )
    , m_scene      (new QGraphicsScene(this))
    , m_sol        (nullptr                 )
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
    for(int i = 0; i < m_kpCount; ++i)
    {
        QDoubleSpinBox* spinBox = m_kpCapacitiesSpins[i];
        ui->formLayout->labelForField(spinBox)->deleteLater();
        spinBox->deleteLater();
    }

    for(int i = 0; i < m_algoritms.size(); ++i)
    {
        delete m_algoritms[i];
    }

    delete ui;
    delete m_scene;
    delete m_sol;
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

    draw();
}

void MainWindow::calculate()
{
    QScopedPointer<Calculator> calc(m_algoritms[ui->comboBox->currentIndex()]->clone());
    QList<double> kpCapacities;

    for(int i = 0; i < m_kpCount; ++i)
        kpCapacities.append(m_kpCapacitiesSpins[i]->value());

    m_sol = calc->calc(ui->spinBox_arcCount         ->value(),
                       ui->doubleSpinBox_arcCapacity->value(),
                       kpCapacities);

    draw();
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

void MainWindow::draw()
{
    if (!m_sol)
        return;

    m_scene->clear();

    double bankCapacity  = ui->doubleSpinBox_arcCapacity->value();
    int    bankCount     = ui->spinBox_arcCount         ->value();
    int    bankNameWidth = QFontMetrics(font()).width(QString("%1%2")
                                                   .arg(m_bankName)
                                                   .arg(bankCount));

    int bankRectOffset   = bankNameWidth + 2*m_pnt.fontMargin;
    int bankRectWidth    = ui->graphicsView->width() - (bankNameWidth + 3*m_pnt.fontMargin);
    int allowedUnitWidth = bankRectWidth - 2*m_pnt.lineWidthWide;

    for (int bankIdx = 0; bankIdx < m_sol->size(); ++bankIdx)
    {
        double bankSize    = m_sol->at(bankIdx).size();
        double bankMaxSize = ui->doubleSpinBox_arcCapacity->value();
        double usage       = bankSize/bankMaxSize;

        QPen* outlinePen;

        if (bankIdx >= bankCount || usage >= 1.0)
            outlinePen = &m_pnt.penRed;
        else if (usage > 0.9 && usage < 1.0)
            outlinePen = &m_pnt.penYellow;
        else
            outlinePen = &m_pnt.penBlack;

        outlinePen->setWidth(m_pnt.lineWidthWide);

        // Хранилище
        QGraphicsTextItem* bankLabel = m_scene->addText(QString("%1%2")
                                                        .arg(m_bankName)
                                                        .arg(bankIdx+1));
        QGraphicsTextItem* bankUsage = m_scene->addText(QString("%1%\n%2/%3")
                                                        .arg(usage*100  , 0, 'g', 3)
                                                        .arg(bankSize   , 0, 'g', 4)
                                                        .arg(bankMaxSize, 0, 'g', 4));
        int yOffset = m_pnt.unitLabelHeigth + bankIdx*m_pnt.period;
        bankLabel->setPos (m_pnt.fontMargin, yOffset);
        bankUsage->setPos (m_pnt.fontMargin, yOffset + m_pnt.unitLabelHeigth);
        m_scene  ->addRect(bankRectOffset, yOffset,
                           bankRectWidth , m_pnt.bankRectHeigth, *outlinePen);

        // Блоки данных
        outlinePen->setWidth(m_pnt.lineWidthThin);

        int xOffset = bankRectOffset;
        const Units* units = m_sol->at(bankIdx).units();
        for (int unitIdx = 0; unitIdx < units->size(); ++unitIdx)
        {
            int unitNo = units->at(unitIdx);
            int unitLableOffset;
            if (unitIdx%2)
            {
                unitLableOffset = yOffset + m_pnt.bankRectHeigth + m_pnt.fontMargin;
            }
            else
            {
                unitLableOffset = yOffset - (m_pnt.fontHeigth + m_pnt.fontMargin);
            }

            double unitRectWidth = m_kpCapacitiesSpins.at(unitNo)->value()*
                                   allowedUnitWidth/
                                   bankCapacity;

            m_scene->addRect(xOffset + m_pnt.unitRectXOffset,
                             yOffset + m_pnt.unitRectYOffset,
                             unitRectWidth - m_pnt.unitRectXOffset,
                             m_pnt.unitRectHeigth,
                             m_pnt.penBlack);

            QGraphicsTextItem* unitLabel = m_scene->addText(QString("№%1")
                                                            .arg(unitNo));
            unitLabel->setPos(xOffset + unitRectWidth/2, unitLableOffset);
            xOffset += unitRectWidth;
        }
    }
}
