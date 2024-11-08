#ifndef GROLEBASE_H
#define GROLEBASE_H

#include "GNET/octetsstream.h"
#include "GRoleForbid.h"

class GRoleBase
{
public:
    qint8 version;
    unsigned int id;
    Octets name;
    int race;
    int cls;
    unsigned char gender;
    Octets custom_data;
    Octets config_data;
    unsigned int custom_stamp;
    unsigned char status;
    unsigned int delete_time;
    unsigned int create_time;
    unsigned int lastlogin_time;
    GRoleForbidVector forbid;
    Octets help_states;
    unsigned int spouse;
    unsigned int userid;
    Octets cross_data;
    unsigned char reserved2;
    Octets custom_data_highmode; // 1.6.5v248 and 173v344 - replace reserved2
    unsigned char reserved3;
    unsigned char reserved4;

public:
    GRoleBase(){}

    void marshal(OctetsStream &os, int Version)
    {
        os << (version);
        os << (id);
        os << (name);
        os << (race);
        os << (cls);
        os << (gender);
        os << (custom_data);
        os << (config_data);
        os << (custom_stamp);
        os << (status);
        os << (delete_time);
        os << (create_time);
        os << (lastlogin_time);
        if (forbid.size() > 0)
        {
            os << ((qint8)(forbid.size()));
            for(int i = 0; i < forbid.size(); i++)
            {
                forbid[i].marshal(os);
            }
        } else os << ((qint8)(0));
        os << (help_states);
        os << (spouse);
        os << (userid);
        os << (cross_data);
        if (Version >= 191)
            os << (custom_data_highmode);
        else
            os << (reserved2);
        os << (reserved3);
        os << (reserved4);
    }

    void unmarshal(OctetsStream os, int Version)
    {
        os >> (version);
        os >> (id);
        os >> (name);
        os >> (race);
        os >> (cls);
        os >> (gender);
        os >> (custom_data);
        os >> (config_data);
        os >> (custom_stamp);
        os >> (status);
        os >> (delete_time);
        os >> (create_time);
        os >> (lastlogin_time);
        quint8 forbid_size;
        os >> (forbid_size);
        if (forbid_size > 0)
        for(int i = 0; i < forbid_size; i++)
        {
            GRoleForbid f;
            f.unmarshal(os);
            forbid.push_back(f);
        }
        os >> (help_states);
        os >> (spouse);
        os >> (userid);
        os >> (cross_data);
        if (Version >= 191)
            os >> (custom_data_highmode);
        else
            os >> (reserved2);
        os >> (reserved3);
        os >> (reserved4);
    }

};

#endif // GROLEBASE_H
