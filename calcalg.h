#ifndef CALCALG_H
#define CALCALG_H

#include <QString>

class CalcAlg
{
public:
    CalcAlg();
    virtual ~CalcAlg() {}

    virtual QString name () = 0;
    virtual QString brief() = 0;

    virtual void    calc () = 0;
};

class CalcUniform : public CalcAlg
{
public:
    CalcUniform();
    ~CalcUniform() {}

    QString name ();
    QString brief();

    void    calc ();
};

class Calculator
{
public:
    Calculator(CalcAlg* alg)
        : m_alg(alg)
    {}

    void calc()
    {
        m_alg->calc();
    }

private:
    CalcAlg* m_alg;
};

#endif // CALCALG_H
