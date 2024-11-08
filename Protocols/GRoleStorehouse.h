#ifndef GROLESTOREHOUSE_H
#define GROLESTOREHOUSE_H

#include "GNET/octetsstream.h"
#include "GRoleInventory.h"

class GRoleStorehouse
{
public:
    unsigned int capacity; // items
    unsigned int money;
    GRoleInventoryVector items;
    unsigned char size1; // dress
    unsigned char size2; // material
    GRoleInventoryVector dress;
    GRoleInventoryVector material;
    unsigned char size3; // generalcard
    GRoleInventoryVector generalcard;
    short reserved;
    GRoleInventoryVector runeitem; // 173v344
    GRoleInventoryVector lottory; // 173v344
    GRoleInventoryVector flysword; // 173v344

public:
    GRoleStorehouse(){}

    void marshal(OctetsStream &os, int Version)
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
        os << (size1);
        os << (size2);
        if (dress.size() > 0)
        {
            os << ((qint8)(dress.size()));
            for(int i = 0; i < dress.size(); i++)
            {
                dress[i].marshal(os);
            }
        } else os << ((qint8)(0));
        if (material.size() > 0)
        {
            os << ((qint8)(material.size()));
            for(int i = 0; i < material.size(); i++)
            {
                material[i].marshal(os);
            }
        } else os << ((qint8)(0));
        os << (size3);
        if (generalcard.size() > 0)
        {
            os << ((qint8)(generalcard.size()));
            for(int i = 0; i < generalcard.size(); i++)
            {
                generalcard[i].marshal(os);
            }
        } else os << ((qint8)(0));
        os << (reserved);
        if (Version == 344)
        {
            if (runeitem.size() > 0)
            {
                os << ((qint8)(runeitem.size()));
                for(int i = 0; i < runeitem.size(); i++)
                {
                    runeitem[i].marshal(os);
                }
            } else os << ((qint8)(0));
            if (lottory.size() > 0)
            {
                os << ((qint8)(lottory.size()));
                for(int i = 0; i < lottory.size(); i++)
                {
                    lottory[i].marshal(os);
                }
            } else os << ((qint8)(0));
            if (flysword.size() > 0)
            {
                os << ((qint8)(flysword.size()));
                for(int i = 0; i < flysword.size(); i++)
                {
                    flysword[i].marshal(os);
                }
            } else os << ((qint8)(0));
        }
    }

    void unmarshal(OctetsStream &os, int Version)
    {
        os >> (capacity);
        os >> (money);
        quint8 items_size;
        os >> (items_size);
        if (items_size > 0)
        for(int i = 0; i < items_size; i++)
        {
            GRoleInventory item;
            item.unmarshal(os);
            items.push_back(item);
        }
        os >> (size1);
        os >> (size2);
        quint8 dress_size;
        os >> (dress_size);
        if (dress_size > 0)
        for(int i = 0; i < dress_size; i++)
        {
            GRoleInventory item;
            item.unmarshal(os);
            dress.push_back(item);
        }
        quint8 material_size;
        os >> (material_size);
        if (material_size > 0)
        for(int i = 0; i < material_size; i++)
        {
            GRoleInventory item;
            item.unmarshal(os);
            material.push_back(item);
        }
        os >> (size3);
        quint8 generalcard_size;
        os >> (generalcard_size);
        if (generalcard_size > 0)
        for(int i = 0; i < generalcard_size; i++)
        {
            GRoleInventory item;
            item.unmarshal(os);
            generalcard.push_back(item);
        }
        os >> (reserved);

        if (Version == 344)
        {
            quint8 runeitem_size;
            os >> (runeitem_size);
            if (runeitem_size > 0)
            for(int i = 0; i < runeitem_size; i++)
            {
                GRoleInventory _runeitem;
                _runeitem.unmarshal(os);
                runeitem.push_back(_runeitem);
            }

            quint8 lottory_size;
            os >> (lottory_size);
            if (lottory_size > 0)
            for(int i = 0; i < lottory_size; i++)
            {
                GRoleInventory _lottory;
                _lottory.unmarshal(os);
                lottory.push_back(_lottory);
            }

            quint8 flysword_size;
            os >> (flysword_size);
            if (flysword_size > 0)
            for(int i = 0; i < flysword_size; i++)
            {
                GRoleInventory _flysword;
                _flysword.unmarshal(os);
                flysword.push_back(_flysword);
            }
        }
    }

};

#endif // GROLESTOREHOUSE_H
