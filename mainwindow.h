#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDoubleSpinBox>

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

private:
    void resizeScroll        ();

    Ui::MainWindow *ui;

    int                    m_arcCount;
    qreal                  m_arcCapacity;
    int                    m_kpCount;
    QList<qreal>           m_kpCapacities;
    QList<QDoubleSpinBox*> m_kpCapacitiesSpins;

    int                    m_scrollValue;
};

#endif // MAINWINDOW_H
