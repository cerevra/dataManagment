#ifndef PLUGINS_H
#define PLUGINS_H

#include <QDialog>
#include <QStandardItemModel>

namespace Ui {
class Plugins;
}

class Plugins : public QDialog
{
    Q_OBJECT

public:
    explicit Plugins(QWidget *parent = 0);
    ~Plugins();

    void addPlugin  (const QString& name);
    void addCalcAlg (const QString& name, bool disabled = false);

    void expandAll  ();

private:
    Ui::Plugins *ui;

    QStandardItemModel m_model;
    QStandardItem*     m_lastItem;
};

#endif // PLUGINS_H
