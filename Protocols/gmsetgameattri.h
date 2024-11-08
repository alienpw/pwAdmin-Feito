#ifndef GMSETGAMEATTRI_H
#define GMSETGAMEATTRI_H

#include "GNET/octetsstream.h"
#include "QVector"

class GMSetGameAttributes
{
public:
    int retcode;
    int gmroleid;
    unsigned int localsid;
    quint8 attribute;
    quint8 count;
    quint8 value;

    void marshal(OctetsStream &os)
    {
        os << retcode;
        os << gmroleid;
        os << localsid;
        os << attribute;
        os << count;
        os << value;
    }
};

class GMGetGameAttributes
{
public:
    quint8 attribute;
    quint8 localsid;
    quint8 value;

    void unmarshal(OctetsStream &os)
    {
        attribute = os.readUInt8();
        localsid = os.readUInt8();
        value = os.readUInt8();
    }
};

class Attributes
{
public:
    QVector<GMGetGameAttributes> attributes;

    void unmarshal(OctetsStream &os)
    {
        auto size = os.uncompact_uint32();
        attributes.resize(size);
        for(uint i = 0; i < size; i++)
        {
            attributes[i].unmarshal(os);
        }
    }

};
#endif // GMSETGAMEATTRI_H
