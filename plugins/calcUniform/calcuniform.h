#ifndef CALCUNIFORM_H
#define CALCUNIFORM_H

#include <QMultiMap>

#include "calcalg.h"

class CalcUniform : public Calculator
{
    typedef QMultiMap<double, int> Ordered;

public:
    CalcUniform      ();
    ~CalcUniform     () {}

    QString     name ();
    QString     brief();
    Calculator* clone();

    Solution*   calc (int storageCount,
                      double storageCapacity,
                      QList<qreal>& unitCapacities);

private:
    bool routine(Storage& storage);

    Ordered  m_orderedCapacities;
    double   m_storageCapacity;
};

#endif // CALCUNIFORM_H
