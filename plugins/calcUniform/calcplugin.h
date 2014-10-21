#ifndef CALCPLUGIN_H
#define CALCPLUGIN_H

#include "iplugin.h"
#include "calcuniform.h"

class calcPlugin : public IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID DataInterface_iid FILE "keys.json")
public:
    QStringList keys();

    Calculator* create(const QString &key);
};

#endif // CALCPLUGIN_H
