#ifndef DBAUTOLOCK_H
#define DBAUTOLOCK_H

#include <GNET/octetsstream.h>
#include <game_defs.h>
#include <Protocols/intoctets.h>

class DBAutoLockGet
{
public:
    int retcode;
    int userid;

    void marshal(OctetsStream &os)
    {
        os << retcode;
        os << userid;
    }
};

class DBAutoLockGetRes
{
public:
    QVector<GPair> autolock;

    void unmarshal(OctetsStream &os)
    {
        os.uncompact_uint32();
        os.readInt32();
        int size = os.readInt32();
        autolock.resize(size);
        for(int i = 0; i < size; i++)
        {
            autolock[i].unmarshal(os);
        }
    }
};

class DBAutoLockSet : public OctetsStream
{
public:
    int retcode;
    int userid;
    char count;
};

#endif // DBAUTOLOCK_H
