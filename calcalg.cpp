
#include "calcalg.h"

Bank::Bank()
    : m_size(0)
{
}

void Bank::append(int unitNo, double unitSize)
{
    m_units.append(unitNo);
    m_size += unitSize;
}

const Units *Bank::units() const
{
    return &m_units;
}

int Bank::size() const
{
    return m_size;
}
