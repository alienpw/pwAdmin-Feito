#include "elementseditor.h"

void ElementsEditor::Unmarshal()
{
    this->qds->setByteOrder(QDataStream::BigEndian);
    this->operator >> (version);
    this->operator >> (signature);

}
