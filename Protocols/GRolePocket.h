#ifndef GROLEPOCKET_H
#define GROLEPOCKET_H

#include "GNET/octetsstream.h"
#include "GRoleInventory.h"

class GRolePocket
{
public:
    unsigned int capacity;
    unsigned int timestamp;
    unsigned int money;
    GRoleInventoryVector items;
    int reserved1;
    int reserved2;
    qint64 money2; // 173v344
    char u_shizhuang; // 173v344
    unsigned int rune1; // 173v344
    unsigned int rune2; // 173v344
    Octets rune_data; // 173v344
    char wuhun1; // 173v344
    Octets wuhun_data; // 173v344

public:
    GRolePocket(){}

    void marshal(OctetsStream &os, int Version = 155)
    {
        os << (capacity);
        os << (timestamp);
        os << (money);
        if (items.size() > 0)
        {
            os << ((qint8)(items.size()));
            for(int i = 0; i < items.size(); i++)
            {
                items[i].marshal(os);
            }
        } else os << ((qint8)(0));
        os << (reserved1);
        os << (reserved2);
        // v1.7.3
        if (Version == 344)
        {
            os<<(money2);
            os<<(u_shizhuang);
            os<<(rune1);
            os<<(rune2);
            os<<(rune_data);
            os<<(wuhun1);
            os<<(wuhun_data);
        }
    }

    void unmarshal(OctetsStream &os, int Version = 155)
    {
        os >> (capacity);
        os >> (timestamp);
        os >> (money);
        quint8 items_size;
        os >> (items_size);
        for(int i = 0; i < items_size; i++)
        {
            GRoleInventory e;
            e.unmarshal(os);
            items.push_back(e);
        }
        os >> (reserved1);
        os >> (reserved2);
        if (Version > 248)
        {
            os>>(money2);
            os>>(u_shizhuang);
            os>>(rune1);
            os>>(rune2);
            os>>(rune_data);
            os>>(wuhun1);
            os>>(wuhun_data);
        }
    }

};

#endif // GROLEPOCKET_H
