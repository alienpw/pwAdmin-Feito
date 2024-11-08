#ifndef TALK_PROC_H
#define TALK_PROC_H
#include <QString>
#include <QByteArray>
#include <QTextCodec>
#include <QVector>
#include "window.h"

class talk_proc {
public:
    int id_talk;
    QByteArray text;

    QString GetText() const {
        QTextCodec *codec = QTextCodec::codecForName("UTF-16LE");
        return codec->toUnicode(text);
    }

    void SetText(const QString &Value) {
        QTextCodec *codec = QTextCodec::codecForName("UTF-16LE");
        QByteArray source = codec->fromUnicode(Value);
        QByteArray target(128, 0);  // Initialize with zeros

        int copyLength = qMin(target.size(), source.size());
        for (int i = 0; i < copyLength; ++i) {
            target[i] = source[i];
        }

        text = target;
    }

    int num_window;
    QVector<window> windows;  // Use QVector instead of raw arrays for ease of use
};

#endif // TALK_PROC_H
