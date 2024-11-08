#ifndef ITEM_H
#define ITEM_H

#include <algorithm>
#include <vector>
#include <cstdint>
#include <GNET/octetsstream.h>
#include "fixedmsg.h"
#include <QDebug>

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
enum
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

//	Proc-type
enum
{
    PROC_DROPWHENDIE	= 0x0001,	//	����ʱ�Ƿ�����
    PROC_DROPPABLE		= 0x0002,	//	�Ƿ��������ڵ���
    PROC_SELLABLE		= 0x0004,	//	�Ƿ���������NPC
    PROC_LOG			= 0x0008,	//	��¼��ϸLog��Ϣ		��������ʾ

    PROC_TRADEABLE		= 0x0010,	//	�Ƿ��������Ҽ佻��
    PROC_TASK			= 0x0020,	//	�Ƿ�����������Ʒ	��������ʾ
    PROC_BIND			= 0x0040,	//	װ��������			��������ʾ
    PROC_UNBINDABLE		= 0x0080,	//  �ɽ���				��������ʾ

    PROC_DISAPEAR		= 0x0100,	//  �뿪������ʧ
    PROC_USE			= 0x0200,	//  ʰȡʹ��
    PROC_DEADDROP		= 0x0400,	//  �����ض�����
    PROC_OFFLINE		= 0x0800,	//  ���ߵ���
    PROC_UNREPAIRABLE	= 0x1000,	//  ��������
    PROC_DESTROYING		= 0x2000,	//  ��������
    PROC_NO_USER_TRASH	= 0x4000,	//  �޷������˺Ųֿ�
    PROC_BINDING		= 0x8000,	//  ���˺�һ
    PROC_CAN_WEBTRADE = 0x10000,	//	Ѱ�����ɽ���
};

enum WEAPON_TYPE
{
    WEAPON_TYPE_MELEE = 0,
    WEAPON_TYPE_RANGE = 1,
    WEAPON_TYPE_MELEE_ASN = 2,
};

enum
{
    ADDON_SOUL = 0x2000,
    ADDON_EMBEDDED	= 0x8000,
    ADDON_SET_ADDON	= 0x10000,	//δʹ��
    ADDON_ENGRAVED	= 0x20000,
    ADDON_INHERITED   = 0x40000,
    ADDON_PURE_TYPE_MASK = ~(ADDON_ENGRAVED | ADDON_SET_ADDON | ADDON_EMBEDDED | ADDON_INHERITED | 0x6000),
};

enum RESISTANCE
{
    METAL,
    WOOD,
    WATER,
    FIRE,
    EARTH,
};

enum
{
    MAGICCLASS_GOLD	= 0,
    MAGICCLASS_WOOD,
    MAGICCLASS_WATER,
    MAGICCLASS_FIRE,
    MAGICCLASS_EARTH,
};

struct prerequisition
{
    short level;
    short race;
    short strength;
    short vitality;
    short agility;
    short energy;
    int durability;
    int max_durability;

    void marshal(OctetsStream &os)
    {
        os << level;
        os << race;
        os << strength;
        os << vitality;
        os << agility;
        os << energy;
        os << durability;
        os << max_durability;
    }

    void unmarshal(OctetsStream &os)
    {
        os >> level;
        os >> race;
        os >> strength;
        os >> vitality;
        os >> agility;
        os >> energy;
        os >> durability;
        os >> max_durability;
    }
};

struct made_tag_t
{
    char tag_type;
    Octets tag_content;

    void marshal(OctetsStream &os)
    {
        os << tag_type;
        os << tag_content;
    }

    void unmarshal(OctetsStream &os)
    {
        os >> tag_type;
        os >> tag_content;
    }
};

struct addon_data
{
    int propNum = 0;
    int paramNum = 0;
    int id_addon = 0;
    bool isSoul = false;
    bool isEmbedded = false;
    bool isEngraved = false;
    bool isInherited = false;
    int id = 0;
    int arg[3] = {0, 0, 0};

    void marshal(OctetsStream &os)
    {
        id = SetArgCount(id_addon, paramNum);
        //if (isSoul)
        //   id += ADDON_SOUL;
        if (isEmbedded)
            id += ADDON_EMBEDDED;
        if (isEngraved)
            id += ADDON_ENGRAVED;
        if (isInherited)
            id += ADDON_INHERITED;
        os << id;
        switch (paramNum)
        {
        case 0: break;
        case 1:
            os << arg[0];
            break;
        case 2:
            os << arg[0];
            os << arg[1];
            break;
        case 3:
            os << arg[0];
            os << arg[1];
            os << arg[2];
            break;
        }
    }

    void unmarshal(OctetsStream &os)
    {
        os >> id;
        paramNum = (id & 0x6000)>>13;
        switch (paramNum)
        {
        case 0: break;
        case 1:
            os >> arg[0];
            break;
        case 2:
            os >> arg[0];
            os >> arg[1];
            break;
        case 3:
            os >> arg[0];
            os >> arg[1];
            os >> arg[2];
            break;
        }
        id_addon = id & 0x1FFF;
        //isSoul = id & ADDON_SOUL;
        isEmbedded = id & ADDON_EMBEDDED;
        isEngraved = id & ADDON_ENGRAVED;
        isInherited = id & ADDON_INHERITED;
    }

    static inline bool IsAddOnSoul(const addon_data & data)
    {
        return data.id & ADDON_SOUL;
    }
    static inline bool IsAddOnEmbedded(const addon_data & data)
    {
        return data.id & ADDON_EMBEDDED;
    }
    static inline bool IsAddOnEngraved(const addon_data & data)
    {
        return data.id & ADDON_ENGRAVED;
    }
    static inline bool IsAddOnInherited(const addon_data & data)
    {
        return data.id & ADDON_INHERITED;
    }
    static inline int GetArgCount(int id)
    {
        return (id & 0x6000)>>13;
    }
    static inline int SetArgCount(int id, int numParams)
    {
        return (numParams << 13) + id;
    }
    static inline int GetAddonID(int id)
    {
        return id & 0x1FFF;
    }
};

struct addon_soul_data
{
    qint8 sacred_activated = 0;
    qint8 lunar_activated = 0;
    int sacred_id = 0;
    qint8 sacred_level = 0;
    short sacred_type = 0;
    int sacred_addon_count = 0;
    QList<addon_data> sacred_addons;
    int lunar_id = 0;
    qint8 lunar_level = 0;
    qint8 lunar_type = 0;
    int unk1 = 0;
    qint8 bloqueado = 0;
    QList<qint8> estrelas = {0,0,0,0,0}; // 5
    QList<qint8> unk2 = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; // 15
    int lunar_addon_count = 0;
    QList<addon_data> lunar_addons;

    void marshal(OctetsStream &os)
    {
        os << sacred_activated;
        os << lunar_activated;
        if (!sacred_activated) return;
        os << sacred_id;
        os << sacred_level;
        os << sacred_type;
        os << sacred_addons.count();
        if (sacred_addons.count() > 0)
            foreach(auto s, sacred_addons)
                s.marshal(os);
        if (!lunar_activated) return;
        os << lunar_id;
        os << lunar_level;
        os << lunar_type;
        os << unk1;
        os << bloqueado;
        foreach(auto e, estrelas)
            os << e;
        foreach(auto u, unk2)
            os << u;
        os << lunar_addons.count();
        if (lunar_addons.count() > 0)
            foreach(auto l, lunar_addons)
                l.marshal(os);
    }

    void unmarshal(OctetsStream &os)
    {
        os >> sacred_activated;
        os >> lunar_activated;
        if (!sacred_activated) return;
        os >> sacred_id;
        os >> sacred_level;
        os >> sacred_type;
        os >> sacred_addon_count;
        if (sacred_addon_count > 0)
        {
            for (int i = 0; i < sacred_addon_count; i++)
            {
                addon_data data;
                data.unmarshal(os);
                sacred_addons.push_back(data);
            }
        }
        if (!lunar_activated) return;
        os >> lunar_id;
        os >> lunar_level;
        os >> lunar_type;
        os >> unk1;
        os >> bloqueado;
        estrelas.reserve(5);
        for (int i = 0; i < 5; i++)
        {
            os >> estrelas[i];
        }
        unk2.reserve(15);
        for (int i = 0; i < 15; i++)
        {
            os >> unk2[i];
        }
        os >> lunar_addon_count;
        if (lunar_addon_count > 0)
        {
            for (int i = 0; i < lunar_addon_count; i++)
            {
                addon_data data;
                data.unmarshal(os);
                lunar_addons.push_back(data);
            }
        }
    }
};

struct item_base
{
    prerequisition prereq;
    short item_type;
    made_tag_t made_tag;
    short slot_count;
    short slot_flag;
    QList<int> slot_list;
    QList<addon_data> addons;
    addon_soul_data addons_soul;

    void SetBase(item_base &base)
    {
        this->operator=(base);
    }
};

struct weapon_essence : public item_base
{
    short weapon_type;
    short weapon_delay;
    int weapon_class;
    int weapon_level;
    int require_projectile;
    int damage_low;
    int damage_high;
    int magic_damage_low;
    int magic_damage_high;
    int attack_speed;
    float attack_range;
    float attack_short_range;

    void marshal(OctetsStream &os, int Version = 155)
    {
        prereq.marshal(os);
        os << item_type;
        made_tag.marshal(os);

        os << weapon_type;
        os << weapon_delay;
        os << weapon_class;
        os << weapon_level;
        os << require_projectile;
        os << damage_low;
        os << damage_high;
        os << magic_damage_low;
        os << magic_damage_high;
        os << attack_speed;
        os << attack_range;
        os << attack_short_range;

        os << slot_count;
        os << slot_flag;
        if (slot_list.count() > 0)
            slot_list.reserve(slot_count);
        for (int i = 0; i < slot_list.count(); i++)
            os << slot_list[i];
        os << addons.count();
        if (addons.count() > 0)
            foreach (addon_data addon , addons)
                addon.marshal(os);
    }

    void unmarshal(OctetsStream &os, int Version = 155)
    {
        prereq.unmarshal(os);
        os >> item_type;
        made_tag.unmarshal(os);

        os >> weapon_type;
        os >> weapon_delay;
        os >> weapon_class;
        os >> weapon_level;
        os >> require_projectile;
        os >> damage_low;
        os >> damage_high;
        os >> magic_damage_low;
        os >> magic_damage_high;
        os >> attack_speed;
        os >> attack_range;
        os >> attack_short_range;

        os >> slot_count;
        os >> slot_flag;

        if (slot_count > 0)
        {
            for (int i = 0; i < slot_count; i++)
            {
                int slotid = 0;
                os >> slotid;
                slot_list.push_back(slotid);
            }
        }
        int addons_count;
        os >> addons_count;
        if (addons_count > 0)
        {
            for (int i = 0; i < addons_count; i++)
            {
                addon_data addon;
                addon.unmarshal(os);
                addons.push_back(addon);
            }
        }
    }
};

struct armor_essence : public item_base
{
    int defense;
    int armor;
    int mp_enhance;
    int hp_enhance;
    int resistance[5];

    void marshal(OctetsStream &os)
    {
        prereq.marshal(os);
        os << item_type;
        made_tag.marshal(os);

        os << defense;
        os << armor;
        os << mp_enhance;
        os << hp_enhance;
        os << resistance[0];
        os << resistance[1];
        os << resistance[2];
        os << resistance[3];
        os << resistance[4];

        os << slot_count;
        os << slot_flag;
        if (slot_list.count() > 0)
            slot_list.reserve(slot_count);
        for (int i = 0; i < slot_list.count(); i++)
            os << slot_list[i];
        os << addons.count();
        if (addons.count() > 0)
            foreach (addon_data addon , addons)
                addon.marshal(os);
    }

    void unmarshal(OctetsStream &os)
    {
        prereq.unmarshal(os);
        os >> item_type;
        made_tag.unmarshal(os);

        os >> defense;
        os >> armor;
        os >> mp_enhance;
        os >> hp_enhance;
        os >> resistance[0];
        os >> resistance[1];
        os >> resistance[2];
        os >> resistance[3];
        os >> resistance[4];

        os >> slot_count;
        os >> slot_flag;

        if (slot_count > 0)
        {
            for (int i = 0; i < slot_count; i++)
            {
                int slotid = 0;
                os >> slotid;
                slot_list.push_back(slotid);
            }
        }
        int addons_count;
        os >> addons_count;
        if (addons_count > 0)
        {
            for (int i = 0; i < addons_count; i++)
            {
                addon_data addon;
                addon.unmarshal(os);
                addons.push_back(addon);
            }
        }
    }

    void SetNewArmor(armor_essence &base)
    {
        this->operator=(base);
    }
};

struct decoration_essence : public item_base
{
    int damage;
    int magic_damage;
    int defense;
    int armor;
    int resistance[5];

    void marshal(OctetsStream &os)
    {
        prereq.marshal(os);
        os << item_type;
        made_tag.marshal(os);

        os << damage;
        os << magic_damage;
        os << defense;
        os << armor;
        os << resistance[0];
        os << resistance[1];
        os << resistance[2];
        os << resistance[3];
        os << resistance[4];

        os << slot_count;
        os << slot_flag;
        if (slot_list.count() > 0)
            slot_list.reserve(slot_count);
        for (int i = 0; i < slot_list.count(); i++)
            os << slot_list[i];
        os << addons.count();
        if (addons.count() > 0)
            foreach (addon_data addon , addons)
                addon.marshal(os);
    }

    void unmarshal(OctetsStream &os)
    {
        prereq.unmarshal(os);
        os >> item_type;
        made_tag.unmarshal(os);

        os >> damage;
        os >> magic_damage;
        os >> defense;
        os >> armor;
        os >> resistance[0];
        os >> resistance[1];
        os >> resistance[2];
        os >> resistance[3];
        os >> resistance[4];

        os >> slot_count;
        os >> slot_flag;

        if (slot_count > 0)
        {
            for (int i = 0; i < slot_count; i++)
            {
                int slotid = 0;
                os >> slotid;
                slot_list.push_back(slotid);
            }
        }
        int addons_count;
        os >> addons_count;
        if (addons_count > 0)
        {
            for (int i = 0; i < addons_count; i++)
            {
                addon_data addon;
                addon.unmarshal(os);
                addons.push_back(addon);
            }
        }
    }
};

struct amulet_essence
{
    int point;
    float trigger_percent;

    void marshal(OctetsStream &os)
    {
        os << point;
        os << trigger_percent;
    }

    void unmarshal(OctetsStream &os)
    {
        os >> point;
        os >> trigger_percent;
    }
};

struct bible_item
{
    QVector<addon_data> _extra_addon;

    void marshal(OctetsStream &os)
    {
        os << _extra_addon.size();
        for(int i = 0; i < _extra_addon.size(); i++)
            _extra_addon[i].marshal(os);
    }

    void unmarshal(OctetsStream &os)
    {
        short size;
        os >> size;
        for (int i = 0; i < size; i++)
        {
            addon_data data;
            data.unmarshal(os);
            _extra_addon.append(data);
        }
    }
};

struct elf_essence			//������Ҫ���������ݿ��е�����
{
    unsigned int exp;
    short level;

    short total_attribute;	//�������������Ե�������������װ�����ӵļ������Գ�ʼֵ
    short strength;			//�ɼ����Ե�������������ֵ��������װ�����ӵļ������Գ�ʼֵ
    short agility;
    short vitality;
    short energy;

    short total_genius;		//�츳�㣬������װ�����ӵ�
    short genius[5];			//��ľˮ����0-4

    short refine_level;
    int stamina; 			//����
    int status_value;		//0: ��ȫ״̬��g_timer.get_systime():ת��״̬��-1:�ɽ���״̬
};

struct elf_extend_prop
{
    //���¿ɴ�ģ���л�ȡ���������������ɣ����豣�������ݿ�
    float exp_factor;
    int max_rand_prop;		//����ʱ������ȡ���Ե�����������ֵ
    int average_rand_prop;	//����ʱ������ȡ���Ե�������ƽ��ֵ

    short cur_strength;			//����װ�����ӵļ������Գ�ʼֵ
    short cur_agility;
    short cur_vitality;
    short cur_energy;

    short cur_genius[5];			//����װ�����ӵģ���ľˮ����0-4

    unsigned int all_equip_mask; //��ǰ��װ����ʲô����װ�� bit 1- equip 0-none��Ӧ��ֻʹ��bit 0--3
    int cur_skill_slot;		//��ǰ��ѧ��������ֵ
    int secure_status;			//0 ��ȫ״̬  elf_item::enum{}
};

struct elf_skill_data		//���������ݿ��м�������
{
    unsigned short id;
    short level;
};

struct elf_item_essence
{
    elf_essence ess;
    QVector<int> equipvect;
    QVector<elf_skill_data> skillvect;
    elf_extend_prop prop;
    int stamina_offset;
};

struct flysword_essence
{
    int cur_time;
    int max_time;
    short require_level;
    char level;
    char improve_level;
    int require_class;
    size_t time_per_element;
    float speed_increase;		//��ͨ�����ٶ�
    float speed_increase2;		//���ٷ����ٶ�
    made_tag_t made;
    short crc;

    void marshal(OctetsStream &os)
    {
        os << cur_time;
        os << max_time;
        os << require_level;
        os << level;
        os << improve_level;
        os << require_class;
        os << time_per_element;
        os << speed_increase;
        os << speed_increase2;
        made.marshal(os);
        os << crc;
    }

    void unmarshal(OctetsStream &os)
    {
        os >> cur_time;
        os >> max_time;
        os >> require_level;
        os >> level;
        os >> improve_level;
        os >> require_class;
        os >> time_per_element;
        os >> speed_increase;
        os >> speed_increase2;
        made.unmarshal(os);
        os >> crc;
    }
};

struct angel_wing_essence
{
    int require_level;
    size_t mp_launch;
    size_t mp_per_second;
    float speed_increase;
};

struct force_ticket_essence
{
    int require_force;
    int repu_total;
    int repu_inc_ratio;
};

struct generalcard_essence
{
    int type;					//����,��װ��λ������Ӧ,�ƾ�,����,����,����,����,����
    int rank;					//Ʒ��,C,B,A,S,S+
    int require_level;			//�����ȼ�
    int require_leadership;		//����ͳ����
    int max_level;				//�����ɳ��ȼ�
    int level;					//�ɳ��ȼ�
    int exp;					//�ɳ�����
    int rebirth_times;			//ת������
};

struct generalcard_extend
{
    int max_hp;
    int damage_low;
    int damage_high;
    int damage_magic_low;
    int damage_magic_high;
    int defense;
    int resistance[5];
    int vigour;
};

struct generalcard_item
{
    generalcard_essence _ess;				//��Ҫ���̵ı�������
    generalcard_extend _extend;
    QVector<addon_data> _extra_addon;
};

struct pet_data
{
    enum
    {
        MAX_PET_SKILL_COUNT = 8,
        MAX_NAME_LEN = 16,
    };

    int honor_point;	//�øж�	�ᾭ���仯
    int hunger_gauge;	//������	�ᾭ���仯
    int feed_period;	//�ϴ�ι�������ڵļ�ʱʱ��
    int pet_tid;		//������ģ��ID
    int pet_vis_tid;	//�����Ŀɼ�ID������Ϊ0������ʾ�������ɼ�ID��
    int pet_egg_tid;	//���ﵰ��ID
    int pet_class;		//�������� ս�裬���裬���ͳ�
    float hp_factor;	//Ѫ���������������ջ�ʱʹ�ã� 0��Ϊ����
    short level;		//���Ｖ��
    unsigned short color;   //������ɫ������λΪ1��ʾ��Ч��Ŀǰ����������Ч
    int exp;		//���ﵱǰ����
    int skill_point;	//ʣ�༼�ܵ�
    char is_bind;		//�Ƿ����ڰ���״̬,������һ��mask 0x01���� 0x02��Ѱ��������
    char unused;
    Octets name;
    struct __skills
    {
        int skill;
        int level;

        void marshal(OctetsStream &os)
        {
            os << skill;
            os << level;
        }

        void unmarshal(OctetsStream &os)
        {
            os >> skill;
            os >> level;
        }
    } skills[MAX_PET_SKILL_COUNT];
    struct __evo_prop
    {
        int r_attack;
        int r_defense;
        int r_hp;
        int r_atk_lvl;
        int r_def_lvl;
        int nature;

        void marshal(OctetsStream &os)
        {
            os << r_attack;
            os << r_defense;
            os << r_hp;
            os << r_atk_lvl;
            os << r_def_lvl;
            os << nature;
        }

        void unmarshal(OctetsStream &os)
        {
            os >> r_attack;
            os >> r_defense;
            os >> r_hp;
            os >> r_atk_lvl;
            os >> r_def_lvl;
            os >> nature;
        }
    } evo_prop;
    int reserved[10];//δ��
    enum
    {
        PET_CLASS_MOUNT,		//����
        PET_CLASS_COMBAT,		//ս������
        PET_CLASS_FOLLOW,		//��������
        PET_CLASS_SUMMON,		//�ٻ���
        PET_CLASS_PLANT,		//ֲ��
        PET_CLASS_EVOLUTION,	//��������
        PET_CLASS_MAX,
    };

    enum
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

    enum
    {
        FEED_TIME_UNIT = 300,		//300	ι����ʱ�䵥λ
    };

    enum
    {
        HONER_LEVEL_0,			//Ұ����ѱ	0-50
        HONER_LEVEL_1,			//�����޳�	51-150
        HONER_LEVEL_2,			//��������	151-500
        HONER_LEVEL_3,			//���Ĺ���	501-999
        HONOR_LEVEL_COUNT,

        HONOR_POINT_MAX	= 999
    };

    void marshal(OctetsStream &os)
    {
        os << honor_point;
        os << hunger_gauge;
        os << feed_period;
        os << pet_tid;
        os << pet_vis_tid;
        os << pet_egg_tid;
        os << pet_class;
        os << hp_factor;
        os << level;
        os << color;
        os << exp;
        os << skill_point;
        os << is_bind;
        os << unused;
        os << name;
        skills->marshal(os);
        evo_prop.marshal(os);
    }

    void unmarshal(OctetsStream &os)
    {
        os << honor_point;
        os << hunger_gauge;
        os << feed_period;
        os << pet_tid;
        os << pet_vis_tid;
        os << pet_egg_tid;
        os << pet_class;
        os << hp_factor;
        os << level;
        os << color;
        os << exp;
        os << skill_point;
        os << is_bind;
        os << unused;
        os << name;
        skills->marshal(os);
        evo_prop.marshal(os);
    }
};

struct pet_food
{
    int food_type;
    int honor;
};

struct player_property
{
    struct _data{
        int id;
        int hp;
        int mp;
        int damage_low;			//����damage
        int damage_high;		//��������damage
        int damage_magic_low;	//ħ�����͹�����
        int damage_magic_high;	//ħ�����߹�����
        int defense;			//������
        int resistance[5];		//ħ������
        int attack;				//������ attack rate
        int armor;				//�����ʣ�װ�׵ȼ���
        int attack_speed;		//����ʱ������ ��tickΪ��λ
        float run_speed;		//�����ٶ� ��λ  m/s
        int attack_degree;		//�����ȼ�
        int defend_degree;		//�����ȼ�
        int crit_rate;			//����
        int damage_reduce;		//�˺������ٷֱȣ�������
        int prayspeed;			//�����ٶ����Ӱٷֱ�,������
        int	crit_damage_bonus;	//�����ı����˺��ӳ�
        int invisible_degree;	//�����ȼ�
        int anti_invisible_degree;//�����ȼ�
        int vigour;				//����ֵ
    }data;
    struct _self_data
    {
        int damage_reduce;
        int prayspeed;
    }self_data;

    void marshal(OctetsStream &os)
    {
        os << data.id;
        os << data.hp;
        os << data.mp;
        os << data.damage_low;
        os << data.damage_high;
        os << data.damage_magic_low;
        os << data.damage_magic_high;
        os << data.defense;
        os << data.resistance[0];
        os << data.resistance[1];
        os << data.resistance[2];
        os << data.resistance[3];
        os << data.resistance[4];
        os << data.attack;
        os << data.armor;
        os << data.attack_speed;
        os << data.run_speed;
        os << data.attack_degree;
        os << data.defend_degree;
        os << data.crit_rate;
        os << data.damage_reduce;
        os << data.prayspeed;
        os << data.crit_damage_bonus;
        os << data.invisible_degree;
        os << data.anti_invisible_degree;
        os << data.vigour;
        os << self_data.damage_reduce;
        os << self_data.prayspeed;
    }

    void unmarshal(OctetsStream &os)
    {
        os >> data.id;
        os >> data.hp;
        os >> data.mp;
        os >> data.damage_low;
        os >> data.damage_high;
        os >> data.damage_magic_low;
        os >> data.damage_magic_high;
        os >> data.defense;
        os >> data.resistance[0];
        os >> data.resistance[1];
        os >> data.resistance[2];
        os >> data.resistance[3];
        os >> data.resistance[4];
        os >> data.attack;
        os >> data.armor;
        os >> data.attack_speed;
        os >> data.run_speed;
        os >> data.attack_degree;
        os >> data.defend_degree;
        os >> data.crit_rate;
        os >> data.damage_reduce;
        os >> data.prayspeed;
        os >> data.crit_damage_bonus;
        os >> data.invisible_degree;
        os >> data.anti_invisible_degree;
        os >> data.vigour;
        os >> self_data.damage_reduce;
        os >> self_data.prayspeed;
    }
};

struct EQUIPMENT_ADDON
{
    unsigned int id;
    QString	name[32];
    int	num_params;
    int	param1;
    int	param2;
    int	param3;

};

struct socket_qihun
{
    int id;
    char _level;
    char _moon_phase_level;
    char _lock;
    QList<addon_data> _total_addon;

    void marshal(OctetsStream &os)
    {
        os << id;
        os << _level;
        os << _moon_phase_level;
        os << _lock;
        os << _total_addon.count();
        if (_total_addon.count() > 0)
            foreach (addon_data addon , _total_addon)
                addon.marshal(os);
    }

    void unmarshal(OctetsStream &os)
    {
        os >> id;
        os >> _level;
        os >> _moon_phase_level;
        os >> _lock;
        int addons_count;
        os >> addons_count;
        if (addons_count > 0)
        {
            for (int i = 0; i < addons_count; i++)
            {
                addon_data addon;
                addon.unmarshal(os);
                _total_addon.push_back(addon);
            }
        }
    }
};

struct socket_qiling
{
    int id;
    char _level;
    char _moon_type;
    int _exp;
    char _lock;
    char _moon_type_level[10];
    char _moon_type_num[10];
    QList<addon_data> _total_addon;

    void marshal(OctetsStream &os)
    {
        os << _total_addon.count();
        if (_total_addon.count() > 0)
            foreach (addon_data addon , _total_addon)
                addon.marshal(os);
    }

    void unmarshal(OctetsStream &os)
    {
        int addons_count;
        os >> addons_count;
        if (addons_count > 0)
        {
            for (int i = 0; i < addons_count; i++)
            {
                addon_data addon;
                addon.unmarshal(os);
                _total_addon.push_back(addon);
            }
        }
    }
};

/* 40905 */
struct new_armor_item : armor_essence
{
    char b_qihun, b_qiling;
    socket_qihun _qihun;
    socket_qiling _qiling;
    addon_data _active_addon_new;

    void marshal(OctetsStream &os)
    {
        prereq.marshal(os);
        os << item_type;
        made_tag.marshal(os);

        os << defense;
        os << armor;
        os << mp_enhance;
        os << hp_enhance;
        os << resistance[0];
        os << resistance[1];
        os << resistance[2];
        os << resistance[3];
        os << resistance[4];

        os << slot_count;
        os << slot_flag;
        if (slot_list.count() > 0)
            slot_list.reserve(slot_count);
        for (int i = 0; i < slot_list.count(); i++)
            os << slot_list[i];
        os << 0;
        os << b_qihun;
        os << b_qiling;
        if (b_qihun)
            _qihun.marshal(os);
        if (b_qiling)
            _qiling.marshal(os);
    }

    void unmarshal(OctetsStream &os)
    {
        prereq.unmarshal(os);
        os >> item_type;
        made_tag.unmarshal(os);

        os >> defense;
        os >> armor;
        os >> mp_enhance;
        os >> hp_enhance;
        os >> resistance[0];
        os >> resistance[1];
        os >> resistance[2];
        os >> resistance[3];
        os >> resistance[4];

        os >> slot_count;
        os >> slot_flag;

        if (slot_count > 0)
        {
            for (int i = 0; i < slot_count; i++)
            {
                int slotid = 0;
                os >> slotid;
                slot_list.push_back(slotid);
            }
        }
        int addons_count;
        os >> addons_count;

        os >> b_qihun;
        os >> b_qiling;
        if (b_qihun)
            _qihun.unmarshal(os);
        if (b_qiling)
            _qiling.unmarshal(os);
    }
};

#endif // ITEM_H
