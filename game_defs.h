#ifndef DEFINICOES_H
#define DEFINICOES_H

#include "GNET/octetsstream.h"

using namespace std;

enum PrivilegeType
{
    PRV_TOGGLE_NAMEID = 0,
    PRV_HIDE_BEGOD = 1,
    PRV_ONLINE_ORNOT = 2,
    PRV_CHAT_ORNOT = 3,
    PRV_MOVETO_ROLE = 4,
    PRV_FETCH_ROLE = 5,
    PRV_MOVE_ASWILL = 6,
    PRV_MOVETO_NPC = 7,
    PRV_MOVETO_MAP = 8,
    PRV_ENHANCE_SPEED = 9,
    PRV_FOLLOW = 10,
    PRV_LISTUSER = 11,
    PRV_FORCE_OFFLINE = 100,
    PRV_FORBID_TALK = 101,
    PRV_FORBID_TRADE = 102,
    PRV_FORBID_SELL = 103,
    PRV_BROADCAST = 104,
    PRV_SHUTDOWN_GAMESERVER = 105,
    PRV_SUMMON_MONSTER = 200,
    PRV_DISPEL_SUMMON = 201,
    PRV_PRETEND = 202,
    PRV_GMASTER = 203,
    PRV_DOUBLEEXP = 204,
    PRV_LAMBDA = 205,
    PRV_ACTIVITYMANAGER = 206,
    PRV_NOTRADE = 207,
    PRV_NOAUCTION = 208,
    PRV_NOMAIL = 209,
    PRV_NOFACTION = 210,
    PRV_DOUBLEMONEY = 211,
    PRV_DOUBLEOBJECT = 212,
    PRV_DOUBLESP = 213,
    PRV_NOSELLPOINT = 214,
    PRV_PVP = 215,
};

enum AUTOLOCK_REASON
{
    REASON_PLAYER,
    REASON_GM,
    REASON_IWEB,
};

enum AUTOLOCK_KEY
{
    LOCKTIME_NOW = 1,
    LOCKTIME_NEW = 2,
    LOCKSET_TIME = 3,
    LOCKSET_TIME_GM = 4,
    LOCKTIME_GM = 5,
};

enum FACTION_ROLES
{
    _R_UNMEMBER = 0,
    _R_SYSTEM = 1,
    _R_MASTER = 2,
    _R_VICEMASTER = 3,
    _R_BODYGUARD = 4,
    _R_POINEER = 5,
    _R_MEMBER = 6,
};

enum PLAYER_STATUS
{
    _STATUS_OFFLINE,
    _STATUS_READYLOGOUT,
    _STATUS_SELECTROLE,
    _STATUS_ONLINE,
    _STATUS_READYGAME,
    _STATUS_ONGAME,
    _STATUS_HIDDEN,
    _STATUS_READYLOGIN,
    _STATUS_SWITCH,
};

enum MessageType : uint8_t
{
    Normal = 0,
    Global = 1,
    Grupo = 2,
    Cla = 3,
    Privado = 4,
    Dano = 5,
    Combate = 6,
    Comercio = 7,
    SistemaAmarelo = 8,
    SistemaGM = 9,
    Outros = 10,
    VermelhoInstancia = 11,
    Mensageiro = 12,
    Batalha = 13,
    Nacoes = 14,
    Interservidor = 15,
};

enum Opcode : int
{
    opAutoLockGet = 0x188,
    opAutoLockSet = 0x310,
    opChatBroadcast = 0x78,
    opChatPrivate = 0x60,
    opClearStorehousePasswd = 0xD4A,
    opDeleteRole = 0xBC0,
    opDebugCommand = 0x369,
    opDebugAddCash = 0x209,
    opForbidUser = 0x1F44,
    opGetFactionDetail = 0x1200,
    opGetUserFaction = 0x11FF,
    opQueryUserRoles = 0x1F41,
    opGetMaxOnlineNum = 0x177,
    opGetUserRoles = 0xD49,
    opGMControlGame = 0x17C,
    opGMListOnlineUser = 0x160,
    opGMListOnlineUserRe = 0x161,
    opGMKickoutRole = 0x168,
    opGMRestartServer = 0x166,
    opGMShutupRole = 0x16A,
    opGMGetGameAttri = 0x178,
    opGMSetGameAttri = 0x179,
    opGetRoleData = 0x1F43,
    opPutRoleData = 0x1F42,
    opSysSendMail = 0x1076,
    opGetRole = 0xBBD,
    opDBGetConsumeInfos = 0x180,
    opDBRawRead = 0xBEF,
};

struct GM
{
public:
    int id;
    Octets nome;
    int regras;

    void unmarshal(OctetsStream &os)
    {
        os >> id;
        os >> nome;
        os >> regras;
    }
};

struct GMPlayerInfo
{
public:
    int userid;
    int roleid;
    int linkid;
    uint localsid;
    int gsid;
    char status;
    Octets name;

    void marshal(OctetsStream os)
    {
        os << userid;
        os << roleid;
        os << linkid;
        os << localsid;
        os << gsid;
        os << status;
        os << name;
    }

    void unmarshal(OctetsStream os)
    {
        os >> userid;
        os >> roleid;
        os >> linkid;
        os >> localsid;
        os >> gsid;
        os >> status;
        os >> name;
    }
};

struct User
{
public:
    int id = 0;
    Octets user;
    Octets prompt;
    Octets answer;
    Octets name;
    Octets email;
    Octets mobilenumber;
    int gender;
    Octets birthday;
    Octets ip;
    Octets created;
    Octets isOnline;

    void unmarshal(OctetsStream &os)
    {
        os >> (id);
        os >> (user);
        os >> prompt;
        os >> answer;
        os >> (name);
        os >> (email);
        os >> mobilenumber;
        os >>  gender;
        os >> birthday;
        os >> (ip);
        os >> (created);
        os >> isOnline;
    }
};

struct Memory
{
public:
    int memory_total = 0;
    int memory_used = 0;
    int swap_total = 0;
    int swap_used = 0;

    void unmarshal(OctetsStream &os)
    {
        os >> memory_total;
        os >> memory_used;
        os >> swap_total;
        os >> swap_used;
    }
};

struct Processes
{
public:
    int pid = 0;
    int processCount = 0;
    Octets processName;
    Octets processDir;
    Octets processFileName;
    Octets processParams;
    Octets processStart;
    Octets processKill;
    int serverProcess = 0;
    int startSleep = 0;
    int stopSleep = 0;
    float mem = 0.0f;
    float cpu = 0.0f;

    void unmarshal(OctetsStream &os)
    {
        os >> pid;
        os >> processCount;
        os >> processName;
        os >> processDir;
        os >> processFileName;
        os >> processParams;
        os >> processStart;
        os >> processKill;
        os >> serverProcess;
        os >> startSleep;
        os >> stopSleep;
        os >> mem;
        os >> cpu;
    }
};

struct MapInstances
{
    Octets map_tag;
    Octets map_name;

    void unmarshal(OctetsStream &os)
    {
        os >> map_tag;
        os >> map_name;
    }
};

struct PlayerProperty
{
public:
    int vitality;
    int energy;
    int strength;
    int agility;
    int max_hp;
    int max_mp;
    int hp_gen;
    int mp_gen;
    float walk_speed;
    float run_speed;
    float swim_speed;
    float flight_speed;
    int attack;
    int damage_low;
    int damage_high;
    int attack_speed;
    float attack_range;
    int damage_low0;
    int damage_high0;
    int damage_low1;
    int damage_high1;
    int damage_low2;
    int damage_high2;
    int damage_low3;
    int damage_high3;
    int damage_low4;
    int damage_high4;
    int damage_magic_low;
    int damage_magic_high;
    int resistence0;
    int resistence1;
    int resistence2;
    int resistence3;
    int resistence4;
    int defense;
    int armor;
    int max_ap;

    void marshal(OctetsStream *os)
    {
        os->operator << (vitality);
        os->operator << (energy);
        os->operator << (strength);
        os->operator << (agility);
        os->operator << (max_hp);
        os->operator << (max_mp);
        os->operator << (hp_gen);
        os->operator << (mp_gen);
        os->operator << (walk_speed);
        os->operator << (run_speed);
        os->operator << (swim_speed);
        os->operator << (flight_speed);
        os->operator << (attack);
        os->operator << (damage_low);
        os->operator << (damage_high);
        os->operator << (attack_speed);
        os->operator << (attack_range);
        os->operator << (damage_low0);
        os->operator << (damage_high0);
        os->operator << (damage_low1);
        os->operator << (damage_high1);
        os->operator << (damage_low2);
        os->operator << (damage_high2);
        os->operator << (damage_low3);
        os->operator << (damage_high3);
        os->operator << (damage_low4);
        os->operator << (damage_high4);
        os->operator << (damage_magic_low);
        os->operator << (damage_magic_high);
        os->operator << (resistence0);
        os->operator << (resistence1);
        os->operator << (resistence2);
        os->operator << (resistence3);
        os->operator << (resistence4);
        os->operator << (defense);
        os->operator << (armor);
        os->operator << (max_ap);
    }

    void unmarshal(OctetsStream *os)
    {
        os->operator >> (vitality);
        os->operator >> (energy);
        os->operator >> (strength);
        os->operator >> (agility);
        os->operator >> (max_hp);
        os->operator >> (max_mp);
        os->operator >> (hp_gen);
        os->operator >> (mp_gen);
        os->operator >> (walk_speed);
        os->operator >> (run_speed);
        os->operator >> (swim_speed);
        os->operator >> (flight_speed);
        os->operator >> (attack);
        os->operator >> (damage_low);
        os->operator >> (damage_high);
        os->operator >> (attack_speed);
        os->operator >> (attack_range);
        os->operator >> (damage_low0);
        os->operator >> (damage_high0);
        os->operator >> (damage_low1);
        os->operator >> (damage_high1);
        os->operator >> (damage_low2);
        os->operator >> (damage_high2);
        os->operator >> (damage_low3);
        os->operator >> (damage_high3);
        os->operator >> (damage_low4);
        os->operator >> (damage_high4);
        os->operator >> (damage_magic_low);
        os->operator >> (damage_magic_high);
        os->operator >> (resistence0);
        os->operator >> (resistence1);
        os->operator >> (resistence2);
        os->operator >> (resistence3);
        os->operator >> (resistence4);
        os->operator >> (defense);
        os->operator >> (armor);
        os->operator >> (max_ap);
    }
};

struct meridian_data
{
public:
    int version = 156;
    int meridian_level;
    int lifegate_times;
    int deathgate_times;
    int	free_refine_times;
    int paid_refine_times;
    int player_login_time;
    int continu_login_days;
    int trigrams_map[3];
    // 1.6.5+
    int reserved1;
    int reserved2;
    int reserved3;
    int reserved4;

    void marshal(OctetsStream *os)
    {
        os->operator << (meridian_level);
        os->operator << (lifegate_times);
        os->operator << (deathgate_times);
        os->operator << (free_refine_times);
        os->operator << (paid_refine_times);
        os->operator << (player_login_time);
        os->operator << (continu_login_days);
        os->operator << (trigrams_map[0]);
        os->operator << (trigrams_map[1]);
        os->operator << (trigrams_map[2]);
        if (version > 156)
        {
            os->operator << (reserved1);
            os->operator << (reserved2);
            os->operator << (reserved3);
            os->operator << (reserved4);
        }
    }

    void unmarshal(OctetsStream *os)
    {
        os->operator >> (meridian_level);
        os->operator >> (lifegate_times);
        os->operator >> (deathgate_times);
        os->operator >> (free_refine_times);
        os->operator >> (paid_refine_times);
        os->operator >> (player_login_time);
        os->operator >> (continu_login_days);
        os->operator >> (trigrams_map[0]);
        os->operator >> (trigrams_map[1]);
        os->operator >> (trigrams_map[2]);
        if (version > 156)
        {
            os->operator >> (reserved1);
            os->operator >> (reserved2);
            os->operator >> (reserved3);
            os->operator >> (reserved4);
        }
    }
};

struct reincarnation_record
{
    int level;
    int timestamp;
    int exp;

    void marshal(OctetsStream &os)
    {
        os << level;
        os << timestamp;
        os << exp;
    }
    void unmarshal(OctetsStream &os)
    {
        os >> level;
        os >> timestamp;
        os >> exp;
    }
};

struct reincarnation_data
{
    int tome_exp;
    char tome_active;
    QList<reincarnation_record> records;

    void marshal(OctetsStream &os)
    {
        os << tome_exp;
        os << tome_active;
        os.compact_uint32(records.count());
        if (records.count() > 0)
            foreach(auto r, records)
                r.marshal(os);
    }

    void unmarshal(OctetsStream &os)
    {
        os >> tome_exp;
        os >> tome_active;
        int size = os.uncompact_uint32();
        if (size > 0)
        {
            for (int i = 0; i < size; i++)
            {
                reincarnation_record r;
                r.unmarshal(os);
                records.push_back(r);
            }
        }
    }
};

struct forcedata
{
public:
    int force_id;
    int reputation;
    int contribution;
    int reserved1;
    int reserved2;
    int reserved3;
    int reserved4;
    int reserved5;
    int reserved6;
    int reserved7;

    void marshal(OctetsStream &os, int version)
    {
        os << force_id;
        os << reputation;
        os << contribution;
        if (version == 248)
        {
            os << reserved1;
            os << reserved2;
            os << reserved3;
            os << reserved4;
            os << reserved5;
            os << reserved6;
            os << reserved7;
        }
    }

    void unmarshal(OctetsStream &os, int version)
    {
        os >> force_id;
        os >> reputation;
        os >> contribution;
        if (version == 248)
        {
            os >> reserved1;
            os >> reserved2;
            os >> reserved3;
            os >> reserved4;
            os >> reserved5;
            os >> reserved6;
            os >> reserved7;
        }
    }
};

struct forcedata_list
{
public:
    int cur_force_id;
    size_t count;
    QList<forcedata> list;
    int reserved1;
    int reserved2;
    int reserved3;

    void marshal(OctetsStream &os, int version)
    {
        os << cur_force_id;
        os.compact_uint32(list.count());
        if (list.count() > 0)
        {
            foreach(auto l, list)
                l.marshal(os, version);
        }

        if (version == 248)
        {
            os << reserved1;
            os << reserved2;
            os << reserved3;
        }
    }

    void unmarshal(OctetsStream &os, int version)
    {
        os >> cur_force_id;
        auto size = os.uncompact_uint32();
        if (size > 0)
        {
            for (int i = 0; i < size; i++)
            {
                forcedata dt;
                dt.unmarshal(os, version);
                list.push_back(dt);
            }
        }
        if (version == 248)
        {
            os >> reserved1;
            os >> reserved2;
            os >> reserved3;
        }
    }
};

struct realm_data
{
    int level;
    int exp;
    int reserved1;
    int reserved2;

    void marshal(OctetsStream &os)
    {
        os << level;
        os << exp;
        os << reserved1;
        os << reserved2;
    }

    void unmarshal(OctetsStream &os)
    {
        os >> level;
        os >> exp;
        os >> reserved1;
        os >> reserved2;
    }
};


struct cooldown_data
{
public:
    int id;
    int timestamp;
    int interval;
    int time;

    void marshal(OctetsStream *os)
    {
        os->operator<<(id);
        os->operator<<(timestamp);
        os->operator<<(interval);
        os->operator<<(time);
    }

    void unmarshal(OctetsStream *os)
    {
        os->operator>>(id);
        os->operator>>(timestamp);
        os->operator>>(interval);
        os->operator>>(time);
    }
};

enum
{
    GROLE_STATUS_EXTRAPROP_TOUCH_HALF_TRADE = 0,
    GROLE_STATUS_EXTRAPROP_DAILY_SIGN_IN,
    GROLE_STATUS_EXTRAPROP_GIFTCARD_HALF_REDEEM,
    GROLE_STATUS_EXTRAPROP_LEADERSHIP,
    GROLE_STATUS_EXTRAPROP_GENERALCARD_COLLECTION,
    GROLE_STATUS_EXTRAPROP_FATERING,
    GROLE_STATUS_EXTRAPROP_CLOCK_DATA,
    GROLE_STATUS_EXTRAPROP_RAND_MALL_DATA,
    GROLE_STATUS_EXTRAPROP_WORLD_CONTRIBUTION,
    GROLE_STATUS_EXTRAPROP_ASTROLABE_EXTERN,

    GROLE_STATUS_EXTRAPROP_COUNT,
};

struct touch_trade
{
public:
    int64_t  sn = 0;
    char     state = 0;
    uint cost = 0;
    uint lots = 0;
    uint itemcount = 0;
    int 	 itemtype = 0;
    int		 itemexpire = 0;

    void marshal(OctetsStream os)
    {
        os << sn;
        os << state;
        os << cost;
        os << lots;
        os << itemcount;
        os << itemtype;
        os << itemexpire;
    }

    void unmarshal(OctetsStream os)
    {
        os >> sn;
        os >> state;
        os >> cost;
        os >> lots;
        os >> itemcount;
        os >> itemtype;
        os >> itemexpire;
    }
};

struct daily_signin
{
public:
    int update_time = 0;
    int month_calendar = 0;
    int curr_year_data = 0;
    int last_year_data = 0;
    char awarded_times = 0;
    char late_signin_times = 0;
    short reserved = 0;

    void marshal(OctetsStream os)
    {
        os << update_time;
        os << month_calendar;
        os << curr_year_data;
        os << last_year_data;
        os << awarded_times;
        os << late_signin_times;
        os << reserved;
    }

    void unmarshal(OctetsStream os)
    {
        os >> update_time;
        os >> month_calendar;
        os >> curr_year_data;
        os >> last_year_data;
        os >> awarded_times;
        os >> late_signin_times;
        os >> reserved;
    }
};

struct giftcard_redeem
{
public:
    char	state = 0;
    int		type = 0;
    int		parenttype = 0;
    char	cardnumber[20];

    void marshal(OctetsStream os)
    {
        os << state;
        os << type;
        os << parenttype;
        for(int i = 0; i < 20; i++)
            os << cardnumber[i];
    }

    void unmarshal(OctetsStream os)
    {
        os >> state;
        os >> type;
        os >> parenttype;
        for(int i = 0; i < 20; i++)
            os >> cardnumber[i];
    }
};

struct world_contribution
{
public:
    int contrib = 0;
    int cost = 0;

    void marshal(OctetsStream os)
    {
        os << contrib;
        os << cost;
    }

    void unmarshal(OctetsStream os)
    {
        os >> contrib;
        os >> cost;
    }
};

struct astrolabe_extern
{
public:
    unsigned char level = 0;
    int  exp = 0;

    void marshal(OctetsStream os)
    {
        os << level;
        os << exp;
    }

    void unmarshal(OctetsStream os)
    {
        os >> level;
        os >> exp;
    }
};



struct title_data
{
public:
    ushort current_title;
    QList<int> delivered_titles;
    QMap<ushort, int> expire_titles;

    void marshal(OctetsStream os)
    {
        os << current_title;
        os << (int)delivered_titles.count();
        if (delivered_titles.count() > 0)
        {
            foreach(int dt, delivered_titles)
                os << dt;
        }
        os << (short)expire_titles.count();
        if (expire_titles.count() > 0)
        {
            for(auto it = expire_titles.begin(); it != expire_titles.end(); it++)
            {
                os << it.key();
                os << it.value();
            }
        }
    }

    void unmarshal(OctetsStream os)
    {
        os >> current_title;
        int dt_size;
        os >> dt_size;
        if (dt_size > 0)
        {
            for(int i = 0; i < dt_size; i++)
            {
                int tmp_dt;
                os >> tmp_dt;
                delivered_titles.push_back(tmp_dt);
            }
        }
        short et_size;
        os >> et_size;
        if (et_size > 0)
        {
            for(int i = 0; i < et_size; i++)
            {
                short id;
                int time;
                os >> id;
                os >> time;
                expire_titles[id] = time;
            }
        }
    }
};

#endif // DEFINICOES_H
