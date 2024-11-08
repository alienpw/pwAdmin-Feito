#ifndef GROLEDATA_H
#define GROLEDATA_H

#include "GNET/octetsstream.h"
#include "GRoleBase.h"
#include "GRoleStatus.h"
#include "GRolePocket.h"
#include "GRoleEquipment.h"
#include "GRoleStorehouse.h"
#include "GRoleTask.h"

class GRoleData
{
public:
    GRoleData(){}

    int Version = 156;
    GRoleBase base;
    GRoleStatus status;
    GRolePocket pocket;
    GRoleEquipment equipment;
    GRoleStorehouse storehouse;
    GRoleTask task;

    void marshal(OctetsStream &os)
    {
        this->base.marshal(os, Version);
        this->status.marshal(os, Version);
        this->pocket.marshal(os, Version);
        this->equipment.marshal(os);
        this->storehouse.marshal(os, Version);
        this->task.marshal(os, Version);
    }

    void unmarshal(OctetsStream &os)
    {
        os.readInt32();
        os.readInt32();
        this->base.unmarshal(os, Version);
        this->status.unmarshal(os, Version);
        this->pocket.unmarshal(os, Version);
        this->equipment.unmarshal(os);
        this->storehouse.unmarshal(os, Version);
        this->task.unmarshal(os, Version);
    }

};

class PutRoleData
{
public:
    int retcode;
    int roleid;
    char overwrite;
    GRoleData data;

    void marshal(OctetsStream &os)
    {
        os<<(retcode);
        os<<(roleid);
        os<<(overwrite);
        data.marshal(os);
    }
};

#endif // GROLEDATA_H
