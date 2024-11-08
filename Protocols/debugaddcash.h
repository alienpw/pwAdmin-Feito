#ifndef DEBUGADDCASH_H
#define DEBUGADDCASH_H

#include "GNET/octetsstream.h"

class DebugAddCash
{
public:
    int userid;
    int cash;

    void marshal(OctetsStream &os)
    {
        os << userid;
        os << cash;
    }
};

#endif // DEBUGADDCASH_H
