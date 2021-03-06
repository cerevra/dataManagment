#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDoubleSpinBox>
#include <QGraphicsView>

#include "calcalg.h"
#include "plugins.h"
#include "about.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void onUnitCountSpinChanged(int count);
    void scrollDock            (int value);
    void resizeEvent           (QResizeEvent *);

    void calculate             ();
    void displayBrief          (int index);

private:
    void resizeScroll          ();
    void draw                  ();

    void loadPlugins           ();

    Ui::MainWindow *ui;

    int                    m_unitCount;
    QList<QDoubleSpinBox*> m_unitCapacitiesSpins;

    int                    m_scrollValue;

    QGraphicsScene *       m_scene;

    QVector<Calculator*>   m_algoritms;
    Solution*              m_sol;

    static const QString   m_storageName;

    Plugins*               m_dlgPlugins;
    About*                 m_dlgAbout;

    struct Paint
    {
        Paint()
            : penBlack (Qt::black )
            , penRed   (Qt::red   )
            , penYellow(Qt::yellow)
        {
            unitLabelHeigth = fontHeigth        + fontMargin*2;
            period          = storageRectHeigth + storageMargin + unitLabelHeigth;

            unitRectHeigth  = storageRectHeigth - unitRectYOffset*2
                                                - lineWidthThin;
        }

        QPen penBlack;
        QPen penRed;
        QPen penYellow;

        const int storageRectHeigth = 57;
        const int storageMargin     = 25;
        const int fontHeigth        = 8;
        const int fontMargin        = 10;
        const int lineWidthWide     = 2;
        const int lineWidthThin     = 1;
        const int unitRectYOffset   = 2;
        const int unitRectXOffset   = 2;
        int unitLabelHeigth;
        int period;
        int unitRectHeigth;
    };
    Paint m_pnt;
};

#endif // MAINWINDOW_H
