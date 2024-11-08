#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QThread>
#include <Protocols/GRoleDetail.h>
#include <Protocols/getuserroles.h>
#include <ElementEngine/elistcollection.h>
#include <Structs/item.h>
#include <PCKEngine/PCKEngine.h>
#include <Structs/skill.h>
#include <utils.h>
#include <server_defs.h>
#include <QTcpSocket>

struct arquivos
{
    eListCollection *elc;

    QMap<int, QString> images_m;
    QMap<int, QString> images_f;
    QMap<int, QString> images_skill;
    QMap<int, QString> images_guild;

    QMap<QString, QPoint> imageposition_m;
    QMap<QString, QPoint> imageposition_f;
    QMap<QString, QPoint> imageposition_skill;
    QMap<QString, QPoint> imageposition_guild;

    QMap<QString, QImage> imagesCache_m;
    QMap<QString, QImage> imagesCache_f;
    QMap<QString, QImage> imagesCache_skill;
    QMap<QString, QImage> imagesCache_guild;

    QPixmap icon_profession;
    QPixmap iconlist_ivtrm;
    QPixmap iconlist_ivtrf;
    QPixmap iconlist_skill;
    QPixmap iconlist_guild;

    QMap<int, int> listItemColor;
    QMap<int, SkillInfo> listSkillInfo;
    QMap<int, QString> listSkillName;
    QMap<int, QString> listSkillDesc;
    QMap<int, QString> listItemDesc;
    QMap<int, QString> listItemExtDesc;
    QMap<int, QString> listFixedMsg;

    QMap<QString, QString> listAddons;
    QMap<int, QList<int>> listAddonsGroup;
    QList<addon_data> listAddonsData;
    QMap<QString, QString> addonsList;
    QMap<int, QString> listClasses;
};

#include <QMutex>

class Worker : public QObject {
    Q_OBJECT

private:
    Profile *profile;
    arquivos pw;

    QTcpSocket *socket;
    QString host;
    quint16 port;



public:
    Worker(){}
    Worker(Profile *profile) : profile(profile) {}
    Worker(Profile *profile, QTcpSocket *socket, QString host, int port) : profile(profile), socket(socket), host(host), port(port) {}

    void CheckConnection(QTcpSocket *socket, QString ip, int port)
    {
        socket->moveToThread(QThread::currentThread());
        socket->connectToHost(ip, port);
        if (socket->waitForConnected(3000))
        {
            emit connectedServer();
        }
    }

public slots:
    void doConnect() {
        emit logWork("Conectando ao servidor...");
        socket->moveToThread(QThread::currentThread());
        socket->connectToHost(host, port);
    }

    void WorkerReadDatas()
    {
        emit logWork("Carregando arquivos pck:", true);
        if (!QFile::exists(profile->surfaces))
        {
            emit logWork("Erro na leitura do surfaces.pck", true, false, QColor::fromRgb(255, 0, 0));
            return;
        }
        else
        {
            emit logWork("surfaces.pck...");
            PCKStream stream_surfaces(profile->surfaces);
            PCKEngine eng;
            auto list = eng.ReadFileEntrys(stream_surfaces);
            for(auto f : list)
            {
                if (f.Path == "surfaces\\ingame\\profession.tga")
                {
                    auto icon = eng.ReadFile(stream_surfaces, f);
                    pw.icon_profession.loadFromData(icon);
                }
                if (f.Path == "surfaces\\iconset\\iconlist_ivtrm.dds")
                {
                    auto icons_m = eng.ReadFile(stream_surfaces, f);
                    pw.iconlist_ivtrm.loadFromData(icons_m);
                }
                if (f.Path == "surfaces\\iconset\\iconlist_ivtrf.dds")
                {
                    auto icons_f = eng.ReadFile(stream_surfaces, f);
                    pw.iconlist_ivtrf.loadFromData(icons_f);
                }
                if (f.Path == "surfaces\\iconset\\iconlist_skill.dds")
                {
                    auto icons_skill = eng.ReadFile(stream_surfaces, f);
                    pw.iconlist_skill.loadFromData(icons_skill);
                }
                if (f.Path == "surfaces\\iconset\\iconlist_guild.dds")
                {
                    auto icons_guild = eng.ReadFile(stream_surfaces, f);
                    pw.iconlist_guild.loadFromData(icons_guild);
                }
                if(f.Path == "surfaces\\iconset\\iconlist_ivtrm.txt")
                {
                    auto icons_m_txt = eng.ReadFile(stream_surfaces, f);
                    QTextCodec* enc = QTextCodec::codecForName("GBK");
                    auto iconlist_ivtrm_txt = enc->toUnicode(icons_m_txt).split('\0')[0];
                    QTextStream filem(&iconlist_ivtrm_txt);
                    QString line;
                    QList<QString> fileNames;
                    pw.images_m.clear();
                    int w = 0;
                    int h = 0;
                    int rows = 0;
                    int cols = 0;
                    int counter = 0;
                    while ((line = filem.readLine()) != NULL)
                    {
                        switch (counter)
                        {
                        case 0:
                            w = line.toInt();
                            break;
                        case 1:
                            h = line.toInt();
                            break;
                        case 2:
                            rows = line.toInt();
                            break;
                        case 3:
                            cols = line.toInt();
                            break;
                        default:
                            fileNames.append(line);
                            break;
                        }
                        counter++;
                    }
                    pw.imageposition_m.clear();
                    int x, y = 0;
                    for (int a = 0; a < fileNames.count(); a++)
                    {
                        QApplication::processEvents(QEventLoop::AllEvents);
                        y = a / cols;
                        x = a - y * cols;
                        x = x * w;
                        y = y * h;
                        pw.images_m.insert(a, fileNames[a]);
                        pw.imageposition_m.insert(fileNames[a], QPoint(x, y));
                    }
                    filem.flush();
                }
                if(f.Path == "surfaces\\iconset\\iconlist_ivtrf.txt")
                {
                    auto icons_f_txt = eng.ReadFile(stream_surfaces, f);
                    QTextCodec* enc = QTextCodec::codecForName("GBK");
                    auto iconlist_ivtrf_txt = enc->toUnicode(icons_f_txt).split('\0')[0];
                    QTextStream filef(&iconlist_ivtrf_txt);
                    QString line;
                    QList<QString> fileNames;
                    pw.images_f.clear();
                    int w = 0;
                    int h = 0;
                    int rows = 0;
                    int cols = 0;
                    int counter = 0;
                    while ((line = filef.readLine()) != NULL)
                    {
                        switch (counter)
                        {
                        case 0:
                            w = line.toInt();
                            break;
                        case 1:
                            h = line.toInt();
                            break;
                        case 2:
                            rows = line.toInt();
                            break;
                        case 3:
                            cols = line.toInt();
                            break;
                        default:
                            fileNames.append(line);
                            break;
                        }
                        counter++;
                    }
                    pw.imageposition_f.clear();
                    int x, y = 0;
                    for (int a = 0; a < fileNames.count(); a++)
                    {
                        QApplication::processEvents(QEventLoop::AllEvents);
                        y = a / cols;
                        x = a - y * cols;
                        x = x * w;
                        y = y * h;
                        pw.images_f.insert(a, fileNames[a]);
                        pw.imageposition_f.insert(fileNames[a], QPoint(x, y));
                    }
                    filef.flush();
                }
                if(f.Path == "surfaces\\iconset\\iconlist_skill.txt")
                {
                    auto icons_skill_txt = eng.ReadFile(stream_surfaces, f);
                    QTextCodec* enc = QTextCodec::codecForName("GBK");
                    auto iconlist_skill_txt = enc->toUnicode(icons_skill_txt).split('\0')[0];
                    QTextStream fileskill(&iconlist_skill_txt);
                    QString line;
                    QList<QString> fileNames;
                    pw.images_skill.clear();
                    int w = 0;
                    int h = 0;
                    int rows = 0;
                    int cols = 0;
                    int counter = 0;
                    while ((line = fileskill.readLine()) != NULL)
                    {
                        switch (counter)
                        {
                        case 0:
                            w = line.toInt();
                            break;
                        case 1:
                            h = line.toInt();
                            break;
                        case 2:
                            rows = line.toInt();
                            break;
                        case 3:
                            cols = line.toInt();
                            break;
                        default:
                            fileNames.append(line);
                            break;
                        }
                        counter++;
                    }
                    pw.imageposition_skill.clear();
                    int x, y = 0;
                    for (int a = 0; a < fileNames.count(); a++)
                    {
                        QApplication::processEvents(QEventLoop::AllEvents);
                        y = a / cols;
                        x = a - y * cols;
                        x = x * w;
                        y = y * h;
                        pw.images_skill.insert(a, fileNames[a]);
                        pw.imageposition_skill.insert(fileNames[a], QPoint(x, y));
                    }
                    fileskill.flush();
                }

                if(f.Path == "surfaces\\iconset\\iconlist_guild.txt")
                {
                    auto icons_guild_txt = eng.ReadFile(stream_surfaces, f);
                    QTextCodec* enc = QTextCodec::codecForName("GBK");
                    auto iconlist_guild_txt = enc->toUnicode(icons_guild_txt).split('\0')[0];
                    QTextStream fileguild(&iconlist_guild_txt);
                    QString line;
                    QList<QString> fileNames;
                    pw.images_guild.clear();
                    int w = 0;
                    int h = 0;
                    int rows = 0;
                    int cols = 0;
                    int counter = 0;
                    while ((line = fileguild.readLine()) != NULL)
                    {
                        switch (counter)
                        {
                        case 0:
                            w = line.toInt();
                            break;
                        case 1:
                            h = line.toInt();
                            break;
                        case 2:
                            rows = line.toInt();
                            break;
                        case 3:
                            cols = line.toInt();
                            break;
                        default:
                            fileNames.append(line);
                            break;
                        }
                        counter++;
                    }
                    pw.imageposition_guild.clear();
                    int x, y = 0;
                    for (int a = 0; a < fileNames.count(); a++)
                    {
                        QApplication::processEvents(QEventLoop::AllEvents);
                        y = a / cols;
                        x = a - y * cols;
                        x = x * w;
                        y = y * h;
                        pw.images_guild.insert(a, fileNames[a]);
                        pw.imageposition_guild.insert(fileNames[a], QPoint(x, y));
                    }
                    fileguild.flush();
                }

            }
            emit logWork("SUCESSO!", true, false, QColor(0, 255, 0));
        }
        if (!QFile::exists(profile->configs))
        {
            emit logWork("Erro na leitura do configs.pck", true, false, QColor::fromRgb(255, 0, 0));
            return;
        } else
        {
            emit logWork("configs.pck...");
            QTextCodec* gbk = QTextCodec::codecForName("GBK");
            QTextCodec* utf16 = QTextCodec::codecForName("UTF-16LE");
            PCKStream stream_configs(profile->configs);
            PCKEngine eng = PCKEngine();
            auto fe = eng.ReadFileEntrys(stream_configs);
            for(auto f: fe)
            {
                if (f.Path == "configs\\item_color.txt")
                {
                    auto item_color = eng.ReadFile(stream_configs, f);
                    auto item_color_txt = gbk->toUnicode(item_color);
                    QTextStream file(&item_color_txt);
                    pw.listItemColor.clear();
                    while(!file.atEnd())
                    {
                        QString line = file.readLine();
                        QStringList splited = line.split("\t");
                        QString v1 = splited[0];
                        QString v2 = splited[1];
                        if (v1.length() > 0 && v2.length() > 0)
                        {
                            pw.listItemColor.insert(v1.toInt(), v2.toInt());
                        }
                        else
                        {
                            if (v1.length() > 0)
                            {
                                pw.listItemColor.insert(v1.toInt(), 0);
                            }
                            if (v2.length() > 0)
                            {
                                pw.listItemColor.insert(0, v2.toInt());
                            }
                        }
                    }
                    file.flush();
                }
                if (f.Path == "configs\\skillstr.txt")
                {
                    pw.listSkillName.clear();
                    pw.listSkillDesc.clear();
                    auto arr = eng.ReadFile(stream_configs, f);
                    auto item_skill_txt = utf16->toUnicode(arr);
                    QTextStream filesk(&item_skill_txt);
                    QStringList skillstr = filesk.readAll().split("\"");
                    QStringList temp = skillstr[0].split("\n");
                    skillstr[0] = temp[temp.length() - 1];
                    pw.listSkillName = Utils::SkillNameToList(skillstr);
                    pw.listSkillDesc = Utils::SkillDescToList(skillstr);
                    filesk.flush();
                }

                if (f.Path == "configs\\item_desc.txt")
                {
                    pw.listItemDesc.clear();
                    auto arr = eng.ReadFile(stream_configs, f);
                    auto item_desc_txt = utf16->toUnicode(arr);
                    QTextStream filedesc(&item_desc_txt);
                    QString line;
                    int count = 0;
                    filedesc.readLine();
                    while (!filedesc.atEnd())
                    {
                        line = filedesc.readLine();
                        line.remove(QChar('\u0000'));
                        if (!line.isEmpty() && !line.startsWith("#") && !line.startsWith("/"))
                        {
                            QStringList data = line.split('"', QString::SkipEmptyParts);
                            try
                            {
                                pw.listItemDesc.insert(count, data[0]);
                                count++;
                            }
                            catch (QException e)
                            {
                                qDebug() << "Err item_desc_txt\n" << e.what();
                            }
                        }
                    }
                    filedesc.flush();
                }
                if (f.Path == "configs\\item_ext_desc.txt")
                {
                    pw.listItemExtDesc.clear();
                    auto arr = eng.ReadFile(stream_configs, f);
                    auto item_ext_desc_txt = utf16->toUnicode(arr);
                    QTextStream fileextdesc(&item_ext_desc_txt);
                    QString line;
                    int count = 0;
                    fileextdesc.readLine();
                    while (!fileextdesc.atEnd())
                    {
                        line = fileextdesc.readLine();
                        line.remove(QChar('\u0000'));
                        if (!line.isNull() && line.length() > 0 && !line.startsWith("#") && !line.startsWith("/"))
                        {
                            QStringList data = line.split('"');
                            try
                            {
                                int id = data[0].toInt();
                                if (id > 0)
                                    pw.listItemExtDesc.insert(data[0].toInt(), data.length() > 1 ? data[1].replace('"', ' ') : "");
                            }
                            catch (QException e)
                            {
                                qDebug() << "Err item_desc_ext_txt\n" << e.what();
                            }
                        }
                        count++;
                    }
                    fileextdesc.flush();
                }
                if (f.Path == "configs\\item_ext_prop.txt")
                {
                    pw.addonsList.clear();
                    auto arr = eng.ReadFile(stream_configs, f);
                    auto item_ext_prop_txt = gbk->toUnicode(arr);
                    QTextStream fileextprop(&item_ext_prop_txt);
                    fileextprop.setAutoDetectUnicode(false);
                    QString line;
                    while (!fileextprop.atEnd())
                    {
                        line = fileextprop.readLine();
                        if (line.startsWith("type:"))
                        {
                            int int32 = line.mid(5).trimmed().toInt();
                            if (fileextprop.readLine().startsWith("{"))
                            {
                                QString str2;
                                while (!(str2 = fileextprop.readLine()).startsWith("}"))
                                {
                                    QStringList strArray = str2.split(',');
                                    for (int index = 0; index < strArray.size(); ++index)
                                    {
                                        QString trimmed = strArray[index].trimmed();
                                        if (!trimmed.isEmpty())
                                        {
                                            pw.addonsList.insert(trimmed, QString::number(int32));
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                if (f.Path == "configs\\fixed_msg.txt")
                {
                    pw.listFixedMsg.clear();
                    auto arr = eng.ReadFile(stream_configs, f);
                    auto fixed_msg_txt = utf16->toUnicode(arr);
                    QTextStream filefixedmsg(&fixed_msg_txt);
                    QString line;
                    int count = 0;
                    filefixedmsg.readLine();
                    while (!filefixedmsg.atEnd())
                    {
                        line = filefixedmsg.readLine();
                        line.remove(QChar('\u0000'));
                        if (!line.isEmpty() && !line.startsWith("#") && !line.startsWith("/"))
                        {
                            QStringList data = line.split('"', QString::SkipEmptyParts);
                            try
                            {
                                pw.listFixedMsg.insert(count, data[0]);
                                count++;
                            }
                            catch (QException e)
                            {
                                qDebug() << "Erro na leitura: fixed_msg.txt\n" << e.what();
                            }
                        }
                    }
                    filefixedmsg.flush();
                }
            }
            emit logWork("SUCESSO!", true, false, QColor(0, 255, 0));
        }
        emit logWork("Carregando arquivos data:", true, true);
        if (!QFile::exists(profile->elements))
        {
            emit logWork("Erro na leitura do elements.data", true, false, QColor::fromRgb(255, 0, 0));
            return;
        } else
        {
            emit logWork("elements.data...");

            pw.elc = new eListCollection(profile->elements);

            if (pw.elc->loaded)
            {
                qDebug() << pw.elc->Lists.count() << pw.elc->Version;
                emit logWork("SUCESSO!", false, false, QColor::fromRgb(0, 255, 0));
                emit logWork(QString(" (v%1)").arg(pw.elc->Version), true, false, QColor("yellow"));
                pw.listClasses.clear();
                for(int i = 0; i < pw.elc->Lists.size(); i++)
                {
                    if (pw.elc->Lists[i].listName.contains("RACTER_CLASS_CONFIG"))
                    {
                        for(int b = 0; b < pw.elc->Lists[i].elementValues.size(); b++)
                        {
                            pw.listClasses[pw.elc->GetValue(i, b, 2).toInt()] = pw.elc->GetValue(i, b, 1);
                        }
                    }
                }
                for (int e = 0; e < pw.elc->Lists[0].elementValues.length(); e++)
                {
                    addon_data addon;
                    addon.id_addon = pw.elc->GetValue(0, e, 0).toInt();
                    addon.paramNum = pw.elc->GetValue(0, e, 2).toInt();
                    addon.arg[0] = pw.elc->GetValue(0, e, 3).toInt();
                    addon.arg[1] = pw.elc->GetValue(0, e, 4).toInt();
                    addon.arg[2] = pw.elc->GetValue(0, e, 5).toInt();
                    auto f = pw.addonsList.find(QString::number(addon.id_addon));
                    if (f != pw.addonsList.end())
                        addon.propNum = f.value().toInt();
                    pw.listAddonsData.push_back(addon);
                }
            }
        }
        emit readElementsFinished(pw);
    }

    void WorkerReadData()
    {
        emit logWork("Carregando arquivos data...");
        if (!QFile::exists(profile->elements))
        {
            emit logWork("Erro na leitura do elements.data", true, false, QColor::fromRgb(255, 0, 0));
            return;
        } else
        {
            pw.elc = new eListCollection(profile->elements);

            if (pw.elc->loaded)
            {
                qDebug() << pw.elc->Lists.count() << pw.elc->Version;
                emit logWork("SUCESSO!", false, false, QColor::fromRgb(0, 255, 0));
                emit logWork(QString(" (v%1)").arg(pw.elc->Version), true, false, QColor("yellow"));
                pw.listClasses.clear();
                for(int i = 0; i < pw.elc->Lists.size(); i++)
                {
                    if (pw.elc->Lists[i].listName.contains("RACTER_CLASS_CONFIG"))
                    {
                        for(int b = 0; b < pw.elc->Lists[i].elementValues.size(); b++)
                        {
                            pw.listClasses[pw.elc->GetValue(i, b, 2).toInt()] = pw.elc->GetValue(i, b, 1);
                        }
                    }
                }
                for (int e = 0; e < pw.elc->Lists[0].elementValues.length(); e++)
                {
                    addon_data addon;
                    addon.id_addon = pw.elc->GetValue(0, e, 0).toInt();
                    addon.paramNum = pw.elc->GetValue(0, e, 2).toInt();
                    addon.arg[0] = pw.elc->GetValue(0, e, 3).toInt();
                    addon.arg[1] = pw.elc->GetValue(0, e, 4).toInt();
                    addon.arg[2] = pw.elc->GetValue(0, e, 5).toInt();
                    auto f = pw.addonsList.find(QString::number(addon.id_addon));
                    if (f != pw.addonsList.end())
                        addon.propNum = f.value().toInt();
                    pw.listAddonsData.push_back(addon);
                }
            }
        }
        emit readElementsFinished(pw);
    }

    void doWork(int msleep, int progress) {
        QThread::msleep(msleep);
        emit workFinished(progress);
    }

    void WorkerReadPcks()
    {
        emit logWork("Carregando arquivos pck...");
        if (!QFile::exists(profile->surfaces))
        {
            emit logWork("Erro na leitura do surfaces.pck", true, false, QColor::fromRgb(255, 0, 0));
            return;
        }
        else {
            PCKStream stream_surfaces(profile->surfaces);
            PCKEngine eng;
            auto list = eng.ReadFileEntrys(stream_surfaces);
            for(auto f : list)
            {
                if (f.Path == "surfaces\\ingame\\profession.tga")
                {
                    auto icon = eng.ReadFile(stream_surfaces, f);
                    pw.icon_profession.loadFromData(icon);
                }
                if (f.Path == "surfaces\\iconset\\iconlist_ivtrm.dds")
                {
                    auto icons_m = eng.ReadFile(stream_surfaces, f);
                    pw.iconlist_ivtrm.loadFromData(icons_m);
                }
                if (f.Path == "surfaces\\iconset\\iconlist_ivtrf.dds")
                {
                    auto icons_f = eng.ReadFile(stream_surfaces, f);
                    pw.iconlist_ivtrf.loadFromData(icons_f);
                }
                if (f.Path == "surfaces\\iconset\\iconlist_skill.dds")
                {
                    auto icons_skill = eng.ReadFile(stream_surfaces, f);
                    pw.iconlist_skill.loadFromData(icons_skill);
                }
                if (f.Path == "surfaces\\iconset\\iconlist_guild.dds")
                {
                    auto icons_guild = eng.ReadFile(stream_surfaces, f);
                    pw.iconlist_guild.loadFromData(icons_guild);
                }
                if(f.Path == "surfaces\\iconset\\iconlist_ivtrm.txt")
                {
                    auto icons_m_txt = eng.ReadFile(stream_surfaces, f);
                    QTextCodec* enc = QTextCodec::codecForName("GBK");
                    auto iconlist_ivtrm_txt = enc->toUnicode(icons_m_txt).split('\0')[0];
                    QTextStream filem(&iconlist_ivtrm_txt);
                    QString line;
                    QList<QString> fileNames;
                    pw.images_m.clear();
                    int w = 0;
                    int h = 0;
                    int rows = 0;
                    int cols = 0;
                    int counter = 0;
                    while ((line = filem.readLine()) != NULL)
                    {
                        switch (counter)
                        {
                        case 0:
                            w = line.toInt();
                            break;
                        case 1:
                            h = line.toInt();
                            break;
                        case 2:
                            rows = line.toInt();
                            break;
                        case 3:
                            cols = line.toInt();
                            break;
                        default:
                            fileNames.append(line);
                            break;
                        }
                        counter++;
                    }
                    pw.imageposition_m.clear();
                    int x, y = 0;
                    for (int a = 0; a < fileNames.count(); a++)
                    {
                        QApplication::processEvents(QEventLoop::AllEvents);
                        y = a / cols;
                        x = a - y * cols;
                        x = x * w;
                        y = y * h;
                        pw.images_m.insert(a, fileNames[a]);
                        pw.imageposition_m.insert(fileNames[a], QPoint(x, y));
                    }
                    filem.flush();
                }
                if(f.Path == "surfaces\\iconset\\iconlist_ivtrf.txt")
                {
                    auto icons_f_txt = eng.ReadFile(stream_surfaces, f);
                    QTextCodec* enc = QTextCodec::codecForName("GBK");
                    auto iconlist_ivtrf_txt = enc->toUnicode(icons_f_txt).split('\0')[0];
                    QTextStream filef(&iconlist_ivtrf_txt);
                    QString line;
                    QList<QString> fileNames;
                    pw.images_f.clear();
                    int w = 0;
                    int h = 0;
                    int rows = 0;
                    int cols = 0;
                    int counter = 0;
                    while ((line = filef.readLine()) != NULL)
                    {
                        switch (counter)
                        {
                        case 0:
                            w = line.toInt();
                            break;
                        case 1:
                            h = line.toInt();
                            break;
                        case 2:
                            rows = line.toInt();
                            break;
                        case 3:
                            cols = line.toInt();
                            break;
                        default:
                            fileNames.append(line);
                            break;
                        }
                        counter++;
                    }
                    pw.imageposition_f.clear();
                    int x, y = 0;
                    for (int a = 0; a < fileNames.count(); a++)
                    {
                        QApplication::processEvents(QEventLoop::AllEvents);
                        y = a / cols;
                        x = a - y * cols;
                        x = x * w;
                        y = y * h;
                        pw.images_f.insert(a, fileNames[a]);
                        pw.imageposition_f.insert(fileNames[a], QPoint(x, y));
                    }
                    filef.flush();
                }
                if(f.Path == "surfaces\\iconset\\iconlist_skill.txt")
                {
                    auto icons_skill_txt = eng.ReadFile(stream_surfaces, f);
                    QTextCodec* enc = QTextCodec::codecForName("GBK");
                    auto iconlist_skill_txt = enc->toUnicode(icons_skill_txt).split('\0')[0];
                    QTextStream fileskill(&iconlist_skill_txt);
                    QString line;
                    QList<QString> fileNames;
                    pw.images_skill.clear();
                    int w = 0;
                    int h = 0;
                    int rows = 0;
                    int cols = 0;
                    int counter = 0;
                    while ((line = fileskill.readLine()) != NULL)
                    {
                        switch (counter)
                        {
                        case 0:
                            w = line.toInt();
                            break;
                        case 1:
                            h = line.toInt();
                            break;
                        case 2:
                            rows = line.toInt();
                            break;
                        case 3:
                            cols = line.toInt();
                            break;
                        default:
                            fileNames.append(line);
                            break;
                        }
                        counter++;
                    }
                    pw.imageposition_skill.clear();
                    int x, y = 0;
                    for (int a = 0; a < fileNames.count(); a++)
                    {
                        QApplication::processEvents(QEventLoop::AllEvents);
                        y = a / cols;
                        x = a - y * cols;
                        x = x * w;
                        y = y * h;
                        pw.images_skill.insert(a, fileNames[a]);
                        pw.imageposition_skill.insert(fileNames[a], QPoint(x, y));
                    }
                    fileskill.flush();
                }

                if(f.Path == "surfaces\\iconset\\iconlist_guild.txt")
                {
                    auto icons_guild_txt = eng.ReadFile(stream_surfaces, f);
                    QTextCodec* enc = QTextCodec::codecForName("GBK");
                    auto iconlist_guild_txt = enc->toUnicode(icons_guild_txt).split('\0')[0];
                    QTextStream fileguild(&iconlist_guild_txt);
                    QString line;
                    QList<QString> fileNames;
                    pw.images_guild.clear();
                    int w = 0;
                    int h = 0;
                    int rows = 0;
                    int cols = 0;
                    int counter = 0;
                    while ((line = fileguild.readLine()) != NULL)
                    {
                        switch (counter)
                        {
                        case 0:
                            w = line.toInt();
                            break;
                        case 1:
                            h = line.toInt();
                            break;
                        case 2:
                            rows = line.toInt();
                            break;
                        case 3:
                            cols = line.toInt();
                            break;
                        default:
                            fileNames.append(line);
                            break;
                        }
                        counter++;
                    }
                    pw.imageposition_guild.clear();
                    int x, y = 0;
                    for (int a = 0; a < fileNames.count(); a++)
                    {
                        QApplication::processEvents(QEventLoop::AllEvents);
                        y = a / cols;
                        x = a - y * cols;
                        x = x * w;
                        y = y * h;
                        pw.images_guild.insert(a, fileNames[a]);
                        pw.imageposition_guild.insert(fileNames[a], QPoint(x, y));
                    }
                    fileguild.flush();
                }

            }
        }
        if (!QFile::exists(profile->configs))
        {
            emit logWork("Erro na leitura do configs.pck", true, false, QColor::fromRgb(255, 0, 0));
            return;
        } else {

            QTextCodec* gbk = QTextCodec::codecForName("GBK");
            QTextCodec* utf16 = QTextCodec::codecForName("UTF-16LE");
            PCKStream stream_configs(profile->configs);
            PCKEngine eng = PCKEngine();
            auto fe = eng.ReadFileEntrys(stream_configs);
            for(auto f: fe)
            {
                if (f.Path == "configs\\item_color.txt")
                {
                    auto item_color = eng.ReadFile(stream_configs, f);
                    auto item_color_txt = gbk->toUnicode(item_color);
                    QTextStream file(&item_color_txt);
                    pw.listItemColor.clear();
                    while(!file.atEnd())
                    {
                        QString line = file.readLine();
                        QStringList splited = line.split("\t");
                        QString v1 = splited[0];
                        QString v2 = splited[1];
                        if (v1.length() > 0 && v2.length() > 0)
                        {
                            pw.listItemColor.insert(v1.toInt(), v2.toInt());
                        }
                        else
                        {
                            if (v1.length() > 0)
                            {
                                pw.listItemColor.insert(v1.toInt(), 0);
                            }
                            if (v2.length() > 0)
                            {
                                pw.listItemColor.insert(0, v2.toInt());
                            }
                        }
                    }
                    file.flush();
                }
                if (f.Path == "configs\\skillstr.txt")
                {
                    pw.listSkillName.clear();
                    pw.listSkillDesc.clear();
                    auto arr = eng.ReadFile(stream_configs, f);
                    auto item_skill_txt = utf16->toUnicode(arr);
                    QTextStream filesk(&item_skill_txt);
                    QStringList skillstr = filesk.readAll().split("\"");
                    QStringList temp = skillstr[0].split("\n");
                    skillstr[0] = temp[temp.length() - 1];
                    pw.listSkillName = Utils::SkillNameToList(skillstr);
                    pw.listSkillDesc = Utils::SkillDescToList(skillstr);
                    filesk.flush();
                }

                if (f.Path == "configs\\item_desc.txt")
                {
                    pw.listItemDesc.clear();
                    auto arr = eng.ReadFile(stream_configs, f);
                    auto item_desc_txt = utf16->toUnicode(arr);
                    QTextStream filedesc(&item_desc_txt);
                    QString line;
                    int count = 0;
                    filedesc.readLine();
                    while (!filedesc.atEnd())
                    {
                        line = filedesc.readLine();
                        line.remove(QChar('\u0000'));
                        if (!line.isEmpty() && !line.startsWith("#") && !line.startsWith("/"))
                        {
                            QStringList data = line.split('"', QString::SkipEmptyParts);
                            try
                            {
                                pw.listItemDesc.insert(count, data[0]);
                                count++;
                            }
                            catch (QException e)
                            {
                                qDebug() << "Err item_desc_txt\n" << e.what();
                            }
                        }
                    }
                    filedesc.flush();
                }
                if (f.Path == "configs\\item_ext_desc.txt")
                {
                    pw.listItemExtDesc.clear();
                    auto arr = eng.ReadFile(stream_configs, f);
                    auto item_ext_desc_txt = utf16->toUnicode(arr);
                    QTextStream fileextdesc(&item_ext_desc_txt);
                    QString line;
                    int count = 0;
                    fileextdesc.readLine();
                    while (!fileextdesc.atEnd())
                    {
                        line = fileextdesc.readLine();
                        line.remove(QChar('\u0000'));
                        if (!line.isNull() && line.length() > 0 && !line.startsWith("#") && !line.startsWith("/"))
                        {
                            QStringList data = line.split('"');
                            try
                            {
                                int id = data[0].toInt();
                                if (id > 0)
                                    pw.listItemExtDesc.insert(data[0].toInt(), data.length() > 1 ? data[1].replace('"', ' ') : "");
                            }
                            catch (QException e)
                            {
                                qDebug() << "Err item_desc_ext_txt\n" << e.what();
                            }
                        }
                        count++;
                    }
                    fileextdesc.flush();
                }
                if (f.Path == "configs\\item_ext_prop.txt")
                {
                    pw.addonsList.clear();
                    auto arr = eng.ReadFile(stream_configs, f);
                    auto item_ext_prop_txt = gbk->toUnicode(arr);
                    QTextStream fileextprop(&item_ext_prop_txt);
                    fileextprop.setAutoDetectUnicode(false);
                    QString line;
                    while (!fileextprop.atEnd())
                    {
                        line = fileextprop.readLine();
                        if (line.startsWith("type:"))
                        {
                            int int32 = line.mid(5).trimmed().toInt();
                            if (fileextprop.readLine().startsWith("{"))
                            {
                                QString str2;
                                while (!(str2 = fileextprop.readLine()).startsWith("}"))
                                {
                                    QStringList strArray = str2.split(',');
                                    for (int index = 0; index < strArray.size(); ++index)
                                    {
                                        QString trimmed = strArray[index].trimmed();
                                        if (!trimmed.isEmpty())
                                        {
                                            pw.addonsList.insert(trimmed, QString::number(int32));
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                if (f.Path == "configs\\fixed_msg.txt")
                {
                    pw.listFixedMsg.clear();
                    auto arr = eng.ReadFile(stream_configs, f);
                    auto fixed_msg_txt = utf16->toUnicode(arr);
                    QTextStream filefixedmsg(&fixed_msg_txt);
                    QString line;
                    int count = 0;
                    filefixedmsg.readLine();
                    while (!filefixedmsg.atEnd())
                    {
                        line = filefixedmsg.readLine();
                        line.remove(QChar('\u0000'));
                        if (!line.isEmpty() && !line.startsWith("#") && !line.startsWith("/"))
                        {
                            QStringList data = line.split('"', QString::SkipEmptyParts);
                            try
                            {
                                pw.listFixedMsg.insert(count, data[0]);
                                count++;
                            }
                            catch (QException e)
                            {
                                qDebug() << "Erro na leitura: fixed_msg.txt\n" << e.what();
                            }
                        }
                    }
                    filefixedmsg.flush();
                }
            }
        }
        emit logWork("SUCESSO!", true, false, QColor::fromRgb(0, 255, 0));
        emit readPcksFinished(pw);
    }

signals:
    void logWork(QString log, bool ret = false, bool time = true, QColor color = QColor("white"));
    void connectedServer();
    void workFinished(int progress);
    void readElementsFinished(arquivos &pw);
    void readPcksFinished(arquivos &pw);
};

#endif // WORKER_H
