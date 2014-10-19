#include "calcuniform.h"

CalcUniform::CalcUniform()
    : m_storageCapacity(0)
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
        "Сначала в прямом, а потом в обратном направлении. "
        "Таким образом получается, что в общем и целом данные ложатся в хранилища \"ровным\" слоем."
                );
}

Calculator *CalcUniform::clone()
{
    return new CalcUniform();
}

Solution* CalcUniform::calc(int storageCount, double storageCapacity, QList<qreal> &unitCapacities)
{
    m_sol->resize(storageCount);
    m_storageCapacity = storageCapacity;

    //сортировка
    for (int i = 0; i < unitCapacities.size(); ++i)
    {
        m_orderedCapacities.insert(unitCapacities[i], i);
    }

    try
    {
        //обход в прямом и обратном направлении
        while (m_orderedCapacities.size())
        {
            bool result = false;
            for (int i = 0; i < storageCount; ++i)
            {
                if (routine((*m_sol)[i]))
                    result = true;
            }

            for (int i = storageCount-1; i >= 0; --i)
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
        Storage* storage = &m_sol->last();
        while(m_orderedCapacities.size())
        {
            double capacity = m_orderedCapacities.lastKey();
            if (storage->size() + capacity >= m_storageCapacity)
            {
                m_sol->append(Storage());
                storage = &m_sol->last();
            }

            int unitNo = m_orderedCapacities.last();
            storage->append(unitNo, capacity);
            m_orderedCapacities.remove(capacity, unitNo);
        }
    }

    return m_sol;
}

bool CalcUniform::routine(Storage &storage)
{
    if (m_orderedCapacities.size())
    {
        double capacity = m_orderedCapacities.lastKey();
        if (storage.size() + capacity < m_storageCapacity)
        {
            int unitNo = m_orderedCapacities.last();
            storage.append(unitNo, capacity);
            m_orderedCapacities.remove(capacity, unitNo);
            return true;
        }
        else
            return false;
    }
    else
        throw int(0);
}
