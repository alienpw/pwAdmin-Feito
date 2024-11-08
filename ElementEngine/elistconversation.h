#ifndef ELISTCONVERSATION_H
#define ELISTCONVERSATION_H

#include <QVector>
#include <QByteArray>
#include <QDataStream>
#include "talk_proc.h"

class eListConversation {
public:
    int talk_proc_count;
    QVector<talk_proc> talk_procs;

    eListConversation(QByteArray &Bytes) {
        QDataStream stream(Bytes);
        stream.setByteOrder(QDataStream::LittleEndian); // Assuming little-endian for BinaryReader compatibility

        stream >> talk_proc_count;
        talk_procs.resize(talk_proc_count);
        for (int d = 0; d < talk_proc_count; ++d) {
            stream >> talk_procs[d].id_talk;
            talk_procs[d].text = stream.device()->read(128);
            stream >> talk_procs[d].num_window;

            talk_procs[d].windows.resize(talk_procs[d].num_window);
            for (int q = 0; q < talk_procs[d].num_window; ++q) {
                stream >> talk_procs[d].windows[q].id;
                stream >> talk_procs[d].windows[q].id_parent;
                stream >> talk_procs[d].windows[q].talk_text_len;

                talk_procs[d].windows[q].talk_text = stream.device()->read(2 * talk_procs[d].windows[q].talk_text_len);
                stream >> talk_procs[d].windows[q].num_option;

                talk_procs[d].windows[q].options.resize(talk_procs[d].windows[q].num_option);
                for (int c = 0; c < talk_procs[d].windows[q].num_option; ++c) {
                    stream >> talk_procs[d].windows[q].options[c].param;
                    talk_procs[d].windows[q].options[c].text = stream.device()->read(128);
                    stream >> talk_procs[d].windows[q].options[c].id;
                }
            }
        }
    }

    QByteArray GetBytes() {
        QByteArray result;
        QDataStream stream(&result, QIODevice::ReadWrite);
        stream.setByteOrder(QDataStream::LittleEndian);

        stream << talk_proc_count;
        for (auto &proc : talk_procs) {
            stream << proc.id_talk;
            stream.writeRawData(proc.text.data(), 128);
            stream << proc.num_window;

            for (auto &win : proc.windows) {
                stream << win.id << win.id_parent << win.talk_text_len;
                stream.writeRawData(win.talk_text.data(), win.talk_text.size());
                stream << win.num_option;

                for (const auto &opt : win.options) {
                    stream << opt.param;
                    stream.writeRawData(opt.text.data(), 128);
                    stream << opt.id;
                }
            }
        }

        return result;
    }
};


#endif
