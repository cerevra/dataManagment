#include "calcuniform.h"

CalcUniform::CalcUniform()
    : m_arcCapacity(0)
{
    m_sol = new Solution;
}

QString CalcUniform::name()
{
    return QString("Равномерное распределение");
}

QString CalcUniform::brief()
{
    return QString(
        "В этом методе на первом этапе происходит сортировка всех КП по объему данных (по возрастанию). "
        "Затем с конца списка по очереди в хранилища складываются блоки данных. "
        "Таким образом получается, что в общем и целом данные ложатся в хранилища \"ровным\" слоем."
                );
}

Calculator *CalcUniform::clone()
{
    return new CalcUniform();
}

Solution* CalcUniform::calc(int arcCount, double arcCapacity, QList<qreal> &kpCapacities)
{
    m_sol->resize(arcCount);
    m_arcCapacity = arcCapacity;

    //сортировка
    for (int i = 0; i < kpCapacities.size(); ++i)
    {
        m_orderedCapacities.insert(kpCapacities[i], i);
    }

    try
    {
        //обход в прямом и обратном направлении
        while (m_orderedCapacities.size())
        {
            bool result = false;
            for (int i = 0; i < arcCount; ++i)
            {
                if (routine((*m_sol)[i]))
                    result = true;
            }

            for (int i = arcCount-1; i >= 0; --i)
            {
                if (routine((*m_sol)[i]))
                    result = true;
            }

            if (!result)
                break;
        }
    }
    catch (int)
    {
    }

    // если не для всех узлов нашлось место
    if (m_orderedCapacities.size())
    {
        m_sol->append(Bank());
        for (int i = 0; i < m_orderedCapacities.size(); ++i)
        {
            double capacity = m_orderedCapacities.lastKey();
            m_sol->last().append(m_orderedCapacities.last(), capacity);
            m_orderedCapacities.remove(capacity);
        }
    }

    return m_sol;
}

bool CalcUniform::routine(Bank &bank)
{
    if (m_orderedCapacities.size())
    {
        if (bank.units()->size() < m_arcCapacity)
        {
            double capacity = m_orderedCapacities.lastKey();
            int    unitNo   = m_orderedCapacities.last   ();
            bank.append(unitNo, capacity);
            m_orderedCapacities.remove(capacity, unitNo);
            return true;
        }
        else
            return false;
    }
    else
        throw int(0);
}
