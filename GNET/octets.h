#ifndef OCTETS_H
#define OCTETS_H

#include <QObject>

struct Octets
{
    uint lenght;
    QByteArray value;

    Octets() {}
    Octets(QByteArray data) : value(data) { lenght = value.length(); }
    Octets(QString data)
    {
        QByteArray byteArray(reinterpret_cast<const char*>(data.utf16()), data.length() * sizeof(ushort));
        this->lenght = data.length() * 2;
        this->value = byteArray;
    }

    Octets(QString data, QString data2)
    {
        QString valor = data.leftJustified(8, '\x00');
        QByteArray byteArray(reinterpret_cast<const char*>(valor.utf16()), valor.length() * sizeof(ushort));
        this->lenght = data.length() * sizeof(ushort);
        this->value = byteArray;
    }

    QString toName()
    {
        return value.replace('\x00', "");
    }
};

#endif // OCTETS_H
