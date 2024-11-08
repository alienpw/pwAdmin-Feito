#ifndef PCKZLIB_H
#define PCKZLIB_H
#include <QByteArray>
#include <zlib.h>
#include "vector"
#include "QDebug"

class PCKZlib {
public:
    static QByteArray zlibDecompress(const QByteArray &data, int sizeDecompressed)
    {
        if (data.isEmpty())
            return QByteArray();

        z_stream strm;
        strm.zalloc = Z_NULL;
        strm.zfree = Z_NULL;
        strm.opaque = Z_NULL;
        strm.avail_in = static_cast<uInt>(data.size());
        strm.next_in = reinterpret_cast<Bytef*>(const_cast<char*>(data.data()));

        // Inicializa a descompressão
        if (inflateInit(&strm) != Z_OK)
            return QByteArray();

        QByteArray decompressed;
        char outbuffer[32768];
        int ret;
        do {
            strm.avail_out = sizeof(outbuffer);
            strm.next_out = reinterpret_cast<Bytef*>(outbuffer);

            ret = inflate(&strm, Z_NO_FLUSH);

            if (decompressed.size() < sizeDecompressed) {
                int oldSize = decompressed.size();
                decompressed.resize(oldSize + static_cast<int>(strm.total_out));
                memcpy(decompressed.data() + oldSize, outbuffer, static_cast<int>(strm.total_out) - oldSize);
            }

        } while (ret == Z_OK);

        inflateEnd(&strm);

        if (decompressed.size() != sizeDecompressed) {
            // Descompressão falhou ou os dados estavam corrompidos
            return QByteArray();
        }

        return decompressed;
    }


    static QByteArray Decompress(const QByteArray& bytes, int size) {
        QByteArray uncompressedData(size, 0);  // Initializes with zeros
        ulong destLen = size;

        int result = uncompress(reinterpret_cast<Bytef*>(uncompressedData.data()), &destLen,
                                reinterpret_cast<const Bytef*>(bytes.data()), bytes.size());

        if (result != Z_OK) {
            return QByteArray();
        }

        return uncompressedData;
    }

    static QByteArray Compress(const QByteArray& bytes, int compressionLevel) {
        ulong destLen = compressBound(bytes.size());
        QByteArray compressedData(destLen, 0);

        int result = compress2(reinterpret_cast<Bytef*>(compressedData.data()), &destLen,
                               reinterpret_cast<const Bytef*>(bytes.data()), bytes.size(), compressionLevel);

        if (result != Z_OK) {
            // Handle compression error
            return bytes;  // Return original bytes as per your logic
        }

        compressedData.resize(destLen);  // Adjust the QByteArray size after compression
        return (compressedData.size() < bytes.size()) ? compressedData : bytes;
    }
};



#endif // PCKZLIB_H
