#ifndef GSHOPLOG_H
#define GSHOPLOG_H

#include "GNET/octetsstream.h"

class GShopLog
{
public:
    int roleid;
    int order_id;
    int item_id;
    int expire;
    int item_count;
    int order_count;
    int cash_need;
    int time;
    int guid1;
    int guid2;

    void marshal(OctetsStream &os)
    {
        os << (roleid);
        os << (order_id);
        os << (item_id);
        os << (expire);
        os << (item_count);
        os << (order_count);
        os << (cash_need);
        os << (time);
        os << (guid1);
        os << (guid2);
    }

    void unmarshal(OctetsStream &os)
    {
        os >> (roleid);
        os >> (order_id);
        os >> (item_id);
        os >> (expire);
        os >> (item_count);
        os >> (order_count);
        os >> (cash_need);
        os >> (time);
        os >> (guid1);
        os >> (guid2);
    }
};
typedef QVector<GShopLog> GShopLogVector;

#endif // GSHOPLOG_H
