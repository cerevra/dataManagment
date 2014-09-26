#ifndef CALCALG_H
#define CALCALG_H

#include <QString>

// паттерн Strategy

class Calculator
{
public:
    Calculator() {}
    virtual ~Calculator() {}

    virtual QString name () = 0;
    virtual QString brief() = 0;

    virtual void    calc () = 0;
};

class CalcUniform : public Calculator
{
public:
    CalcUniform  () {}
    ~CalcUniform () {}

    QString name ();
    QString brief();

    void    calc ();
};

#endif // CALCALG_H
