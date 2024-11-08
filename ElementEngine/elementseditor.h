#ifndef ELEMENTSEDITOR_H
#define ELEMENTSEDITOR_H

#include <GNET/octetsstream.h>

class ElementsEditor : public OctetsStream
{
public:
    ElementsEditor() : OctetsStream(){}

    qint16 version;
    qint16 signature;

    virtual void Unmarshal() override;
};
#endif
