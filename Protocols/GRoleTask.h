#ifndef GROLETASK_H
#define GROLETASK_H

#include "GNET/octetsstream.h"
#include "GRoleInventory.h"

class GRoleTask
{
public:
    Octets task_data;
    Octets task_complete;
    Octets task_finishtime;
    GRoleInventoryVector task_inventory;
    Octets task_data2;
    Octets task_complete2;

public:
    GRoleTask(){}

    void marshal(OctetsStream &os, int Version)
    {
        os << (task_data);
        os << (task_complete);
        os << (task_finishtime);
        if (task_inventory.size() > 0)
        {
            os << ((qint8)(task_inventory.size()));
            for(int i = 0; i < task_inventory.size(); i++)
            {
                task_inventory[i].marshal(os);
            }
        } else os << ((qint8)(0));
        if (Version == 344)
        {
            os << task_data2;
            os << task_complete2;
        }
    }

    void unmarshal(OctetsStream &os, int Version)
    {
        os >> (task_data);
        os >> (task_complete);
        os >> (task_finishtime);
        quint8 task_inventory_size;
        os >> (task_inventory_size);
        task_inventory.resize(task_inventory_size);
        for(int i = 0; i < task_inventory_size; i++)
        {
            task_inventory[i].unmarshal(os);
        }
        if (Version == 344)
        {
            os >> task_data2;
            os >> task_complete2;
        }
    }

};

#endif // GROLETASK_H
