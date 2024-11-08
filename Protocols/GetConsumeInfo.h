#ifndef GETCONSUMEINFO_H
#define GETCONSUMEINFO_H

#include "GNET/octetsstream.h"

class PlayerConsumeInfo
{
public:
    int roleid;
    int level;
    int login_ip;
    int cash_add;
    int mall_consumption;
    int avg_online_time;

    void marshal(OctetsStream &os)
    {
        os<<(roleid);
        os<<(level);
        os<<(login_ip);
        os<<(cash_add);
        os<<(mall_consumption);
        os<<(avg_online_time);
    }

    void unmarshal(OctetsStream &os)
    {
        os>>(roleid);
        os>>(level);
        os>>(login_ip);
        os>>(cash_add);
        os>>(mall_consumption);
        os>>(avg_online_time);
    }
};
typedef QList<PlayerConsumeInfo> PlayerConsumeInfoVector;

class DBGetConsumeInfoArg
{
public:
    int retcode;
    QList<int> ids;

    void marshal(OctetsStream &os)
    {
        os << retcode;
        os << ids;
    }

    void unmarshal(OctetsStream &os)
    {
        os >> retcode;
        os >> ids;
    }
};

class DBGetConsumeInfoRes
{
public:
    int gamedbd;
    int retcode;
    PlayerConsumeInfoVector infos;

    void unmarshal(OctetsStream &os)
    {        
        os >> gamedbd >> retcode;
        int size = os.uncompact_uint32();
        if (size > 0)
        {
            for (int i = 0; i < size; i++)
            {
                PlayerConsumeInfo info;
                info.unmarshal(os);
                infos.push_back(info);
            }
        }
    }
};

#endif // GETCONSUMEINFO_H
