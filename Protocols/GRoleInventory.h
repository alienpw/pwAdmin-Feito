#ifndef GROLEINVENTORY_H
#define GROLEINVENTORY_H

#include "GNET/octetsstream.h"

class GRoleInventory
{
public:
    int id = 0;
    int pos = -1;
    int count = 1;
    int max_count = 1;
    Octets data = Octets();
    int proctype = 0;
    int expire_date = 0;
    int guid1 = 0;
    int guid2 = 0;
    int mask = 0;

    void marshal(OctetsStream &os)
    {
        os << (id);
        os << (pos);
        os << (count);
        os << (max_count);
        os << (data);
        os << (proctype);
        os << (expire_date);
        os << (guid1);
        os << (guid2);
        os << (mask);
    }

    void unmarshal(OctetsStream &os)
    {
        os >> (id);
        os >> (pos);
        os >> (count);
        os >> (max_count);
        os >> (data);
        os >> (proctype);
        os >> (expire_date);
        os >> (guid1);
        os >> (guid2);
        os >> (mask);
    }

};
typedef QVector<GRoleInventory> GRoleInventoryVector;

#endif // GROLEINVENTORY_H
