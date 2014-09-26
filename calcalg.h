#ifndef CALCALG_H
#define CALCALG_H

#include <QString>
#include <QVector>

typedef QVector<int> Units;

class Bank
{
public:
    Bank();

    void         append(int unitNo, double unitSize);

    const Units* units ();

private:
    int   m_size;
    Units m_units;
};

// паттерн Strategy
typedef QVector<Bank> Solution;

class Calculator
{
public:
    Calculator               () {}
    virtual ~Calculator      () {}

    virtual QString  name    () = 0;
    virtual QString  brief   () = 0;
    virtual Calculator* clone() = 0;

    virtual Solution* calc (int arcCount, double arcCapacity, QList<qreal>& kpCapacities) = 0;

protected:
    Solution* m_sol;
};

#endif // CALCALG_H
