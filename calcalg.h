#ifndef CALCALG_H
#define CALCALG_H

#include <QString>
#include <QVector>

// паттерн Strategy
typedef QVector<int>  Bank;
typedef QVector<Bank> Solution;

class Calculator
{
public:
    Calculator           () {}
    virtual ~Calculator  () {}

    virtual QString name () = 0;
    virtual QString brief() = 0;

    virtual const Solution& calc (int arcCount, double arcCapacity, const QList<qreal>& kpCapacities) = 0;
};

class CalcUniform : public Calculator
{
public:
    CalcUniform  () {}
    ~CalcUniform () {}

    QString name ();
    QString brief();

    const Solution& calc (int arcCount, double arcCapacity, QList<qreal>& kpCapacities);
};

#endif // CALCALG_H
