#ifndef IPLUGIN_H
#define IPLUGIN_H

#include <QtPlugin>
#include "calcalg.h"

class IPlugin : public QObject
{
    Q_OBJECT

public:
    virtual QStringList keys  () = 0;

    virtual Calculator* create(const QString& key) = 0;
};

#define DataInterface_iid "org.cerevra.dataManagment.IPlugin"

Q_DECLARE_INTERFACE(IPlugin, DataInterface_iid)

#endif // IPLUGIN_H
