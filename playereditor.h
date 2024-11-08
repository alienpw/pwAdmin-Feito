#ifndef PLAYEREDITOR_H
#define PLAYEREDITOR_H

#include <QStackedWidget>
#include <Protocols/groledata.h>
#include <Protocols/GRoleInventory.h>
#include <utils.h>
#include <QListWidgetItem>
#include <dlgarmoreditor.h>
#include <dlgamuleteditor.h>
#include <dlgflyswordeditor.h>
#include <dlgmeridiandata.h>
#include <dlgpetcorral.h>
#include <dlgskills.h>
#include <dlgweaponeditor.h>
#include <dlgpropertyeditor.h>
#include <QPainter>
#include <dlgcooldowneditor.h>
#include <dlgforcedataeditor.h>
#include <dlgcountrydataeditor.h>
#include <dlgkingdataeditor.h>
#include <dlgextrapropeditor.h>
#include <dlgreincarnationdataeditor.h>
#include <dlgrealmdataeditor.h>
#include <dlgtitledataeditor.h>
#include <dlgqihunessenceeditor.h>
#include <minwindef.h>

namespace Ui {
class PlayerEditor;
}

static int s_ProfDesc[14] = {
    FIXMSG_PROF_WARRIOR,
    FIXMSG_PROF_MAGE,
    FIXMSG_PROF_MONK,
    FIXMSG_PROF_HAG,
    FIXMSG_PROF_ORC,
    FIXMSG_PROF_GHOST,
    FIXMSG_PROF_ARCHOR,
    FIXMSG_PROF_ANGEL,
    FIXMSG_PROF_JIANLING,
    FIXMSG_PROF_MEILING,
    FIXMSG_PROF_YEYING,
    FIXMSG_PROF_YUEXIAN,
    FIXMSG_PROF_ATIRADORA,
    FIXMSG_PROF_PALADIN,
};

class PlayerEditor : public QStackedWidget
{
    Q_OBJECT

public:
    explicit PlayerEditor(GRoleData player, QWidget *parent = nullptr);
    ~PlayerEditor();

    GRoleData p;

    QVector<int> left = QVector{20, 21, 12, 2, 3, 18, 8, 5, 22, 9, 10, 23};
    QVector<int> right = QVector{24, 1, 19, 26, 4, 17, 27, 6, 0, 28, 7, 11};

    void LoadPlayer();
    void PopulateInfos(GRoleInventory inv);
    static QString GetAddonName(int idProp, int p0, int p1, int p2, int* aPEEVals = {0}, int* aRefines = {0});
    void AddInventoryItem(int index);
    void RemoveInventoryItem(int index);


    enum EQUIP_MASK64
    {
        EQUIP_MASK64_WEAPON			= 0x00000001,
        EQUIP_MASK64_HEAD			= 0x00000002,
        EQUIP_MASK64_NECK			= 0x00000004,
        EQUIP_MASK64_SHOULDER		= 0x00000008,
        EQUIP_MASK64_BODY			= 0x00000010,
        EQUIP_MASK64_WAIST			= 0x00000020,
        EQUIP_MASK64_LEG			= 0x00000040,
        EQUIP_MASK64_FOOT			= 0x00000080,
        EQUIP_MASK64_WRIST			= 0x00000100,
        EQUIP_MASK64_FINGER1		= 0x00000200,
        EQUIP_MASK64_FINGER2		= 0x00000400,
        EQUIP_MASK64_FINGERS        = 0x00000600,
        EQUIP_MASK64_PROJECTILE		= 0x00000800,
        EQUIP_MASK64_FLYSWORD		= 0x00001000,
        EQUIP_MASK64_FASHION_BODY	= 0x00002000,
        EQUIP_MASK64_FASHION_LEG 	= 0x00004000,
        EQUIP_MASK64_FASHION_FOOT	= 0x00008000,
        EQUIP_MASK64_FASHION_WRIST	= 0x00010000,
        EQUIP_MASK64_ATTACK_RUNE	= 0x00020000,
        EQUIP_MASK64_BIBLE			= 0x00040000,
        EQUIP_MASK64_BUGLE			= 0x00080000,
        EQUIP_MASK64_HP_ADDON		= 0x00100000,
        EQUIP_MASK64_MP_ADDON		= 0x00200000,
        EQUIP_MASK64_TWEAK			= 0x00400000,
        EQUIP_MASK64_ELF			= 0x00800000,
        EQUIP_MASK64_STALLCARD		= 0x01000000,
        EQUIP_MASK64_FASHION_HEAD	= 0x02000000,
        EQUIP_MASK64_FORCE_TICKET	= 0x04000000,
        EQUIP_MASK64_DYNSKILL0		= 0x08000000,
        EQUIP_MASK64_DYNSKILL1		= 0x10000000,
        EQUIP_MASK64_FASHION_WEAPON = 0x20000000,//ʱװ����
        EQUIP_MASK64_UNUSED1		= 0x40000000,
        EQUIP_MASK64_UNUSED2		= 0x80000000,

        EQUIP_MASK64_GENERALCARD1	= 0x0000000100000000LL,
        EQUIP_MASK64_GENERALCARD2	= 0x0000000200000000LL,
        EQUIP_MASK64_GENERALCARD3	= 0x0000000400000000LL,
        EQUIP_MASK64_GENERALCARD4	= 0x0000000800000000LL,
        EQUIP_MASK64_GENERALCARD5	= 0x0000001000000000LL,
        EQUIP_MASK64_GENERALCARD6	= 0x0000002000000000LL,

        EQUIP_MASK64_CAN_BIND		= 0x220DF7FF,
        EQUIP_MASK64_SECURITY_PASSWD_PROTECTED = 0x2205F7FF,//�ܰ�ȫ���뱣����װ��λ��
        EQUIP_MASK64_DYNSKILL_ALL	= 0x18000000,
    };
    Q_ENUM(EQUIP_MASK64);

    enum EQUIP_INDEX
    {
        EQUIP_INDEX_WEAPON			= 0,
        EQUIP_INDEX_HEAD			= 1,
        EQUIP_INDEX_NECK			= 2,
        EQUIP_INDEX_SHOULDER		= 3,
        EQUIP_INDEX_BODY			= 4,
        EQUIP_INDEX_WAIST			= 5,
        EQUIP_INDEX_LEG				= 6,
        EQUIP_INDEX_FOOT			= 7,
        EQUIP_INDEX_WRIST			= 8,
        EQUIP_INDEX_FINGER1			= 9,
        EQUIP_INDEX_FINGER2			= 10,
        EQUIP_INDEX_PROJECTILE		= 11,
        EQUIP_INDEX_FLYSWORD		= 12,
        EQUIP_INDEX_FASHION_BODY	= 13,
        EQUIP_INDEX_FASHION_LEG		= 14,
        EQUIP_INDEX_FASHION_FOOT	= 15,
        EQUIP_INDEX_FASHION_WRIST	= 16,
        EQUIP_INDEX_RUNE_SLOT		= 17,
        EQUIP_INDEX_BIBLE			= 18,
        EQUIP_INDEX_BUGLE			= 19,
        EQUIP_INDEX_HP_ADDON		= 20,
        EQUIP_INDEX_MP_ADDON		= 21,
        EQUIP_INDEX_TWEAK			= 22,
        EQUIP_INDEX_ELF				= 23,
        EQUIP_INDEX_STALLCARD		= 24,
        EQUIP_INDEX_FASHION_HEAD	= 25,
        EQUIP_INDEX_FORCE_TICKET	= 26,
        EQUIP_INDEX_DYNSKILL0		= 27,
        EQUIP_INDEX_DYNSKILL1		= 28,
        EQUIP_INDEX_FASHION_WEAPON	= 29, //ʱװ����
        EQUIP_INDEX_UNUSED1			= 30,
        EQUIP_INDEX_UNUSED2			= 31,
        EQUIP_INDEX_GENERALCARD1	= 32,
        EQUIP_INDEX_GENERALCARD2	= 33,
        EQUIP_INDEX_GENERALCARD3	= 34,
        EQUIP_INDEX_GENERALCARD4	= 35,
        EQUIP_INDEX_GENERALCARD5	= 36,
        EQUIP_INDEX_GENERALCARD6	= 37,
        EQUIP_INVENTORY_COUNT,

        EQUIP_VISUAL_START	= EQUIP_INDEX_WEAPON,
        EQUIP_VISUAL_END	= EQUIP_INDEX_FASHION_WEAPON + 1,
        EQUIP_ARMOR_START	= EQUIP_INDEX_HEAD,
        EQUIP_ARMOR_END		= EQUIP_INDEX_PROJECTILE,
    };

    enum EQUIP_MASK
    {
        EQUIP_MASK_HAS_ADDON	= 0x40000000,		//�и�������
        EQUIP_MASK_EXTEND64		= 0x80000000,
        EQUIP_MASK_HIGH			= 0xC0000000,
    };

    enum ITEM_MAKE_TAG
    {
        IMT_NULL,
        IMT_CREATE,
        IMT_DROP,
        IMT_SHOP,
        IMT_PRODUCE,
        IMT_SIGN,
    };

    enum
    {
        ITEM_PROC_TYPE_NODROP 	= 0x0001,	//����ʱ������
        ITEM_PROC_TYPE_NOTHROW	= 0x0002,	//�޷����ڵ���  down
        ITEM_PROC_TYPE_NOSELL	= 0x0004,	//�޷�����NPC   down
        ITEM_PROC_TYPE_CASHITEM	= 0x0008,	//��������Ʒ
        ITEM_PROC_TYPE_NOTRADE  = 0x0010,	//���Ҽ䲻�ܽ���
        ITEM_PROC_TYPE_TASKITEM = 0x0020,	//��������Ʒ
        ITEM_PROC_TYPE_BIND2	= 0x0040,	//װ���󼴰󶨵���Ʒ
        ITEM_PROC_TYPE_UNBIND	= 0x0080,	//�Ƿ����Խ���
        ITEM_PROC_TYPE_NO_SAVE	= 0x0100,	//�뿪����ʱ��ʧ
        ITEM_PROC_TYPE_AUTO_USE	= 0x0200,	//�Զ�ʹ��
        ITEM_PROC_TYPE_DEATH_DROP= 0x0400,	//��������
        ITEM_PROC_TYPE_LEAVE_DROP= 0x0800,	//���ߵ���
        ITEM_PROC_TYPE_UNREPAIRABLE = 0x1000,	//��������
        ITEM_PROC_TYPE_DAMAGED		= 0x2000,	//����pk��ɱ��������Ʒ����
        ITEM_PROC_TYPE_NOPUTIN_USERTRASH = 0x4000,	//���ɷ����ʺŲֿ���Ʒ
        ITEM_PROC_TYPE_BIND			= 0x8000,	//���Ѿ��󶨵���Ʒ
        ITEM_PROC_TYPE_CAN_WEBTRADE	= 0x10000,	//������Ѱ��������
        ITEM_PROC_TYPE_MALL			= 0x20000,	//��Ǭ������������Ʒ����Ʒ����

        ITEM_PROC_NO_BIND_MASK	=  ITEM_PROC_TYPE_NODROP | ITEM_PROC_TYPE_NOTHROW | ITEM_PROC_TYPE_NOSELL | ITEM_PROC_TYPE_NOTRADE,
        //�ǲ��ܰ󶨵����ϲ���  �߻�Ҫ������ͬʱ�߱��������� �Ų������󶨣������Ϳ��԰���
    };

    static int Equipmask64To32(int64_t mask64)
    {
        int mask = 0;
        if(mask64 & 0xFFFFFFFF00000000LL)
        {
            mask = ((int)(mask64 >> 32)) & (~EQUIP_MASK_HIGH) | EQUIP_MASK_EXTEND64;
        }
        else
        {
            mask = ((int)(mask64 & 0x00000000FFFFFFFFLL)) & (~EQUIP_MASK_HIGH);
        }
        return mask;
    }

    static int64_t Equipmask32To64(int mask)
    {
        int64_t mask64 = 0;
        if(mask & EQUIP_MASK_EXTEND64)
        {
            mask64 = mask & (~EQUIP_MASK_HIGH);
            mask64 <<= 32;
        }
        else
        {
            mask64 = mask & (~EQUIP_MASK_HIGH);
        }
        return mask64;
    }

private slots:
    void on_equip_list_left_itemClicked(QListWidgetItem *item);

    void on_equip_list_right_itemClicked(QListWidgetItem *item);

    void on_pocket_list_itemClicked(QListWidgetItem *item);

    void on_pushButton_clicked();

    void on_btnCancel_clicked();

    void on_btnSave_clicked();

    void on_status_petcorral_btn_clicked();

    void on_status_skill_btn_clicked();

    void on_status_meridian_data_btn_clicked();

    void on_status_property_btn_clicked();

    void on_status_coolingtime_btn_clicked();

    void on_status_forcedata_btn_clicked();

    void on_status_countrydata_btn_clicked();

    void on_status_kingdata_btn_clicked();

    void on_status_extraprop_btn_clicked();

    void on_status_reincarnationdata_btn_clicked();

    void on_status_realmdata_btn_clicked();

    void on_status_titledata_btn_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_4_clicked();

    void on_base_forbid_list_itemClicked(QTableWidgetItem *item);

    void on_base_forbid_type_currentIndexChanged(int index);

    void on_base_forbid_time_valueChanged(const QString &arg1);

    void on_base_forbid_created_valueChanged(const QString &arg1);

    void on_base_forbid_reason_textChanged(const QString &arg1);

    void on_pocket_list_itemChanged(QListWidgetItem *item);

    void on_pocket_list_pressed(const QModelIndex &index);

    void on_pushButton_7_clicked();

    void on_txt_id_valueChanged(const QString &arg1);

public:
    bool loaded = false;
    bool isEquipment;
    int index_selected;
    static QString desc;
    static void AddDescText(int col, bool bRet, const char *txt, ...);
    static QString RetDescText(bool bRet, const char *szText...);
    static void AddBindDescText(int m_iProcType);
    static QString GetWideString(int id);
    static bool isFloatValue(int value)
    {
        if (value < 10000000)
            return false;
        else return true;
    }
    static int VisualizeFloatPercent(int p)
    {
        return (int)(*(float*)&p * 100.0f + 0.5f);
    }
    static int FloatToInt(float f)
    {
        int* intValuePtr = reinterpret_cast<int*>(&f);
        return *intValuePtr;
    }
    void changeTimestamp(int value);
    static QString AddProfReqDesc(int iProfReq);
    static bool IsSharpenerProperty(quint8 propertyType);
    static bool IsEngraveProperty(quint8 propertyType);
    static bool IsRefineProperty(quint8 propertyType);
    static bool IsNewProperty(quint8 propertyType);
    static bool IsAstrolabeProperty(quint8 propertyType);
    static void AddHtmlDescText(int col, bool bRet, const char *szText...);
    static void AddExpireTimeDesc(int m_expire_date);
    static void BuildAddOnPropDesc(QList<addon_data> m_aProps, int *aPEEVals, int *aRefines);
    static DWORD PropEffectMask(addon_data prop, DWORD dwFlags);
    static DWORD PropEffectEssence(QList<addon_data> m_aProps);
    static int VisualizeEndurance(int v);
    static QString GetFormattedPrice(qint64 i);
    static QString GetHtmlAddonName(int idProp, int p0, int p1, int p2, int *aPEEVals, int *aRefines, int color = ITEMDESC_COL_LIGHTBLUE);
    static void BuildAddOnSoulPropDesc(int id, QList<addon_data> addons, addon_soul_data addons_soul, int *aPEEVals, int *aRefines);
private:
    Ui::PlayerEditor *ui;
};

#endif // PLAYEREDITOR_H
