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

    QString  name    ();
    QString  brief   ();
    Calculator* clone();

    Solution calc (int arcCount, double arcCapacity, QList<qreal>& kpCapacities);

private:
    bool routine  (Bank& bank);

    Solution m_sol;
    Ordered  m_orderedCapacities;
    double   m_arcCapacity;
};

#endif // CALCUNIFORM_H
