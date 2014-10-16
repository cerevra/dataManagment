#ifndef CALCUNIFORM_H
#define CALCUNIFORM_H

#include <QMultiMap>

#include "calcalg.h"

class TemplateCalc : public Calculator
{
    typedef QMultiMap<double, int> Ordered;

public:
    TemplateCalc      ();
    ~TemplateCalc     () {}

    QString     name ();
    QString     brief();
    Calculator* clone();

    Solution*   calc (int arcCount,
                      double arcCapacity,
                      QList<qreal>& kpCapacities);

private:
};

#endif // CALCUNIFORM_H
