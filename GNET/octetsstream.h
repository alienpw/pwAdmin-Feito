#ifndef OCTETSSTREAM_H
#define OCTETSSTREAM_H

#include <QObject>
#include <QByteArray>
#include <QDataStream>
#include <QDebug>
#include <stdlib.h>
#include <QtEndian>
#include <QTcpSocket>
#include <QVector>
#include <QThread>
#include "octets.h"

class OctetsStream
{
public:
    OctetsStream() { init(); }
    OctetsStream(QTcpSocket *sock) { socket = sock; init(); }
    OctetsStream(QByteArray data, bool header = true, bool littleEndian = true) { setData(data, header, littleEndian); }
    void init();
    void setData(QByteArray data, bool header = true, bool littleEndian = true)
    {
        this->data = QByteArray(data);
        init();
        if (header)
        {
            this->opcode = uncompact_uint32();
            this->size = uncompact_uint32();
            this->data.resize(this->size + sizeof(int));
        }
        qds->setByteOrder(littleEndian ? QDataStream::LittleEndian : QDataStream::BigEndian);
    }
    QByteArray getData()
    {
        return this->data;
    }
    uint calcSession();
    void Send(uint opcode);
    void SendNull(uint opcode);
    OctetsStream SendReturn(uint opcode, bool removeHeaders = false, int msecsWrite = 30000, int msecsRead = 30000);
    OctetsStream DebugSendProtocol(uint opcode, bool returnValue = true, bool removeHeaders = true, int msecsWrite = 30000, int msecsRead = 30000);
    void Reset();
    virtual void Unmarshal() {}
    virtual void Marshal() {}

    //Read&Write
    uint uncompact_uint32();
    float readFloat();
    uint readUInt32();
    int readInt32();
    short readInt16();
    ushort readUInt16();
    char readByte();
    qint8 readInt8();
    quint8 readUInt8();
    qint64 readLong();
    quint8 readUByte();
    Octets readOctet();
    QByteArray readBytes(int len);
    QList<int> readListInt();
    void compact_uint32(const uint &value);
    static QByteArray scompact_uint32(const uint &value);
    void writeFloat(const float &value);
    void writeUInt32(const uint &value);
    void writeInt32(const int &value);
    void writeLong(const qint64 &value);
    void writeInt16(const short &value);
    void writeUInt16(const ushort &value);
    void writeInt8(const qint8 &value);
    void writeByte(const char &value);
    void writeUByte(const quint8 &value);
    void writeOctet(const Octets &value);
    void writeListInt(const QList<int> &value);

    //Operator overload
    OctetsStream &operator >>(float &value);
    OctetsStream &operator >>(uint &value);
    OctetsStream &operator >>(int &value);
    OctetsStream &operator >>(short &value);
    OctetsStream &operator >>(ushort &value);
    OctetsStream &operator >>(char &value);
    OctetsStream &operator >>(qint64 &value);
    OctetsStream &operator >>(qint8 &value);
    OctetsStream &operator >>(quint8 &value);
    OctetsStream &operator >>(Octets &value);
    OctetsStream &operator >>(QList<int> &value);

    OctetsStream &operator <<(float value);
    OctetsStream &operator <<(uint value);
    OctetsStream &operator <<(qint64 value);
    OctetsStream &operator <<(int value);
    OctetsStream &operator <<(short value);
    OctetsStream &operator <<(ushort value);
    OctetsStream &operator <<(char value);
    OctetsStream &operator <<(qint8 value);
    OctetsStream &operator <<(quint8 value);
    OctetsStream &operator <<(Octets value);
    OctetsStream &operator <<(QList<int> value);

    QTcpSocket *socket;
    uint session;

    QByteArray data;
    uint opcode;
    uint size;
    QDataStream *qds;
    void writeShortOctets(const Octets &value);
    Octets readShortOctets();
};

#endif // OCTETSSTREAM_H
