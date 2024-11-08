#ifndef INTOCTETS_H
#define INTOCTETS_H

#include <GNET/octetsstream.h>

class IntOctets
{
public:
    int m_int;
    Octets m_octets;

    void marshal(OctetsStream &os)
    {
        os << m_int;
        os << m_octets;
    }

    void unmarshal(OctetsStream &os)
    {
        os >> m_int;
        os >> m_octets;
    }
};

class GPair
{
public:
    int key;
    int value;

    void marshal(OctetsStream &os)
    {
        os << key;
        os << value;
    }

    void unmarshal(OctetsStream &os)
    {
        os >> key;
        os >> value;
    }
};

#endif // INTOCTETS_H
