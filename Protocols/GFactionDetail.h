#ifndef GFACTIONDETAIL_H
#define GFACTIONDETAIL_H

#include "GNET/octetsstream.h"
#include "GFactionAliance.h"
#include "FMemberInfo.h"

class GMember
{
public:
    unsigned int rid;
    char role;

    void unmarshal(OctetsStream &os)
    {
        os >> rid;
        os >> role;
    }
};

typedef QVector<GMember> GMemberVector;

class GFactionInfo
{
public:
    unsigned int fid;
    Octets name;
    char level;
    GMember master;
    GMemberVector member;
    Octets announce;
    Octets sysinfo;

    void unmarshal(OctetsStream &os)
    {
        os >> fid;
        os >> name;
        master.unmarshal(os);
        int cnt = os.uncompact_uint32();
        if (cnt > 0)
        {
            for(int i = 0; i < cnt; i++)
            {
                GMember m;
                m.unmarshal(os);
                member.push_back(m);
            }
        }
        os >> announce;
        os >> sysinfo;
    }
};

class GFactionDetail
{
public:
    unsigned int fid;
    Octets name;
    char level;
    unsigned int master;
    Octets announce;
    Octets sysinfo;
    FMemberInfoVector member;
    int last_op_time;
    GFactionAllianceVector alliance;
    GFactionHostileVector hostile;
    GFactionRelationApplyVector apply;

    void marshal(OctetsStream &os)
    {
        os << (fid);
        os << (name);
        os << (level);
        os << (master);
        os << (announce);
        os << (sysinfo);
        if (member.size() > 0)
        {
            os << ((qint8)(member.size()));
            for(int i = 0; i < member.size(); i++)
            {
                member[i].marshal(os);
            }
        } else os << ((qint8)(0));
        os << (last_op_time);
        if (alliance.size() > 0)
        {
            os << ((qint8)(alliance.size()));
            for(int i = 0; i < alliance.size(); i++)
            {
                alliance[i].marshal(os);
            }
        } else os << ((qint8)(0));
        if (hostile.size() > 0)
        {
            os << ((qint8)(hostile.size()));
            for(int i = 0; i < hostile.size(); i++)
            {
                hostile[i].marshal(os);
            }
        } else os << ((qint8)(0));
        if (apply.size() > 0)
        {
            os << ((qint8)(apply.size()));
            for(int i = 0; i < apply.size(); i++)
            {
                apply[i].marshal(os);
            }
        } else os << ((qint8)(0));
    }

    void unmarshal(OctetsStream &os)
    {
        os.readInt32();
        os.readInt32();
        os >> (fid);
        os >> (name);
        os >> (level);
        os >> (master);
        os >> (announce);
        os >> (sysinfo);
        quint8 member_size;
        os >> (member_size);
        member.resize(member_size);
        for(int i = 0; i < member_size; i++)
        {
            member[i].unmarshal(os);
        }
        os >> (last_op_time);
        quint8 alliance_size;
        os >> (alliance_size);
        alliance.resize(alliance_size);
        for(int i = 0; i < alliance_size; i++)
        {
            alliance[i].unmarshal(os);
        }
        quint8 hostile_size;
        os >> (hostile_size);
        hostile.resize(hostile_size);
        for(int i = 0; i < hostile_size; i++)
        {
            hostile[i].unmarshal(os);
        }
        quint8 apply_size;
        os >> (apply_size);
        apply.resize(apply_size);
        for(int i = 0; i < apply_size; i++)
        {
            apply[i].unmarshal(os);
        }
    }

};

#endif // GFACTIONDETAIL_H
