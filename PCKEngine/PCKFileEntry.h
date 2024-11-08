#ifndef PCKFILEENTRY_H
#define PCKFILEENTRY_H

#include <QByteArray>
#include <QDataStream>
#include <QString>
#include <QTextCodec>
#include "PCKZlib.h"
#include "QDebug"

class PCKFileEntry {
public:
    QString Path;
    qint64 Offset;
    qint32 Size;
    qint32 CompressedSize;

    PCKFileEntry() {}

    PCKFileEntry(QByteArray &bytes, qint16 version) {
        if (version == 3) {
            ReadV3(bytes);
        } else {
            ReadV2(bytes);
        }
    }

    void ReadV2(QByteArray &bytes) {
        if (bytes.size() < 276) {
            bytes = PCKZlib::Decompress(bytes, 276);
        }

        QDataStream reader(bytes);
        reader.setByteOrder(QDataStream::LittleEndian);
        QByteArray pathData;
        pathData.resize(260);
        reader.readRawData(pathData.data(), 260);
        Path = QTextCodec::codecForName("GB18030")->toUnicode(pathData).split(QChar('\0'))[0].replace("/", "\\");
        quint32 offsetUInt32;
        reader >> offsetUInt32;
        Offset = static_cast<qint64>(offsetUInt32);
        reader >> Size >> CompressedSize;
    }

    void ReadV3(QByteArray &bytes) {
        if (bytes.size() < 288) {
            bytes = PCKZlib::Decompress(bytes, 288);
        }

        QDataStream reader(bytes);
        reader.setByteOrder(QDataStream::LittleEndian);
        QByteArray pathData;
        pathData.resize(260);
        reader.readRawData(pathData.data(), 260);
        Path = QTextCodec::codecForName("GB18030")->toUnicode(pathData).split(QChar('\0'))[0].replace("/", "\\");
        qint32 skip;
        reader >> skip >> Offset >> Size >> CompressedSize;
    }

    QByteArray Write(int CompressionLevel) {
        QByteArray data;
        QDataStream writer(&data, QIODevice::WriteOnly);

        writer.writeRawData(QTextCodec::codecForName("GB18030")->fromUnicode(Path.replace("/", "\\")).data(), 260);
        writer.device()->seek(260);
        writer << static_cast<quint32>(Offset) << Size << CompressedSize << 0;

        QByteArray compressedData = PCKZlib::Compress(data, CompressionLevel);
        return compressedData.size() < 276 ? compressedData : data;
    }
};


#endif // PCKFILEENTRY_H
