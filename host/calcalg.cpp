
#include "calcalg.h"

Storage::Storage()
    : m_size(0)
{
}

void Storage::append(int unitNo, double unitSize)
{
    m_units.append(unitNo);
    m_size += unitSize;
}

const Units *Storage::units() const
{
    return &m_units;
}

int Storage::size() const
{
    return m_size;
}
