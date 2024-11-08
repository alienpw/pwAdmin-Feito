#ifndef GMPLAYERINFO_H
#define GMPLAYERINFO_H

#include <GNET/octetsstream.h>

class GMPlayerInfo
{
public:
    int userid;
    int roleid;
    int linkid;
    int localsid;
    int gsid;
    char status;
    Octets name;

    void marshal(OctetsStream &os)
    {
        os<<(userid);
        os<<(roleid);
        os<<(linkid);
        os<<(localsid);
        os<<(gsid);
        os<<(status);
        os<<(name);
    }

    void unmarshal(OctetsStream &os)
    {
        os>>(userid);
        os>>(roleid);
        os>>(linkid);
        os>>(localsid);
        os>>(gsid);
        os>>(status);
        os>>(name);
    }
};

#endif // GMPLAYERINFO_H
