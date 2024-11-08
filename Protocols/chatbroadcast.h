#ifndef CHATBROADCAST_H
#define CHATBROADCAST_H

#include "GNET/octetsstream.h"

class ChatBroadcast : public OctetsStream
{
public:
    ChatBroadcast() : OctetsStream() {}

    virtual void Marshal() override;

    unsigned char channel;
    unsigned char emotion;
    int srcroleid;
    Octets msg;
    Octets data;

    bool SizePolicy(size_t size) const { return size <= 10240; }
};

#endif // CHATBROADCAST_H
