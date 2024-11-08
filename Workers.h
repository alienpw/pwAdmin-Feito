#ifndef WORKERS_H
#define WORKERS_H

#include <QMutex>
#include <QThread>
#include <QDebug>
#include <QTcpSocket>
#include <QColor>
#include <QTextEdit>
#include <QTime>

#include <Protocols/GRoleDetail.h>
#include <Protocols/getuserroles.h>
#include <ElementEngine/elistcollection.h>
#include <Structs/item.h>
#include <PCKEngine/PCKEngine.h>
#include <Structs/skill.h>
#include <utils.h>
#include <server_defs.h>
#include <game_defs.h>
#include <Worker.h>

class wConnectToServer : public QThread {
    Q_OBJECT
public:
    wConnectToServer(QMutex *mutex, QTcpSocket *socket, Profile *profile, QTextEdit *txtLog) : mutex(mutex), socket(socket), profile(profile), txtLog(txtLog) {}

    void LogServer(QString msg, bool ret = false, bool time = true, QColor color = QColor("white"))
    {
        txtLog->insertHtml(QString("<font color=#505050>%1</font><font color=%2> %3</font> %4").arg(time ? QTime::currentTime().toString("[HH:mm:ss]") : "").arg(color.name(QColor::HexRgb)).arg(msg).arg(ret ? "<br>" : ""));
    }

    void run() override {
        mutex->lock();
        LogServer("Conectando ao servidor...");
        socket->connectToHost(profile->server_ip, profile->server_port);
        socket->waitForConnected(3000);
        mutex->unlock();
    }

private:
    QMutex *mutex;
    QTcpSocket *socket;
    Profile *profile;
    QTextEdit* txtLog;
};

class wReadDatas : public QThread {
    Q_OBJECT
public:
    void LogServer(QString msg, bool ret = false, bool time = true, QColor color = QColor("white"))
    {
        txtLog->insertHtml(QString("<font color=#505050>%1</font><font color=%2> %3</font> %4").arg(time ? QTime::currentTime().toString("[HH:mm:ss]") : "").arg(color.name(QColor::HexRgb)).arg(msg).arg(ret ? "<br>" : ""));
    }

    wReadDatas(QMutex *mutex, QTcpSocket *socket, Profile *profile, QTextEdit *txtLog, arquivos *pw) : mutex(mutex), socket(socket), profile(profile), txtLog(txtLog), pw(pw) {}

    void run() override {
        mutex->lock();
        LogServer("Carregando arquivos data...", true, true);
        if (!QFile::exists(profile->elements))
        {
            LogServer("Erro na leitura do elements.data", true, false, QColor::fromRgb(255, 0, 0));
            mutex->unlock();
            return;
        } else {
            LogServer("Carregando elements.data...");

            pw->elc = new eListCollection(profile->elements);
            if (pw->elc->loaded)
            {
                LogServer("SUCESSO!", false, false, QColor::fromRgb(0, 255, 0));
                LogServer(QString(" (v%1)").arg(pw->elc->Version), true, false, QColor("yellow"));
                pw->listClasses.clear();
                for(int i = 0; i < pw->elc->Lists.size(); i++)
                {
                    if (pw->elc->Lists[i].listName.contains("RACTER_CLASS_CONFIG"))
                    {
                        for(int b = 0; b < pw->elc->Lists[i].elementValues.size(); b++)
                        {
                            pw->listClasses[pw->elc->GetValue(i, b, 2).toInt()] = pw->elc->GetValue(i, b, 1);
                        }
                    }
                }
                for (int e = 0; e < pw->elc->Lists[0].elementValues.length(); e++)
                {
                    addon_data addon;
                    addon.id_addon = pw->elc->GetValue(0, e, 0).toInt();
                    addon.paramNum = pw->elc->GetValue(0, e, 2).toInt();
                    addon.arg[0] = pw->elc->GetValue(0, e, 3).toInt();
                    addon.arg[1] = pw->elc->GetValue(0, e, 4).toInt();
                    addon.arg[2] = pw->elc->GetValue(0, e, 5).toInt();
                    auto f = pw->addonsList.find(QString::number(addon.id_addon));
                    if (f != pw->addonsList.end())
                        addon.propNum = f.value().toInt();
                    pw->listAddonsData.push_back(addon);
                }
            }
        }
        mutex->unlock();
    }

private:
    QMutex *mutex;
    QTcpSocket *socket;
    Profile *profile;
    QTextEdit* txtLog;
    arquivos *pw;
};

#endif // WORKERS_H
