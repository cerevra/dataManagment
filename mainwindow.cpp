
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
    const QPen penBlack (Qt::black );
    const QPen penRed   (Qt::red   );
    const QPen penYellow(Qt::yellow);

    const int bankRectHeigth = 56;
    const int bankMargin = 25;
    const int fontHeigth = 8;
    const int fontMargin = 10;
    const int unitLabelHeigth = fontHeigth + 2*fontMargin;
    const int period     = bankRectHeigth + bankMargin + unitLabelHeigth;

    int bankCount     = ui->spinBox_arcCount->value();
    int bankNameWidth = QFontMetrics(font()).width(QString("%1%2")
                                                   .arg(m_bankName)
                                                   .arg(bankCount));

    int sceneWidth     = ui->graphicsView->width();
    int bankRectMargin = bankNameWidth + 2*fontMargin;
    int bankRectWidth  = sceneWidth - (bankNameWidth + 2*fontMargin) - 10;

    if (m_sol)
    {
        m_scene->clear();

        for (int i = 0; i < m_sol->size(); ++i)
        {
            double bankSize    = m_sol->at(i).size();
            double bankMaxSize = ui->doubleSpinBox_arcCapacity->value();
            double usage = bankSize/bankMaxSize;

            QPen* outlinePen;

            if (i >= bankCount || usage >= 1.0)
                outlinePen = new QPen(penRed   );
            else if (usage > 0.9 && usage < 1.0)
                outlinePen = new QPen(penYellow);
            else
                outlinePen = new QPen(penBlack );

            outlinePen->setWidth(2);

            // Хранилище
            QGraphicsTextItem* bankLabel = m_scene->addText(QString("%1%2")
                                                            .arg(m_bankName)
                                                            .arg(i+1));
            QGraphicsTextItem* bankUsage = m_scene->addText(QString("%1%\n%2/%3")
                                                            .arg(usage*100  , 0, 'g', 3)
                                                            .arg(bankSize   , 0, 'g', 4)
                                                            .arg(bankMaxSize, 0, 'g', 4));
            int topMargin = unitLabelHeigth + i*period;
            bankLabel->setPos (fontMargin    , topMargin);
            bankUsage->setPos (fontMargin    , topMargin + fontHeigth + fontMargin);
            m_scene  ->addRect(bankRectMargin, topMargin,
                               bankRectWidth , bankRectHeigth, *outlinePen);

            // Блоки данных
            int rectHeigth   = bankRectHeigth - 4*outlinePen->width();
            int allowedWidth = bankRectWidth  - 4*outlinePen->width();

            int xOffset = bankRectMargin;
            const Units* units = m_sol->at(i).units();
            for (int k = 0; k < units->size(); ++k)
            {
                int yOffset;
                if (k%2)
                {
                    yOffset = topMargin - (fontHeigth + fontMargin);
                }
                else
                {
                    yOffset = topMargin + bankRectHeigth + fontMargin;
                }

//                int unitWidth = ;

                xOffset;

                QGraphicsTextItem* unitLabel = m_scene->addText(QString("№%1")
                                                                .arg(units->at(k)));
                bankLabel->setPos(fontMargin, yOffset);
            }
        }
    }
}
