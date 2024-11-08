#ifndef ELISTCOLLECTION
#define ELISTCOLLECTION

#include <ElementEngine/elist.h>
#include <QObject>
#include <QVector>
#include <QMap>
#include <QByteArray>
#include <QFile>
#include <QDataStream>
#include <QDebug>
#include <QFileInfo>
#include <QFile>
#include <QApplication>
#include <QDir>
#include <QRegularExpression>
#include <GNET/octetsstream.h>
#include <QtEndian>
#include <ElementEngine/elementseditor.h>
#include <QProgressBar>
#include <QTextEdit>
#include <QTime>

class eListCollection
{
public:
    eListCollection(QString pathname, QTextEdit *log = NULL){
        QFile file(pathname);
        QByteArray arr;
        if (file.open(QFile::ReadOnly))
            arr = file.readAll();
        elements.setData(arr, false);
        elements.Unmarshal();
        Version = elements.version;
        Signature = elements.signature;
        Load(elements.version, &elements, log);
    }
    bool loaded = false;
    ElementsEditor elements;
    quint16 Version;
    qint16 Signature;
    int ConversationListIndex;
    QString ConfigFile;
    QVector<eList> Lists;
    QMap<int, int> addonIndex;

    QString GetOffset(int ListIndex)
    {
        return QByteArray::fromRawData(reinterpret_cast<const char*>(Lists[ListIndex].listOffset.data()), Lists[ListIndex].listOffset.size()).toHex('-').toUpper();
    }

    void SetOffset(int ListIndex, const QString& Offset)
    {
        QStringList hex = Offset.split('-');
        QByteArray offsetBytes;
        foreach (const QString& hexValue, hex)
        {
            offsetBytes.append(static_cast<char>(hexValue.toUShort(nullptr, 16)));
        }
        Lists[ListIndex].listOffset = offsetBytes;
    }

    QString GetValue(int ListIndex, int ElementIndex, int FieldIndex)
    {
        return Lists[ListIndex].GetValue(ElementIndex, FieldIndex);
    }

    QString GetType(int ListIndex, int FieldIndex)
    {
        return Lists[ListIndex].GetType(FieldIndex);
    }

    QVariant ReadValue(QDataStream& stream, const QString& type)
    {
        if (type == "int16")
        {
            qint16 value;
            stream >> value;
            return QVariant(qFromBigEndian(value));
        }
        else if (type == "int32")
        {
            qint32 value;
            stream >> value;
            return QVariant(qFromBigEndian(value));
        }
        else if (type == "int64")
        {
            qint64 value;
            stream >> value;
            return QVariant(qFromBigEndian(value));
        }
        else if (type == "float")
        {
            float value;
            stream >> value;
            return QVariant(qFromBigEndian(value));
        }
        else if (type == "double")
        {
            double value;
            stream >> value;
            return QVariant(qFromBigEndian(value));
        }
        else if (type.startsWith("byte:"))
        {
            int byteCount = type.mid(5).toInt();
            QByteArray value(byteCount, 0);
            stream.readRawData(value.data(), byteCount);
            return QVariant(value);
        }
        else if (type.startsWith("wstring:") || type.startsWith("string:"))
        {
            int byteCount = type.mid(type.indexOf(':') + 1).toInt();
            QByteArray value(byteCount, 0);
            stream.readRawData(value.data(), byteCount);
            return QVariant(value);
        }

        return QVariant();
    }

    void WriteValue(QDataStream& stream, const QVariant& value, const QString& type)
    {
        if (type == "int16")
        {
            qint16 intValue = value.toInt();
            stream << intValue;
        }
        else if (type == "int32")
        {
            qint32 intValue = value.toInt();
            stream << intValue;
        }
        else if (type == "int64")
        {
            qint64 intValue = value.toLongLong();
            stream << intValue;
        }
        else if (type == "float")
        {
            float floatValue = value.toFloat();
            stream << floatValue;
        }
        else if (type == "double")
        {
            double doubleValue = value.toDouble();
            stream << doubleValue;
        }
        else if (type.startsWith("byte:") || type.startsWith("wstring:") || type.startsWith("string:"))
        {
            QByteArray byteArray = value.toByteArray();
            stream.writeRawData(byteArray.constData(), byteArray.size());
        }
    }

    QVector<eList> LoadConfiguration(QString file)
    {
        QFile configFile(file);
        if (!configFile.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            return QVector<eList>();
        }

        QTextStream sr(&configFile);
        int numLists = sr.readLine().toInt();
        QVector<eList> Li(numLists);

        try
        {
            ConversationListIndex = sr.readLine().toInt();
        }
        catch (...)
        {
            ConversationListIndex = 58;
        }

        for (int i = 0; i < Li.size(); ++i)
        {
            QString line;
            do
            {
                line = sr.readLine();
            } while (line.isEmpty());

            Li[i] = eList();
            Li[i].listName = line;
            Li[i].listOffset = nullptr;
            QString offset = sr.readLine();
            if (offset != "AUTO")
            {
                Li[i].listOffset.resize(offset.toInt());
            }
            QStringList elementFields = sr.readLine().split(';');
            QStringList elementTypes = sr.readLine().split(';');
            Li[i].elementFields = elementFields.toVector();
            Li[i].elementTypes = elementTypes.toVector();
        }

        configFile.close();
        return Li;
    }

    QMap<QString, QString> Listcnts;
    QMap<QString, QString> Listosets;
    qint16 Listver;
    int SStat[5];

    void Load(int version, OctetsStream *os, QTextEdit *log = NULL)
    {
        addonIndex.clear();
        Listcnts.clear();
        Listosets.clear();
        Listver = -1;
        int SStat[5] = { 0, 0, 0, 0, 0 };

        QStringList configFiles = QDir(QCoreApplication::applicationDirPath() + "/configs").entryList(QStringList() << "PW_*_v" + QString::number(version) + ".cfg", QDir::Files);
        if (!configFiles.isEmpty())
        {
            QString configFile = QCoreApplication::applicationDirPath() + "/configs/" + configFiles.first();
            Lists = LoadConfiguration(configFile);
            if (log != NULL)
                log->append(QString("<font color=#505050>[%1]</font> %2").arg(QTime::currentTime().toString("HH:mm:ss")).arg("Carregando arquivos data..."));
            for (int l = 0; l < Lists.size(); ++l)
            {
                SStat[0] = l;
                QCoreApplication::processEvents();

                if (!Lists[l].listOffset.isEmpty())
                {
                    if (Lists[l].listOffset.length() > 0)
                    {
                        Lists[l].listOffset = os->readBytes(Lists[l].listOffset.length());
                    }
                }
                else
                {
                    if (l == 0)
                    {
                        QByteArray tag = os->readBytes(4);
                        QByteArray len = os->readBytes(4);
                        QByteArray buffer = os->readBytes(qFromLittleEndian<int>(len.data()));
                        Lists[l].listOffset = tag + len + buffer;
                    }
                    if (l == 20)
                    {
                        QByteArray tag = os->readBytes(4);
                        QByteArray len = os->readBytes(4);
                        QByteArray buffer = os->readBytes(qFromLittleEndian<int>(len.data()));
                        QByteArray t = os->readBytes(4);
                        Lists[l].listOffset = tag + len + buffer + t;
                    }
                    int NPC_WAR_TOWERBUILD_SERVICE_index = 100;
                    if (Version >= 191)
                    {
                        NPC_WAR_TOWERBUILD_SERVICE_index = 99;
                    }
                    if (l == NPC_WAR_TOWERBUILD_SERVICE_index)
                    {
                        QByteArray tag = os->readBytes(4);
                        QByteArray len = os->readBytes(4);
                        QByteArray buffer = os->readBytes(qFromLittleEndian<int>(len.data()));
                        Lists[l].listOffset = tag + len + buffer;
                    }
                }

                if (l == ConversationListIndex)
                {
                    if (Version >= 191)
                    {
                        qint64 sourcePosition = os->qds->device()->pos();
                        bool run = true;
                        int listLength = 0;
                        while (run)
                        {
                            run = false;
                            char byteData;
                            if (os->qds->device()->getChar(&byteData))
                            {
                                listLength++;
                                run = true;
                            }
                        }
                        os->qds->device()->seek(sourcePosition);
                        Lists[l].elementTypes[0] = "byte:" + QString::number(listLength);
                    }
                    else
                    {
                        if (Lists[l].elementTypes[0].contains("AUTO"))
                        {
                            QByteArray pattern = QString("facedata\\").toUtf8();
                            qint64 sourcePosition = os->qds->device()->pos();
                            int listLength = -72 - pattern.size();
                            bool run = true;
                            while (run)
                            {
                                run = false;
                                for (int i = 0; i < pattern.size(); ++i)
                                {
                                    ++listLength;
                                    if (os->readInt8() != pattern.at(i))
                                    {
                                        run = true;
                                        break;
                                    }
                                }
                            }
                            os->qds->device()->seek(sourcePosition);
                            Lists[l].elementTypes[0] = "byte:" + QString::number(listLength);
                        }
                    }
                    Lists[l].elementValues.resize(1);
                    Lists[l].elementValues[0].resize(Lists[l].elementTypes.length());
                    Lists[l].elementValues[0][0] = ReadValue(*os->qds, Lists[l].elementTypes[0]);
                }
                else
                {
                    if (Version >= 191)
                    {
                        *os >> Lists[l].listType;
                    }
                    if (Listver > -1 && Listcnts[QString::number(l)] != NULL)
                    {
                        qint32 num = Listcnts[QString::number(l)].toInt();
                        Lists[l].elementValues.resize(num);
                        os->readInt32();
                    }
                    else
                    {
                        qint32 numElements = os->readInt32();
                        Lists[l].elementValues.resize(numElements);
                    }

                    SStat[1] = Lists[l].elementValues.size();

                    if (Version >= 191)
                    {
                        *os >> Lists[l].elementSize;
                    }
                    for (int e = 0; e < Lists[l].elementValues.size(); ++e)
                    {
                        Lists[l].elementValues[e].resize(Lists[l].elementTypes.size());
                        for (int f = 0; f < Lists[l].elementValues[e].size(); ++f)
                        {
                            Lists[l].elementValues[e][f] = ReadValue(*os->qds, Lists[l].elementTypes[f]);
                        }
                    }
                }
            }
            if (log != NULL)
                log->append(QString("<font color=#505050>[%1]</font> %2").arg(QTime::currentTime().toString("HH:mm:ss")).arg(QString("Carregado com sucesso! Versão <font color=\"#00C800\"><b>%1</b></font>").arg(Version)));
        }
        else
        {
            QString str = QString("Não foram encontradas configurações de leitura do elements.data (versão: %1)\n Verifique na pasta configs: configs/PW_*_v%2.cfg").arg(Version).arg(Version);
            if (log != NULL)
                log->append(QString("<font color=#505050>[%1]</font> %2").arg(QTime::currentTime().toString("HH:mm:ss")).arg(str));
        }
        loaded = true;
    }
};

#endif
