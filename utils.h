#ifndef UTILS_H
#define UTILS_H

#include <QColor>
#include <QTextCodec>
#include <QString>
#include <QDebug>
#include <QDateTime>
#include <GNET/octets.h>
#include <iostream>
#include <QImage>
#include <QPixmap>
#include <QIcon>
#include <QtMath>
#include <QApplication>
#include <QMap>
#include <QException>
#include <set>
#include <QBuffer>
#include "Protocols/GRoleInventory.h"

class Utils
{
public:
    bool IsEqual(GRoleInventory& inv1, GRoleInventory& inv2)
    {
        return inv1.id==inv2.id && inv1.count==inv2.count && inv1.data.value==inv2.data.value && inv1.expire_date==inv2.expire_date
                && inv1.guid1==inv2.guid1 && inv1.guid2==inv2.guid2 && inv1.proctype==inv2.proctype && inv1.max_count==inv2.max_count;
    }
    void CheckItems(GRoleInventoryVector& src, GRoleInventoryVector& dst, GRoleInventoryVector& list, int capacity)
    {
        std::set<int> index;
        GRoleInventoryVector::iterator it,is;
        for(it=dst.begin();it!=dst.end();)
        {
            if(it->pos>=0 && (capacity==0 || it->pos<capacity) && index.find(it->pos)==index.end())
            {
                index.insert(it->pos);
                ++it;
            }
            else
            {
                qDebug() << QString("PutRoleData: ignore item %1 with invalid position %2").arg(it->id).arg(it->pos);
                it = dst.erase(it);
            }
        }
        for(it=dst.begin();it!=dst.end();++it)
        {
            for(is=src.begin();is!=src.end();++is)
            {
                if(it->pos==is->pos)
                {
                    if(!IsEqual(*it, *is))
                        list.push_back(*it);
                    break;
                }
            }
            if(is==src.end())
                list.push_back(*it);
        }
    }

    static QColor MemoryUsageColor(float val)
    {
        if (val <= 0.0f)
            return QColor(255, 255, 255);
        else if (val < 30.0f && val > 0.0f)
            return QColor(0, 170, 0);
        else if (val < 60.0f && val >= 30.0f)
            return QColor(255, 170, 0);
        else return QColor(170, 0, 0);
    }

    //	Property effect essence index
    enum
    {
        PEEI_PHYDAMAGE = 0,
        PEEI_PHYDEF,
        PEEI_MAGICDAMAGE,
        PEEI_GOLDDEF,
        PEEI_WOODDEF,
        PEEI_WATERDEF,
        PEEI_FIREDEF,
        PEEI_EARTHDEF,
        PEEI_HP,
        PEEI_MP,
        PEEI_ENDURANCE,
        PEEI_ATKDIST,
        PEEI_STRENGTHREQ,
        PEEI_AGILITYREQ,
        PEEI_ATKSPEED,
        PEEI_DODGE,
        PEEI_MAX_PHYDAMAGE,
        PEEI_MAX_MAGICDAMAGE,
        MAX_PEEINDEX,
    };

    //	Property effect essence mask
    enum
    {
        PEE_PHYDAMAGE		= 0x00000001,
        PEE_PHYDEF			= 0x00000002,
        PEE_MAGICDAMAGE		= 0x00000004,
        PEE_GOLDDEF			= 0x00000008,
        PEE_WOODDEF			= 0x00000010,
        PEE_WATERDEF		= 0x00000020,
        PEE_FIREDEF			= 0x00000040,
        PEE_EARTHDEF		= 0x00000080,
        PEE_HP				= 0x00000100,
        PEE_MP				= 0x00000200,
        PEE_ENDURANCE		= 0x00000400,
        PEE_ATKDIST			= 0x00000800,
        PEE_STRENGTHREQ		= 0x00001000,
        PEE_AGILITYREQ		= 0x00002000,
        PEE_ATKSPEED		= 0x00004000,
        PEE_DODGE			= 0x00008000,
        PEE_ENERGYREQ		= 0x00010000,
        PEE_VITALITYREQ		= 0x00020000,
    };

    //	Refine effect
    enum REFINE_EFFECT
    {
        REFINE_PHYDAMAGE = 0,
        REFINE_MAGICDAMAGE,
        REFINE_PHYDEF,
        REFINE_GOLDDEF,
        REFINE_WOODDEF,
        REFINE_WATERDEF,
        REFINE_FIREDEF,
        REFINE_EARTHDEF,
        REFINE_HP,
        REFINE_DODGE,
        MAX_REFINEINDEX,
    };

    //	Equipment type
    enum EQUIPMENT_TYPE
    {
        EQUIP_UNKNOWN = -1,
        EQUIP_WEAPON = 0,
        EQUIP_ARMOR,
        EQUIP_DECORATION,
        EQUIP_FASHION,
        EQUIP_GENERALCARD,
    };

    static QString TipoCriacao(int id)
    {
        switch(id)
        {
        case 0:
            return "";
        case 1:
            return "Criado";
        case 2:
            return "Dropado";
        case 3:
            return "Comprado";
        case 4:
            return "Produzido";
        case 5:
            return "Assinado";
        }
    }

    enum Gender : char
    {
        Male,
        Female,
    };

    static QString GeneroPersonagem(Gender idGenero)
    {
        switch (idGenero)
        {
        case Male: return "Masculino";
        case Female: return "Feminino";
        default: return "Desconhecido";
        }
    }

    static QString RacaPersonagem(int idRaca)
    {
        switch (idRaca)
        {
        case 0: return "Humano";
        case 1: return "Selvagem";
        case 2: return "Alado";
        case 3: return "Abissal";
        case 4: return "Guardião";
        case 5: return "Sombrio";
        default: return "Desconhecido";
        }
    }

    static QString CultivoPersonagem(int idCultivo)
    {
        switch (idCultivo)
        {
        case 0: return "Astuto";
        case 1: return "Harmonioso";
        case 2: return "O Equilíbrio Celestial";
        case 3: return "Lúcido";
        case 4: return "Enigmático";
        case 5: return "Ameaçador";
        case 6: return "Sinistro";
        case 7: return "Nirvana";
        case 8: return "Mahayana";
        case 20: return "Nobre";
        case 21: return "Iluminado";
        case 22: return "Imortal";
        case 30: return "Diabólico";
        case 31: return "Infernal";
        case 32: return "Demoníaco";
        case 40: return "Alma Caótica";
        case 41: return "Alma Celestial";
        default: return "Desconhecido";
        }
    }

    enum
    {
        GUERREIRO		= 1,
        MAGO			= 2,
        ESPIRITUALISTA	= 4,
        FEITICEIRA		= 8,
        BARBARO         = 16,
        MERCENARIO		= 32,
        ARQUEIRO		= 64,
        SACERDOTE		= 128,
        ARCANO          = 256,
        MISTICO         = 512,
        RETALHADOR		= 1024,
        TORMENTADOR		= 2048,
        ATIRADORA       = 4096,
        PALADINO        = 8192,
        MACACO          = 16384,
        BARDO           = 32768
    };

    static QString MascaraClasse(int number)
    {
        QString mask = "";
        if (number / BARDO > 0)
        {
            number = number % BARDO;
            mask += " Bardo ";
        }
        if (number / MACACO > 0)
        {
            number = number % MACACO;
            mask += " Macaco ";
        }
        if (number / PALADINO > 0)
        {
            number = number % PALADINO;
            mask += " Palad. ";
        }
        if (number / ATIRADORA > 0)
        {
            number = number % ATIRADORA;
            mask += " Atir. ";
        }
        if (number / TORMENTADOR > 0)
        {
            number = number % TORMENTADOR;
            mask += " Torm. ";
        }
        if (number / RETALHADOR > 0)
        {
            number = number % RETALHADOR;
            mask += " Ret. ";
        }
        if (number / MISTICO > 0)
        {
            number = number % MISTICO;
            mask += " Míst. ";
        }
        if (number / ARCANO > 0)
        {
            number = number % ARCANO;
            mask += " Arc. ";
        }
        if (number / SACERDOTE > 0)
        {
            number = number % SACERDOTE;
            mask += " Sacer. ";
        }
        if (number / ARQUEIRO > 0)
        {
            number = number % ARQUEIRO;
            mask += " Arq. ";
        }
        if (number / MERCENARIO > 0)
        {
            number = number % MERCENARIO;
            mask += " Merc. ";
        }
        if (number / BARBARO > 0)
        {
            number = number % BARBARO;
            mask += " Bárb. ";
        }
        if (number / FEITICEIRA > 0)
        {
            number = number % FEITICEIRA;
            mask += " Feit. ";
        }
        if (number / ESPIRITUALISTA > 0)
        {
            number = number % ESPIRITUALISTA;
            mask += " Esp. ";
        }
        if (number / MAGO > 0)
        {
            number = number % MAGO;
            mask += " Mago ";
        }
        if (number / GUERREIRO > 0)
        {
            number = number % GUERREIRO;
            mask += " Guerr. ";
        }

        return mask;
    }

    static QString MapNameFromID(int id)
    {
        switch (id)
        {
        case 1:
            return "Mundo Principal";
        case 101:
            return "Cidade das Feras Sombrias";
        case 102:
            return "Passagem Secreta";
        case 105:
            return "Caverna do Fogo";
        case 106:
            return "Toca dos Lobos";
        case 107:
            return "Caverna do Escorpião-Serpente";
        case 108:
            return "Túmulo do Herói";
        case 109:
            return "Residência de Hades";
        case 110:
            return "Salões Congelados";
        case 111:
            return "Vale do Desastre";
        case 112:
            return "Ruínas da Selva";
        case 113:
            return "Incerteza Fantasma";
        case 114:
            return "Portão Desalmado";
        case 115:
            return "Caverna do Tesouro";
        case 116:
            return "Terra dos Imorta1";
        case 117:
            return "Terra Demoníaca";
        case 118:
            return "Palácio dos Dragões";
        case 119:
            return "Ilha dos Piratas";
        case 120:
            return "Ilha da Serpente";
        case 121:
            return "Sábio";
        case 122:
            return "Demônio";
        case 123:
            return "Purgatório Celeste";
        case 124:
            return "Arcadia Infernal";
        case 125:
            return "Cidade do Brado de Batalha";
        case 126:
            return "Jaula Amaldiçoada";
        case 127:
            return "Clareira da Lua";
        case 128:
            return "Vale Primordial";
        case 129:
            return "Cidade Glacial";
        case 131:
            return "Palácio do Crepusculo";
        case 132:
            return "Cubo do Destino";
        case 133:
            return "Chrono World";
        case 134:
            return "Capela";
        case 135:
            return "Base de clã";
        case 137:
            return "[Morai]";
        case 138:
            return "Vale da Fênix";
        case 139:
            return "Universo Infinito";
        case 140:
            return "Morai Dungeon";
        case 141:
            return "Universo Infinito - Modo Avançado";
        case 142:
            return "Ravina de Guerra";
        case 143:
            return "Cinco Imperadores";
        case 144:
            return "Local de Teste";
        case 145:
            return "Local de Teste";
        case 146:
            return "Local de Teste";
        case 147:
            return "Vale do Pôr-do-Sol";
        case 148:
            return "Palácio Fechado";
        case 149:
            return "Covil do Dragão";
        case 150:
            return "Ilha de BOT";
        case 161:
            return "Vale Celestial";
        case 162:
            return "Origem";
        case 163:
            return "Mundo Primitivo";
        case 164:
            return "Salão do Despertar";
        case 166:
            return "Palácio do Rio de Prata";
        case 167:
            return "Catedral";
        case 168:
            return "Modo da Coruja - Mundo Primitivo";
        case 169:
            return "Caverna das Sombras";
        case 170:
            return "Cubo do Destino";
        case 171:
            return "Ilha dos Lordes Dragões";
        case 172:
            return "Torre do Martírio(1)";
        case 173:
            return "Torre do Martírio(2)";
        case 174:
            return "Torre do Martírio(3)";
        case 175:
            return "Torre do Martírio(4)";
        case 176:
            return "O Paraíso Despedaçado";
        case 177:
            return "Arena dos Campeões";
        case 178:
            return "Continente Ocidental";
        case 179:
            return "Ruínas de Snowchill";
        case 180:
            return "Moradia(1)";
        case 181:
            return "Moradia(2)";
        case 182:
            return "Moradia(3)";
        case 183:
            return "Moradia(4)";
        case 186:
            return "Salões de alvorada";
        case 190:
            return "Salões Dawnlight (Evento)";
        case 191:
            return "Terra da Aventura de Cheero";
        case 301:
            return "Localização móvel";
        case 201:
            return "Teatro Sangrento";
        case 202:
            return "Cave of Fire";
        case 203:
            return "Wolf Den";
        case 204:
            return "Artes Marcia1";
        case 205:
            return "Desconhecido";
        case 230:
            return "Guerra Territorial 3 - PvP";
        case 231:
            return "Guerra Territorial 3 - PvE";
        case 232:
            return "Guerra Territorial 2 - PvP";
        case 233:
            return "Guerra Territorial 2 - PvE";
        case 234:
            return "Guerra Territorial 1 - PvP";
        case 235:
            return "Guerra Territorial 1 - PvE";
        case 213:
            return "Deserto da Miragem";
        case 214:
            return "Labirinto da Areia Viva";
        default:
            return "Desconhecido";
        }
    }

    static QColor CorPK(int state, int pariahTime)
    {
        QColor NAMECOL_WHITE = QColor(255, 255, 255); // White
        QColor NAMECOL_RED0 = QColor(0xff, 0xaa, 0xaa); // Color corresponding to 0xffaaaa
        QColor NAMECOL_RED1 = QColor(0xff, 0x6e, 0x6e); // Color corresponding to 0xff6e6e
        QColor NAMECOL_RED2 = QColor(0xff, 0x28, 0x28); // Color corresponding to 0xff2828

        switch (state)
        {
        case 0: return NAMECOL_WHITE;
        case 1: return NAMECOL_RED0;
        case 2: return pariahTime < 72000 ? NAMECOL_RED1 : NAMECOL_RED2;
        default: return NAMECOL_WHITE;
        }
    }

    enum ForbidType : char
    {
        Login = 100,
        Talk = 101,
        Trade = 102,
        Sell = 103,
        SellPoint = 104,
        Cheater = 105,
    };

    static int ReturnForbidIndex(char type)
    {
        switch (type)
        {
        case Login: return 0;
        case Talk: return 1;
        case Trade: return 2;
        case Sell: return 3;
        case SellPoint: return 4;
        case Cheater: return 5;
        }
    }

    static char ReturnForbidType(int index)
    {
        switch (index)
        {
        case 0: return Login;
        case 1: return Talk;
        case 2: return Trade;
        case 3: return Sell;
        case 4: return SellPoint;
        case 5: return Cheater;
        }
    }

    static QString BanTypes(char tipo)
    {
        switch (tipo)
        {
        case Login: return "Login";
        case Talk: return "Chat";
        case Trade: return "Negociação";
        case Sell: return "Venda";
        case SellPoint: return "Comércio";
        case Cheater: return "Trapaça";
        default: return "Desconhecido";
        }
    }

    enum PetType
    {
        PET_CLASS_MOUNT,        //Montaria
        PET_CLASS_COMBAT,       //Combate
        PET_CLASS_FOLLOW,       //Mascote
        PET_CLASS_SUMMON,       //Invocação
        PET_CLASS_PLANT,        //Planta
        PET_CLASS_EVOLUTION,    //Evolução
        PET_CLASS_MAX,
    };

    enum PetHonor
    {
        HONOR_LEVEL_0,          //Indomável	0-50
        HONOR_LEVEL_1,          //Cansado	51-150
        HONOR_LEVEL_2,          //Obediente	151-500
        HONOR_LEVEL_3,          //Leal	501-999
        HONOR_LEVEL_COUNT,

        HONOR_POINT_MAX = 999
    };
    // Fome
    enum PetHunger
    {
        HUNGER_LEVEL_0,			//��ʳ
        HUNGER_LEVEL_1,			//����
        HUNGER_LEVEL_2,			//���̶�һ��
        HUNGER_LEVEL_3,
        HUNGER_LEVEL_4,			//���̶ȶ���
        HUNGER_LEVEL_5,
        HUNGER_LEVEL_6,
        HUNGER_LEVEL_7,			//���̶�����
        HUNGER_LEVEL_8,
        HUNGER_LEVEL_9,
        HUNGER_LEVEL_A,
        HUNGER_LEVEL_B,			//���̶��ļ�
        HUNGER_LEVEL_COUNT
    };

    static QString TipoDeMascote(PetType tipo)
    {
        switch (tipo)
        {
        case PET_CLASS_MOUNT: return "Montaria";
        case PET_CLASS_COMBAT: return "Combate";
        case PET_CLASS_FOLLOW: return "Seguir";
        case PET_CLASS_SUMMON: return "Invocação";
        case PET_CLASS_PLANT: return "Planta";
        case PET_CLASS_EVOLUTION: return "Evolução";
        default: return "Desconhecido";
        }
    }

    static QString TimestampToLocalDateTime(qint64 timestamp)
    {
        QDateTime utcDateTime = QDateTime::fromSecsSinceEpoch(timestamp, Qt::UTC);
        QDateTime localDateTime = utcDateTime.toLocalTime();
        return localDateTime.toString(Qt::SystemLocaleShortDate);
    }

    static QString SecondsToTimeFormat(qint32 totalSeconds)
    {
        int hours = totalSeconds / 3600;
        int minutes = (totalSeconds % 3600) / 60;
        int seconds = totalSeconds % 60;

        QTime time(hours, minutes, seconds);

        return time.toString("HH:mm:ss");
    }

    static QString toUtf8(Octets octets)
    {
        QTextCodec *codec = QTextCodec::codecForName("UTF-8");
        //QTextCodec *codec_utf16le = QTextCodec::codecForName("UTF-16LE");
        return codec->fromUnicode(octets.value).mid(0, octets.lenght);
    }

    static QString toASCII(Octets octets)
    {
        QTextCodec *codec = QTextCodec::codecForName("ISO 8859-1");
        return codec->fromUnicode(octets.value).mid(0, octets.lenght);
    }

    static QByteArray toUtf16LE(QByteArray text)
    {
        QTextCodec *codec_utf8 = QTextCodec::codecForName("UTF-8");
        QTextCodec *codec_utf16le = QTextCodec::codecForName("UTF-16LE");
        return codec_utf16le->fromUnicode(codec_utf8->toUnicode(text)).remove(0, 2);
    }

    static Octets fromUtf8(QByteArray text)
    {
        Octets o;
        QTextCodec *codec = QTextCodec::codecForName("UTF-8");
        o.value = codec->fromUnicode(text.data());
        o.lenght = o.value.length();
        return o;
    }

    static Octets emptyOctets()
    {
        Octets o;
        o.value = QByteArray();
        o.lenght = 0;
        return o;
    }

    static Octets base64Octets(QString text)
    {
        Octets o;
        o.value = QByteArray::fromBase64(text.toStdString().c_str());
        o.lenght = o.value.length();
        return o;
    }

    static QIcon iconClass(int id_class, int gender)
    {
        QImage img = QImage(":/Icons/profession.png");
        QImage m = img.copy(0, gender == 0 ? id_class * 14 : (id_class * 14) + (img.height() / 2), 14, 14);
        QIcon icon(QPixmap::fromImage(m));
        return icon;
    }

    static QString ConvertToClientX(double x)
    {
        double cx = 400 + std::trunc(x * 0.1);
        return QString::number(cx);
    }

    static QString ConvertToClientY(double y)
    {
        double cy = std::trunc(y * 0.1);
        return QString::number(cy);
    }

    static QString ConvertToClientZ(double z)
    {
        double cz = 550 + std::trunc(z * 0.1);
        return QString::number(cz);
    }

    static QString ItemDesc(int id, QStringList &itemDesc)
    {
        QString result;

        if (id != 0)
        {
            try
            {
                int index = -1;
                for (int num25 = 0; num25 < itemDesc.size() - 1; num25 += 2)
                {
                    if (itemDesc[num25 + 0].toInt() == id)
                    {
                        index = num25 + 1;
                        break;
                    }
                }

                if (index != -1 && index < itemDesc.size())
                {
                    result = itemDesc[index];
                }
                else
                {
                    result = "";
                }
            }
            catch (const std::exception &)
            {
                result = "";
            }
        }
        else
        {
            result = "";
        }

        return result.replace("\\r", QChar('\n')).replace("\\t", QChar(9));
    }

    static QMap<int, QString> ListItemDesc(QStringList &itemDesc)
    {
        QMap<int, QString> lista;
        QString result;
        QString id;

        try
        {
            int index = -1;

            for (int num25 = 0; num25 < itemDesc.size() - 1; num25 += 2)
            {
                index = num25 + 1;

                if (index < itemDesc.size())
                {
                    result = itemDesc[index];
                    result.replace("\\r", QChar('\n')).replace("\\t", QChar(9));
                    id = itemDesc[num25];
                    lista.insert(id.toInt(), result);
                }
            }
        }
        catch (const std::exception &)
        {
            result = "";
        }

        return lista;
    }

    static QMap<int, QString> SkillNameToList(QStringList skillstr)
    {
        QMap<int, QString> result;

        for (int num25 = 0; num25 < skillstr.length() - 1; num25 += 4)
        {
            try
            {
                QString id = skillstr[num25].remove(QChar('\u0000'));
                int tmpid = id.toInt() / 10;
                QString tmpname = skillstr[num25 + 1].remove(QChar('\u0000'));
                result.insert(tmpid, tmpname);
            }
            catch (QException e)
            {
                qDebug() << "Err SkillNameToList\n" << e.what();
            }
        }

        return result;
    }

    static QMap<int, QString> SkillDescToList(QStringList skillstr)
    {
        QMap<int, QString> result;

        for (int num25 = 0; num25 < skillstr.size() - 1; num25 += 4)
        {
            try
            {
                int tmpid = skillstr[num25].remove(QChar('\u0000')).toInt() / 10;
                QString tmpname = skillstr[num25 + 3].remove(QChar('\u0000'));
                result.insert(tmpid, tmpname);
            }
            catch (QException e)
            {
                qDebug() << "Err SkillDescToList\n" << e.what();
            }
        }

        return result;
    }

    static QString ColorClean(QString line)
    {
        if (line.isEmpty() || line.length() <= 1)
        {
            return QString();
        }

        QStringList blocks = line.split('^');
        if (blocks.length() > 1)
        {
            QString result;
            if (!blocks[0].isNull())
            {
                result += blocks[0];
            }
            for(int i = 1; i < blocks.length(); i++)
            {
                if (!blocks[i].isNull())
                {
                    result += blocks[i].left(6);
                }
            }
            return result;
        }
        else
            return line;
    }

    static QString FormatColorText(QString desc) {
        QString formattedText;
        QStringList blocks = desc.split('^');

        for (int i = 1; i < blocks.size(); ++i) {
            QString block = blocks.at(i);
            if (!block.isEmpty()) {
                QString cor = block.left(6);
                block.remove(0, 6);
                formattedText += "<font color=\"#" + cor + "\">" + block + "</font>";
            }
        }

        formattedText.replace("\\n", "<br>").replace("\\r", "<br>").replace("\n", "<br>").replace("\r", "<br>");

        return formattedText;
    }

    static QColor getColorByID(int id)
    {
        switch (id)
        {
        case 0:
            return QColor(Qt::white);
        case 1:
            return QColor(173, 216, 230); // LightBlue
        case 2:
            return QColor(255, 255, 224); // LightYellow
        case 3:
            return QColor(147, 112, 219); // MediumPurple
        case 4:
            return QColor(255, 215, 0);   // Gold
        case 5:
            return QColor(Qt::white);
        case 6:
            return QColor(Qt::gray);
        case 7:
            return QColor(144, 238, 144); // LightGreen
        default:
            return QColor(Qt::white);
        }
    }

    static QColor getColorFromInteger(int color)
    {
        int red = (color >> 16) & 0xFF;
        int green = (color >> 8) & 0xFF;
        int blue = color & 0xFF;
        QColor retColor(red, green, blue);
        return retColor;
    }

    static QColor FASHION_WORDCOLOR_TO_A3DCOLOR(int color)
    {
        int red = (color & (0x1f << 10)) >> 7;
        int blue = (color & (0x1f << 5)) >> 2;
        int green = (color & 0x1f) << 3;
        QColor retColor(red, green, blue);
        return retColor;
    }

    static QString iconToBase64(const QIcon &icon, int width = 32, int height = 32)
    {
        QPixmap pixmap = icon.pixmap(width, height);
        QByteArray byteArray;
        QBuffer buffer(&byteArray);
        pixmap.save(&buffer, "PNG");  // Pode mudar para outros formatos se desejar, como "JPEG".
        return QString("data:image/png;base64,") + byteArray.toBase64();
    }
};
#endif // UTILS_H
