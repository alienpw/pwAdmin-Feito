#ifndef WINDOW_H
#define WINDOW_H

#include <QString>
#include <QByteArray>
#include <QTextCodec>
#include <QVector>
#include "option.h"

class window {
public:
    int id;
    int id_parent;
    int talk_text_len;
    QByteArray talk_text;

    QString GetText() const {
        QTextCodec *codec = QTextCodec::codecForName("UTF-16LE");
        return codec->toUnicode(talk_text);
    }

    void SetText(const QString &Value) {
        QTextCodec *codec = QTextCodec::codecForName("UTF-16LE");
        QString newValue = Value + QChar(0);  // Append null terminator
        talk_text = codec->fromUnicode(newValue);
        talk_text_len = talk_text.length() / 2;
    }

    int num_option;
    QVector<option> options;  // Use QVector for dynamic arrays
};


#endif // WINDOW_H
