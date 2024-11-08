#ifndef GROLEDETAIL_H
#define GROLEDETAIL_H

#include "GNET/octetsstream.h"
#include "GRoleStatus.h"
#include "GRolePocket.h"
#include "GRoleInventory.h"
#include "GRoleStorehouse.h"
#include "GRoleTask.h"
#include "GShopLog.h"
#include "GUserStorehouse.h"
#include "GFactionAliance.h"

#include <QException>

class GRoleDetail
{
public:
    char version;
    unsigned int id;
    unsigned int userid;
    GRoleStatus status;
    Octets name;
    int race;
    int cls;
    unsigned int spouse;
    unsigned char gender;
    int create_time;
    int lastlogin_time;
    int cash_add;
    int cash_total;
    int cash_used;
    int cash_serial;
    unsigned int factionid;
    int factionrole;
    Octets custom_data;
    unsigned int custom_stamp;
    GRolePocket inventory;
    GRoleInventoryVector equipment;
    GRoleStorehouse storehouse;
    GRoleTask task;
    Octets addiction;
    GShopLogVector logs;
    int bonus_add;
    int bonus_reward;
    int bonus_used;
    int referrer;
    GUserStorehouse userstorehouse;
    Octets taskcounter;
    GFactionAllianceVector factionalliance;
    GFactionHostileVector factionhostile;
    int mall_consumption;
    int src_zoneid;
    // 1.5.3+
    int64_t unifid;
    int vip_level;
    int score_add;
    int score_cost;
    int score_consume;
    int day_clear_stamp;
    int week_clear_stamp;
    int month_clear_stamp;
    int year_clear_stamp;
    Octets purchase_limit_data;
    int home_level;

    void marshal(OctetsStream &os, int Version = 155)
    {
        os << ((char)(1));
        os << (id);
        os << (userid);
        status.marshal(os, Version);
        os << (name);
        os << (race);
        os << (cls);
        os << (spouse);
        os << (gender);
        os << (create_time);
        os << (lastlogin_time);
        os << (cash_add);
        os << (cash_total);
        os << (cash_used);
        os << (cash_serial);
        os << (factionid);
        os << (factionrole);
        os << (custom_data);
        os << (custom_stamp);
        inventory.marshal(os);
        if (equipment.size() > 0)
        {
            os << ((qint8)(equipment.size()));
            for(int i = 0; i < equipment.size(); i++)
            {
                equipment[i].marshal(os);
            }
        } else os << ((qint8)(0));
        storehouse.marshal(os, Version);
        task.marshal(os, Version);
        os << (addiction);
        if (logs.size() > 0)
        {
            os << ((qint8)(logs.size()));
            for(int i = 0; i < logs.size(); i++)
            {
                logs[i].marshal(os);
            }
        } else os << ((qint8)(0));
        os << (bonus_add);
        os << (bonus_reward);
        os << (bonus_used);
        os << (referrer);
        userstorehouse.marshal(os);
        os << (taskcounter);
        if (factionalliance.size() > 0)
        {
            os << ((qint8)(factionalliance.size()));
            for(int i = 0; i < factionalliance.size(); i++)
            {
                factionalliance[i].marshal(os);
            }
        } else os << ((qint8)(0));
        if (factionhostile.size() > 0)
        {
            os << ((qint8)(factionhostile.size()));
            for(int i = 0; i < factionhostile.size(); i++)
            {
                factionhostile[i].marshal(os);
            }
        } else os << ((qint8)(0));
        os << (mall_consumption);
        os << (src_zoneid);
        // 1.5.3
        /*if (Version >= 145)
        {
            os << (unifid);
            os << (vip_level);
            os << (score_add);
            os << (score_cost);
            os << (score_consume);
            os << (day_clear_stamp);
            os << (week_clear_stamp);
            os << (month_clear_stamp);
            os << (year_clear_stamp);
            os << (purchase_limit_data);
            os << (home_level);
        }*/
    }

    void unmarshal(OctetsStream &os, int Version = 155)
    {
        try{
            os.readInt32(); // retcode
            os.readInt32(); // unknown
            os.readInt32(); // data_mask
            os.readInt8(); // gameserver_id
            os >> (version);
            os >> (id);
            os >> (userid);
            status.unmarshal(os, Version);
            os >> (name);
            os >> (race);
            os >> (cls);
            os >> (spouse);
            os >> (gender);
            os >> (create_time);
            os >> (lastlogin_time);
            os >> (cash_add);
            os >> (cash_total);
            os >> (cash_used);
            os >> (cash_serial);
            os >> (factionid);
            os >> (factionrole);
            /*os >> (custom_data);
            os >> (custom_stamp);
            inventory.unmarshal(os, Version);
            quint8 equipment_size;
            os >> (equipment_size);
            equipment.resize(equipment_size);
            for(int i = 0; i < equipment_size; i++)
            {
                equipment[i].unmarshal(os);
            }
            storehouse.unmarshal(os);
            task.unmarshal(os);
            os >> (addiction);
            quint8 logs_size;
            os >> (logs_size);
            logs.resize(logs_size);
            for(int i = 0; i < logs_size; i++)
            {
                logs[i].unmarshal(os);
            }
            os >> (bonus_add);
            os >> (bonus_reward);
            os >> (bonus_used);
            os >> (referrer);
            userstorehouse.unmarshal(os);
            os >> (taskcounter);
            quint8 factionalliance_size;
            os >> (factionalliance_size);
            factionalliance.resize(factionalliance_size);
            for(int i = 0; i < factionalliance_size; i++)
            {
                equipment[i].unmarshal(os);
            }
            quint8 factionhostile_size;
            os >> (factionhostile_size);
            factionhostile.resize(factionhostile_size);
            for(int i = 0; i < factionhostile_size; i++)
            {
                factionhostile[i].unmarshal(os);
            }
            os >> (mall_consumption);
            os >> (src_zoneid);
            // 1.5.3
            if (Version >= 145)
            {
                os >> (unifid);
                os >> (vip_level);
                os >> (score_add);
                os >> (score_cost);
                os >> (score_consume);
                os >> (day_clear_stamp);
                os >> (week_clear_stamp);
                os >> (month_clear_stamp);
                os >> (year_clear_stamp);
                os >> (purchase_limit_data);
                os >> (home_level);
            }*/
        }
        catch(QException e)
        {
            qDebug() << e.what();
        }
    }

};

#endif // GROLEDETAIL_H
