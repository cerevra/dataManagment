
#include <QStringList>

#include "calcplugin.h"

QStringList calcPlugin::keys()
{
    QStringList list;
    list
        << "uniform";

    return list;
}

Calculator *calcPlugin::create(const QString &key)
{
    if (key == "uniform")
        return new CalcUniform();

    return nullptr;
}
