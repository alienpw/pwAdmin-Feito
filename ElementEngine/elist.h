#ifndef ELIST_H
#define ELIST_H

#include <QString>
#include <QVector>
#include <QByteArray>
#include <QTextStream>
#include <QTextCodec>
#include <QList>
#include <QFile>
#include <QCoreApplication>

class eList {
public:
    eList() {}

    QString listName; // from config file
    QByteArray listOffset; // length from config file, values from elements.data
    int listType;
    int elementSize;
    QVector<QString> elementFields; // length & values from config file
    QVector<QString> elementTypes; // length & values from config file
    QVector<QVector<QVariant>> elementValues; // list.length from elements.data, elements.length from config file

    QString GetValue(int ElementIndex, int FieldIndex) {
        if (FieldIndex > -1) {
            QVariant value = elementValues[ElementIndex][FieldIndex];
            QString type = elementTypes[FieldIndex];

            if (type == "int16") {
                return QString::number(value.toInt());
            }
            if (type == "int32") {
                return QString::number(value.toInt());
            }
            if (type == "int64") {
                return QString::number(value.toLongLong());
            }
            if (type == "float") {
                return QString::number(value.toFloat(), 'f', 6);
            }
            if (type == "double") {
                return QString::number(value.toDouble());
            }
            if (type.startsWith("byte:")) {
                return QString(value.toByteArray().toHex());
            }
            if (type.startsWith("wstring:")) {
                QTextCodec *codec = QTextCodec::codecForName("UTF-16");
                return codec->toUnicode(value.toByteArray()).split('\0').first();
            }
            if (type.startsWith("string:")) {
                QTextCodec *codec = QTextCodec::codecForName("GBK");
                return codec->toUnicode(value.toByteArray()).split('\0').first();
            }
        }
        return "";
    }

    QString GetType(int FieldIndex) {
        if (FieldIndex > -1 && FieldIndex < elementTypes.size()) {
            return elementTypes[FieldIndex];
        }
        return "";
    }
};
#endif
