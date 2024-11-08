#ifndef GROLESTATUS_H
#define GROLESTATUS_H

#include "GNET/octetsstream.h"

class GRoleStatus
{
public:
    char version;
    int level;
    int level2;
    int exp;
    int sp;
    int pp;
    int hp;
    int mp;
    float posx;
    float posy;
    float posz;
    int worldtag;
    int invader_state;
    int invader_time;
    int pariah_time;
    int reputation;
    Octets custom_status;
    Octets filter_data;
    Octets charactermode;
    Octets instancekeylist;
    int dbltime_expire;
    int dbltime_mode;
    int dbltime_begin;
    int dbltime_used;
    int dbltime_max;
    int time_used;
    Octets dbltime_data;
    unsigned short storesize;
    Octets petcorral;
    Octets property;
    Octets var_data;
    Octets skills;
    Octets storehousepasswd;
    Octets waypointlist;
    Octets coolingtime;
    Octets npc_relation;
    Octets multi_exp_ctrl;
    Octets storage_task;
    Octets faction_contrib;
    Octets force_data;
    Octets online_award;
    Octets profit_time_data;
    Octets country_data;
    Octets king_data;
    Octets meridian_data;
    Octets extraprop;
    Octets title_data;
    Octets reincarnation_data;
    Octets realm_data;
    Octets person_data; // 173v344
    Octets kid_data; // 173v344
    Octets lottery_data; // 173v344
    char reserved1; // 173v344
    char reserved2;
    char reserved3;
    char reserved4; // 173v344
    char reserved5; // 173v344
    char reserved6; // 173v344
    char reserved7; // 173v344
    char reserved8; // 173v344
    char reserved9; // 173v344
    char reserved10; // 173v344
    Octets rank; // custom 152v140

public:
    GRoleStatus(){}

    void marshal(OctetsStream &os, int Version)
    {
        os << (version);
        os << (level);
        os << (level2);
        os << (exp);
        os << (sp);
        os << (pp);
        os << (hp);
        os << (mp);
        os << (posx);
        os << (posy);
        os << (posz);
        os << (worldtag);
        os << (invader_state);
        os << (invader_time);
        os << (pariah_time);
        os << (reputation);
        os << (custom_status);
        os << (filter_data);
        os << (charactermode);
        os << (instancekeylist);
        os << (dbltime_expire);
        os << (dbltime_mode);
        os << (dbltime_begin);
        os << (dbltime_used);
        os << (dbltime_max);
        os << (time_used);
        os << (dbltime_data);
        os << (storesize);
        os << (petcorral);
        os << (property);
        os << (var_data);
        os << (skills);
        os << (storehousepasswd);
        os << (waypointlist);
        os << (coolingtime);
        os << (npc_relation);
        os << (multi_exp_ctrl);
        os << (storage_task);
        os << (faction_contrib);
        os << (force_data);
        os << (online_award);
        os << (profit_time_data);
        os << (country_data);
        os << (king_data);
        os << (meridian_data);
        os << (extraprop);
        os << (title_data);
        os << (reincarnation_data);
        os << (realm_data);
        if (Version == 344)
        {
            os << person_data;
            os << kid_data;
            os << lottery_data;
            os << reserved1;
        }
        if (Version == 140)
            os << rank;
        else
            os << reserved2;
        os << (reserved3);
        if (Version == 344)
        {
            os << reserved4;
            os << reserved5;
            os << reserved6;
            os << reserved7;
            os << reserved8;
            os << reserved9;
            os << reserved10;
        }
    }

    void unmarshal(OctetsStream &os, int Version)
    {
        os >> (version);
        os >> (level);
        os >> (level2);
        os >> (exp);
        os >> (sp);
        os >> (pp);
        os >> (hp);
        os >> (mp);
        os >> (posx);
        os >> (posy);
        os >> (posz);
        os >> (worldtag);
        os >> (invader_state);
        os >> (invader_time);
        os >> (pariah_time);
        os >> (reputation);
        os >> (custom_status);
        os >> (filter_data);
        os >> (charactermode);
        os >> (instancekeylist);
        os >> (dbltime_expire);
        os >> (dbltime_mode);
        os >> (dbltime_begin);
        os >> (dbltime_used);
        os >> (dbltime_max);
        os >> (time_used);
        os >> (dbltime_data);
        os >> (storesize);
        os >> (petcorral);
        os >> (property);
        os >> (var_data);
        os >> (skills);
        os >> (storehousepasswd);
        os >> (waypointlist);
        os >> (coolingtime);
        os >> (npc_relation);
        os >> (multi_exp_ctrl);
        os >> (storage_task);
        os >> (faction_contrib);
        os >> (force_data);
        os >> (online_award);
        os >> (profit_time_data);
        os >> (country_data);
        os >> (king_data);
        os >> (meridian_data);
        os >> (extraprop);
        os >> (title_data);
        os >> (reincarnation_data);
        os >> (realm_data);
        if (Version == 344)
        {
            os >> person_data;
            os >> kid_data;
            os >> lottery_data;
            os >> reserved1;
        }
        if (Version == 140)
            os >> rank;
        else
            os >> reserved2;
        os >> (reserved3);
        if (Version == 344)
        {
            os >> reserved4;
            os >> reserved5;
            os >> reserved6;
            os >> reserved7;
            os >> reserved8;
            os >> reserved9;
            os >> reserved10;
        }
    }

};

#endif // GROLESTATUS_H
