#include "GNET/octetsstream.h"

void OctetsStream::init()
{
    qds = new QDataStream(&data, QIODevice::ReadWrite);
    qds->setByteOrder(QDataStream::LittleEndian);
    qds->setFloatingPointPrecision(QDataStream::SinglePrecision);
}

OctetsStream OctetsStream::DebugSendProtocol(uint opcode, bool returnValue, bool removeHeaders, int msecsWrite, int msecsRead)
{
    try
    {
        QByteArray out;
        out.append(scompact_uint32(501350));
        out.append(scompact_uint32(opcode));
        out.append(scompact_uint32(data.length()));
        out.append(data);
        if (socket->isOpen())
            socket->write(out);
        if (!returnValue) return nullptr;
        if (socket->waitForBytesWritten(msecsWrite))
        {
            if (socket->waitForReadyRead(msecsRead))
            {
                QByteArray arr = socket->readAll();
                while(socket->waitForReadyRead(10))
                    arr += socket->readAll();
                return OctetsStream(arr, removeHeaders);
            }
        }
    }
    catch(...)
    {
        return nullptr;
    }

    return nullptr;
}

void OctetsStream::SendNull(uint opcode)
{
    compact_uint32(501350);
    compact_uint32(opcode);
    compact_uint32(0);
    socket->write(data);
}

void OctetsStream::Send(uint opcode)
{
    QByteArray out;
    out.append(scompact_uint32(501350));
    out.append(scompact_uint32(opcode));
    out.append(scompact_uint32(data.length()));
    out.append(data);

    if (socket->isOpen())
        socket->write(out);
    if (socket->waitForBytesWritten())
        socket->readyRead();
}

OctetsStream OctetsStream::SendReturn(uint opcode, bool removeHeaders, int msecsWrite, int msecsRead)
{
    try
    {
        QByteArray out;
        out.append(scompact_uint32(501350));
        out.append(scompact_uint32(opcode));
        out.append(scompact_uint32(data.length()));
        out.append(data);
        if (socket->isOpen())
            socket->write(out);
        if (socket->waitForBytesWritten(msecsWrite))
        {
            if (socket->waitForReadyRead(msecsRead))
            {
                QByteArray arr = socket->readAll();
                while(socket->waitForReadyRead(10))
                    arr += socket->readAll();
                return OctetsStream(arr, removeHeaders);
            }
        }
    }
    catch(...)
    {
        return nullptr;
    }

    return nullptr;
}

void OctetsStream::Reset()
{
    data.clear();
    init();
}

uint OctetsStream::uncompact_uint32()
{
    char byte = readByte();
    switch (byte & 0xE0)
    {
    case 0x0E:
        return readInt32();
    case 0xC0:
        qds->device()->seek(qds->device()->pos() - 1);
        return readInt32() & 0x1FFFFFFF;
    case 0x80:
    case 0xA0:
        qds->device()->seek(qds->device()->pos() - 1);
        return readInt16() & 0x3FFF;
    default:
        return byte;
    }
}

float OctetsStream::readFloat()
{
    float value;
    this->operator >>(value);
    return value;
}

uint OctetsStream::readUInt32()
{
    uint value;
    this->operator >>(value);
    return value;
}

int OctetsStream::readInt32()
{
    int value;
    this->operator >>(value);
    return value;
}

short OctetsStream::readInt16()
{
    short value;
    this->operator >>(value);
    return value;
}

ushort OctetsStream::readUInt16()
{
    ushort value;
    this->operator >>(value);
    return value;
}

char OctetsStream::readByte()
{
    char value;
    this->operator >>(value);
    return value;
}

qint64 OctetsStream::readLong()
{
    qint64 value;
    this->operator >>(value);
    return value;
}

qint8 OctetsStream::readInt8()
{
    qint8 value;
    this->operator >>(value);
    return value;
}

quint8 OctetsStream::readUInt8()
{
    quint8 value;
    this->operator >>(value);
    return value;
}

quint8 OctetsStream::readUByte()
{
    quint8 value;
    this->operator >>(value);
    return value;
}

Octets OctetsStream::readOctet()
{
    Octets value;
    this->operator >>(value);
    return value;
}

void OctetsStream::compact_uint32(const uint &value)
{
    if (value < 0x80)
        writeByte(value);
    else if (value < 0x4000)
        writeInt16(value | 0x8000);
    else if (value < 0x20000000)
        writeInt32(value | 0xc0000000);
}

QByteArray OctetsStream::scompact_uint32(const uint &value)
{
    QByteArray out;
    QDataStream stream(&out, QIODevice::WriteOnly);
    if (value < 0x80)
        stream << (int8_t)value;
    else if (value < 0x4000)
        stream << (short)(value | 0x8000);
    else if (value < 0x20000000)
        stream << (int)(value | 0xc0000000);
    return out;
}

void OctetsStream::writeFloat(const float &value)
{
    this->operator <<(value);
}

void OctetsStream::writeUInt32(const uint &value)
{
    this->operator <<(value);
}

void OctetsStream::writeInt32(const int &value)
{
    this->operator <<(value);
}

void OctetsStream::writeLong(const qint64 &value)
{
    this->operator <<(value);
}

void OctetsStream::writeInt16(const short &value)
{
    this->operator <<(value);
}

void OctetsStream::writeUInt16(const ushort &value)
{
    this->operator <<(value);
}

void OctetsStream::writeByte(const char &value)
{
    this->operator <<(value);
}

void OctetsStream::writeInt8(const qint8 &value)
{
    this->operator<<(value);
}

void OctetsStream::writeUByte(const quint8 &value)
{
    this->operator <<(value);
}

void OctetsStream::writeOctet(const Octets &value)
{
    this->operator <<(value);
}

void OctetsStream::writeListInt(const QList<int> &value)
{
    compact_uint32(value.size());
    if (value.size() > 0)
    {
        foreach(int v, value)
        {
            this->operator<<(v);
        }
    }
}

void OctetsStream::writeShortOctets(const Octets &value)
{
    writeInt16(value.lenght);
    qds->writeRawData(value.value, value.value.length());
}

Octets OctetsStream::readShortOctets()
{
    uint lenght = readUInt16();
    char* value = new char[16];
    qds->readRawData(value, 16);
    return QByteArray(value, lenght);
}

OctetsStream &OctetsStream::operator >>(float &value)
{
    qds->operator >>(value);
    value = qbswap(value);
    return *this;
}

OctetsStream &OctetsStream::operator >>(uint &value)
{
    qds->operator >>(value);
    value = qbswap(value);
    return *this;
}

OctetsStream &OctetsStream::operator >>(int &value)
{
    qds->operator >>(value);
    value = qbswap(value);
    return *this;
}

OctetsStream &OctetsStream::operator >>(qint64 &value)
{
    qds->operator >>(value);
    value = qbswap(value);
    return *this;
}

OctetsStream &OctetsStream::operator >>(short &value)
{
    qds->operator >>(value);
    value = qbswap(value);
    return *this;
}

OctetsStream &OctetsStream::operator >>(ushort &value)
{
    qds->operator >>(value);
    value = qbswap(value);
    return *this;
}

OctetsStream &OctetsStream::operator >>(char &value)
{
    qds->readRawData(&value, 1);
    return *this;
}

OctetsStream &OctetsStream::operator >>(quint8 &value)
{
    qds->operator >>(value);
    return *this;
}

OctetsStream &OctetsStream::operator >>(qint8 &value)
{
    qds->operator >>(value);
    return *this;
}

OctetsStream &OctetsStream::operator>>(Octets &value)
{
    uint lenght = uncompact_uint32();
    value.lenght = lenght;
    char *data = new char[lenght];
    if (lenght > 1)
        qds->readRawData(data, lenght);
    value.value = QByteArray(data, lenght);
    return *this;
}

OctetsStream &OctetsStream::operator >>(QList<int> &value)
{
    uint size = uncompact_uint32();
    value.reserve(size);
    if (size > 0)
    {
        for(int i = 0; i < size; i++)
        {
            int value = readUInt32();
            qds->operator >>(value);
            value = qbswap(value);
        }
    }
    return *this;
}

OctetsStream &OctetsStream::operator <<(float value)
{
    qds->operator <<(qbswap(value));
    return *this;
}

OctetsStream &OctetsStream::operator <<(uint value)
{
    qds->operator <<(qbswap(value));
    return *this;
}

OctetsStream &OctetsStream::operator <<(int value)
{
    qds->operator <<(qbswap(value));
    return *this;
}

OctetsStream &OctetsStream::operator <<(short value)
{
    qds->operator <<(qbswap(value));
    return *this;
}

OctetsStream &OctetsStream::operator <<(ushort value)
{
    qds->operator <<(qbswap(value));
    return *this;
}

OctetsStream &OctetsStream::operator <<(qint64 value)
{
    qds->operator <<(qbswap(value));
    return *this;
}

OctetsStream &OctetsStream::operator <<(char value)
{
    qds->writeRawData(&value, 1);
    return *this;
}

OctetsStream &OctetsStream::operator <<(qint8 value)
{
    qds->operator <<(value);
    return *this;
}

OctetsStream &OctetsStream::operator <<(quint8 value)
{
    //qds->writeRawData(&value, 1);
    qds->operator <<(value);
    return *this;
}

OctetsStream &OctetsStream::operator <<(Octets value)
{
    compact_uint32(value.lenght);
    if (value.lenght > 1)
        qds->writeRawData(value.value, value.lenght);
    return *this;
}

OctetsStream &OctetsStream::operator <<(QList<int> value)
{
    compact_uint32(value.count());
    if (value.count() > 0)
    {
        foreach(int v, value)
        {
            qds->operator <<(qbswap(v));
        }
    }
    return *this;
}

QByteArray OctetsStream::readBytes(int len)
{
    char* value = new char[len];
    qds->readRawData(value, len);
    return QByteArray(value, len);
}

QList<int> OctetsStream::readListInt()
{
    QList<int> list;
    int size = uncompact_uint32();
    list.reserve(size);
    if (size > 0)
    {
        for(int i = 0; i < size; i++)
        {
            int value = readUInt32();
            list.push_back(value);
        }
    }
    return list;
}
