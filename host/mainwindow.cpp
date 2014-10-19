
#include <QLabel>
#include <QRect>
#include <QScopedPointer>
#include <QGraphicsTextItem>
#include <QPluginLoader>
#include <QStringList>
#include <QDir>
#include <QCoreApplication>

#include "iplugin.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

const QString MainWindow::m_storageName = "Хранилище №";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow  (parent                  )
    , ui           (new Ui::MainWindow      )
    , m_unitCount  (0                       )
    , m_scrollValue(0                       )
    , m_scene      (new QGraphicsScene(this))
    , m_sol        (nullptr                 )
    , m_dlgPlugins (new Plugins       (this))
    , m_dlgAbout   (new About         (this))
{
    ui->setupUi(this);

    ui->graphicsView->setScene(m_scene);

    onUnitCountSpinChanged(ui->spinBox_unitCount->value());
    connect(ui->spinBox_unitCount, SIGNAL(valueChanged          (int)) ,
            this                 , SLOT  (onUnitCountSpinChanged(int)));
    connect(ui->verticalScrollBar, SIGNAL(valueChanged(int)),
            this                 , SLOT  (scrollDock  (int)));

    connect(ui->pushButton       , SIGNAL(clicked  ()),
            this                 , SLOT  (calculate()));

    connect(ui->action_about     , SIGNAL(triggered()),
            m_dlgAbout           , SLOT  (show     ()));

    connect(ui->action_plugins   , SIGNAL(triggered()),
            m_dlgPlugins         , SLOT  (show     ()));
    loadPlugins();

    connect(ui->comboBox         , SIGNAL(currentIndexChanged(int)),
            this                 , SLOT  (displayBrief(int)));
    for (int i = 0; i < m_algoritms.size(); ++i)
    {
        ui->comboBox->addItem(m_algoritms[i]->name(), i);
    }
}

MainWindow::~MainWindow()
{
    for(int i = 0; i < m_unitCount; ++i)
    {
        QDoubleSpinBox* spinBox = m_unitCapacitiesSpins[i];
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

void MainWindow::onUnitCountSpinChanged(int count)
{
    if (count < m_unitCount)
    {
        for(int i = m_unitCount - 1; i > count - 1; --i)
        {
            QDoubleSpinBox* spinBox = m_unitCapacitiesSpins[i];
            ui->formLayout->labelForField(spinBox)->deleteLater();
            spinBox->deleteLater();
            m_unitCapacitiesSpins.removeAt(i);
        }
    }
    else if (count > m_unitCount)
    {
        for(int i = m_unitCount; i < count; ++i)
        {
            QDoubleSpinBox* spinBox = new QDoubleSpinBox(this);
            spinBox->setValue  (2);
            spinBox->setMinimum(0.01);
            ui->formLayout->addRow(QString("№%1").arg(i+1),spinBox);
            m_unitCapacitiesSpins.append(spinBox);
        }
    }

    QRect geometry = ui->widget_unitCapacities->geometry();
    ui->widget_unitCapacities->setGeometry(
        QRect(geometry.topLeft(),
              QSize(geometry.width(),
                    (  ui->spinBox_unitCount->height       ()
                     + ui->formLayout     ->verticalSpacing())*count
                     + 20 // из-за разницы размеров виджета и formLayout
                                       )));

    m_unitCount = count;

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
    if (!ui->comboBox->count())
        return;

    QScopedPointer<Calculator> calc(m_algoritms[ui->comboBox->currentIndex()]->clone());
    QList<double> unitCapacities;

    for(int i = 0; i < m_unitCount; ++i)
        unitCapacities.append(m_unitCapacitiesSpins[i]  ->value());

    m_sol = calc->calc(ui->spinBox_storageCount         ->value(),
                       ui->doubleSpinBox_storageCapacity->value(),
                       unitCapacities);

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

    int max = ui->widget_unitCapacities->y     () - ui->frame->y     ()
            + ui->widget_unitCapacities->height() - ui->frame->height();
    if (max < 0)
        max = 0;

    ui->verticalScrollBar->setMaximum(max);
}

void MainWindow::draw()
{
    if (!m_sol)
        return;

    m_scene->clear();

    double storageCapacity  = ui->doubleSpinBox_storageCapacity->value();
    int    storageCount     = ui->spinBox_storageCount         ->value();
    int    storageNameWidth = QFontMetrics(font()).width(QString("%1%2")
                                                   .arg(m_storageName)
                                                   .arg(storageCount));

    int storageRectOffset   = storageNameWidth + 2*m_pnt.fontMargin;
    int storageRectWidth    = ui->graphicsView->width() - (storageNameWidth + 3*m_pnt.fontMargin);
    int allowedUnitWidth = storageRectWidth - 2*m_pnt.lineWidthWide;

    for (int storageIdx = 0; storageIdx < m_sol->size(); ++storageIdx)
    {
        double storageSize    = m_sol->at(storageIdx).size();
        double storageMaxSize = ui->doubleSpinBox_storageCapacity->value();
        double usage       = storageSize/storageMaxSize;

        QPen* outlinePen;

        if (storageIdx >= storageCount || usage >= 1.0)
            outlinePen = &m_pnt.penRed;
        else if (usage > 0.9 && usage < 1.0)
            outlinePen = &m_pnt.penYellow;
        else
            outlinePen = &m_pnt.penBlack;

        outlinePen->setWidth(m_pnt.lineWidthWide);

        // Хранилище
        QGraphicsTextItem* storageLabel = m_scene->addText(QString("%1%2")
                                                        .arg(m_storageName)
                                                        .arg(storageIdx+1));
        QGraphicsTextItem* storageUsage = m_scene->addText(QString("%1%\n%2/%3")
                                                        .arg(usage*100     , 0, 'g', 3)
                                                        .arg(storageSize   , 0, 'g', 4)
                                                        .arg(storageMaxSize, 0, 'g', 4));
        int yOffset = m_pnt.unitLabelHeigth + storageIdx*m_pnt.period;
        storageLabel->setPos (m_pnt.fontMargin, yOffset);
        storageUsage->setPos (m_pnt.fontMargin, yOffset + m_pnt.unitLabelHeigth);
        m_scene  ->addRect(storageRectOffset, yOffset,
                           storageRectWidth , m_pnt.storageRectHeigth, *outlinePen);

        // Блоки данных
        outlinePen->setWidth(m_pnt.lineWidthThin);

        int xOffset = storageRectOffset;
        const Units* units = m_sol->at(storageIdx).units();
        for (int unitIdx = 0; unitIdx < units->size(); ++unitIdx)
        {
            int unitNo = units->at(unitIdx);
            int unitLableOffset;
            if (unitIdx%2)
            {
                unitLableOffset = yOffset + m_pnt.storageRectHeigth + m_pnt.fontMargin;
            }
            else
            {
                unitLableOffset = yOffset - (m_pnt.fontHeigth + m_pnt.fontMargin);
            }

            double unitRectWidth = m_unitCapacitiesSpins.at(unitNo)->value()*
                                   allowedUnitWidth/
                                   storageCapacity;

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

void MainWindow::loadPlugins()
{
    QDir          pluginsDir = QDir(qApp->applicationDirPath() + "/plugins");
    QPluginLoader loader;

    foreach(QString fileName, pluginsDir.entryList(QDir::Files))
    {
        loader.setFileName(pluginsDir.absoluteFilePath(fileName));
        m_dlgPlugins->addPlugin(fileName);

        IPlugin* plugin = dynamic_cast<IPlugin*>(loader.instance());
        foreach(const QString& key, plugin->keys())
        {
            Calculator* calc = plugin->create(key);
            if (calc)
            {
                m_algoritms.append(calc);
                m_dlgPlugins->addCalcAlg(key);
            }
            else
                m_dlgPlugins->addCalcAlg(key, true);
        }
    }

    m_dlgPlugins->expandAll();
}
