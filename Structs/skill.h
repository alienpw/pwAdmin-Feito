#ifndef SKILL_H
#define SKILL_H

#include <GNET/octetsstream.h>
#include <QMap>
#include <QString>

class SkillData
{
public:
    int id;
    int progress;
    int level;

    OctetsStream marshal(OctetsStream *os)
    {
        os->operator<<(id);
        os->operator<<(progress);
        os->operator<<(level);
        return *os;
    }

    OctetsStream unmarshal(OctetsStream *os)
    {
        os->operator>>(id);
        os->operator>>(progress);
        os->operator>>(level);
        return *os;
    }
};

class SkillList
{
public:
    int count;
    QList<SkillData> listSkills;

    OctetsStream marshal(OctetsStream *os)
    {
        os->operator<<(listSkills.count());
        for(auto sk : listSkills)
            sk.marshal(os);
        return *os;
    }

    OctetsStream unmarshal(OctetsStream *os)
    {
        os->operator>>(count);
        listSkills.reserve(count);
        for(int i = 0; i < count; i++)
        {
            SkillData sd;
            sd.unmarshal(os);
            listSkills.append(sd);
        }
        return *os;
    }
};

class SkillInfo
{
public:
    int max_level = 0;
    int cls = 0;
    QString icon_name = "";
    int rank = 0;

    SkillInfo(){};
    SkillInfo(int _max_level, int _cls, QString _icon_name, int _rank) :
        max_level(_max_level), cls(_cls), icon_name(_icon_name), rank(_rank) {}

};

class Skills
{
public:
    QMap<int, SkillInfo*> skillInfo;

    void LoadSkills();
};

#endif // SKILL_H
