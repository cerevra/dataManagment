#include "calcalg.h"

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

const Solution &CalcUniform::calc(int arcCount, double arcCapacity, QList<qreal> &kpCapacities)
{
    int i = 0 ;
    return Solution();
}
