#include "dlgitemeditor.h"
#include "playereditor.h"
#include "ui_playereditor.h"
#include <qmenu.h>
#include <connection.h>
#include <QtGlobal>

QString PlayerEditor::desc;

PlayerEditor::PlayerEditor(GRoleData player, QWidget *parent) :
    QStackedWidget(parent),
    p(player),
    ui(new Ui::PlayerEditor)
{
    ui->setupUi(this);
    QList<QSpinBox*> spinBoxes = findChildren<QSpinBox*>();

    for (QSpinBox* spinBox : spinBoxes) {
        QObject::connect(spinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &PlayerEditor::changeTimestamp);
    }

    QList<QDoubleSpinBox*> dspinBoxes = findChildren<QDoubleSpinBox*>();

    for (QDoubleSpinBox* dspinBox : dspinBoxes) {
        QObject::connect(dspinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &PlayerEditor::changeTimestamp);
    }
    pwAdmin &pw = pwAdmin::getInstance();

    ui->base_class->addItems(pw.listClasses.values());
    for (int i = 0; i < 6; i++)
        ui->base_race->addItem(Utils::RacaPersonagem(i));


    ui->base_forbid_list->setColumnWidth(0, 60);
    ui->base_forbid_list->setColumnWidth(3, 80);
    ui->base_forbid_list->setColumnWidth(4, 100);
    for (int i = 100; i < 106; i++)
    {
        ui->base_forbid_type->addItem(Utils::BanTypes((Utils::ForbidType)i));
    }
    for(int i = 0; i < 9; i++)
    {
        ui->status_cultivation->addItem(Utils::CultivoPersonagem(i), i);
    }
    ui->status_cultivation->addItem(Utils::CultivoPersonagem(20), 20);
    ui->status_cultivation->addItem(Utils::CultivoPersonagem(21), 21);
    ui->status_cultivation->addItem(Utils::CultivoPersonagem(22), 22);
    ui->status_cultivation->addItem(Utils::CultivoPersonagem(30), 30);
    ui->status_cultivation->addItem(Utils::CultivoPersonagem(31), 31);
    ui->status_cultivation->addItem(Utils::CultivoPersonagem(32), 32);
    if (player.Version > 191)
    {
        ui->status_cultivation->addItem(Utils::CultivoPersonagem(40), 40);
        ui->status_cultivation->addItem(Utils::CultivoPersonagem(41), 41);
    }
    LoadPlayer();

    // Cria o menu ao clicar com o botão direito do mouse no inventário
    ui->pocket_list->setContextMenuPolicy(Qt::CustomContextMenu);
    QObject::connect(ui->pocket_list, &QWidget::customContextMenuRequested, [this, pock = ui->pocket_list](const QPoint &pos)
    {
        int index = pock->currentRow();
        if (index < 0) return; // Verifica se um item válido foi clicado

        QMenu contextMenu;
        QAction *action1 = contextMenu.addAction("Adicionar item");
        QAction *action2 = contextMenu.addAction("Remover item");

        QObject::connect(action1, &QAction::triggered, [this, index]()
        {
            AddInventoryItem(index);
        });

        QObject::connect(action2, &QAction::triggered, [this, index]()
        {
            RemoveInventoryItem(index);
        });

        contextMenu.exec(pock->mapToGlobal(pos));
    });
}

PlayerEditor::~PlayerEditor()
{
    delete ui;
}

void PlayerEditor::changeTimestamp(int value)
{
    if (!loaded) return;
    try
    {
        ui->base_createtime_txt->setText(ui->base_createtime->value() <= 0 ? "-" : QDateTime::fromSecsSinceEpoch(ui->base_createtime->value()).toString("dd/MM/yyyy hh:mm:ss"));
        ui->base_deletetime_txt->setText(ui->base_deletetime->value() <= 0 ? "-" : QDateTime::fromSecsSinceEpoch(ui->base_deletetime->value()).toString("dd/MM/yyyy hh:mm:ss"));
        ui->base_lastlogintime_txt->setText(ui->base_lastlogintime->value() <= 0 ? "-" : QDateTime::fromSecsSinceEpoch(ui->base_lastlogintime->value()).toString("dd/MM/yyyy hh:mm:ss"));
        ui->status_pariahtime_txt->setText(ui->status_pariahtime->value() <= 0 ? "00:00:00" : Utils::SecondsToTimeFormat(ui->status_pariahtime->value()));
        ui->status_invadertime_txt->setText(ui->status_invadertime->value() <= 0 ? "00:00:00" : Utils::SecondsToTimeFormat(ui->status_invadertime->value()));
        ui->status_worldtag_label->setText(ui->status_worldtag->value() > 0 ? Utils::MapNameFromID(ui->status_worldtag->value()) : "");
        ui->status_posx_label->setText(Utils::ConvertToClientX(ui->status_posx->value()));
        ui->status_posy_label->setText(Utils::ConvertToClientY(ui->status_posy->value()));
        ui->status_posz_label->setText(Utils::ConvertToClientZ(ui->status_posz->value()));
        ui->status_dbltimebegin_txt->setText(ui->status_dbltimebegin->value() <= 0 ? "-" : QDateTime::fromSecsSinceEpoch(ui->status_dbltimebegin->value()).toString("dd/MM/yyyy hh:mm:ss"));
        ui->status_dbltimemax_txt->setText(ui->status_dbltimemax->value() <= 0 ? "00:00:00" : Utils::SecondsToTimeFormat(ui->status_dbltimemax->value()));
        ui->status_timeused_txt->setText(ui->status_timeused->value() <= 0 ? "00:00:00" : Utils::SecondsToTimeFormat(ui->status_timeused->value()));
    }
    catch(QException e){qDebug()<< e.what();}
}

void PlayerEditor::LoadPlayer()
{
    OctetsStream os;
    p.marshal(os);
    ui->recebe->setText(os.data.toHex());
    if (p.Version >= 191)
        ui->label_18->setText("custom_data_highmode");
    else ui->label_18->setText("reserved2");
    //  base
    ui->base_class->setCurrentIndex(p.base.cls);
    ui->base_configdata->setText(p.base.config_data.value.toHex());
    ui->base_createtime->setValue(p.base.create_time);
    ui->base_crossdata->setText(p.base.cross_data.value.toHex());
    ui->base_customdata->setText(p.base.custom_data.value.toHex());
    ui->base_customstamp->setText(QString::number(p.base.custom_stamp));
    ui->base_deletetime->setValue(p.base.delete_time);
    ui->base_gender->setCurrentIndex(p.base.gender);
    ui->base_helpstates->setText(p.base.help_states.value.toHex());
    ui->base_id->setText(QString::number(p.base.id));
    ui->base_lastlogintime->setValue(p.base.lastlogin_time);
    ui->base_name->setText(p.base.name.toName());
    ui->base_race->setCurrentIndex(p.base.race);
    if (p.Version < 191)
        ui->base_reserved2->setText(QString::number(p.base.reserved2));
    else ui->base_reserved2->setText(p.base.custom_data_highmode.value.toHex());
    ui->base_reserved3->setText(QString::number(p.base.reserved3));
    ui->base_reserved4->setText(QString::number(p.base.reserved4));
    ui->base_spouse->setText(QString::number(p.base.spouse));
    ui->base_status->setText(QString::number(p.base.status));
    ui->base_userid->setText(QString::number(p.base.userid));
    ui->base_version->setText(QString::number(p.base.version));
    if(p.base.forbid.count() > 0)
    {
        int row = 0;
        foreach(auto f, p.base.forbid)
        {
            ui->base_forbid_list->insertRow(row);
            ui->base_forbid_list->setItem(row, 0, new QTableWidgetItem(Utils::BanTypes(f.type)));
            ui->base_forbid_list->setItem(row, 1, new QTableWidgetItem(QString::number(f.time)));
            ui->base_forbid_list->setItem(row, 2, new QTableWidgetItem(QString::number(f.createtime)));
            ui->base_forbid_list->setItem(row, 3, new QTableWidgetItem(f.reason.toName()));
            row++;
        }
    }
    //  status
    ui->status_charactermode->setText(p.status.charactermode.value.toHex());
    ui->status_coolingtime->setText(p.status.coolingtime.value.toHex());
    ui->status_countrydata->setText(p.status.country_data.value.toHex());
    ui->status_cultivation->setCurrentIndex(ui->status_cultivation->findData(p.status.level2));
    ui->status_customstatus->setText(p.status.custom_status.value.toHex());
    ui->status_dbltimebegin->setValue(p.status.dbltime_begin);
    ui->status_dbltimedata->setText(p.status.dbltime_data.value.toHex());
    ui->status_dbltimeexpire->setText(QString::number(p.status.dbltime_expire));
    ui->status_dbltimemax->setValue(p.status.dbltime_max);
    ui->status_dbltimemode->setText(QString::number(p.status.dbltime_mode));
    ui->status_dbltimeused->setText(QString::number(p.status.dbltime_used));
    ui->status_exp->setText(QString::number(p.status.exp));
    ui->status_extraprop->setText(p.status.extraprop.value.toHex());
    ui->status_factioncontrib->setText(p.status.faction_contrib.value.toHex());
    ui->status_filterdata->setText(p.status.filter_data.value.toHex());
    ui->status_forcedata->setText(p.status.force_data.value.toHex());
    ui->status_hp->setText(QString::number(p.status.hp));
    ui->status_instancekeylist->setText(p.status.instancekeylist.value.toHex());
    ui->status_invaderstate->setCurrentIndex(p.status.invader_state);
    ui->status_invadertime->setValue(p.status.invader_time);
    ui->status_kingdata->setText(p.status.king_data.value.toHex());
    ui->status_level->setText(QString::number(p.status.level));
    ui->status_meridiandata->setText(p.status.meridian_data.value.toHex());
    ui->status_mp->setText(QString::number(p.status.mp));
    ui->status_multiexpctrl->setText(p.status.multi_exp_ctrl.value.toHex());
    ui->status_npcrelation->setText(p.status.npc_relation.value.toHex());
    ui->status_onlineaward->setText(p.status.online_award.value.toHex());
    ui->status_pariahtime->setValue(p.status.pariah_time);
    ui->status_petcorral->setText(p.status.petcorral.value.toHex());
    ui->status_posx->setValue(p.status.posx);
    ui->status_posy->setValue(p.status.posy);
    ui->status_posz->setValue(p.status.posz);
    ui->status_profittimedata->setText(p.status.profit_time_data.value.toHex());
    ui->status_property->setText(p.status.property.value.toHex());
    ui->status_realmdata->setText(p.status.realm_data.value.toHex());
    ui->status_reincarnationdata->setText(p.status.reincarnation_data.value.toHex());
    ui->status_reputation->setText(QString::number(p.status.reputation));
    if (p.Version == 140)
    {
        ui->label_92->setText("Rank");
        ui->status_reserved2->setText(p.status.rank.value.toHex());
    }
    else
    {
        ui->label_92->setText("reserved2");
        ui->status_reserved2->setText(QString::number(p.status.reserved2));
    }
    ui->status_reserved3->setText(QString::number(p.status.reserved3));
    ui->status_skillpoints->setText(QString::number(p.status.pp));
    ui->status_skill->setText(p.status.skills.value.toHex());
    ui->status_sp->setText(QString::number(p.status.sp));
    ui->status_storagetask->setText(p.status.storage_task.value.toHex());
    ui->status_storehousepassword->setText(p.status.storehousepasswd.value.toHex());
    ui->status_storesize->setText(QString::number(p.status.storesize));
    ui->status_timeused->setValue(p.status.time_used);
    ui->status_titledata->setText(p.status.title_data.value.toHex());
    ui->status_vardata->setText(p.status.var_data.value.toHex());
    ui->status_version->setText(QString::number(p.status.version));
    ui->status_waypointlist->setText(p.status.waypointlist.value.toHex());
    ui->status_worldtag->setValue(p.status.worldtag);

    //  pocket
    ui->pocket_money->setText(QString::number(p.pocket.money));

    ui->pocket_list->setStyleSheet(QString("QListWidget { background-image: url(:/Icons/bg.png)} QListWidget::item{background:transparent;margin-top:1px;margin-right:1px} QListWidget::item:selected{border:1px solid yellow;border-radius:5px;margin-top:0px}"));
    ui->storehouse_list->setStyleSheet(QString("QListWidget { background-image: url(:/Icons/bg.png)} QListWidget::item{background:transparent;margin-top:1px;margin-right:1px} QListWidget::item:selected{border:1px solid yellow;border-radius:5px;margin-top:0px}"));
    ui->quest_list->setStyleSheet(QString("QListWidget { background-image: url(:/Icons/bg.png)} QListWidget::item{background:transparent;margin-top:1px;margin-right:1px} QListWidget::item:selected{border:1px solid yellow;border-radius:5px;margin-top:0px}"));
    ui->cloth_list->setStyleSheet(QString("QListWidget { background-image: url(:/Icons/bg.png)} QListWidget::item{background:transparent;margin-top:1px;margin-right:1px} QListWidget::item:selected{border:1px solid yellow;border-radius:5px;margin-top:0px}"));
    ui->avatar_list->setStyleSheet(QString("QListWidget { background-image: url(:/Icons/bg.png)} QListWidget::item{background:transparent;margin-top:1px;margin-right:1px} QListWidget::item:selected{border:1px solid yellow;border-radius:5px;margin-top:0px}"));

    for (uint i = 0; i < p.pocket.capacity; i++)
    {
        QListWidgetItem *item = new QListWidgetItem(QIcon(":/Icons/transparent.png"), NULL);
        item->setTextAlignment(Qt::AlignLeft | Qt::AlignBottom);
        item->setTextColor(Qt::white);
        QFont font;
        font.setBold(true);
        font.setStyleName("Arial");
        font.setPixelSize(10);
        item->setFont(font);
        ui->pocket_list->addItem(item);
    }
    if (p.pocket.items.size() > 0)
        foreach(auto item, p.pocket.items)
        {
            ui->pocket_list->item(item.pos)->setIcon(QIcon(Commands::GetItemImage(item.id, (Utils::Gender)p.base.gender)));
            if (item.count > 1)
                ui->pocket_list->item(item.pos)->setText(QString::number(item.count));
            if (item.id >= 59757 && item.id <= 59771)
            {
                OctetsStream qihun_os;
                qihun_os.setData(item.data.value, false, false);
                socket_qihun qihun;
                qihun.unmarshal(qihun_os);
                if (qihun._moon_phase_level > 0)
                    ui->pocket_list->item(item.pos)->setText("○");
                else ui->pocket_list->item(item.pos)->setText(QString::null);
            }
        }
    foreach(auto eqp, p.equipment.inv)
    {
        if (eqp.id > 0)
        {
            if (left.contains(eqp.pos))
            {
                int index = left.indexOf(eqp.pos);
                ui->equip_list_left->item(index)->setIcon(QIcon(Commands::GetItemImage(eqp.id)));
            }
            if (right.contains(eqp.pos))
            {
                int index = right.indexOf(eqp.pos);
                ui->equip_list_right->item(index)->setIcon(QIcon(Commands::GetItemImage(eqp.id)));
            }
        }
    }
    for (uint i = 0; i < p.storehouse.capacity; i++)
    {
        ui->storehouse_list->addItem(new QListWidgetItem(QIcon(":/Icons/transparent.png"), NULL));
    }
    if (p.storehouse.items.size() > 0)
        foreach(auto item, p.storehouse.items)
        {
            ui->storehouse_list->item(item.pos)->setIcon(QIcon(Commands::GetItemImage(item.id, (Utils::Gender)p.base.gender)));
        }
    for (uint i = 0; i < p.storehouse.size1; i++)
    {
        ui->cloth_list->addItem(new QListWidgetItem(QIcon(":/Icons/transparent.png"), NULL));
    }
    if (p.storehouse.dress.size() > 0)
        foreach(auto item, p.storehouse.dress)
        {
            ui->cloth_list->item(item.pos)->setIcon(QIcon(Commands::GetItemImage(item.id, (Utils::Gender)p.base.gender)));
        }
    for (uint i = 0; i < p.storehouse.size2; i++)
    {
        ui->quest_list->addItem(new QListWidgetItem(QIcon(":/Icons/transparent.png"), NULL));
    }
    if (p.storehouse.material.size() > 0)
        foreach(auto item, p.storehouse.material)
        {
            ui->quest_list->item(item.pos)->setIcon(QIcon(Commands::GetItemImage(item.id, (Utils::Gender)p.base.gender)));
        }
    for (uint i = 0; i < p.storehouse.size3; i++)
    {
        ui->avatar_list->addItem(new QListWidgetItem(QIcon(":/Icons/transparent.png"), NULL));
    }
    if (p.storehouse.generalcard.size() > 0)
        foreach(auto item, p.storehouse.generalcard)
        {
            ui->avatar_list->item(item.pos)->setIcon(QIcon(Commands::GetItemImage(item.id, (Utils::Gender)p.base.gender)));
        }

    if (p.base.gender == Utils::Female)
    {
        ui->label_99->setPixmap(QPixmap(":/Icons/inventory_f.png"));
    }
    QList<QLineEdit *> lineEdits = this->findChildren<QLineEdit *>();
    for (QLineEdit *lineEdit : lineEdits) {
        lineEdit->setCursorPosition(0);
    }
    loaded = true;
    changeTimestamp(0);
}

QString PlayerEditor::AddProfReqDesc(int iProfReq)
{
    QString desc;
    for (int i=0; i < pwAdmin::getInstance().listClasses.count(); i++)
    {
        if (iProfReq & (1 << i))
        {
            desc += " ";
            desc += pwAdmin::getInstance().listFixedMsg[s_ProfDesc[i]];
        }
    }
    return desc;
}

void PlayerEditor::AddHtmlDescText(int col, bool bRet, const char *szText, ...)
{
    //	Add color
    if ((col >= ITEMDESC_COL_LIGHTBLUE && col <= ITEMDESC_COL_CYANINE) ||
            (col > ITEMDESC_COL2_START && col <= ITEMDESC_COL2_NULL07))
    {
        QString szCol = GetWideString(col);
        auto color = szCol.left(7);
        desc += "<font color=\"#" + color.right(6) + "\">";
    }
    char szLine[256];

    va_list argList;
    va_start(argList, szText);
    _vsnprintf(szLine, sizeof(szLine)/sizeof(szLine[0]), szText, argList);
    va_end(argList);

    desc += szLine;

    if (bRet)
        desc += "<br>";
}

void PlayerEditor::AddDescText(int col, bool bRet, const char *szText, ...)
{
    /*if (bRet)
        desc += "<br>";
    //	Add color
    if ((col >= ITEMDESC_COL_LIGHTBLUE && col <= ITEMDESC_COL_CYANINE) ||
            (col > ITEMDESC_COL2_START && col <= ITEMDESC_COL2_NULL07))
    {
        QString szCol = GetWideString(col);
        auto color = szCol.left(6);
        desc += "<font color=\"#" + color + "\">";
    }*/
    char szLine[256];

    va_list argList;
    va_start(argList, szText);
    _vsnprintf(szLine, sizeof(szLine)/sizeof(szLine[0]), szText, argList);
    va_end(argList);

    desc += szLine;
    /*if (col != -1)
    {
        desc += "</font>";
    }*/
}

QString PlayerEditor::RetDescText(bool bRet, const char *szText, ...)
{
    QString txt;
    char szLine[256];
    va_list argList;
    va_start(argList, szText);
    _vsnprintf(szLine, sizeof(szLine)/sizeof(szLine[0]), szText, argList);
    va_end(argList);
    txt += szLine;
    return txt;
}

QString PlayerEditor::GetWideString(int id)
{
    pwAdmin &pw = pwAdmin::getInstance();
    return pw.listItemDesc.value(id);
}

void PlayerEditor::AddBindDescText(int m_iProcType)
{
    if (m_iProcType & PROC_BINDING)
    {
        QString strTemp = GetWideString(ITEMDESC_EQUIP_BIND);
        if (m_iProcType & PROC_CAN_WEBTRADE)
        {
            strTemp += "(";
            strTemp += GetWideString(ITEMDESC_CAN_WEBTRADE);
            strTemp += ")";
        }
        AddHtmlDescText(ITEMDESC_COL_CYANINE, true, strTemp.toStdString().c_str());
    }
    else if (m_iProcType & PROC_BIND)
        AddHtmlDescText(ITEMDESC_COL_DARKGOLD, true, GetWideString(ITEMDESC_EQUIP_BINDAFTERUSE).toStdString().c_str());
}

void PlayerEditor::AddExpireTimeDesc(int m_expire_date)
{
    if( m_expire_date == 0 )
        return;

    int green = ITEMDESC_COL_GREEN;
    int yellow = ITEMDESC_COL_YELLOW;
    int gold = ITEMDESC_COL_DARKGOLD;
    int red = ITEMDESC_COL_RED;
    time_t timeLeft = m_expire_date - QDateTime::currentMSecsSinceEpoch();
    if( timeLeft < 0 ) timeLeft = 0;

    if( timeLeft > 24 * 3600 )
        AddHtmlDescText(green, true, GetWideString(ITEMDESC_EXPIRETIME_DAY).toStdString().c_str(), timeLeft / (24 * 3600), (timeLeft % (24 * 3600)) / 3600);
    else if( timeLeft > 3600 )
    {
        AddHtmlDescText(yellow, true, GetWideString(ITEMDESC_EXPIRETIME_HOUR_MIN).toStdString().c_str(), timeLeft / 3600, (timeLeft % 3600) / 60);
    }
    else if( timeLeft > 60 )
    {
        AddHtmlDescText(gold, true, GetWideString(ITEMDESC_EXPIRETIME_MIN_SEC).toStdString().c_str(), timeLeft / 60, timeLeft % 60);
    }
    else
    {
        AddHtmlDescText(red, true, GetWideString(ITEMDESC_EXPIRETIME_SECOND).toStdString().c_str(), timeLeft);
    }
}

bool PlayerEditor::IsSharpenerProperty(quint8 propertyType)
{
    return propertyType >= 100 && propertyType <= 116;
}

bool PlayerEditor::IsEngraveProperty(quint8 propertyType)
{
    return propertyType >= 120 && propertyType <= 147;
}

bool PlayerEditor::IsRefineProperty(quint8 propertyType)
{
    return propertyType >= 200 && propertyType <= 212;
}

bool PlayerEditor::IsNewProperty(quint8 propertyType)
{
    return propertyType >= 215 && propertyType <= 220;
}

bool PlayerEditor::IsAstrolabeProperty(quint8 propertyType)
{
    return propertyType >= 161 && propertyType <= 176;
}

void PlayerEditor::BuildAddOnPropDesc(QList<addon_data> m_aProps, int* aPEEVals, int* aRefines)
{
    if (!m_aProps.count())
        return;

    for (int i=0; i < m_aProps.count(); i++)
    {
        auto prop = m_aProps[i];
        if (prop.isEmbedded || prop.isInherited || prop.isEngraved)
            continue;

        GetHtmlAddonName(prop.id_addon, prop.arg[0], prop.arg[1], prop.arg[2], aPEEVals, aRefines);
    }
}

void PlayerEditor::BuildAddOnSoulPropDesc(int id, QList<addon_data> addons, addon_soul_data addons_soul, int* aPEEVals, int* aRefines)
{
    if (addons_soul.sacred_addons.count() > 0)
    {
        for (int i=0; i < addons_soul.sacred_addons.count(); i++)
        {
            auto prop = addons_soul.sacred_addons[i];
            if (prop.isEmbedded || prop.isInherited || prop.isEngraved)
                continue;

            GetHtmlAddonName(prop.id_addon, prop.arg[0], prop.arg[1], prop.arg[2], aPEEVals, aRefines, ITEMDESC_COL_RED);
        }
    }
    else if (addons_soul.sacred_addons.count() == 0 && addons.count() == 0)
    {
        for (int i = 0; i < 32; i++)
        {
            int addon_id = Commands::GetItemValue(id, QString("addons_%1_id_addon").arg(i), "NEW_ARMOR_ESSENCE").toInt();
            if (addon_id == 0) continue;
            foreach(auto addon, pwAdmin::getInstance().listAddonsData)
            {
                if (addon.id_addon == addon_id)
                {
                    GetHtmlAddonName(addon.id_addon, addon.arg[0], addon.arg[1], addon.arg[2], aPEEVals, aRefines);
                    break;
                }
            }
        }
    }
    else
    {
        for (int i=0; i < addons.count(); i++)
        {
            auto prop = addons[i];
            if (prop.isEmbedded || prop.isInherited || prop.isEngraved)
                continue;
            GetHtmlAddonName(prop.id_addon, prop.arg[0], prop.arg[1], prop.arg[2], aPEEVals, aRefines);
        }
    }
}

QString PlayerEditor::GetAddonName(int idProp, int p0, int p1, int p2, int* aPEEVals, int* aRefines)
{
    pwAdmin &pw = pwAdmin::getInstance();
    desc.clear();
    quint8 byPropType = (qint8)pw.addonsList.value(QString::number(idProp)).toInt();
    qDebug() << "PropTYPE: " << byPropType;
    int color = -1;
    bool bLocal = true;
#define ADD_RANGE_VALUE_DESC_ID(id_first_format_str, second_format_str, value0, value1, value2)	\
    if(bLocal)\
    {\
    if(p0 != p1 && p1 > 0)\
    {\
    AddDescText(color, false, GetWideString((id_first_format_str)).toStdString().c_str(), (value0));\
    AddDescText(color, true, (second_format_str), (value1));\
}\
    else\
    {\
    AddDescText(color, true, GetWideString((id_first_format_str)).toStdString().c_str(), (value0));\
}\
}\
    else\
    {\
    AddDescText(color, true, GetWideString((id_first_format_str)).toStdString().c_str(), (value2));\
}

#define ADD_RANGE_VALUE_DESC_STR(id_first_format_1, first_format_str_2, second_format_str, value0, value1, value2)	\
    {\
    QString strFirstFormat = QString("%1 %2").arg(GetWideString(id_first_format_1)).arg(first_format_str_2);\
    if(bLocal)\
    {\
    if(p0 != p1 && p1 > 0)\
    {\
    AddDescText(color, false, strFirstFormat.toStdString().c_str(), (value0));\
    AddDescText(color, true, (second_format_str), (value1));\
}\
    else\
    {\
    AddDescText(color, true, strFirstFormat.toStdString().c_str(), (value0));\
}\
}\
    else\
    {\
    AddDescText(color, true, strFirstFormat.toStdString().c_str(), (value2));\
}\
}

#define ADD_RANGE_VALUE_DESC_ID_NORMAL(id_string)					ADD_RANGE_VALUE_DESC_ID((id_string), "~%d", p0, p1, p0)
#define ADD_RANGE_VALUE_DESC_ID_FLOAT(id_string)						ADD_RANGE_VALUE_DESC_ID((id_string), "~%.2f", *(float*)&p0, *(float*)&p1, *(float*)&p0)
#define ADD_RANGE_VALUE_DESC_ID_FLOAT2(id_string)						ADD_RANGE_VALUE_DESC_ID((id_string), "~%.2f", *(float*)&alcance, *(float*)&alcance1, *(float*)&alcance)
#define ADD_RANGE_VALUE_DESC_ID_PERCENT(id_string)					ADD_RANGE_VALUE_DESC_ID((id_string), "~%d%%", (p0), (p1), p0)
#define ADD_RANGE_VALUE_DESC_ID_MINUS_PERCENT_1(id_string)	ADD_RANGE_VALUE_DESC_ID((id_string), "~%d%%", -(p0), (p1), -p0)
#define ADD_RANGE_VALUE_DESC_ID_MINUS_PERCENT_2(id_string)	ADD_RANGE_VALUE_DESC_ID((id_string), "~%d%%", -(p0), (p1), -(p0))
#define ADD_RANGE_VALUE_DESC_ID_HALF(id_string)						ADD_RANGE_VALUE_DESC_ID((id_string), "~%d", (p0/2), (p1/2), (p0/2))
#define ADD_RANGE_VALUE_DESC_STR_NORMAL(id_string)					ADD_RANGE_VALUE_DESC_STR((id_string), "%+d", "~%d", p0, p1, p0)

    if (IsSharpenerProperty(byPropType))
        AddDescText(color, false, "Runa: ");
    if (IsEngraveProperty(byPropType))
        AddDescText(color, false, "Gravura: ");
    if (IsAstrolabeProperty(byPropType))
        AddDescText(color, false, "Astrolábio: ");
    {
        int alcance = p0;
        int alcance1 = p1;
        p0 = isFloatValue(p0) ? VisualizeFloatPercent(p0) : p0;
        p1 = isFloatValue(p1) ? VisualizeFloatPercent(p1) : p1;
        p2 = isFloatValue(p2) ? VisualizeFloatPercent(p2) : p2;
        switch (byPropType)
        {
        case 0:		//	???��???��
            if (aPEEVals)
                aPEEVals[PEEI_PHYDAMAGE] += p0;
            AddDescText(color, false, GetWideString(ITEMDESC_ADDPHYDAMAGE).toStdString().c_str());
            AddDescText(color, true, " %+d", p0);
            break;

        case 1:		//	???��???��????

            if (aPEEVals)
                aPEEVals[PEEI_MAX_PHYDAMAGE] += p0;
            if(p0 != p1 && p1 > 0)
            {
                AddDescText(color, false, GetWideString(ITEMDESC_MAXPHYDAMAGE).toStdString().c_str(), p0);
                AddDescText(color, true, "~%d", p1);
            }
            else
            {
                AddDescText(color, true, GetWideString(ITEMDESC_MAXPHYDAMAGE).toStdString().c_str(), p0);
            }

            break;

        case 2:		//	???��???��(%)

            AddDescText(color, true, GetWideString(ITEMDESC_PHYDMGEXTRA).toStdString().c_str(), p0);

            break;

        case 3:		//	?�졤��???��
            if (aPEEVals)
                aPEEVals[PEEI_MAGICDAMAGE] += p0;
            AddDescText(color, false, GetWideString(ITEMDESC_ADDMAGICDAMAGE).toStdString().c_str());
            AddDescText(color, true, " %+d", p0);
            break;

        case 4: 	//	?�졤��???��????
            if (aPEEVals)
                aPEEVals[PEEI_MAX_MAGICDAMAGE] += p0;
            if(p0 != p1 && p1 > 0)
            {
                AddDescText(color, false, GetWideString(ITEMDESC_MAXMAGICDAMAGE).toStdString().c_str(), p0);
                AddDescText(color, true, "~%d", p1);
            }
            else
            {
                AddDescText(color, true, GetWideString(ITEMDESC_MAXMAGICDAMAGE).toStdString().c_str(), p0);
            }

            break;

        case 5: 	//	?�졤��???��(%)

            AddDescText(color, true, GetWideString(ITEMDESC_MAGICDMGEXTRA).toStdString().c_str(), p0);

            break;

        case 6: 	//	+??��?-????
            if (aPEEVals)
            {
                aPEEVals[PEEI_PHYDEF]	 += p0;
                aPEEVals[PEEI_PHYDAMAGE] -= p1;
            }
            AddDescText(color, false, GetWideString(ITEMDESC_PHYDEFENCE).toStdString().c_str());
            AddDescText(color, true, " %+d & ", p0);
            AddDescText(color, false, GetWideString(ITEMDESC_ADDPHYDAMAGE).toStdString().c_str());
            AddDescText(color, true, " %+d", -p1);
            break;

        case 7: 	//	+????-??��?

            if (aPEEVals)
            {
                aPEEVals[PEEI_PHYDAMAGE] += p0;
                aPEEVals[PEEI_PHYDEF]	 -= p1;
            }
            AddDescText(color, false, GetWideString(ITEMDESC_ADDPHYDAMAGE).toStdString().c_str());
            AddDescText(color, true, " %+d & ", p0);
            AddDescText(color, false, GetWideString(ITEMDESC_PHYDEFENCE).toStdString().c_str());
            AddDescText(color, true, " %+d", -p1);
            break;

        case 8: 	//	+?��??-?�졤?
            if (aPEEVals)
            {
                aPEEVals[PEEI_MAGICDAMAGE]	+= p0;
                aPEEVals[PEEI_GOLDDEF]		-= p1;
                aPEEVals[PEEI_WOODDEF]		-= p1;
                aPEEVals[PEEI_WATERDEF]		-= p1;
                aPEEVals[PEEI_FIREDEF]		-= p1;
                aPEEVals[PEEI_EARTHDEF]		-= p1;
            }
            AddDescText(color, false, GetWideString(ITEMDESC_ADDMAGICDAMAGE).toStdString().c_str());
            AddDescText(color, true, " %+d & ", p0);
            AddDescText(color, false, GetWideString(ITEMDESC_ALLMAGICDEF).toStdString().c_str());
            AddDescText(color, true, " %+d", -p1);
            break;

        case 9: 	//	???��????

            AddDescText(color, true, GetWideString(ITEMDESC_ATKTIME).toStdString().c_str(), -p0 * 0.05f);

            break;

        case 10:	//	???��?��??
        {
            if (aPEEVals)
            {
                float fDist = *(float*)&aPEEVals[PEEI_ATKDIST] + *(float*)&p0;
                aPEEVals[PEEI_ATKDIST] = *(DWORD*)&fDist;
            }
            AddDescText(color, true, GetWideString(ITEMDESC_ADDATKDIST).toStdString().c_str(), *(float*)&alcance);

            break;
        }
        case 11:	//	?��???��??

            AddDescText(color, true, GetWideString(ITEMDESC_CASTTIME).toStdString().c_str(), -p0);

            break;

        case 12: 	//	???����??��
            if (aPEEVals)
                aPEEVals[PEEI_PHYDEF] += p0;
            AddDescText(color, false, GetWideString(ITEMDESC_PHYDEFENCE).toStdString().c_str());
            AddDescText(color, true, " %+d", p0);
            break;

        case 13: 	//	???����??��(%)

            AddDescText(color, true, GetWideString(ITEMDESC_PHYDEFEXTRA).toStdString().c_str(), p0);

            break;

        case 14: 	//	????��??��
            if (aPEEVals)
            {
                aPEEVals[PEEI_GOLDDEF]	+= p0;
                aPEEVals[PEEI_WOODDEF]	+= p0;
                aPEEVals[PEEI_WATERDEF] += p0;
                aPEEVals[PEEI_FIREDEF]	+= p0;
                aPEEVals[PEEI_EARTHDEF] += p0;
            }
            AddDescText(color, false, GetWideString(ITEMDESC_ALLMAGICDEF).toStdString().c_str());
            AddDescText(color, true, " %+d", p0);
            break;

        case 15: 	//	??��?

            if (aPEEVals)
                aPEEVals[PEEI_GOLDDEF] += p0;
            AddDescText(color, false, GetWideString(ITEMDESC_GOLDDEFENCE).toStdString().c_str());

            if(p0 != p1 && p1 > 0)
                AddDescText(color, true, " +%d~%d", p0, p1);
            else
                AddDescText(color, true, " +%d", p0);

            break;

        case 16: 	//	??��?(%)
            ADD_RANGE_VALUE_DESC_ID_PERCENT(ITEMDESC_GOLDDEFEXTRA);
            break;

        case 17: 	//	??��?
            if (aPEEVals)
                aPEEVals[PEEI_WOODDEF] += p0;
            AddDescText(color, false, GetWideString(ITEMDESC_WOODDEFENCE).toStdString().c_str());

            if(p0 != p1 && p1 > 0)
                AddDescText(color, true, " +%d~%d", p0, p1);
            else
                AddDescText(color, true, " +%d", p0);
            break;

        case 18: 	//	??��?(%)
            ADD_RANGE_VALUE_DESC_ID_PERCENT(ITEMDESC_WOODDEFEXTRA);
            break;

        case 19: 	//	??��?
            if (aPEEVals)
                aPEEVals[PEEI_WATERDEF] += p0;
            AddDescText(color, false, GetWideString(ITEMDESC_WATERDEFENCE).toStdString().c_str());

            if(p0 != p1 && p1 > 0)
                AddDescText(color, true, " +%d~%d", p0, p1);
            else
                AddDescText(color, true, " +%d", p0);
            break;

        case 20: 	//	??��?(%)
            ADD_RANGE_VALUE_DESC_ID_PERCENT(ITEMDESC_WATERDEFEXTRA);
            break;

        case 21: 	//	??��?
            if (aPEEVals)
                aPEEVals[PEEI_FIREDEF] += p0;
            AddDescText(color, false, GetWideString(ITEMDESC_FIREDEFENCE).toStdString().c_str());

            if(p0 != p1 && p1 > 0)
                AddDescText(color, true, " +%d~%d", p0, p1);
            else
                AddDescText(color, true, " +%d", p0);
            break;

        case 22: 	//	??��?(%)
            ADD_RANGE_VALUE_DESC_ID_PERCENT(ITEMDESC_FIREDEFEXTRA);
            break;

        case 23: 	//	??��?
            if (aPEEVals)
                aPEEVals[PEEI_EARTHDEF] += p0;
            AddDescText(color, false, GetWideString(ITEMDESC_EARTHDEFENCE).toStdString().c_str());

            if(p0 != p1 && p1 > 0)
                AddDescText(color, true, " +%d~%d", p0, p1);
            else
                AddDescText(color, true, " +%d", p0);


            break;

        case 24: 	//	??��?(%)
            ADD_RANGE_VALUE_DESC_ID_PERCENT(ITEMDESC_EARTHDEFEXTRA);
            break;

        case 25: 	//	+??��?(%)-??��?(%)

            AddDescText(color, true, GetWideString(ITEMDESC_GOLDDEFEXTRA).toStdString().c_str(), p0);
            AddDescText(color, true, GetWideString(ITEMDESC_FIREDEFEXTRA).toStdString().c_str(), -p1);
            break;

        case 26: 	//	+??��?(%)-??��?(%)

            AddDescText(color, true, GetWideString(ITEMDESC_WOODDEFEXTRA).toStdString().c_str(), p0);
            AddDescText(color, true, GetWideString(ITEMDESC_GOLDDEFEXTRA).toStdString().c_str(), -p1);
            break;

        case 27: 	//	+??��?(%)-??��?(%)

            AddDescText(color, true, GetWideString(ITEMDESC_WATERDEFEXTRA).toStdString().c_str(), p0);
            AddDescText(color, true, GetWideString(ITEMDESC_EARTHDEFEXTRA).toStdString().c_str(), -p1);
            break;

        case 28: 	//	+??��?(%)-??��?(%)

            AddDescText(color, true, GetWideString(ITEMDESC_FIREDEFEXTRA).toStdString().c_str(), (p0));
            AddDescText(color, true, GetWideString(ITEMDESC_WATERDEFEXTRA).toStdString().c_str(), -(p1));
            break;

        case 29: 	//	+??��?(%)-??��?(%)

            AddDescText(color, true, GetWideString(ITEMDESC_EARTHDEFEXTRA).toStdString().c_str(), (p0));
            AddDescText(color, true, GetWideString(ITEMDESC_WOODDEFEXTRA).toStdString().c_str(), -(p1));
            break;

        case 30: 	//	+??��?-??��?
            if (aPEEVals)
            {
                aPEEVals[PEEI_GOLDDEF]	+= p0;
                aPEEVals[PEEI_FIREDEF]	-= p1;
            }
            AddDescText(color, false, GetWideString(ITEMDESC_GOLDDEFENCE).toStdString().c_str());
            AddDescText(color, true, " %+d & ", p0);
            AddDescText(color, false, GetWideString(ITEMDESC_FIREDEFENCE).toStdString().c_str());
            AddDescText(color, true, " %+d", -p1);
            break;

        case 31: 	//	+??��?-??��?

            if (aPEEVals)
            {
                aPEEVals[PEEI_WOODDEF]	+= p0;
                aPEEVals[PEEI_GOLDDEF]	-= p1;
            }
            AddDescText(color, false, GetWideString(ITEMDESC_WOODDEFENCE).toStdString().c_str());
            AddDescText(color, true, " %+d & ", p0);
            AddDescText(color, false, GetWideString(ITEMDESC_GOLDDEFENCE).toStdString().c_str());
            AddDescText(color, true, " %+d", -p1);
            break;

        case 32: 	//	+??��?-??��?
            if (aPEEVals)
            {
                aPEEVals[PEEI_WATERDEF]	+= p0;
                aPEEVals[PEEI_EARTHDEF]	-= p1;
            }
            AddDescText(color, false, GetWideString(ITEMDESC_WATERDEFENCE).toStdString().c_str());
            AddDescText(color, true, " %+d", p0);
            AddDescText(color, false, GetWideString(ITEMDESC_EARTHDEFENCE).toStdString().c_str());
            AddDescText(color, true, " %+d", -p1);
            break;

        case 33: 	//	+??��?-??��?

            if (aPEEVals)
            {
                aPEEVals[PEEI_FIREDEF]	+= p0;
                aPEEVals[PEEI_WATERDEF]	-= p1;
            }
            AddDescText(color, false, GetWideString(ITEMDESC_FIREDEFENCE).toStdString().c_str());
            AddDescText(color, true, " %+d", p0);
            AddDescText(color, false, GetWideString(ITEMDESC_WATERDEFENCE).toStdString().c_str());
            AddDescText(color, true, " %+d", -p1);
            break;

        case 34: 	//	+??��?-??��?

            if (aPEEVals)
            {
                aPEEVals[PEEI_EARTHDEF]	+= p0;
                aPEEVals[PEEI_WOODDEF]	-= p1;
            }
            AddDescText(color, false, GetWideString(ITEMDESC_EARTHDEFENCE).toStdString().c_str());
            AddDescText(color, true, " %+d & ", p0);
            AddDescText(color, false, GetWideString(ITEMDESC_WOODDEFENCE).toStdString().c_str());
            AddDescText(color, true, " %+d", -p1);
            break;

        case 35: 	//	HP
            if (aPEEVals)
                aPEEVals[PEEI_HP] += p0;

            AddDescText(color, false, GetWideString(ITEMDESC_ADDHP).toStdString().c_str());
            AddDescText(color, true, " %+d", p0);
            break;

        case 36: 	//	MP
            if (aPEEVals)
                aPEEVals[PEEI_MP] += p0;
            AddDescText(color, false, GetWideString(ITEMDESC_ADDMP).toStdString().c_str());
            AddDescText(color, true, " %+d", p0);
            break;

        case 37: 	//	HP(%)

            AddDescText(color, true, GetWideString(ITEMDESC_HPEXTRA).toStdString().c_str(), p0);
            break;

        case 38: 	//	MP(%)

            AddDescText(color, true, GetWideString(ITEMDESC_MPEXTRA).toStdString().c_str(), p0);
            break;

        case 39: 	//	HP????????

            AddDescText(color, true, GetWideString(ITEMDESC_HPRECOVER).toStdString().c_str(), p0 / 2);
            break;

        case 40: 	//	MP????????

            AddDescText(color, true, GetWideString(ITEMDESC_MPRECOVER).toStdString().c_str(), p0 / 2);
            break;

        case 41: 	//	????

            if(bLocal)
            {
                if(p0 != p1 && p1 > 0)
                {
                    AddDescText(color, false, GetWideString(ITEMDESC_STRENGTH).toStdString().c_str(), p0);
                    AddDescText(color, true, "~%d", p1);
                }
                else
                {
                    AddDescText(color, true, GetWideString(ITEMDESC_STRENGTH).toStdString().c_str(), p0);
                }
            }
            else
            {
                AddDescText(color, true, GetWideString(ITEMDESC_STRENGTH).toStdString().c_str(), p0);
            }
            break;

        case 42: 	//	????

            if(bLocal)
            {
                if(p0 != p1 && p1 > 0)
                {
                    AddDescText(color, false, GetWideString(ITEMDESC_AGILITY).toStdString().c_str(), p0);
                    AddDescText(color, true, "~%d", p1);
                }
                else
                {
                    AddDescText(color, true, GetWideString(ITEMDESC_AGILITY).toStdString().c_str(), p0);
                }
            }
            else
            {
                AddDescText(color, true, GetWideString(ITEMDESC_AGILITY).toStdString().c_str(), p0);
            }
            break;

        case 43: 	//	?��??

            if(bLocal)
            {
                if(p0 != p1 && p1 > 0)
                {
                    AddDescText(color, false, GetWideString(ITEMDESC_ENERGY).toStdString().c_str(), p0);
                    AddDescText(color, true, "~%d", p1);
                }
                else
                {
                    AddDescText(color, true, GetWideString(ITEMDESC_ENERGY).toStdString().c_str(), p0);
                }
            }
            else
            {
                AddDescText(color, true, GetWideString(ITEMDESC_ENERGY).toStdString().c_str(), p0);
            }
            break;

        case 44: 	//	????

            if(bLocal)
            {
                if(p0 != p1 && p1 > 0)
                {
                    AddDescText(color, false, GetWideString(ITEMDESC_VITALITY).toStdString().c_str(), p0);
                    AddDescText(color, true, "~%d", p1);
                }
                else
                {
                    AddDescText(color, true, GetWideString(ITEMDESC_VITALITY).toStdString().c_str(), p0);
                }
            }
            else
            {
                AddDescText(color, true, GetWideString(ITEMDESC_VITALITY).toStdString().c_str(), p0);
            }
            break;

        case 45: 	//	???��???��??

            AddDescText(color, true, GetWideString(ITEMDESC_DEADLYSTRIKE).toStdString().c_str(), p0);

            break;

        case 46: 	//	?��??

            if(bLocal)
            {
                if(p0 != p1 && p1 > 0)
                {
                    AddDescText(color, false, GetWideString(ITEMDESC_ATKRATING).toStdString().c_str(), p0);
                    AddDescText(color, true, "~%d", p1);
                }
                else
                {
                    AddDescText(color, true, GetWideString(ITEMDESC_ATKRATING).toStdString().c_str(), p0);
                }
            }
            else
            {
                AddDescText(color, true, GetWideString(ITEMDESC_ATKRATING).toStdString().c_str(), p0);
            }
            break;

        case 47: 	//	?��??(%)

            AddDescText(color, true, GetWideString(ITEMDESC_ATKRATINGEXTRA).toStdString().c_str(), p0);

            break;

        case 48: 	//	????????

            AddDescText(color, true, GetWideString(ITEMDESC_RUNSPEED).toStdString().c_str(), *(float*)&alcance);
            break;

        case 49: 	//	????????(%)

            AddDescText(color, true, GetWideString(ITEMDESC_RUNSPEEDEXTRA).toStdString().c_str(), p0);

            break;

        case 50: 	//	????
            if (aPEEVals)
                aPEEVals[PEEI_DODGE] += p0;
            AddDescText(color, false, GetWideString(ITEMDESC_DODGE).toStdString().c_str());
            AddDescText(color, true, " %+d", p0);
            break;

        case 51:
            AddDescText(color, true, GetWideString(ITEMDESC_DODGEEXTRA).toStdString().c_str(), p0);

            break;

        case 52: 	//	??????

            AddDescText(color, false, GetWideString(ITEMDESC_ENDURANCE).toStdString().c_str());
            AddDescText(color, true, " %+d", p0);
            break;

        case 53: 	//	??????(%)

            AddDescText(color, true, GetWideString(ITEMDESC_ENDURANCEEXTRA).toStdString().c_str(), (p0));
            break;

        case 54: 	//	???��????

            AddDescText(color, true, GetWideString(ITEMDESC_PHYRESIST).toStdString().c_str(), p0);

            break;

        case 55: 	//	????????
        {
            //	Get skill description
            QString skill = pw.listSkillDesc[alcance];
            skill.replace("\r", "");
            skill.replace("\r\n", "");
            skill.replace("\n\r", "");
            skill.replace("\n", "");
            QRegularExpression regex("\\^([0-9A-Fa-f]{6})");
            skill.remove(regex);
            AddDescText(color, true, skill.toStdString().c_str());
            break;
        }
        case 56: 	//	������??��?��

            if((p0) != (p1))
            {
                AddDescText(color, false, GetWideString(ITEMDESC_REQEXTRA).toStdString().c_str(), -(p0));
                AddDescText(color, true, "~%d", p1);
            }
            else
            {
                AddDescText(color, true, GetWideString(ITEMDESC_REQEXTRA).toStdString().c_str(), -(p0));
            }

            break;

        case 57: 	//	????????

            AddDescText(color, true, GetWideString(ITEMDESC_RANDOMPROP).toStdString().c_str());
            break;

        case 58:	//	???��??????

            AddDescText(color, true, GetWideString(ITEMDESC_EXP).toStdString().c_str(), p0);

            break;

        case 59:	//	???��????

            AddDescText(color, true, GetWideString(ITEMDESC_ATK_DEGREE).toStdString().c_str(), p0);
            break;

        case 60:	//	��??��????

            AddDescText(color, true, GetWideString(ITEMDESC_DEF_DEGREE).toStdString().c_str(), p0);
            break;

        case 61:	//	????��??��?��%??

            AddDescText(color, true, GetWideString(ITEMDESC_TOTAL_DEFENCE_ADD).toStdString().c_str(), (p0));

            break;

        case 62:	//	????????

            AddDescText(color, true, GetWideString(ITEMDESC_PROFVIEW).toStdString().c_str());
            break;

        case 63:	//	?��??

            AddDescText(color, true, GetWideString(ITEMDESC_SOULPOWER).toStdString().c_str(), p0);
            break;

        case 64: 	//	????????(%)

            AddDescText(color, true, GetWideString(ITEMDESC_GOLDRESIST).toStdString().c_str(), p0);

            break;

        case 65: 	//	?
            AddDescText(color, true, GetWideString(ITEMDESC_WOODRESIST).toStdString().c_str(), p0);

            break;

        case 66: 	//	????????(%)

            AddDescText(color, true, GetWideString(ITEMDESC_WATERRESIST).toStdString().c_str(), p0);

            break;

        case 67: 	//	????????(%)


            AddDescText(color, true, GetWideString(ITEMDESC_FIRERESIST).toStdString().c_str(), p0);

            break;

        case 68: 	//	????????(%)


            AddDescText(color, true, GetWideString(ITEMDESC_EARTHRESIST).toStdString().c_str(), p0);

            break;

        case 69: 	//	????????(%)


            AddDescText(color, true, GetWideString(ITEMDESC_ALLMAGICRESIST).toStdString().c_str(), p0);

            break;

        case 70:	//	???��????��??��?��?????????��??????

            ADD_RANGE_VALUE_DESC_ID_NORMAL(ITEMDESC_ATK_DEGREE)
                    break;

        case 71:	//	��??��????��??��?��?????????��??????

            ADD_RANGE_VALUE_DESC_ID_NORMAL(ITEMDESC_DEF_DEGREE)
                    break;

        case 72:	//	???��???��??(%)��??��?��?????????��??????

            ADD_RANGE_VALUE_DESC_ID_PERCENT(ITEMDESC_DEADLYSTRIKE)
                    break;

        case 73: 	//	HP��??��?��?????????��??????

            ADD_RANGE_VALUE_DESC_STR_NORMAL(ITEMDESC_ADDHP)
                    break;

        case 74: 	//	MP��??��?��?????????��??????

            ADD_RANGE_VALUE_DESC_STR_NORMAL(ITEMDESC_ADDMP)
                    break;

        case 75:	//	?��??(%)��??��?��?????????��??????

            ADD_RANGE_VALUE_DESC_ID_PERCENT(ITEMDESC_ATKRATINGEXTRA)
                    break;

        case 76:	//	???����??����??��?��?????????��??????

            ADD_RANGE_VALUE_DESC_STR_NORMAL(ITEMDESC_PHYDEFENCE)
                    break;

        case 77:	//	????��??����??��?��?????????��??????

            ADD_RANGE_VALUE_DESC_STR_NORMAL(ITEMDESC_ALLMAGICDEF)
                    break;

        case 78:	//	???��????(%)��??��?��?????????��??????

            ADD_RANGE_VALUE_DESC_ID_PERCENT(ITEMDESC_PHYRESIST)
                    break;

        case 79:	//	????????(%)��??��?��?????????��??????

            ADD_RANGE_VALUE_DESC_ID_PERCENT(ITEMDESC_ALLMAGICRESIST)
                    break;

        case 80:	//	?��???��??(%)��??��?��?????????��??????

            ADD_RANGE_VALUE_DESC_ID_MINUS_PERCENT_1(ITEMDESC_CASTTIME)
                    break;

        case 81:	//	???��?��??��??��?��?????????��??????

            ADD_RANGE_VALUE_DESC_ID_FLOAT2(ITEMDESC_ADDATKDIST)
                    break;

        case 82:	//	MP????????��??��?��?????????��??????

            ADD_RANGE_VALUE_DESC_ID_HALF(ITEMDESC_MPRECOVER)
                    break;

        case 83:	//	???����??��(%)��??��?��?????????��??????

            ADD_RANGE_VALUE_DESC_ID_PERCENT(ITEMDESC_PHYDEFEXTRA)
                    break;

        case 84:	//	????��??��(%)��??��?��?????????��??????

            ADD_RANGE_VALUE_DESC_ID_PERCENT(ITEMDESC_TOTAL_DEFENCE_ADD)
                    break;

        case 85:	//	HP????????��??��?��?????????��??????

            ADD_RANGE_VALUE_DESC_ID_HALF(ITEMDESC_HPRECOVER)
                    break;

        case 86:	//	????��??��?��?????????��??????

            ADD_RANGE_VALUE_DESC_STR_NORMAL(ITEMDESC_DODGE)
                    break;

        case 87:	//	???��???��????��??��?��?????????��??????

            ADD_RANGE_VALUE_DESC_ID_NORMAL(ITEMDESC_MAXPHYDAMAGE)
                    break;

        case 88:	//	?�졤��???��????��??��?��?????????��??????

            ADD_RANGE_VALUE_DESC_ID_NORMAL(ITEMDESC_MAXMAGICDAMAGE)
                    break;

        case 89:	//	������??��?����??��?��?????????��??????

            ADD_RANGE_VALUE_DESC_ID_MINUS_PERCENT_2(ITEMDESC_REQEXTRA)
                    break;

        case 90:	//	???��????

            AddDescText(color, true, GetWideString(ITEMDESC_PENETRATION).toStdString().c_str(), p0);
            break;

        case 91:	//	?��?��????

            AddDescText(color, true, GetWideString(ITEMDESC_RESILIENCE).toStdString().c_str(), p0);
            break;

        case 92: 	//	+??��?+?�졤?

            if (aPEEVals)
            {
                aPEEVals[PEEI_PHYDEF]	+= p0;
                aPEEVals[PEEI_GOLDDEF]	+= p1;
                aPEEVals[PEEI_WOODDEF]	+= p1;
                aPEEVals[PEEI_WATERDEF] += p1;
                aPEEVals[PEEI_FIREDEF]	+= p1;
                aPEEVals[PEEI_EARTHDEF] += p1;
            }
            AddDescText(color, false, GetWideString(ITEMDESC_PHYDEFENCE).toStdString().c_str());
            AddDescText(color, true, " %+d & ", p0);
            AddDescText(color, false, GetWideString(ITEMDESC_ALLMAGICDEF).toStdString().c_str());
            AddDescText(color, true, " %+d", p1);
            break;

        case 93: 	//	????HP
            AddDescText(color, false, GetWideString(ITEMDESC_ADDHP).toStdString().c_str());
            AddDescText(color, true, " %+d", p0);
            break;

        case 94: 	//	????HP��??��
            ADD_RANGE_VALUE_DESC_STR_NORMAL(ITEMDESC_ADDHP)
                    break;

        case 95: 	//	????
            AddDescText(color, true, GetWideString(ITEMDESC_STRENGTH).toStdString().c_str(), p0);
            break;

        case 96: 	//	????
            AddDescText(color, true, GetWideString(ITEMDESC_AGILITY).toStdString().c_str(), p0);
            break;

        case 97: 	//	?��??
            AddDescText(color, true, GetWideString(ITEMDESC_ENERGY).toStdString().c_str(), p0);
            break;

        case 98:	//	????
            AddDescText(color, true, GetWideString(ITEMDESC_VITALITY).toStdString().c_str(), p0);
            break;

        case 99: 	//	????MP
            AddDescText(color, false, GetWideString(ITEMDESC_ADDMP).toStdString().c_str());
            AddDescText(color, true, " %+d", p0);
            break;

        case 100:	//	ĥ��ʯ��������
            AddDescText(color, false, GetWideString(ITEMDESC_ADDPHYDAMAGE).toStdString().c_str());
            AddDescText(color, true, " %+d", p0);
            break;

        case 101:	//	ĥ��ʯ������������
            AddDescText(color, false, GetWideString(ITEMDESC_MAXPHYDAMAGE).toStdString().c_str(), p0);
            break;

        case 102:	//	ĥ��ʯħ������
            AddDescText(color, false, GetWideString(ITEMDESC_ADDMAGICDAMAGE).toStdString().c_str());
            AddDescText(color, false, " %+d", p0);
            break;

        case 103:	//	ĥ��ʯħ����������
            AddDescText(color, false, GetWideString(ITEMDESC_MAXMAGICDAMAGE).toStdString().c_str(), p0);
            break;

        case 104:	//	ĥ��ʯ��������
            AddDescText(color, false, GetWideString(ITEMDESC_PHYDEFENCE).toStdString().c_str());
            AddDescText(color, false, " %+d", p0);
            break;

        case 105:	//	ĥ��ʯHP
            AddDescText(color, false, GetWideString(ITEMDESC_ADDHP).toStdString().c_str());
            AddDescText(color, false, " %+d", p0);
            break;

        case 106:	//	ĥ��ʯ����
            AddDescText(color, false, GetWideString(ITEMDESC_STRENGTH).toStdString().c_str(), p0);
            break;

        case 107:	//	ĥ��ʯ����
            AddDescText(color, false, GetWideString(ITEMDESC_AGILITY).toStdString().c_str(), p0);
            break;

        case 108:	//	ĥ��ʯ����
            AddDescText(color, false, GetWideString(ITEMDESC_ENERGY).toStdString().c_str(), p0);
            break;

        case 109:	//	ĥ��ʯ������
            AddDescText(color, false, GetWideString(ITEMDESC_ATKRATING).toStdString().c_str(), p0);
            break;

        case 110:	//	ĥ��ʯ����һ����

            AddDescText(color, false, GetWideString(ITEMDESC_DEADLYSTRIKE).toStdString().c_str(), p0);
            break;

        case 111:	//	ĥ��ʯ�����ȼ�
            AddDescText(color, false, GetWideString(ITEMDESC_ATK_DEGREE).toStdString().c_str(), p0);
            break;

        case 112:	//	ĥ��ʯ�����ȼ�
            AddDescText(color, false, GetWideString(ITEMDESC_DEF_DEGREE).toStdString().c_str(), p0);
            break;

        case 113:	//	ĥ��ʯ����(%d)

            AddDescText(color, false, GetWideString(ITEMDESC_CASTTIME).toStdString().c_str(), -p0);
            break;

        case 114:	//	ĥ��ʯħ������
            AddDescText(color, false, GetWideString(ITEMDESC_ALLMAGICDEF).toStdString().c_str());
            AddDescText(color, false, " %+d", p0);
            break;

        case 115:	//	ĥ��ʯ��˼���
            AddDescText(color, false, GetWideString(ITEMDESC_ADDRIDEONPETSPEED).toStdString().c_str(), *(float*)&alcance);
            break;

        case 116:	//	ĥ��ʯ��˼���
            AddDescText(color, false, GetWideString(ITEMDESC_ADDFLYSPEED2).toStdString().c_str(), *(float*)&alcance);
            break;

        case 160: 	//	???????��??
            AddDescText(color, false, GetWideString(ITEMDESC_VIGOUR).toStdString().c_str());
            AddDescText(color, true, " %+d", p0);
            break;

        case 161:	//	???????��???��
            AddDescText(color, false, GetWideString(ITEMDESC_ADDPHYDAMAGE).toStdString().c_str());
            AddDescText(color, true, " %+d", p0);

            break;

        case 162:	//	?????�졤��???��

            AddDescText(color, false, GetWideString(ITEMDESC_ADDMAGICDAMAGE).toStdString().c_str());
            AddDescText(color, true, " %+d", p0);

            break;

        case 163:	//	???????����??��

            AddDescText(color, false, GetWideString(ITEMDESC_DEFENCE).toStdString().c_str());
            AddDescText(color, true, " %+d", p0);

            break;

        case 164:	//	??????��?

            AddDescText(color, false, GetWideString(ITEMDESC_GOLDDEFENCE).toStdString().c_str());
            AddDescText(color, true, " %+d", p0);

            break;

        case 165:	//	??????��?

            AddDescText(color, false, GetWideString(ITEMDESC_ADDHP).toStdString().c_str());
            AddDescText(color, true, " %+d", p0);

            break;

        case 166:	//	??????��?

            AddDescText(color, false, GetWideString(ITEMDESC_VIGOUR).toStdString().c_str());
            AddDescText(color, true, " %+d", p0);

            break;

        case 167:	//	??????��?

            AddDescText(color, false, GetWideString(ITEMDESC_GOLDDEFENCE).toStdString().c_str());
            AddDescText(color, true, " %+d", p0);

            break;

        case 168:	//	??????��?

            AddDescText(color, false, GetWideString(ITEMDESC_WOODDEFENCE).toStdString().c_str());
            AddDescText(color, true, " %+d", p0);

            break;

        case 169:	//	??????��?

            AddDescText(color, false, GetWideString(ITEMDESC_WATERDEFENCE).toStdString().c_str());
            AddDescText(color, true, " %+d", p0);

            break;

        case 170:	//	??????��?

            AddDescText(color, false, GetWideString(ITEMDESC_FIREDEFENCE).toStdString().c_str());
            AddDescText(color, true, " %+d", p0);

            break;

        case 171:	//	??????��?

            AddDescText(color, false, GetWideString(ITEMDESC_EARTHDEFENCE).toStdString().c_str());
            AddDescText(color, true, " %+d", p0);

            break;

        case 172: 	//	?????��??

            AddDescText(color, true, GetWideString(ITEMDESC_ATKRATING).toStdString().c_str(), p0);
            break;

        case 173: 	//	????????

            AddDescText(color, false, GetWideString(ITEMDESC_DODGE).toStdString().c_str());
            AddDescText(color, true, " %+d", p0);
            break;

        case 174: 	//	????????

            AddDescText(color, false, GetWideString(ITEMDESC_VIGOUR).toStdString().c_str());
            AddDescText(color, true, " %+d", p0);
            break;

        case 175: 	//	????????


            AddDescText(color, true, GetWideString(ITEMDESC_PHYRESIST).toStdString().c_str(), p0);

            break;

        case 176: 	//	????????


            AddDescText(color, true, GetWideString(ITEMDESC_ALLMAGICRESIST).toStdString().c_str(), p0);

            break;

        case 177:	//	???????��???��
            ADD_RANGE_VALUE_DESC_STR_NORMAL(ITEMDESC_PHYDEFENCE);
            break;

        case 178:	//	???????��???��
            ADD_RANGE_VALUE_DESC_STR_NORMAL(ITEMDESC_ALLMAGICDEF);
            break;

        case 179:	//	???????��???��
            ADD_RANGE_VALUE_DESC_STR_NORMAL(ITEMDESC_VIGOUR);
            break;

        case 180:	//	???????��???��
            ADD_RANGE_VALUE_DESC_STR_NORMAL(ITEMDESC_PHY_PENETRATION);
            break;

        case 181:	//	???????��???��
            ADD_RANGE_VALUE_DESC_STR_NORMAL(ITEMDESC_ALLMAGIC_PENETRATION);
            break;

        case 200:	//	???????��???��
            AddDescText(color, false, "Refino");
            AddDescText(color, true, " %+d: ", p1);
            AddDescText(color, false, GetWideString(ITEMDESC_ADDPHYDAMAGE).toStdString().c_str());
            AddDescText(color, true, " %+d", p0);

            break;

        case 201:	//	?????�졤��???��

            AddDescText(color, false, "Refino");
            AddDescText(color, true, " %+d: ", p1);
            AddDescText(color, false, GetWideString(ITEMDESC_ADDMAGICDAMAGE).toStdString().c_str());
            AddDescText(color, true, " %+d", p0);

            break;

        case 202:	//	???????����??��

            AddDescText(color, false, "Refino");
            AddDescText(color, true, " %+d: ", p1);
            AddDescText(color, false, GetWideString(ITEMDESC_DEFENCE).toStdString().c_str());
            AddDescText(color, true, " %+d", p0);

            break;

        case 203:	//	??????��?

            AddDescText(color, false, "Refino");
            AddDescText(color, true, " %+d: ", p1);
            AddDescText(color, false, GetWideString(ITEMDESC_GOLDDEFENCE).toStdString().c_str());
            AddDescText(color, true, " %+d", p0);

            break;

        case 204:	//	??????��?

            AddDescText(color, false, "Refino");
            AddDescText(color, true, " %+d: ", p1);
            AddDescText(color, false, GetWideString(ITEMDESC_WOODDEFENCE).toStdString().c_str());
            AddDescText(color, true, " %+d", p0);

            break;

        case 205:	//	??????��?

            AddDescText(color, false, "Refino");
            AddDescText(color, true, " %+d: ", p1);
            AddDescText(color, false, GetWideString(ITEMDESC_WATERDEFENCE).toStdString().c_str());
            AddDescText(color, true, " %+d", p0);

            break;

        case 206:	//	??????��?

            AddDescText(color, false, "Refino");
            AddDescText(color, true, " %+d: ", p1);
            AddDescText(color, false, GetWideString(ITEMDESC_FIREDEFENCE).toStdString().c_str());
            AddDescText(color, true, " %+d", p0);

            break;

        case 207:	//	??????��?

            AddDescText(color, false, "Refino");
            AddDescText(color, true, " %+d: ", p1);
            AddDescText(color, false, GetWideString(ITEMDESC_EARTHDEFENCE).toStdString().c_str());
            AddDescText(color, true, " %+d", p0);

            break;

        case 208:	//	????HP
            AddDescText(color, false, "Refino");
            AddDescText(color, true, " %+d: ", p1);
            AddDescText(color, false, GetWideString(ITEMDESC_ADDHP).toStdString().c_str());
            AddDescText(color, true, " %+d", p0);

            break;

        case 209:	//	????????

            AddDescText(color, false, "Refino");
            AddDescText(color, true, " %+d: ", p1);
            AddDescText(color, false, GetWideString(ITEMDESC_DODGE).toStdString().c_str());
            AddDescText(color, true, " %+d", p0);
            break;

        case 210:	//	????????��??��

            AddDescText(color, false, "Refino");
            AddDescText(color, true, " %+d: ", p1);
            AddDescText(color, false, GetWideString(ITEMDESC_ALLMAGICDEF).toStdString().c_str());
            AddDescText(color, true, " %+d", p0);

            break;

        case 211:	//	???????��???�� & ?�졤��???��

            AddDescText(color, false, "Refino");
            AddDescText(color, true, " %+d: ", p1);
            AddDescText(color, false, GetWideString(ITEMDESC_PHYDAMAGE).toStdString().c_str());
            AddDescText(color, true, " %+d &", p0);
            AddDescText(color, false, GetWideString(ITEMDESC_MAGICDAMAGE).toStdString().c_str());
            AddDescText(color, true, " %+d", p0);

            break;

        case 212:	//	???????����??�� & ?�졤����??��

            AddDescText(color, false, "Refino");
            AddDescText(color, true, " %+d: ", p1);
            AddDescText(color, false, GetWideString(ITEMDESC_PHYDEFENCE).toStdString().c_str());
            AddDescText(color, true, " %+d &", p0);
            AddDescText(color, false, GetWideString(ITEMDESC_ALLMAGICDEF).toStdString().c_str());
            AddDescText(color, true, " %+d", p0);

            break;

        case 215:	//	???????����??�� & ?�졤����??��

            AddDescText(color, true, GetWideString(ITEMDESC_MAIORNIVEL).toStdString().c_str(), p0);
            break;

        case 216:	//	???????����??�� & ?�졤����??��

            AddDescText(color, false, GetWideString(ITEMDESC_ADDPHYDAMAGE).toStdString().c_str());
            AddDescText(color, true, " %+d", p0);
            break;

        case 217:	//	???????����??�� & ?�졤����??��

            AddDescText(color, false, GetWideString(ITEMDESC_ADDMAGICDAMAGE).toStdString().c_str());
            AddDescText(color, true, " %+d", p0);
            break;

        case 218:
            AddDescText(color, true, GetWideString(ITEMDESC_ATKTIME).toStdString().c_str(), -p0 * 0.05f);
            break;

        case 219: 	//	HP��??��?��?????????��??????
            ADD_RANGE_VALUE_DESC_STR_NORMAL(ITEMDESC_ADDHP);
            break;

        case 220: 	//	????????(%)


            AddDescText(color, true, GetWideString(ITEMDESC_RUNSPEEDEXTRA).toStdString().c_str(), p0);

            break;

            //	?????��??????
        case 120: 	//	??????��?

            AddDescText(color, false, GetWideString(ITEMDESC_GOLDDEFENCE).toStdString().c_str());
            AddDescText(color, true, " %+d", p0);
            break;

        case 121: 	//	??????��?

            AddDescText(color, false, GetWideString(ITEMDESC_WOODDEFENCE).toStdString().c_str());
            AddDescText(color, true, " %+d", p0);
            break;

        case 122: 	//	??????��?

            AddDescText(color, false, GetWideString(ITEMDESC_WATERDEFENCE).toStdString().c_str());
            AddDescText(color, true, " %+d", p0);
            break;

        case 123: 	//	??????��?

            AddDescText(color, false, GetWideString(ITEMDESC_FIREDEFENCE).toStdString().c_str());
            AddDescText(color, true, " %+d", p0);
            break;

        case 124: 	//	??????��?

            AddDescText(color, false, GetWideString(ITEMDESC_EARTHDEFENCE).toStdString().c_str());
            AddDescText(color, true, " %+d", p0);
            break;

        case 125: 	//	?????��??

            AddDescText(color, true, GetWideString(ITEMDESC_ATKRATING).toStdString().c_str(), p0);
            break;

        case 126: 	//	????????

            AddDescText(color, false, GetWideString(ITEMDESC_DODGE).toStdString().c_str());
            AddDescText(color, true, " %+d", p0);
            break;

        case 127: 	//	????MP

            AddDescText(color, false, GetWideString(ITEMDESC_ADDMP).toStdString().c_str());
            AddDescText(color, true, " %+d", p0);
            break;

        case 128: 	//	????????

            if(bLocal)
            {
                if(p0 != p1 && p1 > 0)
                {
                    AddDescText(color, false, GetWideString(ITEMDESC_VITALITY).toStdString().c_str(), p0);
                    AddDescText(color, true, "~%d", p1);
                }
                else
                {
                    AddDescText(color, true, GetWideString(ITEMDESC_VITALITY).toStdString().c_str(), p0);
                }
            }
            else
            {
                AddDescText(color, true, GetWideString(ITEMDESC_VITALITY).toStdString().c_str(), p0);
            }
            break;

        case 129: 	//	????????

            if(bLocal)
            {
                if(p0 != p1 && p1 > 0)
                {
                    AddDescText(color, false, GetWideString(ITEMDESC_STRENGTH).toStdString().c_str(), p0);
                    AddDescText(color, true, "~%d", p1);
                }
                else
                {
                    AddDescText(color, true, GetWideString(ITEMDESC_STRENGTH).toStdString().c_str(), p0);
                }
            }
            else
            {
                AddDescText(color, true, GetWideString(ITEMDESC_STRENGTH).toStdString().c_str(), p0);
            }
            break;

        case 130: 	//	????????

            if(bLocal)
            {
                if(p0 != p1 && p1 > 0)
                {
                    AddDescText(color, false, GetWideString(ITEMDESC_AGILITY).toStdString().c_str(), p0);
                    AddDescText(color, true, "~%d", p1);
                }
                else
                {
                    AddDescText(color, true, GetWideString(ITEMDESC_AGILITY).toStdString().c_str(), p0);
                }
            }
            else
            {
                AddDescText(color, true, GetWideString(ITEMDESC_AGILITY).toStdString().c_str(), p0);
            }
            break;

        case 131: 	//	?????��??

            if(bLocal)
            {
                if(p0 != p1 && p1 > 0)
                {
                    AddDescText(color, false, GetWideString(ITEMDESC_ENERGY).toStdString().c_str(), p0);
                    AddDescText(color, true, "~%d", p1);
                }
                else
                {
                    AddDescText(color, true, GetWideString(ITEMDESC_ENERGY).toStdString().c_str(), p0);
                }
            }
            else
            {
                AddDescText(color, true, GetWideString(ITEMDESC_ENERGY).toStdString().c_str(), p0);
            }
            break;

        case 132: 	//	????HP

            AddDescText(color, false, GetWideString(ITEMDESC_ADDHP).toStdString().c_str());
            AddDescText(color, true, " %+d", p0);
            break;

        case 133: 	//	???????����??��

            AddDescText(color, false, GetWideString(ITEMDESC_PHYDEFENCE).toStdString().c_str());
            AddDescText(color, true, " %+d", p0);
            break;

        case 134: 	//	????????��??��

            AddDescText(color, false, GetWideString(ITEMDESC_ALLMAGICDEF).toStdString().c_str());
            AddDescText(color, true, " %+d", p0);
            break;

        case 135:	//	???????��???��

            AddDescText(color, false, GetWideString(ITEMDESC_ADDPHYDAMAGE).toStdString().c_str());
            AddDescText(color, true, " %+d", p0);
            break;

        case 136:	//	?????�졤��???��

            AddDescText(color, false, GetWideString(ITEMDESC_ADDMAGICDAMAGE).toStdString().c_str());
            AddDescText(color, true, " %+d", p0);
            break;

        case 137: 	//	????????????(%)


            AddDescText(color, true, GetWideString(ITEMDESC_GOLDRESIST).toStdString().c_str(), p0);

            break;

        case 138: 	//	????????????(%)


            AddDescText(color, true, GetWideString(ITEMDESC_WOODRESIST).toStdString().c_str(), p0);

            break;

        case 139: 	//	????????????(%)


            AddDescText(color, true, GetWideString(ITEMDESC_WATERRESIST).toStdString().c_str(), p0);

            break;

        case 140: 	//	????????????(%)


            AddDescText(color, true, GetWideString(ITEMDESC_FIRERESIST).toStdString().c_str(), p0);

            break;

        case 141: 	//	????????????(%)


            AddDescText(color, true, GetWideString(ITEMDESC_EARTHRESIST).toStdString().c_str(), p0);

            break;

        case 142: 	//	????????????(%)


            AddDescText(color, true, GetWideString(ITEMDESC_ALLMAGICRESIST).toStdString().c_str(), p0);

            break;

        case 143: 	//	???????��???��??


            AddDescText(color, true, GetWideString(ITEMDESC_DEADLYSTRIKE).toStdString().c_str(), p0);

            break;

        case 144:	//	???????��????

            AddDescText(color, true, GetWideString(ITEMDESC_ATK_DEGREE).toStdString().c_str(), p0);
            break;

        case 145:	//	????��??��????

            AddDescText(color, true, GetWideString(ITEMDESC_DEF_DEGREE).toStdString().c_str(), p0);
            break;

        case 146: 	//	???????��????


            AddDescText(color, true, GetWideString(ITEMDESC_PHYRESIST).toStdString().c_str(), p0);

            break;

        case 147: 	//	???????��????
            AddDescText(color, false, GetWideString(ITEMDESC_VIGOUR).toStdString().c_str());
            AddDescText(color, true, " %+d", p0);
            break;

        case 150:


            AddDescText(color, true, GetWideString(ITEMDESC_DEADLYSTRIKE).toStdString().c_str(), p0);

            break;
        case 151:


            AddDescText(color, true, GetWideString(ITEMDESC_DEADLYSTRIKE).toStdString().c_str(), p0);

            break;
        case 152:


            AddDescText(color, true, GetWideString(ITEMDESC_DEADLYSTRIKE).toStdString().c_str(), p0);

            break;
        case 153:

            AddDescText(color, true, GetWideString(ITEMDESC_DEADLYSTRIKE).toStdString().c_str(), p0);

            break;
        case 154:


            AddDescText(color, true, GetWideString(ITEMDESC_DEADLYSTRIKE).toStdString().c_str(), p0);

            break;
        case 155:


            AddDescText(color, true, GetWideString(ITEMDESC_DEADLYSTRIKE).toStdString().c_str(), p0);

            break;

        case 156:
        {
            AddDescText(color, true, GetWideString(ITEMDESC_SOULPOWER).toStdString().c_str(), p0);
        }break;


        case 182:
        {
            AddDescText(color, false, GetWideString(ITEMDESC_VIGOUR).toStdString().c_str());
            AddDescText(color, true, " %+d", p0);
        }break;

        default:

            AddDescText(color, true, GetWideString(ITEMDESC_ERRORPROP).toStdString().c_str(), idProp);
            break;
        }
    }
    return desc;
}

QString PlayerEditor::GetHtmlAddonName(int idProp, int p0, int p1, int p2, int* aPEEVals, int* aRefines, int color)
{
    pwAdmin &pw = pwAdmin::getInstance();
    quint8 byPropType = (qint8)pw.addonsList.value(QString::number(idProp)).toInt();
    //int color = ITEMDESC_COL_LIGHTBLUE;
    bool bLocal = true;
#define ADD_RANGE_VALUE_DESC_ID(id_first_format_str, second_format_str, value0, value1, value2)	\
    if(bLocal)\
    {\
    if(p0 != p1 && p1 > 0)\
    {\
    AddHtmlDescText(color, false, GetWideString((id_first_format_str)).toStdString().c_str(), (value0));\
    AddHtmlDescText(color, true, (second_format_str), (value1));\
}\
    else\
    {\
    AddHtmlDescText(color, true, GetWideString((id_first_format_str)).toStdString().c_str(), (value0));\
}\
}\
    else\
    {\
    AddHtmlDescText(color, true, GetWideString((id_first_format_str)).toStdString().c_str(), (value2));\
}

#define ADD_RANGE_VALUE_DESC_STR(id_first_format_1, first_format_str_2, second_format_str, value0, value1, value2)	\
    {\
    QString strFirstFormat = QString("%1 %2").arg(GetWideString(id_first_format_1)).arg(first_format_str_2);\
    if(bLocal)\
    {\
    if(p0 != p1 && p1 > 0)\
    {\
    AddHtmlDescText(color, false, strFirstFormat.toStdString().c_str(), (value0));\
    AddHtmlDescText(color, true, (second_format_str), (value1));\
}\
    else\
    {\
    AddHtmlDescText(color, true, strFirstFormat.toStdString().c_str(), (value0));\
}\
}\
    else\
    {\
    AddHtmlDescText(color, true, strFirstFormat.toStdString().c_str(), (value2));\
}\
}

#define ADD_RANGE_VALUE_DESC_ID_NORMAL(id_string)					ADD_RANGE_VALUE_DESC_ID((id_string), "~%d", p0, p1, p0)
#define ADD_RANGE_VALUE_DESC_ID_FLOAT(id_string)						ADD_RANGE_VALUE_DESC_ID((id_string), "~%.2f", *(float*)&p0, *(float*)&p1, *(float*)&p0)
#define ADD_RANGE_VALUE_DESC_ID_FLOAT2(id_string)						ADD_RANGE_VALUE_DESC_ID((id_string), "~%.2f", *(float*)&alcance, *(float*)&alcance1, *(float*)&alcance)
#define ADD_RANGE_VALUE_DESC_ID_PERCENT(id_string)					ADD_RANGE_VALUE_DESC_ID((id_string), "~%d%%", (p0), (p1), p0)
#define ADD_RANGE_VALUE_DESC_ID_MINUS_PERCENT_1(id_string)	ADD_RANGE_VALUE_DESC_ID((id_string), "~%d%%", -(p0), (p1), -p0)
#define ADD_RANGE_VALUE_DESC_ID_MINUS_PERCENT_2(id_string)	ADD_RANGE_VALUE_DESC_ID((id_string), "~%d%%", -(p0), (p1), -(p0))
#define ADD_RANGE_VALUE_DESC_ID_HALF(id_string)						ADD_RANGE_VALUE_DESC_ID((id_string), "~%d", (p0/2), (p1/2), (p0/2))
#define ADD_RANGE_VALUE_DESC_STR_NORMAL(id_string)					ADD_RANGE_VALUE_DESC_STR((id_string), "%+d", "~%d", p0, p1, p0)

    if (IsSharpenerProperty(byPropType))
        AddHtmlDescText(color, false, "Runa: ");
    if (IsEngraveProperty(byPropType))
        AddHtmlDescText(color, true, "Gravura: ");
    if (IsAstrolabeProperty(byPropType))
        AddHtmlDescText(color, true, "Astrolábio: ");
    {
        int alcance = p0;
        int alcance1 = p1;
        p0 = isFloatValue(p0) ? VisualizeFloatPercent(p0) : p0;
        p1 = isFloatValue(p1) ? VisualizeFloatPercent(p1) : p1;
        p2 = isFloatValue(p2) ? VisualizeFloatPercent(p2) : p2;
        switch (byPropType)
        {
        case 0:		//	???��???��
            if (aPEEVals)
                aPEEVals[PEEI_PHYDAMAGE] += p0;
            AddHtmlDescText(color, false, GetWideString(ITEMDESC_ADDPHYDAMAGE).toStdString().c_str());
            AddHtmlDescText(color, true, " %+d", p0);
            break;

        case 1:		//	???��???��????

            if (aPEEVals)
                aPEEVals[PEEI_MAX_PHYDAMAGE] += p0;
            if(p0 != p1 && p1 > 0)
            {
                AddHtmlDescText(color, false, GetWideString(ITEMDESC_MAXPHYDAMAGE).toStdString().c_str(), p0);
                AddHtmlDescText(color, true, "~%d", p1);
            }
            else
            {
                AddHtmlDescText(color, true, GetWideString(ITEMDESC_MAXPHYDAMAGE).toStdString().c_str(), p0);
            }

            break;

        case 2:		//	???��???��(%)

            AddHtmlDescText(color, true, GetWideString(ITEMDESC_PHYDMGEXTRA).toStdString().c_str(), p0);

            break;

        case 3:		//	?�졤��???��
            if (aPEEVals)
                aPEEVals[PEEI_MAGICDAMAGE] += p0;
            AddHtmlDescText(color, false, GetWideString(ITEMDESC_ADDMAGICDAMAGE).toStdString().c_str());
            AddHtmlDescText(color, true, " %+d", p0);
            break;

        case 4: 	//	?�졤��???��????
            if (aPEEVals)
                aPEEVals[PEEI_MAX_MAGICDAMAGE] += p0;
            if(p0 != p1 && p1 > 0)
            {
                AddHtmlDescText(color, false, GetWideString(ITEMDESC_MAXMAGICDAMAGE).toStdString().c_str(), p0);
                AddHtmlDescText(color, true, "~%d", p1);
            }
            else
            {
                AddHtmlDescText(color, true, GetWideString(ITEMDESC_MAXMAGICDAMAGE).toStdString().c_str(), p0);
            }

            break;

        case 5: 	//	?�졤��???��(%)

            AddHtmlDescText(color, true, GetWideString(ITEMDESC_MAGICDMGEXTRA).toStdString().c_str(), p0);

            break;

        case 6: 	//	+??��?-????
            if (aPEEVals)
            {
                aPEEVals[PEEI_PHYDEF]	 += p0;
                aPEEVals[PEEI_PHYDAMAGE] -= p1;
            }
            AddHtmlDescText(color, false, GetWideString(ITEMDESC_PHYDEFENCE).toStdString().c_str());
            AddHtmlDescText(color, true, " %+d & ", p0);
            AddHtmlDescText(color, false, GetWideString(ITEMDESC_ADDPHYDAMAGE).toStdString().c_str());
            AddHtmlDescText(color, true, " %+d", -p1);
            break;

        case 7: 	//	+????-??��?

            if (aPEEVals)
            {
                aPEEVals[PEEI_PHYDAMAGE] += p0;
                aPEEVals[PEEI_PHYDEF]	 -= p1;
            }
            AddHtmlDescText(color, false, GetWideString(ITEMDESC_ADDPHYDAMAGE).toStdString().c_str());
            AddHtmlDescText(color, true, " %+d & ", p0);
            AddHtmlDescText(color, false, GetWideString(ITEMDESC_PHYDEFENCE).toStdString().c_str());
            AddHtmlDescText(color, true, " %+d", -p1);
            break;

        case 8: 	//	+?��??-?�졤?
            if (aPEEVals)
            {
                aPEEVals[PEEI_MAGICDAMAGE]	+= p0;
                aPEEVals[PEEI_GOLDDEF]		-= p1;
                aPEEVals[PEEI_WOODDEF]		-= p1;
                aPEEVals[PEEI_WATERDEF]		-= p1;
                aPEEVals[PEEI_FIREDEF]		-= p1;
                aPEEVals[PEEI_EARTHDEF]		-= p1;
            }
            AddHtmlDescText(color, false, GetWideString(ITEMDESC_ADDMAGICDAMAGE).toStdString().c_str());
            AddHtmlDescText(color, true, " %+d & ", p0);
            AddHtmlDescText(color, false, GetWideString(ITEMDESC_ALLMAGICDEF).toStdString().c_str());
            AddHtmlDescText(color, true, " %+d", -p1);
            break;

        case 9: 	//	???��????

            AddHtmlDescText(color, true, GetWideString(ITEMDESC_ATKTIME).toStdString().c_str(), -p0 * 0.05f);

            break;

        case 10:	//	???��?��??
        {
            if (aPEEVals)
            {
                float fDist = *(float*)&aPEEVals[PEEI_ATKDIST] + *(float*)&p0;
                aPEEVals[PEEI_ATKDIST] = *(DWORD*)&fDist;
            }
            AddHtmlDescText(color, true, GetWideString(ITEMDESC_ADDATKDIST).toStdString().c_str(), *(float*)&alcance);

            break;
        }
        case 11:	//	?��???��??

            AddHtmlDescText(color, true, GetWideString(ITEMDESC_CASTTIME).toStdString().c_str(), -p0);

            break;

        case 12: 	//	???����??��
            if (aPEEVals)
                aPEEVals[PEEI_PHYDEF] += p0;
            AddHtmlDescText(color, false, GetWideString(ITEMDESC_PHYDEFENCE).toStdString().c_str());
            AddHtmlDescText(color, true, " %+d", p0);
            break;

        case 13: 	//	???����??��(%)

            AddHtmlDescText(color, true, GetWideString(ITEMDESC_PHYDEFEXTRA).toStdString().c_str(), p0);

            break;

        case 14: 	//	????��??��
            if (aPEEVals)
            {
                aPEEVals[PEEI_GOLDDEF]	+= p0;
                aPEEVals[PEEI_WOODDEF]	+= p0;
                aPEEVals[PEEI_WATERDEF] += p0;
                aPEEVals[PEEI_FIREDEF]	+= p0;
                aPEEVals[PEEI_EARTHDEF] += p0;
            }
            AddHtmlDescText(color, false, GetWideString(ITEMDESC_ALLMAGICDEF).toStdString().c_str());
            AddHtmlDescText(color, true, " %+d", p0);
            break;

        case 15: 	//	??��?

            if (aPEEVals)
                aPEEVals[PEEI_GOLDDEF] += p0;
            AddHtmlDescText(color, false, GetWideString(ITEMDESC_GOLDDEFENCE).toStdString().c_str());

            if(p0 != p1 && p1 > 0)
                AddHtmlDescText(color, true, " +%d~%d", p0, p1);
            else
                AddHtmlDescText(color, true, " +%d", p0);

            break;

        case 16: 	//	??��?(%)
            ADD_RANGE_VALUE_DESC_ID_PERCENT(ITEMDESC_GOLDDEFEXTRA);
            break;

        case 17: 	//	??��?
            if (aPEEVals)
                aPEEVals[PEEI_WOODDEF] += p0;
            AddHtmlDescText(color, false, GetWideString(ITEMDESC_WOODDEFENCE).toStdString().c_str());

            if(p0 != p1 && p1 > 0)
                AddHtmlDescText(color, true, " +%d~%d", p0, p1);
            else
                AddHtmlDescText(color, true, " +%d", p0);
            break;

        case 18: 	//	??��?(%)
            ADD_RANGE_VALUE_DESC_ID_PERCENT(ITEMDESC_WOODDEFEXTRA);
            break;

        case 19: 	//	??��?
            if (aPEEVals)
                aPEEVals[PEEI_WATERDEF] += p0;
            AddHtmlDescText(color, false, GetWideString(ITEMDESC_WATERDEFENCE).toStdString().c_str());

            if(p0 != p1 && p1 > 0)
                AddHtmlDescText(color, true, " +%d~%d", p0, p1);
            else
                AddHtmlDescText(color, true, " +%d", p0);
            break;

        case 20: 	//	??��?(%)
            ADD_RANGE_VALUE_DESC_ID_PERCENT(ITEMDESC_WATERDEFEXTRA);
            break;

        case 21: 	//	??��?
            if (aPEEVals)
                aPEEVals[PEEI_FIREDEF] += p0;
            AddHtmlDescText(color, false, GetWideString(ITEMDESC_FIREDEFENCE).toStdString().c_str());

            if(p0 != p1 && p1 > 0)
                AddHtmlDescText(color, true, " +%d~%d", p0, p1);
            else
                AddHtmlDescText(color, true, " +%d", p0);
            break;

        case 22: 	//	??��?(%)
            ADD_RANGE_VALUE_DESC_ID_PERCENT(ITEMDESC_FIREDEFEXTRA);
            break;

        case 23: 	//	??��?
            if (aPEEVals)
                aPEEVals[PEEI_EARTHDEF] += p0;
            AddHtmlDescText(color, false, GetWideString(ITEMDESC_EARTHDEFENCE).toStdString().c_str());

            if(p0 != p1 && p1 > 0)
                AddHtmlDescText(color, true, " +%d~%d", p0, p1);
            else
                AddHtmlDescText(color, true, " +%d", p0);


            break;

        case 24: 	//	??��?(%)
            ADD_RANGE_VALUE_DESC_ID_PERCENT(ITEMDESC_EARTHDEFEXTRA);
            break;

        case 25: 	//	+??��?(%)-??��?(%)

            AddHtmlDescText(color, true, GetWideString(ITEMDESC_GOLDDEFEXTRA).toStdString().c_str(), p0);
            AddHtmlDescText(color, true, GetWideString(ITEMDESC_FIREDEFEXTRA).toStdString().c_str(), -p1);
            break;

        case 26: 	//	+??��?(%)-??��?(%)

            AddHtmlDescText(color, true, GetWideString(ITEMDESC_WOODDEFEXTRA).toStdString().c_str(), p0);
            AddHtmlDescText(color, true, GetWideString(ITEMDESC_GOLDDEFEXTRA).toStdString().c_str(), -p1);
            break;

        case 27: 	//	+??��?(%)-??��?(%)

            AddHtmlDescText(color, true, GetWideString(ITEMDESC_WATERDEFEXTRA).toStdString().c_str(), p0);
            AddHtmlDescText(color, true, GetWideString(ITEMDESC_EARTHDEFEXTRA).toStdString().c_str(), -p1);
            break;

        case 28: 	//	+??��?(%)-??��?(%)

            AddHtmlDescText(color, true, GetWideString(ITEMDESC_FIREDEFEXTRA).toStdString().c_str(), (p0));
            AddHtmlDescText(color, true, GetWideString(ITEMDESC_WATERDEFEXTRA).toStdString().c_str(), -(p1));
            break;

        case 29: 	//	+??��?(%)-??��?(%)

            AddHtmlDescText(color, true, GetWideString(ITEMDESC_EARTHDEFEXTRA).toStdString().c_str(), (p0));
            AddHtmlDescText(color, true, GetWideString(ITEMDESC_WOODDEFEXTRA).toStdString().c_str(), -(p1));
            break;

        case 30: 	//	+??��?-??��?
            if (aPEEVals)
            {
                aPEEVals[PEEI_GOLDDEF]	+= p0;
                aPEEVals[PEEI_FIREDEF]	-= p1;
            }
            AddHtmlDescText(color, false, GetWideString(ITEMDESC_GOLDDEFENCE).toStdString().c_str());
            AddHtmlDescText(color, true, " %+d & ", p0);
            AddHtmlDescText(color, false, GetWideString(ITEMDESC_FIREDEFENCE).toStdString().c_str());
            AddHtmlDescText(color, true, " %+d", -p1);
            break;

        case 31: 	//	+??��?-??��?

            if (aPEEVals)
            {
                aPEEVals[PEEI_WOODDEF]	+= p0;
                aPEEVals[PEEI_GOLDDEF]	-= p1;
            }
            AddHtmlDescText(color, false, GetWideString(ITEMDESC_WOODDEFENCE).toStdString().c_str());
            AddHtmlDescText(color, true, " %+d & ", p0);
            AddHtmlDescText(color, false, GetWideString(ITEMDESC_GOLDDEFENCE).toStdString().c_str());
            AddHtmlDescText(color, true, " %+d", -p1);
            break;

        case 32: 	//	+??��?-??��?
            if (aPEEVals)
            {
                aPEEVals[PEEI_WATERDEF]	+= p0;
                aPEEVals[PEEI_EARTHDEF]	-= p1;
            }
            AddHtmlDescText(color, false, GetWideString(ITEMDESC_WATERDEFENCE).toStdString().c_str());
            AddHtmlDescText(color, true, " %+d", p0);
            AddHtmlDescText(color, false, GetWideString(ITEMDESC_EARTHDEFENCE).toStdString().c_str());
            AddHtmlDescText(color, true, " %+d", -p1);
            break;

        case 33: 	//	+??��?-??��?

            if (aPEEVals)
            {
                aPEEVals[PEEI_FIREDEF]	+= p0;
                aPEEVals[PEEI_WATERDEF]	-= p1;
            }
            AddHtmlDescText(color, false, GetWideString(ITEMDESC_FIREDEFENCE).toStdString().c_str());
            AddHtmlDescText(color, true, " %+d", p0);
            AddHtmlDescText(color, false, GetWideString(ITEMDESC_WATERDEFENCE).toStdString().c_str());
            AddHtmlDescText(color, true, " %+d", -p1);
            break;

        case 34: 	//	+??��?-??��?

            if (aPEEVals)
            {
                aPEEVals[PEEI_EARTHDEF]	+= p0;
                aPEEVals[PEEI_WOODDEF]	-= p1;
            }
            AddHtmlDescText(color, false, GetWideString(ITEMDESC_EARTHDEFENCE).toStdString().c_str());
            AddHtmlDescText(color, true, " %+d & ", p0);
            AddHtmlDescText(color, false, GetWideString(ITEMDESC_WOODDEFENCE).toStdString().c_str());
            AddHtmlDescText(color, true, " %+d", -p1);
            break;

        case 35: 	//	HP
            if (aPEEVals)
                aPEEVals[PEEI_HP] += p0;

            AddHtmlDescText(color, false, GetWideString(ITEMDESC_ADDHP).toStdString().c_str());
            AddHtmlDescText(color, true, " %+d", p0);
            break;

        case 36: 	//	MP
            if (aPEEVals)
                aPEEVals[PEEI_MP] += p0;
            AddHtmlDescText(color, false, GetWideString(ITEMDESC_ADDMP).toStdString().c_str());
            AddHtmlDescText(color, true, " %+d", p0);
            break;

        case 37: 	//	HP(%)

            AddHtmlDescText(color, true, GetWideString(ITEMDESC_HPEXTRA).toStdString().c_str(), p0);
            break;

        case 38: 	//	MP(%)

            AddHtmlDescText(color, true, GetWideString(ITEMDESC_MPEXTRA).toStdString().c_str(), p0);
            break;

        case 39: 	//	HP????????

            AddHtmlDescText(color, true, GetWideString(ITEMDESC_HPRECOVER).toStdString().c_str(), p0 / 2);
            break;

        case 40: 	//	MP????????

            AddHtmlDescText(color, true, GetWideString(ITEMDESC_MPRECOVER).toStdString().c_str(), p0 / 2);
            break;

        case 41: 	//	????

            if(bLocal)
            {
                if(p0 != p1 && p1 > 0)
                {
                    AddHtmlDescText(color, false, GetWideString(ITEMDESC_STRENGTH).toStdString().c_str(), p0);
                    AddHtmlDescText(color, true, "~%d", p1);
                }
                else
                {
                    AddHtmlDescText(color, true, GetWideString(ITEMDESC_STRENGTH).toStdString().c_str(), p0);
                }
            }
            else
            {
                AddHtmlDescText(color, true, GetWideString(ITEMDESC_STRENGTH).toStdString().c_str(), p0);
            }
            break;

        case 42: 	//	????

            if(bLocal)
            {
                if(p0 != p1 && p1 > 0)
                {
                    AddHtmlDescText(color, false, GetWideString(ITEMDESC_AGILITY).toStdString().c_str(), p0);
                    AddHtmlDescText(color, true, "~%d", p1);
                }
                else
                {
                    AddHtmlDescText(color, true, GetWideString(ITEMDESC_AGILITY).toStdString().c_str(), p0);
                }
            }
            else
            {
                AddHtmlDescText(color, true, GetWideString(ITEMDESC_AGILITY).toStdString().c_str(), p0);
            }
            break;

        case 43: 	//	?��??

            if(bLocal)
            {
                if(p0 != p1 && p1 > 0)
                {
                    AddHtmlDescText(color, false, GetWideString(ITEMDESC_ENERGY).toStdString().c_str(), p0);
                    AddHtmlDescText(color, true, "~%d", p1);
                }
                else
                {
                    AddHtmlDescText(color, true, GetWideString(ITEMDESC_ENERGY).toStdString().c_str(), p0);
                }
            }
            else
            {
                AddHtmlDescText(color, true, GetWideString(ITEMDESC_ENERGY).toStdString().c_str(), p0);
            }
            break;

        case 44: 	//	????

            if(bLocal)
            {
                if(p0 != p1 && p1 > 0)
                {
                    AddHtmlDescText(color, false, GetWideString(ITEMDESC_VITALITY).toStdString().c_str(), p0);
                    AddHtmlDescText(color, true, "~%d", p1);
                }
                else
                {
                    AddHtmlDescText(color, true, GetWideString(ITEMDESC_VITALITY).toStdString().c_str(), p0);
                }
            }
            else
            {
                AddHtmlDescText(color, true, GetWideString(ITEMDESC_VITALITY).toStdString().c_str(), p0);
            }
            break;

        case 45: 	//	???��???��??

            AddHtmlDescText(color, true, GetWideString(ITEMDESC_DEADLYSTRIKE).toStdString().c_str(), p0);

            break;

        case 46: 	//	?��??

            if(bLocal)
            {
                if(p0 != p1 && p1 > 0)
                {
                    AddHtmlDescText(color, false, GetWideString(ITEMDESC_ATKRATING).toStdString().c_str(), p0);
                    AddHtmlDescText(color, true, "~%d", p1);
                }
                else
                {
                    AddHtmlDescText(color, true, GetWideString(ITEMDESC_ATKRATING).toStdString().c_str(), p0);
                }
            }
            else
            {
                AddHtmlDescText(color, true, GetWideString(ITEMDESC_ATKRATING).toStdString().c_str(), p0);
            }
            break;

        case 47: 	//	?��??(%)

            AddHtmlDescText(color, true, GetWideString(ITEMDESC_ATKRATINGEXTRA).toStdString().c_str(), p0);

            break;

        case 48: 	//	????????

            AddHtmlDescText(color, true, GetWideString(ITEMDESC_RUNSPEED).toStdString().c_str(), *(float*)&alcance);
            break;

        case 49: 	//	????????(%)

            AddHtmlDescText(color, true, GetWideString(ITEMDESC_RUNSPEEDEXTRA).toStdString().c_str(), p0);

            break;

        case 50: 	//	????
            if (aPEEVals)
                aPEEVals[PEEI_DODGE] += p0;
            AddHtmlDescText(color, false, GetWideString(ITEMDESC_DODGE).toStdString().c_str());
            AddHtmlDescText(color, true, " %+d", p0);
            break;

        case 51:
            AddHtmlDescText(color, true, GetWideString(ITEMDESC_DODGEEXTRA).toStdString().c_str(), p0);

            break;

        case 52: 	//	??????

            AddHtmlDescText(color, false, GetWideString(ITEMDESC_ENDURANCE).toStdString().c_str());
            AddHtmlDescText(color, true, " %+d", p0);
            break;

        case 53: 	//	??????(%)

            AddHtmlDescText(color, true, GetWideString(ITEMDESC_ENDURANCEEXTRA).toStdString().c_str(), (p0));
            break;

        case 54: 	//	???��????

            AddHtmlDescText(color, true, GetWideString(ITEMDESC_PHYRESIST).toStdString().c_str(), p0);

            break;

        case 55: 	//	????????
        {
            //	Get skill description
            QString skill = pw.listSkillDesc[alcance];
            skill.replace("\r", "");
            skill.replace("\r\n", "");
            skill.replace("\n\r", "");
            skill.replace("\n", "");
            QRegularExpression regex("\\^([0-9A-Fa-f]{6})");
            skill.remove(regex);
            AddHtmlDescText(color, true, skill.toStdString().c_str());
            break;
        }
        case 56: 	//	������??��?��

            if((p0) != (p1))
            {
                AddHtmlDescText(color, false, GetWideString(ITEMDESC_REQEXTRA).toStdString().c_str(), -(p0));
                AddHtmlDescText(color, true, "~%d", p1);
            }
            else
            {
                AddHtmlDescText(color, true, GetWideString(ITEMDESC_REQEXTRA).toStdString().c_str(), -(p0));
            }

            break;

        case 57: 	//	????????

            AddHtmlDescText(color, true, GetWideString(ITEMDESC_RANDOMPROP).toStdString().c_str());
            break;

        case 58:	//	???��??????

            AddHtmlDescText(color, true, GetWideString(ITEMDESC_EXP).toStdString().c_str(), p0);

            break;

        case 59:	//	???��????

            AddHtmlDescText(color, true, GetWideString(ITEMDESC_ATK_DEGREE).toStdString().c_str(), p0);
            break;

        case 60:	//	��??��????

            AddHtmlDescText(color, true, GetWideString(ITEMDESC_DEF_DEGREE).toStdString().c_str(), p0);
            break;

        case 61:	//	????��??��?��%??

            AddHtmlDescText(color, true, GetWideString(ITEMDESC_TOTAL_DEFENCE_ADD).toStdString().c_str(), (p0));

            break;

        case 62:	//	????????

            AddHtmlDescText(color, true, GetWideString(ITEMDESC_PROFVIEW).toStdString().c_str());
            break;

        case 63:	//	?��??

            AddHtmlDescText(color, true, GetWideString(ITEMDESC_SOULPOWER).toStdString().c_str(), p0);
            break;

        case 64: 	//	????????(%)

            AddHtmlDescText(color, true, GetWideString(ITEMDESC_GOLDRESIST).toStdString().c_str(), p0);

            break;

        case 65: 	//	?
            AddHtmlDescText(color, true, GetWideString(ITEMDESC_WOODRESIST).toStdString().c_str(), p0);

            break;

        case 66: 	//	????????(%)

            AddHtmlDescText(color, true, GetWideString(ITEMDESC_WATERRESIST).toStdString().c_str(), p0);

            break;

        case 67: 	//	????????(%)


            AddHtmlDescText(color, true, GetWideString(ITEMDESC_FIRERESIST).toStdString().c_str(), p0);

            break;

        case 68: 	//	????????(%)


            AddHtmlDescText(color, true, GetWideString(ITEMDESC_EARTHRESIST).toStdString().c_str(), p0);

            break;

        case 69: 	//	????????(%)


            AddHtmlDescText(color, true, GetWideString(ITEMDESC_ALLMAGICRESIST).toStdString().c_str(), p0);

            break;

        case 70:	//	???��????��??��?��?????????��??????

            ADD_RANGE_VALUE_DESC_ID_NORMAL(ITEMDESC_ATK_DEGREE)
                    break;

        case 71:	//	��??��????��??��?��?????????��??????

            ADD_RANGE_VALUE_DESC_ID_NORMAL(ITEMDESC_DEF_DEGREE)
                    break;

        case 72:	//	???��???��??(%)��??��?��?????????��??????

            ADD_RANGE_VALUE_DESC_ID_PERCENT(ITEMDESC_DEADLYSTRIKE)
                    break;

        case 73: 	//	HP��??��?��?????????��??????

            ADD_RANGE_VALUE_DESC_STR_NORMAL(ITEMDESC_ADDHP)
                    break;

        case 74: 	//	MP��??��?��?????????��??????

            ADD_RANGE_VALUE_DESC_STR_NORMAL(ITEMDESC_ADDMP)
                    break;

        case 75:	//	?��??(%)��??��?��?????????��??????

            ADD_RANGE_VALUE_DESC_ID_PERCENT(ITEMDESC_ATKRATINGEXTRA)
                    break;

        case 76:	//	???����??����??��?��?????????��??????

            ADD_RANGE_VALUE_DESC_STR_NORMAL(ITEMDESC_PHYDEFENCE)
                    break;

        case 77:	//	????��??����??��?��?????????��??????

            ADD_RANGE_VALUE_DESC_STR_NORMAL(ITEMDESC_ALLMAGICDEF)
                    break;

        case 78:	//	???��????(%)��??��?��?????????��??????

            ADD_RANGE_VALUE_DESC_ID_PERCENT(ITEMDESC_PHYRESIST)
                    break;

        case 79:	//	????????(%)��??��?��?????????��??????

            ADD_RANGE_VALUE_DESC_ID_PERCENT(ITEMDESC_ALLMAGICRESIST)
                    break;

        case 80:	//	?��???��??(%)��??��?��?????????��??????

            ADD_RANGE_VALUE_DESC_ID_MINUS_PERCENT_1(ITEMDESC_CASTTIME)
                    break;

        case 81:	//	???��?��??��??��?��?????????��??????

            ADD_RANGE_VALUE_DESC_ID_FLOAT2(ITEMDESC_ADDATKDIST)
                    break;

        case 82:	//	MP????????��??��?��?????????��??????

            ADD_RANGE_VALUE_DESC_ID_HALF(ITEMDESC_MPRECOVER)
                    break;

        case 83:	//	???����??��(%)��??��?��?????????��??????

            ADD_RANGE_VALUE_DESC_ID_PERCENT(ITEMDESC_PHYDEFEXTRA)
                    break;

        case 84:	//	????��??��(%)��??��?��?????????��??????

            ADD_RANGE_VALUE_DESC_ID_PERCENT(ITEMDESC_TOTAL_DEFENCE_ADD)
                    break;

        case 85:	//	HP????????��??��?��?????????��??????

            ADD_RANGE_VALUE_DESC_ID_HALF(ITEMDESC_HPRECOVER)
                    break;

        case 86:	//	????��??��?��?????????��??????

            ADD_RANGE_VALUE_DESC_STR_NORMAL(ITEMDESC_DODGE)
                    break;

        case 87:	//	???��???��????��??��?��?????????��??????

            ADD_RANGE_VALUE_DESC_ID_NORMAL(ITEMDESC_MAXPHYDAMAGE)
                    break;

        case 88:	//	?�졤��???��????��??��?��?????????��??????

            ADD_RANGE_VALUE_DESC_ID_NORMAL(ITEMDESC_MAXMAGICDAMAGE)
                    break;

        case 89:	//	������??��?����??��?��?????????��??????

            ADD_RANGE_VALUE_DESC_ID_MINUS_PERCENT_2(ITEMDESC_REQEXTRA)
                    break;

        case 90:	//	???��????

            AddHtmlDescText(color, true, GetWideString(ITEMDESC_PENETRATION).toStdString().c_str(), p0);
            break;

        case 91:	//	?��?��????

            AddHtmlDescText(color, true, GetWideString(ITEMDESC_RESILIENCE).toStdString().c_str(), p0);
            break;

        case 92: 	//	+??��?+?�졤?

            if (aPEEVals)
            {
                aPEEVals[PEEI_PHYDEF]	+= p0;
                aPEEVals[PEEI_GOLDDEF]	+= p1;
                aPEEVals[PEEI_WOODDEF]	+= p1;
                aPEEVals[PEEI_WATERDEF] += p1;
                aPEEVals[PEEI_FIREDEF]	+= p1;
                aPEEVals[PEEI_EARTHDEF] += p1;
            }
            AddHtmlDescText(color, false, GetWideString(ITEMDESC_PHYDEFENCE).toStdString().c_str());
            AddHtmlDescText(color, true, " %+d & ", p0);
            AddHtmlDescText(color, false, GetWideString(ITEMDESC_ALLMAGICDEF).toStdString().c_str());
            AddHtmlDescText(color, true, " %+d", p1);
            break;

        case 93: 	//	????HP
            AddHtmlDescText(color, false, GetWideString(ITEMDESC_ADDHP).toStdString().c_str());
            AddHtmlDescText(color, true, " %+d", p0);
            break;

        case 94: 	//	????HP��??��
            ADD_RANGE_VALUE_DESC_STR_NORMAL(ITEMDESC_ADDHP)
                    break;

        case 95: 	//	????
            AddHtmlDescText(color, true, GetWideString(ITEMDESC_STRENGTH).toStdString().c_str(), p0);
            break;

        case 96: 	//	????
            AddHtmlDescText(color, true, GetWideString(ITEMDESC_AGILITY).toStdString().c_str(), p0);
            break;

        case 97: 	//	?��??
            AddHtmlDescText(color, true, GetWideString(ITEMDESC_ENERGY).toStdString().c_str(), p0);
            break;

        case 98:	//	????
            AddHtmlDescText(color, true, GetWideString(ITEMDESC_VITALITY).toStdString().c_str(), p0);
            break;

        case 99: 	//	????MP
            AddHtmlDescText(color, false, GetWideString(ITEMDESC_ADDMP).toStdString().c_str());
            AddHtmlDescText(color, true, " %+d", p0);
            break;

        case 100:	//	ĥ��ʯ��������
            AddHtmlDescText(color, false, GetWideString(ITEMDESC_ADDPHYDAMAGE).toStdString().c_str());
            AddHtmlDescText(color, true, " %+d", p0);
            break;

        case 101:	//	ĥ��ʯ������������
            AddHtmlDescText(color, false, GetWideString(ITEMDESC_MAXPHYDAMAGE).toStdString().c_str(), p0);
            break;

        case 102:	//	ĥ��ʯħ������
            AddHtmlDescText(color, false, GetWideString(ITEMDESC_ADDMAGICDAMAGE).toStdString().c_str());
            AddHtmlDescText(color, false, " %+d", p0);
            break;

        case 103:	//	ĥ��ʯħ����������
            AddHtmlDescText(color, false, GetWideString(ITEMDESC_MAXMAGICDAMAGE).toStdString().c_str(), p0);
            break;

        case 104:	//	ĥ��ʯ��������
            AddHtmlDescText(color, false, GetWideString(ITEMDESC_PHYDEFENCE).toStdString().c_str());
            AddHtmlDescText(color, false, " %+d", p0);
            break;

        case 105:	//	ĥ��ʯHP
            AddHtmlDescText(color, false, GetWideString(ITEMDESC_ADDHP).toStdString().c_str());
            AddHtmlDescText(color, false, " %+d", p0);
            break;

        case 106:	//	ĥ��ʯ����
            AddHtmlDescText(color, false, GetWideString(ITEMDESC_STRENGTH).toStdString().c_str(), p0);
            break;

        case 107:	//	ĥ��ʯ����
            AddHtmlDescText(color, false, GetWideString(ITEMDESC_AGILITY).toStdString().c_str(), p0);
            break;

        case 108:	//	ĥ��ʯ����
            AddHtmlDescText(color, false, GetWideString(ITEMDESC_ENERGY).toStdString().c_str(), p0);
            break;

        case 109:	//	ĥ��ʯ������
            AddHtmlDescText(color, false, GetWideString(ITEMDESC_ATKRATING).toStdString().c_str(), p0);
            break;

        case 110:	//	ĥ��ʯ����һ����

            AddHtmlDescText(color, false, GetWideString(ITEMDESC_DEADLYSTRIKE).toStdString().c_str(), p0);
            break;

        case 111:	//	ĥ��ʯ�����ȼ�
            AddHtmlDescText(color, false, GetWideString(ITEMDESC_ATK_DEGREE).toStdString().c_str(), p0);
            break;

        case 112:	//	ĥ��ʯ�����ȼ�
            AddHtmlDescText(color, false, GetWideString(ITEMDESC_DEF_DEGREE).toStdString().c_str(), p0);
            break;

        case 113:	//	ĥ��ʯ����(%d)

            AddHtmlDescText(color, false, GetWideString(ITEMDESC_CASTTIME).toStdString().c_str(), -p0);
            break;

        case 114:	//	ĥ��ʯħ������
            AddHtmlDescText(color, false, GetWideString(ITEMDESC_ALLMAGICDEF).toStdString().c_str());
            AddHtmlDescText(color, false, " %+d", p0);
            break;

        case 115:	//	ĥ��ʯ��˼���
            AddHtmlDescText(color, false, GetWideString(ITEMDESC_ADDRIDEONPETSPEED).toStdString().c_str(), *(float*)&alcance);
            break;

        case 116:	//	ĥ��ʯ��˼���
            AddHtmlDescText(color, false, GetWideString(ITEMDESC_ADDFLYSPEED2).toStdString().c_str(), *(float*)&alcance);
            break;

        case 160: 	//	???????��??
            AddHtmlDescText(color, false, GetWideString(ITEMDESC_VIGOUR).toStdString().c_str());
            AddHtmlDescText(color, true, " %+d", p0);
            break;

        case 161:	//	???????��???��
            AddHtmlDescText(color, false, GetWideString(ITEMDESC_ADDPHYDAMAGE).toStdString().c_str());
            AddHtmlDescText(color, true, " %+d", p0);

            break;

        case 162:	//	?????�졤��???��

            AddHtmlDescText(color, false, GetWideString(ITEMDESC_ADDMAGICDAMAGE).toStdString().c_str());
            AddHtmlDescText(color, true, " %+d", p0);

            break;

        case 163:	//	???????����??��

            AddHtmlDescText(color, false, GetWideString(ITEMDESC_DEFENCE).toStdString().c_str());
            AddHtmlDescText(color, true, " %+d", p0);

            break;

        case 164:	//	??????��?

            AddHtmlDescText(color, false, GetWideString(ITEMDESC_GOLDDEFENCE).toStdString().c_str());
            AddHtmlDescText(color, true, " %+d", p0);

            break;

        case 165:	//	??????��?

            AddHtmlDescText(color, false, GetWideString(ITEMDESC_ADDHP).toStdString().c_str());
            AddHtmlDescText(color, true, " %+d", p0);

            break;

        case 166:	//	??????��?

            AddHtmlDescText(color, false, GetWideString(ITEMDESC_VIGOUR).toStdString().c_str());
            AddHtmlDescText(color, true, " %+d", p0);

            break;

        case 167:	//	??????��?

            AddHtmlDescText(color, false, GetWideString(ITEMDESC_GOLDDEFENCE).toStdString().c_str());
            AddHtmlDescText(color, true, " %+d", p0);

            break;

        case 168:	//	??????��?

            AddHtmlDescText(color, false, GetWideString(ITEMDESC_WOODDEFENCE).toStdString().c_str());
            AddHtmlDescText(color, true, " %+d", p0);

            break;

        case 169:	//	??????��?

            AddHtmlDescText(color, false, GetWideString(ITEMDESC_WATERDEFENCE).toStdString().c_str());
            AddHtmlDescText(color, true, " %+d", p0);

            break;

        case 170:	//	??????��?

            AddHtmlDescText(color, false, GetWideString(ITEMDESC_FIREDEFENCE).toStdString().c_str());
            AddHtmlDescText(color, true, " %+d", p0);

            break;

        case 171:	//	??????��?

            AddHtmlDescText(color, false, GetWideString(ITEMDESC_EARTHDEFENCE).toStdString().c_str());
            AddHtmlDescText(color, true, " %+d", p0);

            break;

        case 172: 	//	?????��??

            AddHtmlDescText(color, true, GetWideString(ITEMDESC_ATKRATING).toStdString().c_str(), p0);
            break;

        case 173: 	//	????????

            AddHtmlDescText(color, false, GetWideString(ITEMDESC_DODGE).toStdString().c_str());
            AddHtmlDescText(color, true, " %+d", p0);
            break;

        case 174: 	//	????????

            AddHtmlDescText(color, false, GetWideString(ITEMDESC_VIGOUR).toStdString().c_str());
            AddHtmlDescText(color, true, " %+d", p0);
            break;

        case 175: 	//	????????


            AddHtmlDescText(color, true, GetWideString(ITEMDESC_PHYRESIST).toStdString().c_str(), p0);

            break;

        case 176: 	//	????????


            AddHtmlDescText(color, true, GetWideString(ITEMDESC_ALLMAGICRESIST).toStdString().c_str(), p0);

            break;

        case 177:	//	???????��???��
            ADD_RANGE_VALUE_DESC_STR_NORMAL(ITEMDESC_PHYDEFENCE);
            break;

        case 178:	//	???????��???��
            ADD_RANGE_VALUE_DESC_STR_NORMAL(ITEMDESC_ALLMAGICDEF);
            break;

        case 179:	//	???????��???��
            ADD_RANGE_VALUE_DESC_STR_NORMAL(ITEMDESC_VIGOUR);
            break;

        case 180:	//	???????��???��
            ADD_RANGE_VALUE_DESC_STR_NORMAL(ITEMDESC_PHY_PENETRATION);
            break;

        case 181:	//	???????��???��
            ADD_RANGE_VALUE_DESC_STR_NORMAL(ITEMDESC_ALLMAGIC_PENETRATION);
            break;

        case 200:	//	???????��???��
            if (aRefines)
                aRefines[REFINE_PHYDAMAGE] += p0;
            break;

        case 201:	//	?????�졤��???��
            if (aRefines)
                aRefines[REFINE_MAGICDAMAGE] += p0;
            break;

        case 202:	//	???????����??��
            if (aRefines)
                aRefines[REFINE_PHYDEF] += p0;
            break;

        case 203:	//	??????��?
            if (aRefines)
                aRefines[REFINE_GOLDDEF] += p0;
            break;

        case 204:	//	??????��?
            if (aRefines)
                aRefines[REFINE_WOODDEF] += p0;
            break;

        case 205:	//	??????��?
            if (aRefines)
                aRefines[REFINE_WATERDEF] += p0;
            break;

        case 206:	//	??????��?
            if (aRefines)
                aRefines[REFINE_FIREDEF] += p0;
            break;

        case 207:	//	??????��?
            if (aRefines)
                aRefines[REFINE_EARTHDEF] += p0;
            break;

        case 208:	//	????HP
            if (aRefines)
                aRefines[REFINE_HP] += p0;
            break;

        case 209:	//	????????
            if (aRefines)
                aRefines[REFINE_DODGE] += p0;
            break;

        case 210:	//	????????��??��
            if (aRefines)
            {
                aRefines[REFINE_GOLDDEF] += p0;
                aRefines[REFINE_WOODDEF] += p0;
                aRefines[REFINE_WATERDEF] += p0;
                aRefines[REFINE_FIREDEF] += p0;
                aRefines[REFINE_EARTHDEF] += p0;
            }
            break;

        case 211:	//	???????��???�� & ?�졤��???��
            if (aRefines)
            {
                aRefines[REFINE_PHYDAMAGE] += p0;
                aRefines[REFINE_MAGICDAMAGE] += p0;
            }
            break;

        case 212:	//	???????����??�� & ?�졤����??��
            if (aRefines)
            {
                aRefines[REFINE_PHYDEF] += p0;
                aRefines[REFINE_GOLDDEF] += p0;
                aRefines[REFINE_WOODDEF] += p0;
                aRefines[REFINE_WATERDEF] += p0;
                aRefines[REFINE_FIREDEF] += p0;
                aRefines[REFINE_EARTHDEF] += p0;
            }
            break;

        case 215:	//	???????����??�� & ?�졤����??��

            AddHtmlDescText(color, true, GetWideString(ITEMDESC_MAIORNIVEL).toStdString().c_str(), p0);
            break;

        case 216:	//	???????����??�� & ?�졤����??��

            AddHtmlDescText(color, false, GetWideString(ITEMDESC_ADDPHYDAMAGE).toStdString().c_str());
            AddHtmlDescText(color, true, " %+d", p0);
            break;

        case 217:	//	???????����??�� & ?�졤����??��

            AddHtmlDescText(color, false, GetWideString(ITEMDESC_ADDMAGICDAMAGE).toStdString().c_str());
            AddHtmlDescText(color, true, " %+d", p0);
            break;

        case 218:
            AddHtmlDescText(color, true, GetWideString(ITEMDESC_ATKTIME).toStdString().c_str(), -p0 * 0.05f);
            break;

        case 219: 	//	HP��??��?��?????????��??????
            ADD_RANGE_VALUE_DESC_STR_NORMAL(ITEMDESC_ADDHP);
            break;

        case 220: 	//	????????(%)


            AddHtmlDescText(color, true, GetWideString(ITEMDESC_RUNSPEEDEXTRA).toStdString().c_str(), p0);

            break;

            //	?????��??????
        case 120: 	//	??????��?

            AddHtmlDescText(color, false, GetWideString(ITEMDESC_GOLDDEFENCE).toStdString().c_str());
            AddHtmlDescText(color, true, " %+d", p0);
            break;

        case 121: 	//	??????��?

            AddHtmlDescText(color, false, GetWideString(ITEMDESC_WOODDEFENCE).toStdString().c_str());
            AddHtmlDescText(color, true, " %+d", p0);
            break;

        case 122: 	//	??????��?

            AddHtmlDescText(color, false, GetWideString(ITEMDESC_WATERDEFENCE).toStdString().c_str());
            AddHtmlDescText(color, true, " %+d", p0);
            break;

        case 123: 	//	??????��?

            AddHtmlDescText(color, false, GetWideString(ITEMDESC_FIREDEFENCE).toStdString().c_str());
            AddHtmlDescText(color, true, " %+d", p0);
            break;

        case 124: 	//	??????��?

            AddHtmlDescText(color, false, GetWideString(ITEMDESC_EARTHDEFENCE).toStdString().c_str());
            AddHtmlDescText(color, true, " %+d", p0);
            break;

        case 125: 	//	?????��??

            AddHtmlDescText(color, true, GetWideString(ITEMDESC_ATKRATING).toStdString().c_str(), p0);
            break;

        case 126: 	//	????????

            AddHtmlDescText(color, false, GetWideString(ITEMDESC_DODGE).toStdString().c_str());
            AddHtmlDescText(color, true, " %+d", p0);
            break;

        case 127: 	//	????MP

            AddHtmlDescText(color, false, GetWideString(ITEMDESC_ADDMP).toStdString().c_str());
            AddHtmlDescText(color, true, " %+d", p0);
            break;

        case 128: 	//	????????

            if(bLocal)
            {
                if(p0 != p1 && p1 > 0)
                {
                    AddHtmlDescText(color, false, GetWideString(ITEMDESC_VITALITY).toStdString().c_str(), p0);
                    AddHtmlDescText(color, true, "~%d", p1);
                }
                else
                {
                    AddHtmlDescText(color, true, GetWideString(ITEMDESC_VITALITY).toStdString().c_str(), p0);
                }
            }
            else
            {
                AddHtmlDescText(color, true, GetWideString(ITEMDESC_VITALITY).toStdString().c_str(), p0);
            }
            break;

        case 129: 	//	????????

            if(bLocal)
            {
                if(p0 != p1 && p1 > 0)
                {
                    AddHtmlDescText(color, false, GetWideString(ITEMDESC_STRENGTH).toStdString().c_str(), p0);
                    AddHtmlDescText(color, true, "~%d", p1);
                }
                else
                {
                    AddHtmlDescText(color, true, GetWideString(ITEMDESC_STRENGTH).toStdString().c_str(), p0);
                }
            }
            else
            {
                AddHtmlDescText(color, true, GetWideString(ITEMDESC_STRENGTH).toStdString().c_str(), p0);
            }
            break;

        case 130: 	//	????????

            if(bLocal)
            {
                if(p0 != p1 && p1 > 0)
                {
                    AddHtmlDescText(color, false, GetWideString(ITEMDESC_AGILITY).toStdString().c_str(), p0);
                    AddHtmlDescText(color, true, "~%d", p1);
                }
                else
                {
                    AddHtmlDescText(color, true, GetWideString(ITEMDESC_AGILITY).toStdString().c_str(), p0);
                }
            }
            else
            {
                AddHtmlDescText(color, true, GetWideString(ITEMDESC_AGILITY).toStdString().c_str(), p0);
            }
            break;

        case 131: 	//	?????��??

            if(bLocal)
            {
                if(p0 != p1 && p1 > 0)
                {
                    AddHtmlDescText(color, false, GetWideString(ITEMDESC_ENERGY).toStdString().c_str(), p0);
                    AddHtmlDescText(color, true, "~%d", p1);
                }
                else
                {
                    AddHtmlDescText(color, true, GetWideString(ITEMDESC_ENERGY).toStdString().c_str(), p0);
                }
            }
            else
            {
                AddHtmlDescText(color, true, GetWideString(ITEMDESC_ENERGY).toStdString().c_str(), p0);
            }
            break;

        case 132: 	//	????HP

            AddHtmlDescText(color, false, GetWideString(ITEMDESC_ADDHP).toStdString().c_str());
            AddHtmlDescText(color, true, " %+d", p0);
            break;

        case 133: 	//	???????����??��

            AddHtmlDescText(color, false, GetWideString(ITEMDESC_PHYDEFENCE).toStdString().c_str());
            AddHtmlDescText(color, true, " %+d", p0);
            break;

        case 134: 	//	????????��??��

            AddHtmlDescText(color, false, GetWideString(ITEMDESC_ALLMAGICDEF).toStdString().c_str());
            AddHtmlDescText(color, true, " %+d", p0);
            break;

        case 135:	//	???????��???��

            AddHtmlDescText(color, false, GetWideString(ITEMDESC_ADDPHYDAMAGE).toStdString().c_str());
            AddHtmlDescText(color, true, " %+d", p0);
            break;

        case 136:	//	?????�졤��???��

            AddHtmlDescText(color, false, GetWideString(ITEMDESC_ADDMAGICDAMAGE).toStdString().c_str());
            AddHtmlDescText(color, true, " %+d", p0);
            break;

        case 137: 	//	????????????(%)


            AddHtmlDescText(color, true, GetWideString(ITEMDESC_GOLDRESIST).toStdString().c_str(), p0);

            break;

        case 138: 	//	????????????(%)


            AddHtmlDescText(color, true, GetWideString(ITEMDESC_WOODRESIST).toStdString().c_str(), p0);

            break;

        case 139: 	//	????????????(%)


            AddHtmlDescText(color, true, GetWideString(ITEMDESC_WATERRESIST).toStdString().c_str(), p0);

            break;

        case 140: 	//	????????????(%)


            AddHtmlDescText(color, true, GetWideString(ITEMDESC_FIRERESIST).toStdString().c_str(), p0);

            break;

        case 141: 	//	????????????(%)


            AddHtmlDescText(color, true, GetWideString(ITEMDESC_EARTHRESIST).toStdString().c_str(), p0);

            break;

        case 142: 	//	????????????(%)


            AddHtmlDescText(color, true, GetWideString(ITEMDESC_ALLMAGICRESIST).toStdString().c_str(), p0);

            break;

        case 143: 	//	???????��???��??


            AddHtmlDescText(color, true, GetWideString(ITEMDESC_DEADLYSTRIKE).toStdString().c_str(), p0);

            break;

        case 144:	//	???????��????

            AddHtmlDescText(color, true, GetWideString(ITEMDESC_ATK_DEGREE).toStdString().c_str(), p0);
            break;

        case 145:	//	????��??��????

            AddHtmlDescText(color, true, GetWideString(ITEMDESC_DEF_DEGREE).toStdString().c_str(), p0);
            break;

        case 146: 	//	???????��????


            AddHtmlDescText(color, true, GetWideString(ITEMDESC_PHYRESIST).toStdString().c_str(), p0);

            break;

        case 147: 	//	???????��????
            AddHtmlDescText(color, false, GetWideString(ITEMDESC_VIGOUR).toStdString().c_str());
            AddHtmlDescText(color, true, " %+d", p0);
            break;

        case 150:


            AddHtmlDescText(color, true, GetWideString(ITEMDESC_DEADLYSTRIKE).toStdString().c_str(), p0);

            break;
        case 151:


            AddHtmlDescText(color, true, GetWideString(ITEMDESC_DEADLYSTRIKE).toStdString().c_str(), p0);

            break;
        case 152:


            AddHtmlDescText(color, true, GetWideString(ITEMDESC_DEADLYSTRIKE).toStdString().c_str(), p0);

            break;
        case 153:

            AddHtmlDescText(color, true, GetWideString(ITEMDESC_DEADLYSTRIKE).toStdString().c_str(), p0);

            break;
        case 154:


            AddHtmlDescText(color, true, GetWideString(ITEMDESC_DEADLYSTRIKE).toStdString().c_str(), p0);

            break;
        case 155:


            AddHtmlDescText(color, true, GetWideString(ITEMDESC_DEADLYSTRIKE).toStdString().c_str(), p0);

            break;

        case 156:
        {
            AddHtmlDescText(color, true, GetWideString(ITEMDESC_SOULPOWER).toStdString().c_str(), p0);
        }break;


        case 182:
        {
            AddHtmlDescText(color, false, GetWideString(ITEMDESC_VIGOUR).toStdString().c_str());
            AddHtmlDescText(color, true, " %+d", p0);
        }break;

        default:

            AddHtmlDescText(color, true, GetWideString(ITEMDESC_ERRORPROP).toStdString().c_str(), idProp);
            break;
        }
    }
    return desc;
}

void PlayerEditor::AddInventoryItem(int index)
{
    foreach(auto item, p.pocket.items)
    {
        if (item.pos == index)
        {
            QMessageBox::warning(this, "Atenção", "Não foi possível adicionar um novo item.\nEssa posição já está ocupada por um item.");
            return;
        }
    }

    GRoleInventory inv;
    inv.count = 1;
    inv.data = Octets();
    inv.expire_date = 0;
    inv.guid1 = 0;
    inv.guid2 = 0;
    inv.id = 0;
    inv.mask = 0;
    inv.max_count = 1;
    inv.pos = index;
    inv.proctype = 0;
    p.pocket.items.push_back(inv);

    ui->pocket_list->item(index)->setIcon(QIcon(":/Icons/0.gif"));
    PopulateInfos(inv);
}

void PlayerEditor::RemoveInventoryItem(int index)
{
    foreach(auto item, p.pocket.items)
    {
        if (item.pos == index)
        {
            QMessageBox::warning(this, "Atenção", "Não há item para remover.");
            return;
        }
    }

    p.pocket.items.removeAt(index);
    ui->pocket_list->item(index)->setIcon(QIcon(":/Icons/transparent.png"));
}

DWORD PlayerEditor::PropEffectEssence(QList<addon_data> m_aProps)
{
    DWORD dwFlags = 0;

    for (int i=0; i < m_aProps.count(); i++)
    {
        dwFlags = PropEffectMask(m_aProps[i], dwFlags);
    }

    return dwFlags;
}

DWORD PlayerEditor::PropEffectMask(addon_data prop, DWORD dwFlags)
{
    BYTE byPropType = (BYTE)pwAdmin::getInstance().addonsList.value(QString::number(prop.id_addon)).toInt();

    switch (byPropType)
    {
    case 0:		//	��������

        dwFlags |= PEE_PHYDAMAGE;
        break;

    case 1:		//	������������

        dwFlags |= PEE_PHYDAMAGE;
        break;

    case 3:		//	ħ������

        dwFlags |= PEE_MAGICDAMAGE;
        break;

    case 6: 	//	+���-�﹥

        dwFlags |= PEE_PHYDAMAGE;
        dwFlags |= PEE_PHYDEF;
        break;

    case 7: 	//	+�﹥-���

        dwFlags |= PEE_PHYDAMAGE;
        dwFlags |= PEE_PHYDEF;
        break;

    case 8: 	//	+ħ��-ħ��

        dwFlags |= PEE_MAGICDAMAGE;
        dwFlags |= PEE_GOLDDEF;
        dwFlags |= PEE_WOODDEF;
        dwFlags |= PEE_WATERDEF;
        dwFlags |= PEE_FIREDEF;
        dwFlags |= PEE_EARTHDEF;
        break;

    case 9: 	//	�����ٶ�

        dwFlags |= PEE_ATKSPEED;
        break;

    case 10: 	//	��������

        dwFlags |= PEE_ATKDIST;
        break;

    case 12: 	//	��������

        dwFlags |= PEE_PHYDEF;
        break;

    case 14: 	//	���з���

        dwFlags |= PEE_GOLDDEF;
        dwFlags |= PEE_WOODDEF;
        dwFlags |= PEE_WATERDEF;
        dwFlags |= PEE_FIREDEF;
        dwFlags |= PEE_EARTHDEF;
        break;

    case 15: 	//	���

        dwFlags |= PEE_GOLDDEF;
        break;

    case 17: 	//	ľ��

        dwFlags |= PEE_WOODDEF;
        break;

    case 19: 	//	ˮ��

        dwFlags |= PEE_WATERDEF;
        break;

    case 21: 	//	���

        dwFlags |= PEE_FIREDEF;
        break;

    case 23: 	//	����

        dwFlags |= PEE_EARTHDEF;
        break;

    case 30: 	//	+���-���

        dwFlags |= PEE_GOLDDEF;
        dwFlags |= PEE_FIREDEF;
        break;

    case 31: 	//	+ľ��-���

        dwFlags |= PEE_GOLDDEF;
        dwFlags |= PEE_WOODDEF;
        break;

    case 32: 	//	+ˮ��-����

        dwFlags |= PEE_WATERDEF;
        dwFlags |= PEE_EARTHDEF;
        break;

    case 33: 	//	+���-ˮ��

        dwFlags |= PEE_WATERDEF;
        dwFlags |= PEE_FIREDEF;
        break;

    case 34: 	//	+����-ľ��

        dwFlags |= PEE_WOODDEF;
        dwFlags |= PEE_EARTHDEF;
        break;

    case 35: 	//	HP

        dwFlags |= PEE_HP;
        break;

    case 36: 	//	MP

        dwFlags |= PEE_MP;
        break;

    case 50: 	//	����

        dwFlags |= PEE_DODGE;
        break;

    case 53: 	//	�;ö�(%)

        dwFlags |= PEE_ENDURANCE;
        break;

    case 56: 	//	װ������

        dwFlags |= PEE_STRENGTHREQ;
        dwFlags |= PEE_AGILITYREQ;
        dwFlags |= PEE_ENERGYREQ;
        dwFlags |= PEE_VITALITYREQ;
        break;

    case 92: 	//	+���+ħ��

        dwFlags |= PEE_PHYDEF;
        dwFlags |= PEE_GOLDDEF;
        dwFlags |= PEE_WOODDEF;
        dwFlags |= PEE_WATERDEF;
        dwFlags |= PEE_FIREDEF;
        dwFlags |= PEE_EARTHDEF;
        break;

        //	case 2:		//	��������(%)
        //	case 4: 	//	ħ����������
        //	case 5: 	//	ħ������(%)
        //	case 11: 	//	����ʱ��
        //	case 13: 	//	��������(%)
        //	case 16: 	//	���(%)
        //	case 18: 	//	ľ��(%)
        //	case 20: 	//	ˮ��(%)
        //	case 22: 	//	���(%)
        //	case 24: 	//	����(%)
        //	case 25: 	//	+���(%)-���(%)
        //	case 26: 	//	+ľ��(%)-���(%)
        //	case 27: 	//	+ˮ��(%)-����(%)
        //	case 28: 	//	+���(%)-ˮ��(%)
        //	case 29: 	//	+����(%)-ľ��(%)
        //	case 37: 	//	HP(%)
        //	case 38: 	//	MP(%)
        //	case 39: 	//	HP�ָ��ٶ�
        //	case 40: 	//	MP�ָ��ٶ�
        //	case 41: 	//	����
        //	case 42: 	//	����
        //	case 43: 	//	����
        //	case 44: 	//	����
        //	case 45: 	//	����һ����
        //	case 46: 	//	����
        //	case 47: 	//	����(%)
        //	case 48: 	//	�ƶ��ٶ�
        //	case 49: 	//	�ƶ��ٶ�(%)
        //	case 51: 	//	����(%)
        //	case 52: 	//	�;ö�
        //	case 54: 	//	��������
        //	case 55: 	//	���Ӽ���
        //	case 57: 	//	δ֪����
        //	case 58:	//	����ֵ�ӳ�
        //	case 59:	//	�����ȼ�
        //	case 60:	//	�����ȼ�
    }

    return dwFlags;
}

int PlayerEditor::VisualizeEndurance(int v)
{
    return (v+100-1) / 100;
}

QString PlayerEditor::GetFormattedPrice(qint64 i)
{
    QString szRes;
    QString strSeparator = GetWideString(ITEMDESC_PRICE_SEPERATOR);
    if (strSeparator.isEmpty())
        strSeparator = ",";

    if( i < 1000 )
        szRes = QString("%1").arg((int)i);
    else if( i < 1000000 )
        szRes = QString("%1%2%3")
                .arg(i / 1000) // Dividir i por 1000 e converter para string
                .arg(strSeparator) // Inserir a string separadora
                .arg(i % 1000, 3, 10, QChar('0')); // i mod 1000, formatado com 3 dígitos, preenchendo com zeros

    else if( i < 1000000000 )
        szRes = QString("%1%2%3%4%5")
                .arg(i / 1000000) // Dividir i por 1.000.000 e converter para string
                .arg(strSeparator) // Inserir a primeira string separadora
                .arg(i / 1000 % 1000, 3, 10, QChar('0')) // (i / 1000) % 1000, formatado com 3 dígitos, preenchendo com zeros
                .arg(strSeparator) // Inserir a segunda string separadora
                .arg(i % 1000, 3, 10, QChar('0'));
    else
    {
        int nHigh = int(i / 1000000000);
        int nLow = int(i % 1000000000);

        szRes = QString("%1%2%3%4%5%6%7")
                .arg(nHigh) // Parte dos bilhões
                .arg(strSeparator) // Inserir o primeiro separador
                .arg(nLow / 1000000 % 1000, 3, 10, QChar('0')) // Parte dos milhões de nLow, formatada
                .arg(strSeparator) // Inserir o segundo separador
                .arg(nLow / 1000 % 1000, 3, 10, QChar('0')) // Parte dos milhares de nLow, formatada
                .arg(strSeparator) // Inserir o terceiro separador
                .arg(nLow % 1000, 3, 10, QChar('0'));
    }
    return szRes;
}

void PlayerEditor::PopulateInfos(GRoleInventory inv)
{
    ui->txt_count->setValue(inv.count);
    ui->txt_data->setText(inv.data.value.toHex());
    ui->txt_data->setCursorPosition(0);
    ui->txt_expiredata->setValue(inv.expire_date);
    ui->txt_guid1->setValue(inv.guid1);
    ui->txt_guid2->setValue(inv.guid2);
    ui->txt_id->setValue(inv.id);
    ui->txt_mask->setValue(inv.mask);
    ui->txt_maxcount->setValue(inv.max_count);
    ui->txt_pos->setValue(inv.pos);
    ui->txt_proctype->setValue(inv.proctype);

    int type = (inv.mask & EQUIP_MASK::EQUIP_MASK_HAS_ADDON) > 0 ? inv.mask - EQUIP_MASK::EQUIP_MASK_HAS_ADDON : inv.mask;
    qDebug() << type;
    OctetsStream os(inv.data.value, false);
    os.qds->setByteOrder(QDataStream::BigEndian);
    desc.clear();
    int aPEEVals[MAX_PEEINDEX];
    int aRefines[MAX_REFINEINDEX];
    memset(aPEEVals, 0, sizeof (aPEEVals));
    memset(aRefines, 0, sizeof (aRefines));
    int color = -1;
    int lblue = ITEMDESC_COL_LIGHTBLUE;
    int white = ITEMDESC_COL_WHITE;
    int red = ITEMDESC_COL_RED;
    switch((EQUIP_MASK64)type)
    {
    case EQUIP_MASK64_WEAPON:
    {
        weapon_essence ess;
        ess.unmarshal(os, pwAdmin::getInstance().infos.ServerVersion);
        BuildAddOnPropDesc(ess.addons, aPEEVals, aRefines);
        auto strAddon = desc;
        desc.clear();

        // DefaultInfo()
        int m_iLevelReq		= ess.prereq.level;
        int  m_iStrengthReq	= ess.prereq.strength;
        int  m_iAgilityReq	= ess.prereq.agility;
        int m_iVitalityReq = ess.prereq.vitality;
        int m_iEnergyReq = ess.prereq.energy;
        int m_iReputationReq= Commands::GetItemValue(inv.id, "require_reputation", "WEAPON_ESSENCE").toInt();
        int m_iCurEndurance	= ess.prereq.durability;
        int m_iMaxEndurance = ess.prereq.max_durability;

        if (ess.slot_count > 0)
            AddHtmlDescText(color, false, GetWideString(ITEMDESC_NAMESOCKET).toStdString().c_str(), Commands::GetItemName(inv.id).toStdString().c_str(), ess.slot_count);
        else AddHtmlDescText(color, false, GetWideString(ITEMDESC_NAME).toStdString().c_str(), Commands::GetItemName(inv.id).toStdString().c_str());
        DWORD dwPEE = PropEffectEssence(ess.addons);
        OctetsStream os(p.status.property.value, false, false);
        PlayerProperty pp;
        pp.unmarshal(&os);
        int refino = 0;
        foreach(auto addon, ess.addons)
        {
            quint8 byPropType = (qint8)pwAdmin::getInstance().addonsList.value(QString::number(addon.id_addon)).toInt();
            switch(byPropType)
            {
            case 200:
            case 201:
            case 202:
            case 203:
            case 204:
            case 205:
            case 206:
            case 207:
            case 208:
            case 209:
            case 210:
            case 211:
            case 212:
                refino = addon.arg[1];
                break;
            }
        }
        if (refino > 0)
            AddHtmlDescText(color, true, " +%d", refino);
        else desc += "<br>";
        AddBindDescText(inv.proctype);
        AddExpireTimeDesc(inv.expire_date);
        int id_subtype = Commands::GetItemValue(inv.id, "id_sub_type", "WEAPON_ESSENCE").toInt();
        AddHtmlDescText(white, true, GetWideString(ITEMDESC_CLASSNAME).toStdString().c_str(), Commands::GetItemValue(id_subtype, "Name", "WEAPON_SUB_TYPE").toStdString().c_str());
        AddHtmlDescText(-1, true, GetWideString(ITEMDESC_LEVEL).toStdString().c_str(), ess.weapon_level);
        int col = (dwPEE & PEE_ATKSPEED) ? lblue : white;
        AddHtmlDescText(col, false, GetWideString(ITEMDESC_ATKSPEED).toStdString().c_str());
        AddHtmlDescText(col, true, " %.2f", 1.0f / (ess.attack_speed * 0.05f));
        AddHtmlDescText(white, true, GetWideString(ITEMDESC_ATKDISTANCE).toStdString().c_str(), ess.attack_range - *(float*)&aPEEVals[PEEI_ATKDIST]);
        if (ess.weapon_type == WEAPON_TYPE_RANGE)
            AddHtmlDescText(white, true, GetWideString(ITEMDESC_WEAKDIST).toStdString().c_str(), ess.attack_short_range);

        //	Physical damage
        if (ess.damage_low || ess.damage_high || aRefines[REFINE_PHYDAMAGE])
        {
            AddHtmlDescText(white, false, GetWideString(ITEMDESC_PHYDAMAGE).toStdString().c_str());
            AddHtmlDescText(white, true, (" %d-%d"), ess.damage_low - aPEEVals[PEEI_PHYDAMAGE] + aRefines[REFINE_PHYDAMAGE],
                            ess.damage_high - aPEEVals[PEEI_PHYDAMAGE] - aPEEVals[PEEI_MAX_PHYDAMAGE] + aRefines[REFINE_PHYDAMAGE]);
        }

        //	Magic damage
        if (ess.magic_damage_low || ess.magic_damage_high || aRefines[REFINE_MAGICDAMAGE])
        {
            AddHtmlDescText(white, false, GetWideString(ITEMDESC_MAGICDAMAGE).toStdString().c_str());
            AddHtmlDescText(white, true, (" %d-%d"), ess.magic_damage_low - aPEEVals[PEEI_MAGICDAMAGE] + aRefines[REFINE_MAGICDAMAGE],
                            ess.magic_damage_high - aPEEVals[PEEI_MAGICDAMAGE] - aPEEVals[PEEI_MAX_MAGICDAMAGE] + aRefines[REFINE_MAGICDAMAGE]);
        }

        //	Endurance
        col = white;
        if (!m_iCurEndurance)
            col = red;
        else if (dwPEE & PEE_ENDURANCE)
            col = lblue;

        AddHtmlDescText(col, false, GetWideString(ITEMDESC_ENDURANCE).toStdString().c_str());
        AddHtmlDescText(col, true, (" %d/%d"), VisualizeEndurance(m_iCurEndurance), VisualizeEndurance(m_iMaxEndurance));

        //	Projectile requirement
        if (ess.weapon_type == WEAPON_TYPE_RANGE && ess.require_projectile)
        {
            auto projectile_name = Commands::GetItemValue(ess.require_projectile, "Name", "PROJECTILE_TYPE");
            AddHtmlDescText(white, true, GetWideString(ITEMDESC_PROJECTILE).toStdString().c_str(), projectile_name.toStdString().c_str());
        }

        //	Profession requirement
        int col_prof_req = (ess.prereq.race & (1 << p.base.cls)) ? ITEMDESC_COL_WHITE : ITEMDESC_COL_RED;
        AddHtmlDescText(col_prof_req, false, GetWideString(ITEMDESC_PROFESSIONREQ).toStdString().c_str());
        for (int i=0; i < pwAdmin::getInstance().listClasses.count(); i++)
        {
            if (ess.prereq.race & (1 << i))
            {
                desc += " ";
                AddHtmlDescText(col_prof_req, false, pwAdmin::getInstance().listFixedMsg[s_ProfDesc[i]].toStdString().c_str());
            }
        }
        desc += "<br>";
        //	Level requirment
        if (m_iLevelReq)
        {
            col = p.status.level >= m_iLevelReq ? white : red;
            AddHtmlDescText(col, true, GetWideString(ITEMDESC_LEVELREQ).toStdString().c_str(), m_iLevelReq);
        }

        //	Strength requirment
        if (m_iStrengthReq)
        {
            if (pp.strength < m_iStrengthReq)
                col = red;
            else
                col = (dwPEE & PEE_STRENGTHREQ) ? lblue : white;

            AddHtmlDescText(col, true, GetWideString(ITEMDESC_STRENGTHREQ).toStdString().c_str(), m_iStrengthReq);
        }

        //	Agility requirment
        if (m_iAgilityReq)
        {
            if (pp.agility < m_iAgilityReq)
                col = red;
            else
                col = (dwPEE & PEE_AGILITYREQ) ? lblue : white;

            AddHtmlDescText(col, true, GetWideString(ITEMDESC_AGILITYREQ).toStdString().c_str(), m_iAgilityReq);
        }

        //	Vitality requirment
        if (m_iVitalityReq)
        {
            if (pp.vitality < m_iVitalityReq)
                col = red;
            else
                col = (dwPEE & PEE_VITALITYREQ) ? lblue : white;

            AddHtmlDescText(col, true, GetWideString(ITEMDESC_VITALITYREQ).toStdString().c_str(), m_iVitalityReq);
        }

        //	Energy requirment
        if (m_iEnergyReq)
        {
            if (pp.energy < m_iEnergyReq)
                col = red;
            else
                col = (dwPEE & PEE_ENERGYREQ) ? lblue : white;

            AddHtmlDescText(col, true, GetWideString(ITEMDESC_ENERGYREQ).toStdString().c_str(), m_iEnergyReq);
        }

        if (m_iReputationReq)
        {
            int col = p.status.reputation >= m_iReputationReq ? ITEMDESC_COL_WHITE : ITEMDESC_COL_RED;
            AddHtmlDescText(col, true, GetWideString(ITEMDESC_REPUTATION_REQ).toStdString().c_str(), m_iReputationReq);
        }

        if (strAddon.length())
            desc += strAddon;

        if (ess.slot_count)
        {
            int cyanine = ITEMDESC_COL_CYANINE;

            for (int i=0; i < ess.slot_count; i++)
            {
                if (!ess.slot_list[i])
                    continue;
                auto szText = Commands::GetItemValue(ess.slot_list[i], "weapon_desc", "STONE_ESSENCE");
                AddHtmlDescText(cyanine, true, GetWideString(ITEMDESC_2STRINGS).toStdString().c_str(), Commands::GetItemName(ess.slot_list[i], "STONE_ESSENCE").toStdString().c_str(), szText.toStdString().c_str());
            }
        }

        if(Commands::GetItemValue(inv.id, "fixed_props", "WEAPON_ESSENCE").toInt() == 0)
        {
            AddHtmlDescText(ITEMDESC_COL2_BRIGHTBLUE, true, GetWideString(ITEMDESC_HASRANDOM_PROP).toStdString().c_str());
        }

        int price = Commands::GetItemValue(inv.id, "price", "WEAPON_ESSENCE").toUInt();
        if(price >= 100000000) // 100 million
            col = ITEMDESC_COL_GREEN;
        else if ( price >= 10000000) // 10 million
            col = ITEMDESC_COL_DARKGOLD;
        else if ( price >= 1000000) // 1 million
            col = ITEMDESC_COL_YELLOW;
        else col = ITEMDESC_COL_WHITE;
        desc += "<br>";
        AddHtmlDescText(col, false, GetWideString(ITEMDESC_PRICE).toStdString().c_str());
        AddHtmlDescText(-1, false, " %s", GetFormattedPrice(price).toStdString().c_str());

        if(ess.addons.size())
        {
            int bFirstProp = true;
            foreach(auto ad, ess.addons)
            {
                if (ad.isEngraved)
                {
                    if (bFirstProp)
                    {
                        bFirstProp = false;
                        desc += "<br>";
                        desc += GetWideString(ITEMDESC_COL_YELLOW);
                    }
                    GetHtmlAddonName(ad.id_addon, ad.arg[0], ad.arg[1], ad.arg[2], NULL, NULL);
                }
            }
        }

        if (!ess.made_tag.tag_content.toName().isEmpty())
        {
            desc += "<br>";
            if (ess.made_tag.tag_type != IMT_SIGN)
            {
                AddHtmlDescText(ITEMDESC_COL_GREEN, false, GetWideString(ITEMDESC_MADEFROM).toStdString().c_str(), ess.made_tag.tag_content.toName().toStdString().c_str());
            } else
            {
                AddHtmlDescText(ITEMDESC_COL_GREEN, false, "[%s]", ess.made_tag.tag_content.toName().toStdString().c_str());
            }
        }

        desc += "<br>";
        int green = ITEMDESC_COL2_BRIGHTBLUE;
        bool bAddLine = true;
        if ((inv.proctype & PROC_NO_USER_TRASH)
                || !(inv.proctype & PROC_BINDING )
                && (inv.proctype & PROC_DROPWHENDIE ||
                    inv.proctype & PROC_DROPPABLE ||
                    inv.proctype & PROC_SELLABLE ||
                    inv.proctype & PROC_TRADEABLE ||
                    inv.proctype & PROC_DISAPEAR ||
                    inv.proctype & PROC_USE ||
                    inv.proctype & PROC_DEADDROP ||
                    inv.proctype & PROC_OFFLINE ||
                    inv.proctype & PROC_UNREPAIRABLE))
        {
            bAddLine = false;
            auto szCol = GetWideString(green);
            qDebug()<< szCol << Utils::FormatColorText(szCol);

            if(inv.proctype & PROC_DROPWHENDIE)
            {
                szCol += "<br>";
                szCol += GetWideString(ITEMDESC_DEAD_PROTECT);
            }
            if(inv.proctype & PROC_DROPPABLE)
            {
                szCol += "<br>";
                szCol += GetWideString(ITEMDESC_NO_DROP);
            }
            if(inv.proctype & PROC_SELLABLE)
            {
                szCol += "<br>";
                szCol += GetWideString(ITEMDESC_NO_TRADE);
            }
            if(inv.proctype & PROC_TRADEABLE)
            {
                szCol += "<br>";
                szCol += GetWideString(ITEMDESC_NO_PLAYER_TRADE);
            }
            if(inv.proctype & PROC_DISAPEAR)
            {
                szCol += "<br>";
                szCol += GetWideString(ITEMDESC_LEAVE_SCENE_DISAPEAR);
            }
            if(inv.proctype & PROC_USE)
            {
                szCol += "<br>";
                szCol += GetWideString(ITEMDESC_USE_AFTER_PICK_UP);
            }
            if(inv.proctype & PROC_DEADDROP)
            {
                szCol += "<br>";
                szCol += GetWideString(ITEMDESC_DROP_WHEN_DEAD);
            }
            if(inv.proctype & PROC_OFFLINE)
            {
                szCol += "<br>";
                szCol += GetWideString(ITEMDESC_DROP_WHEN_OFFLINE);
            }
            if(inv.proctype & PROC_UNREPAIRABLE)
            {
                szCol += "<br>";
                szCol += GetWideString(ITEMDESC_UNREPAIRABLE);
            }
            if(inv.proctype & PROC_NO_USER_TRASH)
            {
                szCol += "<br>";
                szCol += GetWideString(ITEMDESC_NO_USER_TRASH);
            }

            desc += Utils::FormatColorText(szCol);
        }

        auto extdesc = pwAdmin::getInstance().listItemExtDesc[inv.id];
        if (!extdesc.isEmpty())
        {
            if(bAddLine)
                desc += "<br><br>";
            else
                desc += "<br><br>";
            desc += Utils::FormatColorText(extdesc);
        }

        break;
    }
    case EQUIP_MASK64_HP_ADDON:
    {
        amulet_essence ess;
        ess.unmarshal(os);
        break;
    }
    case EQUIP_MASK64_MP_ADDON:
    {
        amulet_essence ess;
        ess.unmarshal(os);
        break;
    }
    case EQUIP_MASK64_FLYSWORD:
    {
        flysword_essence ess;
        ess.unmarshal(os);
        break;
    }
    case EQUIP_MASK64_FORCE_TICKET:
    {

        break;
    }
    case EQUIP_MASK64_FINGER1:
    case EQUIP_MASK64_FINGER2:
    case EQUIP_MASK64_FINGERS:
    case EQUIP_MASK64_NECK:
    case EQUIP_MASK64_WAIST:
    {
        decoration_essence ess;
        ess.unmarshal(os);
        int col = white;
        BuildAddOnPropDesc(ess.addons, aPEEVals, aRefines);
        auto strAddon = desc;
        desc.clear();

        // DefaultInfo()
        int m_iLevelReq		= ess.prereq.level;
        int  m_iStrengthReq	= ess.prereq.strength;
        int  m_iAgilityReq	= ess.prereq.agility;
        int m_iVitalityReq = ess.prereq.vitality;
        int m_iEnergyReq = ess.prereq.energy;
        int m_iReputationReq= Commands::GetItemValue(inv.id, "require_reputation", "DECORATION_ESSENCE").toInt();
        int m_iCurEndurance	= ess.prereq.durability;
        int m_iMaxEndurance = ess.prereq.max_durability;
        if (ess.slot_count > 0)
            AddHtmlDescText(color, false, GetWideString(ITEMDESC_NAMESOCKET).toStdString().c_str(), Commands::GetItemName(inv.id).toStdString().c_str(), ess.slot_count);
        else AddHtmlDescText(color, false, GetWideString(ITEMDESC_NAME).toStdString().c_str(), Commands::GetItemName(inv.id).toStdString().c_str());

        DWORD dwPEE = PropEffectEssence(ess.addons);
        OctetsStream os(p.status.property.value, false, false);
        PlayerProperty pp;
        pp.unmarshal(&os);
        int refino = 0;
        foreach(auto addon, ess.addons)
        {
            quint8 byPropType = (qint8)pwAdmin::getInstance().addonsList.value(QString::number(addon.id_addon)).toInt();
            switch(byPropType)
            {
            case 200:
            case 201:
            case 202:
            case 203:
            case 204:
            case 205:
            case 206:
            case 207:
            case 208:
            case 209:
            case 210:
            case 211:
            case 212:
                refino = addon.arg[1];
                break;
            }
        }
        if (refino > 0)
            AddHtmlDescText(color, true, " +%d", refino);
        else desc += "<br>";
        AddBindDescText(inv.proctype);
        AddExpireTimeDesc(inv.expire_date);
        int id_subtype = Commands::GetItemValue(inv.id, "id_sub_type", "DECORATION_ESSENCE").toInt();
        int level = Commands::GetItemValue(inv.id, "level", "DECORATION_ESSENCE").toInt();
        AddHtmlDescText(white, true, GetWideString(ITEMDESC_CLASSNAME).toStdString().c_str(), Commands::GetItemValue(id_subtype, "Name", "DECORATION_SUB_TYPE").toStdString().c_str());
        AddHtmlDescText(-1, true, GetWideString(ITEMDESC_LEVEL).toStdString().c_str(), level);

        //	Add physical damage
        if (ess.damage - aPEEVals[PEEI_PHYDAMAGE] + aRefines[REFINE_PHYDAMAGE])
        {
            AddHtmlDescText(white, false, GetWideString(ITEMDESC_ADDPHYDAMAGE).toStdString().c_str());
            AddHtmlDescText(white, true, " %+d", ess.damage - aPEEVals[PEEI_PHYDAMAGE] + aRefines[REFINE_PHYDAMAGE]);
        }

        //	Add magic damage
        if (ess.magic_damage - aPEEVals[PEEI_MAGICDAMAGE] + aRefines[REFINE_MAGICDAMAGE])
        {
            AddHtmlDescText(white, false, GetWideString(ITEMDESC_ADDMAGICDAMAGE).toStdString().c_str());
            AddHtmlDescText(white, true, " %+d", ess.magic_damage - aPEEVals[PEEI_MAGICDAMAGE] + aRefines[REFINE_MAGICDAMAGE]);
        }

        //	Physical defence
        if (ess.defense - aPEEVals[PEEI_PHYDEF] + aRefines[REFINE_PHYDEF])
        {
            AddHtmlDescText(white, false, GetWideString(ITEMDESC_PHYDEFENCE).toStdString().c_str());
            AddHtmlDescText(white, true, (" %+d"), ess.defense - aPEEVals[PEEI_PHYDEF] + aRefines[REFINE_PHYDEF]);
        }

        //	Dodge
        if (ess.armor - aPEEVals[PEEI_DODGE] + aRefines[REFINE_DODGE])
        {
            AddHtmlDescText(white, false, GetWideString(ITEMDESC_DODGE).toStdString().c_str());
            AddHtmlDescText(white, true, (" %+d"), ess.armor - aPEEVals[PEEI_DODGE] + aRefines[REFINE_DODGE]);
        }

        if (ess.resistance[MAGICCLASS_GOLD] - aPEEVals[PEEI_GOLDDEF] + aRefines[REFINE_GOLDDEF])
        {
            AddHtmlDescText(white, false, GetWideString(ITEMDESC_GOLDDEFENCE).toStdString().c_str());
            AddHtmlDescText(white, true, (" %+d"), ess.resistance[MAGICCLASS_GOLD] - aPEEVals[PEEI_GOLDDEF] + aRefines[REFINE_GOLDDEF]);
        }

        if (ess.resistance[MAGICCLASS_WOOD] - aPEEVals[PEEI_WOODDEF] + aRefines[REFINE_WOODDEF])
        {
            AddHtmlDescText(white, false, GetWideString(ITEMDESC_WOODDEFENCE).toStdString().c_str());
            AddHtmlDescText(white, true, (" %+d"), ess.resistance[MAGICCLASS_WOOD] - aPEEVals[PEEI_WOODDEF] + aRefines[REFINE_WOODDEF]);
        }

        if (ess.resistance[MAGICCLASS_WATER] - aPEEVals[PEEI_WATERDEF] + aRefines[REFINE_WATERDEF])
        {
            AddHtmlDescText(white, false, GetWideString(ITEMDESC_WATERDEFENCE).toStdString().c_str());
            AddHtmlDescText(white, true, (" %+d"), ess.resistance[MAGICCLASS_WATER] - aPEEVals[PEEI_WATERDEF] + aRefines[REFINE_WATERDEF]);
        }

        if (ess.resistance[MAGICCLASS_FIRE] - aPEEVals[PEEI_FIREDEF] + aRefines[REFINE_FIREDEF])
        {
            AddHtmlDescText(white, false, GetWideString(ITEMDESC_FIREDEFENCE).toStdString().c_str());
            AddHtmlDescText(white, true, (" %+d"), ess.resistance[MAGICCLASS_FIRE] - aPEEVals[PEEI_FIREDEF] + aRefines[REFINE_FIREDEF]);
        }

        if (ess.resistance[MAGICCLASS_EARTH] - aPEEVals[PEEI_EARTHDEF] + aRefines[REFINE_EARTHDEF])
        {
            AddHtmlDescText(white, false, GetWideString(ITEMDESC_EARTHDEFENCE).toStdString().c_str());
            AddHtmlDescText(white, true, (" %+d"), ess.resistance[MAGICCLASS_EARTH] - aPEEVals[PEEI_EARTHDEF] + aRefines[REFINE_EARTHDEF]);
        }
        //	Endurance
        col = white;
        if (!m_iCurEndurance)
            col = red;
        else if (dwPEE & PEE_ENDURANCE)
            col = lblue;

        AddHtmlDescText(col, false, GetWideString(ITEMDESC_ENDURANCE).toStdString().c_str());
        AddHtmlDescText(col, true, (" %d/%d"), VisualizeEndurance(m_iCurEndurance), VisualizeEndurance(m_iMaxEndurance));

        //	Profession requirement
        int col_prof_req = (ess.prereq.race & (1 << p.base.cls)) ? ITEMDESC_COL_WHITE : ITEMDESC_COL_RED;
        AddHtmlDescText(col_prof_req, false, GetWideString(ITEMDESC_PROFESSIONREQ).toStdString().c_str());
        for (int i=0; i < pwAdmin::getInstance().listClasses.count(); i++)
        {
            if (ess.prereq.race & (1 << i))
            {
                desc += " ";
                AddHtmlDescText(col_prof_req, false, pwAdmin::getInstance().listFixedMsg[s_ProfDesc[i]].toStdString().c_str());
            }
        }
        desc += "<br>";
        //	Level requirment
        if (m_iLevelReq)
        {
            col = p.status.level >= m_iLevelReq ? white : red;
            AddHtmlDescText(col, true, GetWideString(ITEMDESC_LEVELREQ).toStdString().c_str(), m_iLevelReq);
        }

        //	Strength requirment
        if (m_iStrengthReq)
        {
            if (pp.strength < m_iStrengthReq)
                col = red;
            else
                col = (dwPEE & PEE_STRENGTHREQ) ? lblue : white;

            AddHtmlDescText(col, true, GetWideString(ITEMDESC_STRENGTHREQ).toStdString().c_str(), m_iStrengthReq);
        }

        //	Agility requirment
        if (m_iAgilityReq)
        {
            if (pp.agility < m_iAgilityReq)
                col = red;
            else
                col = (dwPEE & PEE_AGILITYREQ) ? lblue : white;

            AddHtmlDescText(col, true, GetWideString(ITEMDESC_AGILITYREQ).toStdString().c_str(), m_iAgilityReq);
        }

        //	Vitality requirment
        if (m_iVitalityReq)
        {
            if (pp.vitality < m_iVitalityReq)
                col = red;
            else
                col = (dwPEE & PEE_VITALITYREQ) ? lblue : white;

            AddHtmlDescText(col, true, GetWideString(ITEMDESC_VITALITYREQ).toStdString().c_str(), m_iVitalityReq);
        }

        //	Energy requirment
        if (m_iEnergyReq)
        {
            if (pp.energy < m_iEnergyReq)
                col = red;
            else
                col = (dwPEE & PEE_ENERGYREQ) ? lblue : white;

            AddHtmlDescText(col, true, GetWideString(ITEMDESC_ENERGYREQ).toStdString().c_str(), m_iEnergyReq);
        }

        // Reputation requirement
        if (m_iReputationReq)
        {
            int col = p.status.reputation >= m_iReputationReq ? ITEMDESC_COL_WHITE : ITEMDESC_COL_RED;
            AddHtmlDescText(col, true, GetWideString(ITEMDESC_REPUTATION_REQ).toStdString().c_str(), m_iReputationReq);
        }

        //	Add addon properties
        if (strAddon.length())
            desc += strAddon;

        //	Build tessera description
        if (ess.slot_count)
        {
            int cyanine = ITEMDESC_COL_CYANINE;

            for (int i=0; i < ess.slot_count; i++)
            {
                if (!ess.slot_list[i])
                    continue;
                auto szText = Commands::GetItemValue(ess.slot_list[i], "armor_desc", "STONE_ESSENCE");
                AddHtmlDescText(cyanine, true, GetWideString(ITEMDESC_2STRINGS).toStdString().c_str(), Commands::GetItemName(ess.slot_list[i], "STONE_ESSENCE").toStdString().c_str(), szText.toStdString().c_str());
            }
        }

        if(Commands::GetItemValue(inv.id, "fixed_props", "DECORATION_ESSENCE").toInt() == 0)
        {
            AddHtmlDescText(ITEMDESC_COL2_BRIGHTBLUE, true, GetWideString(ITEMDESC_HASRANDOM_PROP).toStdString().c_str());
        }


        //	Price
        int price = Commands::GetItemValue(inv.id, "price", "DECORATION_ESSENCE").toUInt();
        if(price >= 100000000) // 100 million
            col = ITEMDESC_COL_GREEN;
        else if ( price >= 10000000) // 10 million
            col = ITEMDESC_COL_DARKGOLD;
        else if ( price >= 1000000) // 1 million
            col = ITEMDESC_COL_YELLOW;
        else col = ITEMDESC_COL_WHITE;
        desc += "<br>";
        AddHtmlDescText(col, false, GetWideString(ITEMDESC_PRICE).toStdString().c_str());
        AddHtmlDescText(-1, false, " %s", GetFormattedPrice(price).toStdString().c_str());

        if(ess.addons.size())
        {
            int bFirstProp = true;
            foreach(auto ad, ess.addons)
            {
                if (ad.isEngraved)
                {
                    if (bFirstProp)
                    {
                        bFirstProp = false;
                        desc += "<br>";
                        desc += GetWideString(ITEMDESC_COL_YELLOW);
                    }
                    GetHtmlAddonName(ad.id_addon, ad.arg[0], ad.arg[1], ad.arg[2], NULL, NULL);
                }
            }
        }

        if (!ess.made_tag.tag_content.toName().isEmpty())
        {
            desc += "<br>";
            if (ess.made_tag.tag_type != IMT_SIGN)
            {
                AddHtmlDescText(ITEMDESC_COL_GREEN, false, GetWideString(ITEMDESC_MADEFROM).toStdString().c_str(), ess.made_tag.tag_content.toName().toStdString().c_str());
            } else
            {
                AddHtmlDescText(ITEMDESC_COL_GREEN, false, "[%s]", ess.made_tag.tag_content.toName().toStdString().c_str());
            }
        }

        desc += "<br>";
        int green = ITEMDESC_COL2_BRIGHTBLUE;
        bool bAddLine = true;
        if ((inv.proctype & PROC_NO_USER_TRASH)
                || !(inv.proctype & PROC_BINDING )
                && (inv.proctype & PROC_DROPWHENDIE ||
                    inv.proctype & PROC_DROPPABLE ||
                    inv.proctype & PROC_SELLABLE ||
                    inv.proctype & PROC_TRADEABLE ||
                    inv.proctype & PROC_DISAPEAR ||
                    inv.proctype & PROC_USE ||
                    inv.proctype & PROC_DEADDROP ||
                    inv.proctype & PROC_OFFLINE ||
                    inv.proctype & PROC_UNREPAIRABLE))
        {
            bAddLine = false;
            auto szCol = GetWideString(green);
            qDebug()<< szCol << Utils::FormatColorText(szCol);

            if(inv.proctype & PROC_DROPWHENDIE)
            {
                szCol += "<br>";
                szCol += GetWideString(ITEMDESC_DEAD_PROTECT);
            }
            if(inv.proctype & PROC_DROPPABLE)
            {
                szCol += "<br>";
                szCol += GetWideString(ITEMDESC_NO_DROP);
            }
            if(inv.proctype & PROC_SELLABLE)
            {
                szCol += "<br>";
                szCol += GetWideString(ITEMDESC_NO_TRADE);
            }
            if(inv.proctype & PROC_TRADEABLE)
            {
                szCol += "<br>";
                szCol += GetWideString(ITEMDESC_NO_PLAYER_TRADE);
            }
            if(inv.proctype & PROC_DISAPEAR)
            {
                szCol += "<br>";
                szCol += GetWideString(ITEMDESC_LEAVE_SCENE_DISAPEAR);
            }
            if(inv.proctype & PROC_USE)
            {
                szCol += "<br>";
                szCol += GetWideString(ITEMDESC_USE_AFTER_PICK_UP);
            }
            if(inv.proctype & PROC_DEADDROP)
            {
                szCol += "<br>";
                szCol += GetWideString(ITEMDESC_DROP_WHEN_DEAD);
            }
            if(inv.proctype & PROC_OFFLINE)
            {
                szCol += "<br>";
                szCol += GetWideString(ITEMDESC_DROP_WHEN_OFFLINE);
            }
            if(inv.proctype & PROC_UNREPAIRABLE)
            {
                szCol += "<br>";
                szCol += GetWideString(ITEMDESC_UNREPAIRABLE);
            }
            if(inv.proctype & PROC_NO_USER_TRASH)
            {
                szCol += "<br>";
                szCol += GetWideString(ITEMDESC_NO_USER_TRASH);
            }

            desc += Utils::FormatColorText(szCol);
        }

        auto extdesc = pwAdmin::getInstance().listItemExtDesc[inv.id];
        if (!extdesc.isEmpty())
        {
            if(bAddLine)
                desc += "<br><br>";
            else
                desc += "<br><br>";
            desc += Utils::FormatColorText(extdesc);
        }
        break;
    }
    case EQUIP_MASK64_BIBLE:
    case EQUIP_MASK64_FOOT:
    case EQUIP_MASK64_SHOULDER:
    case EQUIP_MASK64_HEAD:
    case EQUIP_MASK64_LEG:
    case EQUIP_MASK64_WRIST:
    case EQUIP_MASK64_BODY:
    {
        armor_essence ess;
        ess.unmarshal(os);
        int col = white;
        if (Commands::GetItemValue(inv.id, "level", "NEW_ARMOR_ESSENCE").toInt())
            BuildAddOnSoulPropDesc(inv.id, ess.addons, ess.addons_soul, aPEEVals, aRefines);
        else
            BuildAddOnPropDesc(ess.addons, aPEEVals, aRefines);
        auto strAddon = desc;
        desc.clear();

        // DefaultInfo()
        int m_iLevelReq		= ess.prereq.level;
        int  m_iStrengthReq	= ess.prereq.strength;
        int  m_iAgilityReq	= ess.prereq.agility;
        int m_iVitalityReq = ess.prereq.vitality;
        int m_iEnergyReq = ess.prereq.energy;
        int m_iReputationReq= Commands::GetItemValue(inv.id, "require_reputation", "ARMOR_ESSENCE").toInt();
        int m_iCurEndurance	= ess.prereq.durability;
        int m_iMaxEndurance = ess.prereq.max_durability;

        if (ess.slot_count > 0)
            AddHtmlDescText(color, false, GetWideString(ITEMDESC_NAMESOCKET).toStdString().c_str(), Commands::GetItemName(inv.id).toStdString().c_str(), ess.slot_count);
        else AddHtmlDescText(color, false, GetWideString(ITEMDESC_NAME).toStdString().c_str(), Commands::GetItemName(inv.id).toStdString().c_str());
        DWORD dwPEE = PropEffectEssence(ess.addons);
        OctetsStream os(p.status.property.value, false, false);
        PlayerProperty pp;
        pp.unmarshal(&os);
        int refino = 0;
        foreach(auto addon, ess.addons)
        {
            quint8 byPropType = (qint8)pwAdmin::getInstance().addonsList.value(QString::number(addon.id_addon)).toInt();
            switch(byPropType)
            {
            case 200:
            case 201:
            case 202:
            case 203:
            case 204:
            case 205:
            case 206:
            case 207:
            case 208:
            case 209:
            case 210:
            case 211:
            case 212:
                refino = addon.arg[1];
                break;
            }
        }
        if (refino > 0)
            AddHtmlDescText(color, true, " +%d", refino);
        else desc += "<br>";
        AddBindDescText(inv.proctype);
        AddExpireTimeDesc(inv.expire_date);
        int id_subtype = Commands::GetItemValue(inv.id, "id_sub_type", "ARMOR_ESSENCE").toInt();
        int level = Commands::GetItemValue(inv.id, "level", "ARMOR_ESSENCE").toInt();
        AddHtmlDescText(white, true, GetWideString(ITEMDESC_CLASSNAME).toStdString().c_str(), Commands::GetItemValue(id_subtype, "Name", "ARMOR_SUB_TYPE").toStdString().c_str());
        AddHtmlDescText(-1, true, GetWideString(ITEMDESC_LEVEL).toStdString().c_str(), level);

        //	Physical defence
        if (ess.defense - aPEEVals[PEEI_PHYDEF] + aRefines[REFINE_PHYDEF])
        {
            AddHtmlDescText(white, false, GetWideString(ITEMDESC_PHYDEFENCE).toStdString().c_str());
            AddHtmlDescText(white, true, (" %+d"), ess.defense - aPEEVals[PEEI_PHYDEF] + aRefines[REFINE_PHYDEF]);
        }

        //	Dodge
        if (ess.armor - aPEEVals[PEEI_DODGE] + aRefines[REFINE_DODGE])
        {
            AddHtmlDescText(white, false, GetWideString(ITEMDESC_DODGE).toStdString().c_str());
            AddHtmlDescText(white, true, (" %+d"), ess.armor - aPEEVals[PEEI_DODGE] + aRefines[REFINE_DODGE]);
        }

        //	+ HP
        if (ess.hp_enhance - aPEEVals[PEEI_HP] + aRefines[REFINE_HP])
        {
            AddHtmlDescText(white, false, GetWideString(ITEMDESC_ADDHP).toStdString().c_str());
            AddHtmlDescText(white, true, (" %+d"), ess.hp_enhance - aPEEVals[PEEI_HP] + aRefines[REFINE_HP]);
        }

        //	+ MP
        if (ess.mp_enhance - aPEEVals[PEEI_MP])
        {
            AddHtmlDescText(white, false, GetWideString(ITEMDESC_ADDMP).toStdString().c_str());
            AddHtmlDescText(white, true, (" %+d"), ess.mp_enhance - aPEEVals[PEEI_MP]);
        }

        if (ess.resistance[MAGICCLASS_GOLD] - aPEEVals[PEEI_GOLDDEF] + aRefines[REFINE_GOLDDEF])
        {
            AddHtmlDescText(white, false, GetWideString(ITEMDESC_GOLDDEFENCE).toStdString().c_str());
            AddHtmlDescText(white, true, (" %+d"), ess.resistance[MAGICCLASS_GOLD] - aPEEVals[PEEI_GOLDDEF] + aRefines[REFINE_GOLDDEF]);
        }

        if (ess.resistance[MAGICCLASS_WOOD] - aPEEVals[PEEI_WOODDEF] + aRefines[REFINE_WOODDEF])
        {
            AddHtmlDescText(white, false, GetWideString(ITEMDESC_WOODDEFENCE).toStdString().c_str());
            AddHtmlDescText(white, true, (" %+d"), ess.resistance[MAGICCLASS_WOOD] - aPEEVals[PEEI_WOODDEF] + aRefines[REFINE_WOODDEF]);
        }

        if (ess.resistance[MAGICCLASS_WATER] - aPEEVals[PEEI_WATERDEF] + aRefines[REFINE_WATERDEF])
        {
            AddHtmlDescText(white, false, GetWideString(ITEMDESC_WATERDEFENCE).toStdString().c_str());
            AddHtmlDescText(white, true, (" %+d"), ess.resistance[MAGICCLASS_WATER] - aPEEVals[PEEI_WATERDEF] + aRefines[REFINE_WATERDEF]);
        }

        if (ess.resistance[MAGICCLASS_FIRE] - aPEEVals[PEEI_FIREDEF] + aRefines[REFINE_FIREDEF])
        {
            AddHtmlDescText(white, false, GetWideString(ITEMDESC_FIREDEFENCE).toStdString().c_str());
            AddHtmlDescText(white, true, (" %+d"), ess.resistance[MAGICCLASS_FIRE] - aPEEVals[PEEI_FIREDEF] + aRefines[REFINE_FIREDEF]);
        }

        if (ess.resistance[MAGICCLASS_EARTH] - aPEEVals[PEEI_EARTHDEF] + aRefines[REFINE_EARTHDEF])
        {
            AddHtmlDescText(white, false, GetWideString(ITEMDESC_EARTHDEFENCE).toStdString().c_str());
            AddHtmlDescText(white, true, (" %+d"), ess.resistance[MAGICCLASS_EARTH] - aPEEVals[PEEI_EARTHDEF] + aRefines[REFINE_EARTHDEF]);
        }
        //	Endurance
        col = white;
        if (!m_iCurEndurance)
            col = red;
        else if (dwPEE & PEE_ENDURANCE)
            col = lblue;

        AddHtmlDescText(col, false, GetWideString(ITEMDESC_ENDURANCE).toStdString().c_str());
        AddHtmlDescText(col, true, (" %d/%d"), VisualizeEndurance(m_iCurEndurance), VisualizeEndurance(m_iMaxEndurance));

        //	Profession requirement
        int col_prof_req = (ess.prereq.race & (1 << p.base.cls)) ? ITEMDESC_COL_WHITE : ITEMDESC_COL_RED;
        AddHtmlDescText(col_prof_req, false, GetWideString(ITEMDESC_PROFESSIONREQ).toStdString().c_str());
        for (int i=0; i < pwAdmin::getInstance().listClasses.count(); i++)
        {
            if (ess.prereq.race & (1 << i))
            {
                desc += " ";
                AddHtmlDescText(col_prof_req, false, pwAdmin::getInstance().listFixedMsg[s_ProfDesc[i]].toStdString().c_str());
            }
        }
        desc += "<br>";
        //	Level requirment
        if (m_iLevelReq)
        {
            col = p.status.level >= m_iLevelReq ? white : red;
            AddHtmlDescText(col, true, GetWideString(ITEMDESC_LEVELREQ).toStdString().c_str(), m_iLevelReq);
        }

        //	Strength requirment
        if (m_iStrengthReq)
        {
            if (pp.strength < m_iStrengthReq)
                col = red;
            else
                col = (dwPEE & PEE_STRENGTHREQ) ? lblue : white;

            AddHtmlDescText(col, true, GetWideString(ITEMDESC_STRENGTHREQ).toStdString().c_str(), m_iStrengthReq);
        }

        //	Agility requirment
        if (m_iAgilityReq)
        {
            if (pp.agility < m_iAgilityReq)
                col = red;
            else
                col = (dwPEE & PEE_AGILITYREQ) ? lblue : white;

            AddHtmlDescText(col, true, GetWideString(ITEMDESC_AGILITYREQ).toStdString().c_str(), m_iAgilityReq);
        }

        //	Vitality requirment
        if (m_iVitalityReq)
        {
            if (pp.vitality < m_iVitalityReq)
                col = red;
            else
                col = (dwPEE & PEE_VITALITYREQ) ? lblue : white;

            AddHtmlDescText(col, true, GetWideString(ITEMDESC_VITALITYREQ).toStdString().c_str(), m_iVitalityReq);
        }

        //	Energy requirment
        if (m_iEnergyReq)
        {
            if (pp.energy < m_iEnergyReq)
                col = red;
            else
                col = (dwPEE & PEE_ENERGYREQ) ? lblue : white;

            AddHtmlDescText(col, true, GetWideString(ITEMDESC_ENERGYREQ).toStdString().c_str(), m_iEnergyReq);
        }

        // Reputation requirement
        if (m_iReputationReq)
        {
            int col = p.status.reputation >= m_iReputationReq ? ITEMDESC_COL_WHITE : ITEMDESC_COL_RED;
            AddHtmlDescText(col, true, GetWideString(ITEMDESC_REPUTATION_REQ).toStdString().c_str(), m_iReputationReq);
        }

        //	Add addon properties
        if (strAddon.length())
            desc += strAddon;

        //	Build tessera description
        if (ess.slot_count)
        {
            int cyanine = ITEMDESC_COL_CYANINE;

            for (int i=0; i < ess.slot_count; i++)
            {
                if (!ess.slot_list[i])
                    continue;
                auto szText = Commands::GetItemValue(ess.slot_list[i], "armor_desc", "STONE_ESSENCE");
                AddHtmlDescText(cyanine, true, GetWideString(ITEMDESC_2STRINGS).toStdString().c_str(), Commands::GetItemName(ess.slot_list[i], "STONE_ESSENCE").toStdString().c_str(), szText.toStdString().c_str());
            }
        }

        if(Commands::GetItemValue(inv.id, "fixed_props", "ARMOR_ESSENCE").toInt() == 0)
        {
            AddHtmlDescText(ITEMDESC_COL2_BRIGHTBLUE, true, GetWideString(ITEMDESC_HASRANDOM_PROP).toStdString().c_str());
        }

        //	Price
        int price = Commands::GetItemValue(inv.id, "price", "ARMOR_ESSENCE").toUInt();
        if(price >= 100000000) // 100 million
            col = ITEMDESC_COL_GREEN;
        else if ( price >= 10000000) // 10 million
            col = ITEMDESC_COL_DARKGOLD;
        else if ( price >= 1000000) // 1 million
            col = ITEMDESC_COL_YELLOW;
        else col = ITEMDESC_COL_WHITE;
        desc += "<br>";
        AddHtmlDescText(col, false, GetWideString(ITEMDESC_PRICE).toStdString().c_str());
        AddHtmlDescText(-1, false, " %s", GetFormattedPrice(price).toStdString().c_str());

        if(ess.addons.size())
        {
            int bFirstProp = true;
            foreach(auto ad, ess.addons)
            {
                if (ad.isEngraved)
                {
                    if (bFirstProp)
                    {
                        bFirstProp = false;
                        desc += "<br>";
                        desc += GetWideString(ITEMDESC_COL_YELLOW);
                    }
                    GetHtmlAddonName(ad.id_addon, ad.arg[0], ad.arg[1], ad.arg[2], NULL, NULL);
                }
            }
        }

        if (!ess.made_tag.tag_content.toName().isEmpty())
        {
            desc += "<br>";
            if (ess.made_tag.tag_type != IMT_SIGN)
            {
                AddHtmlDescText(ITEMDESC_COL_GREEN, false, GetWideString(ITEMDESC_MADEFROM).toStdString().c_str(), ess.made_tag.tag_content.toName().toStdString().c_str());
            } else
            {
                AddHtmlDescText(ITEMDESC_COL_GREEN, false, "[%s]", ess.made_tag.tag_content.toName().toStdString().c_str());
            }
        }

        desc += "<br>";
        int green = ITEMDESC_COL2_BRIGHTBLUE;
        bool bAddLine = true;
        if ((inv.proctype & PROC_NO_USER_TRASH)
                || !(inv.proctype & PROC_BINDING )
                && (inv.proctype & PROC_DROPWHENDIE ||
                    inv.proctype & PROC_DROPPABLE ||
                    inv.proctype & PROC_SELLABLE ||
                    inv.proctype & PROC_TRADEABLE ||
                    inv.proctype & PROC_DISAPEAR ||
                    inv.proctype & PROC_USE ||
                    inv.proctype & PROC_DEADDROP ||
                    inv.proctype & PROC_OFFLINE ||
                    inv.proctype & PROC_UNREPAIRABLE))
        {
            bAddLine = false;
            auto szCol = GetWideString(green);
            qDebug()<< szCol << Utils::FormatColorText(szCol);

            if(inv.proctype & PROC_DROPWHENDIE)
            {
                szCol += "<br>";
                szCol += GetWideString(ITEMDESC_DEAD_PROTECT);
            }
            if(inv.proctype & PROC_DROPPABLE)
            {
                szCol += "<br>";
                szCol += GetWideString(ITEMDESC_NO_DROP);
            }
            if(inv.proctype & PROC_SELLABLE)
            {
                szCol += "<br>";
                szCol += GetWideString(ITEMDESC_NO_TRADE);
            }
            if(inv.proctype & PROC_TRADEABLE)
            {
                szCol += "<br>";
                szCol += GetWideString(ITEMDESC_NO_PLAYER_TRADE);
            }
            if(inv.proctype & PROC_DISAPEAR)
            {
                szCol += "<br>";
                szCol += GetWideString(ITEMDESC_LEAVE_SCENE_DISAPEAR);
            }
            if(inv.proctype & PROC_USE)
            {
                szCol += "<br>";
                szCol += GetWideString(ITEMDESC_USE_AFTER_PICK_UP);
            }
            if(inv.proctype & PROC_DEADDROP)
            {
                szCol += "<br>";
                szCol += GetWideString(ITEMDESC_DROP_WHEN_DEAD);
            }
            if(inv.proctype & PROC_OFFLINE)
            {
                szCol += "<br>";
                szCol += GetWideString(ITEMDESC_DROP_WHEN_OFFLINE);
            }
            if(inv.proctype & PROC_UNREPAIRABLE)
            {
                szCol += "<br>";
                szCol += GetWideString(ITEMDESC_UNREPAIRABLE);
            }
            if(inv.proctype & PROC_NO_USER_TRASH)
            {
                szCol += "<br>";
                szCol += GetWideString(ITEMDESC_NO_USER_TRASH);
            }

            desc += Utils::FormatColorText(szCol);
        }

        auto extdesc = pwAdmin::getInstance().listItemExtDesc[inv.id];
        if (!extdesc.isEmpty())
        {
            if(bAddLine)
                desc += "<br><br>";
            else
                desc += "<br><br>";
            desc += Utils::FormatColorText(extdesc);
        }
        break;
    }
    }

    QString htmlString =
            "<html>"
            "<style>"
            "body {margin: 0; padding: 3px; color:#ffffff; background-color:#101010; font-size:11px; font-family: verdana;	line-height:1.15em;} p, ul {margin:0; padding:0px;}"
            "ul {margin-left:20px; padding:1px;list-style-type: disc;}"
            "</style>"
            "<body>"
            "<font color=\"#FF6000\"><b> " + desc + " </b></font></body</html>"                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           "</body></html>";
    ui->txt_info_item->setHtml(htmlString);
}

void PlayerEditor::on_equip_list_left_itemClicked(QListWidgetItem *item)
{
    ui->equip_list_right->clearSelection();
    ui->pocket_list->clearSelection();
    QModelIndex index = item->listWidget()->currentIndex();
    for(int i = 0; i < p.equipment.inv.count(); i++)
    {
        if (p.equipment.inv[i].pos == left.at(index.row()))
        {
            isEquipment = true;
            index_selected = i;
            PopulateInfos(p.equipment.inv[i]);
            break;
        }
        else
        {
            ui->txt_count->clear();
            ui->txt_data->clear();
            ui->txt_expiredata->clear();
            ui->txt_guid1->clear();
            ui->txt_guid2->clear();
            ui->txt_id->clear();
            ui->txt_mask->clear();
            ui->txt_maxcount->clear();
            ui->txt_pos->clear();
            ui->txt_proctype->clear();
        }
    }
}


void PlayerEditor::on_equip_list_right_itemClicked(QListWidgetItem *item)
{
    ui->equip_list_left->clearSelection();
    ui->pocket_list->clearSelection();
    QModelIndex index = item->listWidget()->currentIndex();
    for(int i = 0; i < p.equipment.inv.count(); i++)
    {
        if (p.equipment.inv[i].pos == right.at(index.row()))
        {
            isEquipment = true;
            index_selected = i;
            PopulateInfos(p.equipment.inv[i]);
            break;
        }
        else
        {
            ui->txt_count->clear();
            ui->txt_data->clear();
            ui->txt_expiredata->clear();
            ui->txt_guid1->clear();
            ui->txt_guid2->clear();
            ui->txt_id->clear();
            ui->txt_mask->clear();
            ui->txt_maxcount->clear();
            ui->txt_pos->clear();
            ui->txt_proctype->clear();
        }
    }
}


void PlayerEditor::on_pocket_list_itemClicked(QListWidgetItem *item)
{
    ui->equip_list_left->clearSelection();
    ui->equip_list_right->clearSelection();
    QModelIndex index = item->listWidget()->currentIndex();
    for(int i = 0; i < p.pocket.items.count(); i++)
    {
        if (p.pocket.items[i].pos == index.row())
        {
            isEquipment = false;
            index_selected = i;
            PopulateInfos(p.pocket.items[i]);
            break;
        }
        else
        {
            ui->txt_count->clear();
            ui->txt_data->clear();
            ui->txt_expiredata->clear();
            ui->txt_guid1->clear();
            ui->txt_guid2->clear();
            ui->txt_id->clear();
            ui->txt_mask->clear();
            ui->txt_maxcount->clear();
            ui->txt_pos->clear();
            ui->txt_proctype->clear();
        }
    }
}


void PlayerEditor::on_pushButton_clicked()
{
    int64_t mask = ui->txt_mask->text().toULong();
    int type = (mask & EQUIP_MASK::EQUIP_MASK_HAS_ADDON) > 0 ? mask - EQUIP_MASK::EQUIP_MASK_HAS_ADDON : mask;
    OctetsStream os;
    /*if (!isEquipment)
        os.setData(p.pocket.items[index_selected].data.value, false);
    else
        os.setData(p.equipment.inv[index_selected].data.value, false);*/
    os.setData(QByteArray::fromHex(ui->txt_data->text().toUtf8()), false, false);
    //os.qds->setByteOrder(QDataStream::BigEndian);
    qDebug()<<type;

    // QIHUN_ESSENCE
    int id = ui->txt_id->value();
    if (id >= 59757 && id <= 59771)
    {
        socket_qihun ess;
        ess.unmarshal(os);
        DlgQihunEssenceEditor editor;
        editor.Load(ess);
        if (editor.exec() == QDialog::Accepted)
        {
            OctetsStream nos;
            nos.qds->setByteOrder(QDataStream::BigEndian);
            editor.ess.marshal(nos);
            p.pocket.items[index_selected].data = Octets(nos.getData());
            PopulateInfos(p.pocket.items[index_selected]);
        }
        return;
    }

    switch((EQUIP_MASK64)type)
    {
    case EQUIP_MASK64_WEAPON:
    {
        weapon_essence ess;
        ess.unmarshal(os, pwAdmin::getInstance().infos.ServerVersion);
        DlgArmorEditor editor;
        editor.LoadWeapon(ess);
        if (editor.exec() == QDialog::Accepted)
        {
            OctetsStream nos;
            nos.qds->setByteOrder(QDataStream::BigEndian);
            editor.weapon_ess.marshal(nos, pwAdmin::getInstance().infos.ServerVersion);
            if (!isEquipment)
            {
                p.pocket.items[index_selected].data = Octets(nos.getData());
                PopulateInfos(p.pocket.items[index_selected]);
            }
            else
            {
                p.equipment.inv[index_selected].data = Octets(nos.getData());
                PopulateInfos(p.equipment.inv[index_selected]);
            }
        }
        break;
    }
    case EQUIP_MASK64_HP_ADDON:
    {
        amulet_essence ess;
        ess.unmarshal(os);
        DlgAmuletEditor editor;
        editor.LoadInfo(&ess);
        if (editor.exec() == QDialog::Accepted)
        {
            OctetsStream nos;
            nos.qds->setByteOrder(QDataStream::BigEndian);
            editor.ess->marshal(nos);
            if (!isEquipment)
            {
                p.pocket.items[index_selected].data = Octets(nos.getData());
                PopulateInfos(p.pocket.items[index_selected]);
            }
            else
            {
                p.equipment.inv[index_selected].data = Octets(nos.getData());
                PopulateInfos(p.equipment.inv[index_selected]);
            }
        }
        break;
    }
    case EQUIP_MASK64_MP_ADDON:
    {
        amulet_essence ess;
        ess.unmarshal(os);
        DlgAmuletEditor editor;
        editor.LoadInfo(&ess);
        if (editor.exec() == QDialog::Accepted)
        {
            OctetsStream nos;
            nos.qds->setByteOrder(QDataStream::BigEndian);
            editor.ess->marshal(nos);
            if (!isEquipment)
            {
                p.pocket.items[index_selected].data = Octets(nos.getData());
                PopulateInfos(p.pocket.items[index_selected]);
            }
            else
            {
                p.equipment.inv[index_selected].data = Octets(nos.getData());
                PopulateInfos(p.equipment.inv[index_selected]);
            }
        }
        break;
    }
    case EQUIP_MASK64_FLYSWORD:
    {
        flysword_essence ess;
        ess.unmarshal(os);
        DlgFlyswordEditor editor;
        editor.LoadInfo(&ess);
        if (editor.exec() == QDialog::Accepted)
        {
            OctetsStream nos;
            nos.qds->setByteOrder(QDataStream::BigEndian);
            editor.ess->marshal(nos);
            if (!isEquipment)
            {
                p.pocket.items[index_selected].data = Octets(nos.getData());
                PopulateInfos(p.pocket.items[index_selected]);
            }
            else
            {
                p.equipment.inv[index_selected].data = Octets(nos.getData());
                PopulateInfos(p.equipment.inv[index_selected]);
            }
        }
        break;
    }
    case EQUIP_MASK64_FORCE_TICKET:
    {

        break;
    }

    default:
    {
        if (id >= 59921 && id <= 59963)
        {
            new_armor_item ess;
            ess.unmarshal(os);
            DlgItemEditor editor;
            editor.LoadNewArmor(ess);
            if (editor.exec() == QDialog::Accepted)
            {
                OctetsStream nos;
                nos.qds->setByteOrder(QDataStream::BigEndian);
                editor.ess.marshal(nos);
                if (!isEquipment)
                {
                    p.pocket.items[index_selected].data = Octets(nos.getData());
                    PopulateInfos(p.pocket.items[index_selected]);
                }
                else
                {
                    p.equipment.inv[index_selected].data = Octets(nos.getData());
                    PopulateInfos(p.equipment.inv[index_selected]);
                }
            }
            break;
        }
        else
        {
            armor_essence ess;
            ess.unmarshal(os);
            //DlgArmorEditor editor;
            //editor.LoadArmor(ess);
            DlgItemEditor editor;
            editor.LoadArmor(ess);
            if (editor.exec() == QDialog::Accepted)
            {
                OctetsStream nos;
                nos.qds->setByteOrder(QDataStream::BigEndian);
                editor.ess.marshal(nos);
                if (!isEquipment)
                {
                    p.pocket.items[index_selected].data = Octets(nos.getData());
                    PopulateInfos(p.pocket.items[index_selected]);
                }
                else
                {
                    p.equipment.inv[index_selected].data = Octets(nos.getData());
                    PopulateInfos(p.equipment.inv[index_selected]);
                }
            }
        }
    }break;
    }
}


void PlayerEditor::on_btnCancel_clicked()
{
    delete this;
    pwAdmin &pw = pwAdmin::getInstance();
    pw.closeSelectedTab();
}


void PlayerEditor::on_btnSave_clicked()
{
    // base
    p.base.cls = ui->base_class->currentIndex();
    p.base.config_data = Octets(QByteArray::fromHex(ui->base_configdata->toPlainText().toUtf8()));
    p.base.create_time = ui->base_createtime->value();
    p.base.cross_data = Octets(QByteArray::fromHex(ui->base_crossdata->toPlainText().toUtf8()));
    p.base.custom_data = Octets(QByteArray::fromHex(ui->base_customdata->toPlainText().toUtf8()));
    p.base.custom_stamp = ui->base_customstamp->text().toUInt();
    p.base.delete_time = ui->base_deletetime->value();
    p.base.gender = ui->base_gender->currentIndex();
    p.base.help_states = Octets(QByteArray::fromHex(ui->base_helpstates->toPlainText().toUtf8()));
    p.base.id = ui->base_id->text().toInt();
    p.base.lastlogin_time = ui->base_lastlogintime->value();
    p.base.name = Octets(ui->base_name->text());
    p.base.race = ui->base_race->currentIndex();
    if (p.Version < 191)
        p.base.reserved2 = ui->base_reserved2->text().toInt();
    else p.base.custom_data_highmode = Octets(QByteArray::fromHex(ui->base_reserved2->text().toUtf8()));
    p.base.reserved3 = ui->base_reserved3->text().toInt();
    p.base.reserved4 = ui->base_reserved4->text().toInt();
    p.base.spouse = ui->base_spouse->text().toInt();
    p.base.status = ui->base_status->text().toInt();
    p.base.userid = ui->base_userid->text().toInt();
    p.base.version = ui->base_version->text().toInt();

    // status
    p.status.charactermode = Octets(QByteArray::fromHex(ui->status_charactermode->toPlainText().toUtf8()));
    p.status.coolingtime = Octets(QByteArray::fromHex(ui->status_coolingtime->text().toUtf8()));
    p.status.country_data = Octets(QByteArray::fromHex(ui->status_countrydata->text().toUtf8()));
    int level2 = 0;
    switch(ui->status_cultivation->currentIndex())
    {
    case 0: level2 = 0; break;
    case 1: level2 = 1; break;
    case 2: level2 = 2; break;
    case 3: level2 = 3; break;
    case 4: level2 = 4; break;
    case 5: level2 = 5; break;
    case 6: level2 = 6; break;
    case 7: level2 = 7; break;
    case 8: level2 = 8; break;
    case 9: level2 = 20; break;
    case 10: level2 = 21; break;
    case 11: level2 = 22; break;
    case 12: level2 = 30; break;
    case 13: level2 = 31; break;
    case 14: level2 = 32; break;
    case 15: level2 = 40; break;
    case 16: level2 = 41; break;
    }
    p.status.level2 = level2;
    p.status.custom_status = Octets(QByteArray::fromHex(ui->status_customstatus->toPlainText().toUtf8()));
    p.status.dbltime_begin = ui->status_dbltimebegin->value();
    p.status.dbltime_data = Octets(QByteArray::fromHex(ui->status_dbltimedata->toPlainText().toUtf8()));
    p.status.dbltime_expire = ui->status_dbltimeexpire->text().toLongLong();
    p.status.dbltime_max = ui->status_dbltimemax->value();
    p.status.dbltime_mode = ui->status_dbltimemode->text().toInt();
    p.status.dbltime_used = ui->status_dbltimeused->text().toInt();
    p.status.exp = ui->status_exp->text().toLongLong();
    p.status.extraprop = Octets(QByteArray::fromHex(ui->status_extraprop->toPlainText().toUtf8()));
    p.status.faction_contrib = Octets(QByteArray::fromHex(ui->status_factioncontrib->text().toUtf8()));
    p.status.filter_data = Octets(QByteArray::fromHex(ui->status_filterdata->toPlainText().toUtf8()));
    p.status.force_data = Octets(QByteArray::fromHex(ui->status_forcedata->text().toUtf8()));
    p.status.hp = ui->status_hp->text().toInt();
    p.status.instancekeylist = Octets(QByteArray::fromHex(ui->status_instancekeylist->text().toUtf8()));
    p.status.invader_state = ui->status_invaderstate->currentIndex() == -1 ? 0 : ui->status_invaderstate->currentIndex();
    p.status.invader_time = ui->status_invadertime->value();
    p.status.king_data = Octets(QByteArray::fromHex(ui->status_kingdata->text().toUtf8()));
    p.status.level = ui->status_level->text().toInt();
    p.status.meridian_data = Octets(QByteArray::fromHex(ui->status_meridiandata->text().toUtf8()));
    p.status.mp = ui->status_mp->text().toInt();
    p.status.multi_exp_ctrl = Octets(QByteArray::fromHex(ui->status_multiexpctrl->text().toUtf8()));
    p.status.npc_relation = Octets(QByteArray::fromHex(ui->status_npcrelation->text().toUtf8()));
    p.status.online_award = Octets(QByteArray::fromHex(ui->status_onlineaward->text().toUtf8()));
    p.status.pariah_time = ui->status_pariahtime->value();
    p.status.petcorral = Octets(QByteArray::fromHex(ui->status_petcorral->text().toUtf8()));
    p.status.posx = static_cast<float>(ui->status_posx->value());
    p.status.posy = static_cast<float>(ui->status_posy->value());
    p.status.posz = static_cast<float>(ui->status_posz->value());
    p.status.profit_time_data = Octets(QByteArray::fromHex(ui->status_profittimedata->text().toUtf8()));
    p.status.property = Octets(QByteArray::fromHex(ui->status_property->text().toUtf8()));
    p.status.realm_data = Octets(QByteArray::fromHex(ui->status_realmdata->text().toUtf8()));
    p.status.reincarnation_data = Octets(QByteArray::fromHex(ui->status_reincarnationdata->text().toUtf8()));
    p.status.reputation = ui->status_reputation->text().toInt();
    if (p.Version == 140)
        p.status.rank = Octets(QByteArray::fromHex(ui->status_reserved2->text().toUtf8()));
    else
        p.status.reserved2 = ui->status_reserved2->text().toInt();
    p.status.reserved3 = ui->status_reserved3->text().toInt();
    p.status.pp = ui->status_skillpoints->text().toInt();
    p.status.skills = Octets(QByteArray::fromHex(ui->status_skill->text().toUtf8()));
    p.status.sp = ui->status_sp->text().toInt();
    p.status.storage_task = Octets(QByteArray::fromHex(ui->status_storagetask->text().toUtf8()));
    p.status.storehousepasswd = Octets(QByteArray::fromHex(ui->status_storehousepassword->text().toUtf8()));
    p.status.storesize = ui->status_storesize->text().toUShort();
    p.status.time_used = ui->status_timeused->value();
    p.status.title_data = Octets(QByteArray::fromHex(ui->status_titledata->text().toUtf8()));
    p.status.var_data = Octets(QByteArray::fromHex(ui->status_vardata->text().toUtf8()));
    p.status.version = ui->status_version->text().toInt();
    p.status.waypointlist = Octets(QByteArray::fromHex(ui->status_waypointlist->text().toUtf8()));
    p.status.worldtag = ui->status_worldtag->value();

    OctetsStream os;
    os << -1;
    os << p.base.id;
    os << (char)1;
    p.marshal(os);
    os.socket = &pwAdmin::getInstance().client;
    qDebug() << os.SendReturn(opPutRoleData, false, 5000, 2000).data.toHex();
    ui->envia->setText(os.data.toHex());
}


void PlayerEditor::on_status_petcorral_btn_clicked()
{
    DlgPetCorral dlg;
    dlg.Load(QByteArray::fromHex(ui->status_petcorral->text().toUtf8()));
    if (dlg.exec() == QDialog::Accepted)
    {
        ui->status_petcorral->setText(dlg.returnedData.data.toHex());
        ui->status_petcorral->setCursorPosition(0);
    }
}


void PlayerEditor::on_status_skill_btn_clicked()
{
    DlgSkills dlg;
    dlg.LoadSkills(QByteArray::fromHex(ui->status_skill->text().toUtf8()), p.base.gender, p.base.cls);
    if (dlg.exec() == QDialog::Accepted)
    {
        ui->status_skill->setText(dlg.returnedOctets.data.toHex());
        ui->status_skill->setCursorPosition(0);
    }
}


void PlayerEditor::on_status_meridian_data_btn_clicked()
{
    DlgMeridianData dlg;
    dlg.Load(QByteArray::fromHex(ui->status_meridiandata->text().toUtf8()));
    if (dlg.exec() == QDialog::Accepted)
    {
        ui->status_meridiandata->setText(dlg.returnedData.data.toHex());
        ui->status_meridiandata->setCursorPosition(0);
    }
}


void PlayerEditor::on_status_property_btn_clicked()
{
    DlgPropertyEditor dlg;
    dlg.Load(QByteArray::fromHex(ui->status_property->text().toUtf8()));
    if (dlg.exec() == QDialog::Accepted)
    {
        ui->status_property->setText(dlg.returnedData.data.toHex());
        ui->status_property->setCursorPosition(0);
    }
}


void PlayerEditor::on_status_coolingtime_btn_clicked()
{
    DlgCooldownEditor dlg;
    dlg.Load(QByteArray::fromHex(ui->status_coolingtime->text().toUtf8()));
    if (dlg.exec() == QDialog::Accepted)
    {
        ui->status_coolingtime->setText(dlg.returnedData.toHex());
        ui->status_coolingtime->setCursorPosition(0);
    }
}


void PlayerEditor::on_status_forcedata_btn_clicked()
{
    DlgForceDataEditor dlg;
    dlg.Load(QByteArray::fromHex(ui->status_forcedata->text().toUtf8()));
    if (dlg.exec() == QDialog::Accepted)
    {
        ui->status_forcedata->setText(dlg.returnedData.toHex());
        ui->status_forcedata->setCursorPosition(0);
    }
}


void PlayerEditor::on_status_countrydata_btn_clicked()
{
    DlgCountryDataEditor dlg;
    dlg.Load(QByteArray::fromHex(ui->status_countrydata->text().toUtf8()));
    if (dlg.exec() == QDialog::Accepted)
    {
        ui->status_countrydata->setText(dlg.returnedData.toHex());
        ui->status_countrydata->setCursorPosition(0);
    }
}


void PlayerEditor::on_status_kingdata_btn_clicked()
{
    DlgKingDataEditor dlg;
    dlg.Load(QByteArray::fromHex(ui->status_kingdata->text().toUtf8()));
    if (dlg.exec() == QDialog::Accepted)
    {
        ui->status_kingdata->setText(dlg.returnedData.toHex());
        ui->status_kingdata->setCursorPosition(0);
    }
}


void PlayerEditor::on_status_extraprop_btn_clicked()
{
    DlgExtraPropEditor dlg;
    dlg.Load(QByteArray::fromHex(ui->status_extraprop->toPlainText().toUtf8()));
    if (dlg.exec() == QDialog::Accepted)
    {
        ui->status_extraprop->setText(dlg.returnedData.toHex());
    }
}


void PlayerEditor::on_status_reincarnationdata_btn_clicked()
{
    DlgReincarnationDataEditor dlg;
    dlg.Load(QByteArray::fromHex(ui->status_reincarnationdata->text().toUtf8()));
    if (dlg.exec() == QDialog::Accepted)
    {
        ui->status_reincarnationdata->setText(dlg.returnedData.toHex());
    }
}


void PlayerEditor::on_status_realmdata_btn_clicked()
{
    DlgRealmDataEditor dlg;
    dlg.Load(QByteArray::fromHex(ui->status_realmdata->text().toUtf8()));
    if (dlg.exec() == QDialog::Accepted)
    {
        ui->status_realmdata->setText(dlg.returnedData.toHex());
    }
}


void PlayerEditor::on_status_titledata_btn_clicked()
{
    DlgTitleDataEditor dlg;
    dlg.Load(QByteArray::fromHex(ui->status_titledata->text().toUtf8()));
    if (dlg.exec() == QDialog::Accepted)
    {
        ui->status_titledata->setText(dlg.returnedData.toHex());
    }
}


void PlayerEditor::on_pushButton_6_clicked()
{
    GRoleForbid f;
    f.type = Utils::ForbidType::Login;
    f.time = 0;
    f.reason = Utils::fromUtf8("");
    f.createtime = QDateTime::currentSecsSinceEpoch();
    p.base.forbid.push_back(f);
    int row = ui->base_forbid_list->rowCount();
    ui->base_forbid_list->insertRow(row);
    ui->base_forbid_list->setItem(row, 0, new QTableWidgetItem(Utils::BanTypes(f.type)));
    ui->base_forbid_list->setItem(row, 1, new QTableWidgetItem(QString::number(f.time)));
    ui->base_forbid_list->setItem(row, 2, new QTableWidgetItem(QString::number(f.createtime)));
    ui->base_forbid_list->setItem(row, 3, new QTableWidgetItem(f.reason.toName()));
}


void PlayerEditor::on_pushButton_4_clicked()
{
    int index = ui->base_forbid_list->currentRow();
    if (index == -1) return;
    p.base.forbid.takeAt(index);
    ui->base_forbid_list->removeRow(ui->base_forbid_list->currentRow());
}


void PlayerEditor::on_base_forbid_list_itemClicked(QTableWidgetItem *item)
{
    auto f = p.base.forbid.at(item->row());
    ui->base_forbid_type->setCurrentIndex(Utils::ReturnForbidType(f.type));
    ui->base_forbid_created->setValue(f.createtime);
    ui->base_forbid_created_txt->setText(Utils::TimestampToLocalDateTime(f.createtime));
    ui->base_forbid_reason->setText(f.reason.toName());
    ui->base_forbid_time->setValue(f.time);
    ui->base_forbid_time_txt->setText(Utils::SecondsToTimeFormat(f.time));
}


void PlayerEditor::on_base_forbid_type_currentIndexChanged(int index)
{
    int idx = ui->base_forbid_list->currentRow();
    if (idx == -1) return;
    p.base.forbid[idx].type = Utils::ReturnForbidType(index);
    ui->base_forbid_list->setItem(idx, 0, new QTableWidgetItem(Utils::BanTypes(Utils::ReturnForbidType(index))));
}


void PlayerEditor::on_base_forbid_time_valueChanged(const QString &arg1)
{
    int idx = ui->base_forbid_list->currentRow();
    if (idx == -1) return;
    p.base.forbid[idx].time = arg1.toUInt();
    ui->base_forbid_time_txt->setText(Utils::SecondsToTimeFormat(arg1.toUInt()));
    ui->base_forbid_list->setItem(idx, 1, new QTableWidgetItem(arg1));
}


void PlayerEditor::on_base_forbid_created_valueChanged(const QString &arg1)
{
    int idx = ui->base_forbid_list->currentRow();
    if (idx == -1) return;
    p.base.forbid[idx].createtime = arg1.toUInt();
    ui->base_forbid_created_txt->setText(Utils::TimestampToLocalDateTime(arg1.toUInt()));
    ui->base_forbid_list->setItem(idx, 2, new QTableWidgetItem(arg1));
}


void PlayerEditor::on_base_forbid_reason_textChanged(const QString &arg1)
{
    int idx = ui->base_forbid_list->currentRow();
    if (idx == -1) return;
    p.base.forbid[idx].reason = Octets(arg1);
    ui->base_forbid_list->setItem(idx, 3, new QTableWidgetItem(arg1));
}


void PlayerEditor::on_pocket_list_itemChanged(QListWidgetItem *item)
{

}


void PlayerEditor::on_pocket_list_pressed(const QModelIndex &index)
{

}


void PlayerEditor::on_pushButton_7_clicked()
{
    DlgSearchEssence dlg;
    dlg.PopulateItems();
    if (dlg.exec() > 0)
    {
        ui->txt_id->setValue(dlg.result());
    }
}


void PlayerEditor::on_txt_id_valueChanged(const QString &arg1)
{
    if (arg1.toInt() <= 0)
        return;
    auto myColor = Utils::getColorByID(pwAdmin::getInstance().listItemColor[arg1.toInt()]);
    auto str = QString("color: #%1%2%3;").arg(myColor.red(), 2, 16, QChar('0'))
            .arg(myColor.green(), 2, 16, QChar('0'))
            .arg(myColor.blue(), 2, 16, QChar('0'));
    auto str2 = QString("text-align: left;\
                        padding: 3px;\
            background-color: rgb(16, 16, 16);\
    %1").arg(str);
    ui->pushButton_7->setStyleSheet(str2);
    ui->pushButton_7->setText(Commands::GetItemName(arg1.toInt()));
    ui->pushButton_7->setIcon(Commands::GetItemImage(arg1.toInt(), (Utils::Gender)p.base.gender));
}

