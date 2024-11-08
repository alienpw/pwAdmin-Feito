#ifndef GROLEFORBID_H
#define GROLEFORBID_H

#include "GNET/octetsstream.h"

class GRoleForbid
{
public:
    unsigned char type;
    uint time;
    uint createtime;
    Octets reason;

    void marshal(OctetsStream &os)
    {
        os << type;
        os << time;
        os << createtime;
        os << reason;
    }

    void unmarshal(OctetsStream &os)
    {
        os >> type;
        os >> time;
        os >> createtime;
        os >> reason;
    }
};
typedef QVector<GRoleForbid>	GRoleForbidVector;

#endif // GROLEFORBID_H
