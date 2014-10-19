#include "plugins.h"
#include "ui_plugins.h"

Plugins::Plugins(QWidget *parent) :
    QDialog    (parent         ),
    ui         (new Ui::Plugins),
    m_lastItem (nullptr        )
{
    ui->setupUi(this);

    ui->treeView->setModel(&m_model);

    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

Plugins::~Plugins()
{
    delete ui;
}

void Plugins::addPlugin(const QString &name)
{
    QStandardItem *parentItem = m_model.invisibleRootItem();

    m_lastItem = new QStandardItem(name);

    QFont boldFont(m_lastItem->font());
    boldFont.setBold(true);
    m_lastItem->setFont(boldFont);

    parentItem->appendRow(m_lastItem);
}

void Plugins::addCalcAlg(const QString &name, bool disabled)
{
    QStandardItem *item = new QStandardItem(name);

    if (disabled)
    {
        item->setBackground(QColor(213, 114, 117));
    }

    m_lastItem->appendRow(item);
}

void Plugins::expandAll()
{
    ui->treeView->expandAll();
}
