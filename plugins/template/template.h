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

    Solution*   calc (int storageCount,
                      double storageCapacity,
                      QList<qreal>& unitCapacities);

private:
};

#endif // CALCUNIFORM_H
