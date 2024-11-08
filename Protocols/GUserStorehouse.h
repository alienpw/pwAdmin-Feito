#ifndef GUSERSTOREHOUSE_H
#define GUSERSTOREHOUSE_H

#include "GNET/octetsstream.h"
#include "GRoleInventory.h"

class GUserStorehouse
    {
    public:
        int capacity;
        unsigned int money;
        GRoleInventoryVector items;
        int reserved1;
        int reserved2;
        int reserved3;
        int reserved4;

    public:
        void marshal(OctetsStream &os)
        {
            os << (capacity);
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
            os << (reserved3);
            os << (reserved4);
        }

        void unmarshal(OctetsStream &os)
        {
            os >> (capacity);
            os >> (money);
            quint8 items_size;
            os >> (items_size);
            items.resize(items_size);
            for(int i = 0; i < items_size; i++)
            {
                items[i].unmarshal(os);
            }
            os >> (reserved1);
            os >> (reserved2);
            os >> (reserved3);
            os >> (reserved4);
        }

    };

#endif // GUSERSTOREHOUSE_H
