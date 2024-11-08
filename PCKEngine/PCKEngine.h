#ifndef PCKENGINE_H
#define PCKENGINE_H

#include "PCKStream.h"
#include "PCKFileEntry.h"

class PCKEngine
{
public:
    short version;

    PCKEngine(){}

    int GetFilesCount(PCKStream &stream)
    {
        stream.seek(-8L, SEEK_END);
        return stream.readInt32();
    }

    QList<PCKFileEntry> ReadFileAll(PCKStream& stream)
    {
        int offset1 = -272;
        int offset2 = 280;
        if (this->version == 3)
        {
            offset1 = -280;
            offset2 = 288;
        }
        stream.seek(-8L, SEEK_END);
        qint32 FilesCount = stream.readInt32();
        stream.seek(offset1, SEEK_END);
        long FileTableOffset = 0;
        if (version == 3)
            FileTableOffset = stream.readInt64() ^ stream.key.KEY_1;
        else
            FileTableOffset = (long)((uint)((ulong)stream.readUInt32() ^ (ulong)stream.key.KEY_1));
        stream.seek(FileTableOffset, SEEK_SET);
        QList<PCKFileEntry> fileEntries;
        for (int i = 0; i < FilesCount; ++i)
        {
            int EntrySize = stream.readInt32() ^ stream.key.KEY_1;
            stream.readInt32();
            auto arr = stream.readBytes(EntrySize);
            fileEntries.append(PCKFileEntry(arr, version));
        }
        return fileEntries;
    }

    QList<PCKFileEntry> ReadFileEntrys(PCKStream &stream)
    {
        stream.seek(-4L, SEEK_END);
        this->version = stream.readInt16();
        auto files = ReadFileAll(stream);
        return files;
    }

    QByteArray ReadFile(PCKStream &stream, PCKFileEntry file)
    {
        stream.seek(file.Offset, SEEK_SET);
        QByteArray bytes = stream.readBytes(file.CompressedSize);
        return file.CompressedSize < file.Size ? PCKZlib::Decompress(bytes, file.Size) : bytes;
    }
};

#endif // ARCHIVEENGINE_H
