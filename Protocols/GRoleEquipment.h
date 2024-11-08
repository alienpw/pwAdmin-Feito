#ifndef GROLEEQUIPMENT_H
#define GROLEEQUIPMENT_H

#include "GNET/octetsstream.h"
#include "GRoleInventory.h"

class GRoleEquipment
    {
    public:
        GRoleInventoryVector inv;

    public:
        GRoleEquipment(){}

        void marshal(OctetsStream &os)
        {
            if (inv.size() > 0)
            {
                os << ((qint8)(inv.size()));
                for(int i = 0; i < inv.size(); i++)
                {
                    inv[i].marshal(os);
                }
            } else os << ((qint8)(0));
        }

        void unmarshal(OctetsStream &os)
        {
            quint8 inv_size;
            os >> (inv_size);
            for(int i = 0; i < inv_size; i++)
            {
                GRoleInventory e;
                e.unmarshal(os);
                inv.push_back(e);
            }
        }
    };

#endif // GROLEEQUIPMENT_H
