#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDoubleSpinBox>
#include <QGraphicsView>

#include "calcalg.h"

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
    void onKpCountSpinChanged(int count);
    void scrollDock          (int value);
    void resizeEvent         (QResizeEvent *);

    void calculate           ();
    void displayBrief        (int index);

private:
    void resizeScroll        ();

    Ui::MainWindow *ui;

    int                    m_arcCount;
    qreal                  m_arcCapacity;
    int                    m_kpCount;
    QList<qreal>           m_kpCapacities;
    QList<QDoubleSpinBox*> m_kpCapacitiesSpins;

    int                    m_scrollValue;

    QGraphicsScene *       m_scene;

    QVector<CalcAlg*>      m_algoritms;
};

#endif // MAINWINDOW_H
