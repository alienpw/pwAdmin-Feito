#ifndef FMEMBERINFO_H
#define FMEMBERINFO_H

#include "GNET/octetsstream.h"
class FMemberInfo
{
public:
    unsigned int roleid;
    unsigned char level;
    unsigned char occupation;
    unsigned char froleid;
    short loginday;
    unsigned char online_status;
    Octets name;
    Octets nickname;
    int contrib;
    unsigned char delayexpel;
    int expeltime;
    int reputation;
    unsigned char reincarn_times;
    unsigned char gender;

    void marshal(OctetsStream &os)
    {
        os << (roleid);
        os << (level);
        os << (occupation);
        os << (froleid);
        os << (loginday);
        os << (online_status);
        os << (name);
        os << (nickname);
        os << (contrib);
        os << (delayexpel);
        os << (expeltime);
        os << (reputation);
        os << (reincarn_times);
        os << (gender);
    }

    void unmarshal(OctetsStream &os)
    {
        os >> (roleid);
        os >> (level);
        os >> (occupation);
        os >> (froleid);
        os >> (loginday);
        os >> (online_status);
        os >> (name);
        os >> (nickname);
        os >> (contrib);
        os >> (delayexpel);
        os >> (expeltime);
        os >> (reputation);
        os >> (reincarn_times);
        os >> (gender);
    }

};
typedef QVector<FMemberInfo>	FMemberInfoVector;


#endif // FMEMBERINFO_H
