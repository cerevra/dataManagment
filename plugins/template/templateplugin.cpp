
#include <QStringList>

#include "templateplugin.h"

QStringList TemplatePlugin::keys()
{
    QStringList list;
    list
        << "templateKey";

    return list;
}

Calculator *TemplatePlugin::create(const QString &key)
{
    if (key == "templateKey")
        return new TemplateCalc();

    return nullptr;
}
