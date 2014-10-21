#include "template.h"

TemplateCalc::TemplateCalc()
{
    m_sol = new Solution;
}

QString TemplateCalc::name()
{
    return QString("Name to display");
}

QString TemplateCalc::brief()
{
    return QString(
        "Some Description"
                );
}

Calculator *TemplateCalc::clone()
{
    return new TemplateCalc();
}

Solution* TemplateCalc::calc(int storageCount, double storageCapacity, QList<qreal> &unitCapacities)
{
    return m_sol;
}
