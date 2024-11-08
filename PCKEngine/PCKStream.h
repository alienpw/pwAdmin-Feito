#ifndef PCKSTREAM_H
#define PCKSTREAM_H

#include <QFile>
#include <QDataStream>
#include <QBuffer>
#include <QDebug>
#include "PCKKey.h"

class PCKStream {
public:
    QFile pck;
    QFile pkx;
    QString path;
    qint64 position = 0;
    PCKKey key;  // Assuming you have the PCKKey class defined as provided earlier
    static const quint32 PCK_MAX_SIZE = 2147483392;
    static const int BUFFER_SIZE = 33554432;

public:
    PCKStream(QString& path, PCKKey key = PCKKey())
        : path(path), key(key) {
        pck.setFileName(path);
        if (!pck.open(QIODevice::ReadWrite)) {
            qWarning() << "Failed to open" << path;
        }

        QString pkxPath = path.endsWith(".cup") ? path : path.replace(".pck", ".pkx");
        if (QFile::exists(pkxPath)) {
            pkx.setFileName(pkxPath);
            if (!pkx.open(QIODevice::ReadWrite)) {
                qWarning() << "Failed to open" << pkxPath;
            }
        }
    }

    void seek(qint64 offset, int mode) {
        switch (mode) {
        case SEEK_SET:
            position = offset;
            break;
        case SEEK_CUR:
            position += offset;
            break;
        case SEEK_END:
            position = getLength() + offset;
            break;
        }

        if (position < pck.size())
            pck.seek(position);
        else if(pkx.isOpen())
            pkx.seek(position - pck.size());
    }

    qint64 getLength() const {
        return pkx.isOpen() ? pck.size() + pkx.size() : pck.size();
    }

    QByteArray readBytes(int count)
    {
        QByteArray array(count, '\0');  // Initialize a byte array with a specific size
        int bytesRead = 0;

        if (position < pck.size())
        {
            bytesRead = pck.read(array.data(), count);
            if (bytesRead < count && pkx.isOpen())
            {
                pkx.seek(0);
                bytesRead += pkx.read(array.data() + bytesRead, count - bytesRead);
            }
        }
        else if (position > pck.size() && pkx.isOpen())
        {
            bytesRead = pkx.read(array.data(), count);
        }
        position += count;
        return array;
    }


    void writeBytes(const QByteArray& data) {
        if (position + data.size() < PCK_MAX_SIZE) {
            pck.write(data);
        } else if (position + data.size() > PCK_MAX_SIZE) {
            if (!pkx.isOpen()) {
                pkx.setFileName(path.replace(".pck", ".pkx"));
                pkx.open(QIODevice::ReadWrite);
            }

            if (position > PCK_MAX_SIZE) {
                pkx.write(data);
            } else {
                int bytesToPck = PCK_MAX_SIZE - position;
                pck.write(data.data(), bytesToPck);
                pkx.write(data.data() + bytesToPck, data.size() - bytesToPck);
            }
        }

        position += data.size();
    }

    qint16 readInt16() {
        QByteArray data = readBytes(2);
        QDataStream stream(data);
        stream.setByteOrder(QDataStream::LittleEndian);  // Assuming little-endian, adjust as needed
        qint16 result;
        stream >> result;
        return result;
    }

    quint32 readUInt32() {
        QByteArray data = readBytes(4);
        QDataStream stream(data);
        stream.setByteOrder(QDataStream::LittleEndian);  // Assuming little-endian, adjust as needed
        quint32 result;
        stream >> result;
        return result;
    }

    qint32 readInt32() {
        QByteArray data = readBytes(4);
        QDataStream stream(data);
        stream.setByteOrder(QDataStream::LittleEndian);  // Assuming little-endian, adjust as needed
        qint32 result;
        stream >> result;
        return result;
    }

    qint64 readInt64() {
        QByteArray data = readBytes(8);
        QDataStream stream(data);
        stream.setByteOrder(QDataStream::LittleEndian);  // Assuming little-endian, adjust as needed
        qint64 result;
        stream >> result;
        return result;
    }

    void writeUInt32(quint32 value) {
        QByteArray data;
        QDataStream stream(&data, QIODevice::WriteOnly);
        stream.setByteOrder(QDataStream::LittleEndian);  // Assuming little-endian, adjust as needed
        stream << value;
        writeBytes(data);
    }

    void writeInt32(qint32 value) {
        QByteArray data;
        QDataStream stream(&data, QIODevice::WriteOnly);
        stream.setByteOrder(QDataStream::LittleEndian);  // Assuming little-endian, adjust as needed
        stream << value;
        writeBytes(data);
    }

    void writeInt16(qint16 value) {
        QByteArray data;
        QDataStream stream(&data, QIODevice::WriteOnly);
        stream.setByteOrder(QDataStream::LittleEndian);  // Assuming little-endian, adjust as needed
        stream << value;
        writeBytes(data);
    }

    ~PCKStream() {
        pck.close();
        if(pkx.isOpen()) pkx.close();
    }
};

#endif // PCKSTREAM_H
