#ifndef GPETCORRAL_H
#define GPETCORRAL_H

#include "GNET/octetsstream.h"
#include "utils.h"

struct GPetSkill
{
    int id = 0;
    int level = 0;

    GPetSkill(int _id, int _level)
    {
        id = _id;
        level = _level;
    }

    void marshal(OctetsStream &os)
    {
        os<<(id);
        os<<(level);
    }

    void unmarshal(OctetsStream &os)
    {
        os>>(id);
        os>>(level);
    }
};

struct GPetEvoProp
{
    int r_attack = 0;
    int r_defense = 0;
    int r_hp = 0;
    int r_atk_lvl = 0;
    int r_def_lvl = 0;
    int nature = 0;

    void marshal(OctetsStream &os)
    {
        os<<(r_attack);
        os<<(r_defense);
        os<<(r_hp);
        os<<(r_atk_lvl);
        os<<(r_def_lvl);
        os<<(nature);
    }

    void unmarshal(OctetsStream &os)
    {
        os>>(r_attack);
        os>>(r_defense);
        os>>(r_hp);
        os>>(r_atk_lvl);
        os>>(r_def_lvl);
        os>>(nature);
    }
};

struct GPetInfo
{
    int Version = 156;
    int honor_point = 0;
    int hunger = 0;
    int feed_time = 0;
    int pet_tid = 0;
    int pet_vis_tid = 0;
    int pet_egg_tid = 0;
    int pet_class = 0;
    float hp_factor = 0;
    short level = 0;
    short color = 0;
    int exp = 0;
    int skill_point = 0;
    char is_bind = 0;
    char unused = 0;
    Octets name = Octets(QString(""), QString(""));
    GPetSkill skills[8] = {GPetSkill(0,0),GPetSkill(0,0),GPetSkill(0,0),GPetSkill(0,0),GPetSkill(0,0),GPetSkill(0,0),GPetSkill(0,0),GPetSkill(0,0)};
    GPetEvoProp evo_prop = GPetEvoProp();
    int reserved[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    void marshal(OctetsStream &os)
    {
        os<<(honor_point);
        os<<(hunger);
        os<<(feed_time);
        os<<(pet_tid);
        os<<(pet_vis_tid);
        os<<(pet_egg_tid);
        os<<(pet_class);
        os<<(hp_factor);
        os<<(level);
        os<<(color);
        os<<(exp);
        os<<(skill_point);
        os<<(is_bind);
        os<<(unused);
        os.writeShortOctets(name);
        for(int i = 0; i < 8; i++)
            skills[i].marshal(os);
        if(pet_class == Utils::PET_CLASS_EVOLUTION)
            evo_prop.marshal(os);
        for(int i = 0; i < 10; i++)
        {
            os<<(reserved[i]);
        }
    }

    void unmarshal(OctetsStream &os)
    {
        os>>(honor_point);
        os>>(hunger);
        os>>(feed_time);
        os>>(pet_tid);
        os>>(pet_vis_tid);
        os>>(pet_egg_tid);
        os>>(pet_class);
        os>>(hp_factor);
        os>>(level);
        os>>(color);
        os>>(exp);
        os>>(skill_point);
        os>>(is_bind);
        os>>(unused);
        name = os.readShortOctets();
        for(int i = 0; i < 8; i++)
            skills[i].unmarshal(os);
        if(pet_class == Utils::PET_CLASS_EVOLUTION)
            evo_prop.unmarshal(os);
        for(int i = 0; i < 10; i++)
        {
            os>>(reserved[i]);
        }

    }
};

struct GPet
{
public:
    int index;
    Octets data;

    void marshal(OctetsStream &os)
    {
        os<<(index);
        os<<(data);
    }

    void unmarshal(OctetsStream &os)
    {
        os>>(index);
        os>>(data);
    }
};

class GPetCorral
{
public:
    int capacity;
    QVector<GPet> listPet;

    void marshal(OctetsStream &os)
    {
        os<<(capacity);
        os.compact_uint32(listPet.count());
        for(auto pet : listPet)
            pet.marshal(os);
    }

    void unmarshal(OctetsStream &os)
    {
        os>>(capacity);
        qint8 size = os.readByte();
        for(int i = 0; i < size; i++)
        {
            GPet pet;
            pet.unmarshal(os);
            listPet.push_back(pet);
        }
    }
};

#endif // GPETCORRAL_H
