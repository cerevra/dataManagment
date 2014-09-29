#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDoubleSpinBox>
#include <QGraphicsView>

#include "calcuniform.h"

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
    void draw                ();

    Ui::MainWindow *ui;

    int                    m_kpCount;
    QList<QDoubleSpinBox*> m_kpCapacitiesSpins;

    int                    m_scrollValue;

    QGraphicsScene *       m_scene;

    QVector<Calculator*>   m_algoritms;
    Solution*              m_sol;

    static const QString   m_bankName;
};

#endif // MAINWINDOW_H
