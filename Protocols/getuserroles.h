#ifndef GETUSERROLES_H
#define GETUSERROLES_H

#include <GNET/octetsstream.h>
#include "intoctets.h"

class GetUserRolesArg
{
public:
    int retcode;
    int userid;

    void marshal(OctetsStream &os)
    {
        os << retcode;
        os << userid;
    }
};

class GetUserRolesRes
{
public:
    QVector<IntOctets> roles;

    void unmarshal(OctetsStream &os)
    {
        os.uncompact_uint32(); // retcode
        os.readInt32(); // gamedbd return
        auto size = os.readInt32();
        roles.resize(size);
        for(int i = 0; i < size; i++)
        {
            roles[i].unmarshal(os);
        }
    }
};

#endif // GETUSERROLES_H
