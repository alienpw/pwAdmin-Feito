#ifndef OPTION_H
#define OPTION_H
#include <QString>
#include <QByteArray>
#include <QTextCodec>

class option {
public:
    int param;
    QByteArray text;

    QString GetText() const {
        QTextCodec *codec = QTextCodec::codecForName("UTF-16LE");
        return codec->toUnicode(text);
    }

    void SetText(const QString &Value) {
        QTextCodec *codec = QTextCodec::codecForName("UTF-16LE");
        QByteArray source = codec->fromUnicode(Value);
        QByteArray target(128, 0);  // Initializes with zeros

        if (target.size() > source.size()) {
            target.replace(0, source.size(), source);
        } else {
            target = source.left(target.size());
        }

        text = target;
    }

    int id;
};

#endif // OPTION_H
