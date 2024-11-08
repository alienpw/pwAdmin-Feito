#ifndef GFACTIONALIANCE_H
#define GFACTIONALIANCE_H

#include "GNET/octetsstream.h"

class GFactionAlliance
{
public:
    int fid;
    int end_time;

    void marshal(OctetsStream &os)
    {
        os << (fid);
        os << (end_time);
    }

    void unmarshal(OctetsStream &os)
    {
        os >> (fid);
        os >> (end_time);
    }

};

class GFactionRelationApply
{
public:
    int type;
    int fid;
    int end_time;

    void marshal(OctetsStream &os)
    {
        os << (type);
        os << (fid);
        os << (end_time);
    }

    void unmarshal(OctetsStream &os)
    {
        os >> (type);
        os >> (fid);
        os >> (end_time);
    }

};
typedef QVector<GFactionAlliance>	GFactionAllianceVector;
typedef QVector<GFactionAlliance>	GFactionHostileVector;
typedef QVector<GFactionRelationApply>	GFactionRelationApplyVector;

#endif // GFACTIONALIANCE_H
