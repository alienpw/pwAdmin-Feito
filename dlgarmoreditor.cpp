#include "dlgarmoreditor.h"
#include "ui_dlgarmoreditor.h"
#include "connection.h"

DlgArmorEditor::DlgArmorEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgArmorEditor)
{
    ui->setupUi(this);
    ui->tableWidget->selectRow(0);
    ui->tableWidget->setFocus();
    ui->table_addons->setColumnWidth(0, 52);
    ui->table_addons->setColumnWidth(1, 290);
    ui->table_addons->setColumnWidth(2, 52);
    ui->table_addons->setColumnWidth(3, 52);
    ui->table_addons->setColumnWidth(4, 52);
    ui->tableAddonEspiritoSagrado->setColumnWidth(0, 52);
    ui->tableAddonEspiritoSagrado->setColumnWidth(1, 200);
    ui->tableAddonEspiritoSagrado->setColumnWidth(2, 52);
    ui->tableAddonEspiritoSagrado->setColumnWidth(3, 52);
    ui->tableAddonEspiritoSagrado->setColumnWidth(4, 52);

    ui->widget->setVisible(false);

    auto cbs = ui->widget->findChildren<QCheckBox*>();
    foreach(auto cb, cbs)
        connect(cb, &QCheckBox::stateChanged, this, &DlgArmorEditor::on_e0_stateChanged);
}

DlgArmorEditor::~DlgArmorEditor()
{
    delete ui;
}

void DlgArmorEditor::on_tableWidget_cellClicked(int row, int column)
{
    ui->stackedWidget->setCurrentIndex(row);
}


void DlgArmorEditor::on_tableWidget_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    ui->stackedWidget->setCurrentIndex(currentRow);
}

void DlgArmorEditor::LoadWeapon(weapon_essence &ess)
{
    this->weapon_ess = ess;
    base = ess;
    whatIs = Utils::EQUIP_WEAPON;
    ui->tableWidget->hideRow(4);
    ui->stackedWidget_2->setCurrentIndex(0);

    ui->txt_prereq_agility->setText(QString::number(weapon_ess.prereq.agility));
    ui->txt_prereq_class->setText(QString::number(weapon_ess.prereq.race));
    ui->txt_prereq_class_label->setText(PlayerEditor::AddProfReqDesc(weapon_ess.prereq.race));
    ui->txt_prereq_durab->setText(QString::number(weapon_ess.prereq.durability / 100));
    ui->txt_prereq_energy->setText(QString::number(weapon_ess.prereq.energy));
    ui->txt_prereq_level->setText(QString::number(weapon_ess.prereq.level));
    ui->txt_prereq_maxdurab->setText(QString::number(weapon_ess.prereq.max_durability / 100));
    ui->txt_prereq_strength->setText(QString::number(weapon_ess.prereq.strength));
    ui->txt_prereq_vitality->setText(QString::number(weapon_ess.prereq.vitality));

    ui->txt_atkrange->setText(QString::number(weapon_ess.attack_range));
    ui->txt_atkshortrange->setText(QString::number(weapon_ess.attack_short_range));
    ui->txt_atkspeed->setText(QString::number(weapon_ess.attack_speed));
    ui->txt_class->setText(QString::number(weapon_ess.weapon_class));
    ui->txt_delay->setText(QString::number(weapon_ess.weapon_delay));
    ui->txt_fdamage->setText(QString::number(weapon_ess.damage_low));
    ui->txt_fdamagemax->setText(QString::number(weapon_ess.damage_high));
    ui->txt_level->setText(QString::number(weapon_ess.weapon_level));
    ui->txt_mdamage->setText(QString::number(weapon_ess.magic_damage_low));
    ui->txt_mdamagemax->setText(QString::number(weapon_ess.magic_damage_high));
    ui->txt_projectile->setText(QString::number(weapon_ess.require_projectile));
    ui->txt_type->setText(QString::number(weapon_ess.weapon_type));

    ui->txt_made_by_2->setText(weapon_ess.made_tag.tag_content.toName());
    ui->comboBox_2->setCurrentIndex(weapon_ess.made_tag.tag_type);

    ui->txt_slot_flag->setText(QString::number(weapon_ess.slot_flag));

    for(int i = 0; i < base.slot_count; i++)
    {
        ui->table_slots->insertRow(i);
        QTableWidgetItem *id = new QTableWidgetItem(QString::number(weapon_ess.slot_list[i]));
        id->setForeground(Utils::getColorByID(4));
        QTableWidgetItem *name = new QTableWidgetItem(QIcon(Commands::GetItemImage(weapon_ess.slot_list[i])), Commands::GetItemName(weapon_ess.slot_list[i]));
        name->setFlags(name->flags() & ~Qt::ItemIsEditable);
        QColor color = Utils::getColorByID(pwAdmin::getInstance().listItemColor[ess.slot_list[i]]);
        name->setForeground(QBrush(color));
        ui->table_slots->setItem(i, 0, id);
        ui->table_slots->setItem(i, 1, name);
    }

    UpdateAddons();

    loaded = true;
}

void DlgArmorEditor::LoadArmor(armor_essence &ess)
{
    this->armor_ess = ess;
    base = ess;
    whatIs = Utils::EQUIP_ARMOR;
    ui->stackedWidget_2->setCurrentIndex(1);

    ui->txt_prereq_agility->setText(QString::number(armor_ess.prereq.agility));
    ui->txt_prereq_class->setText(QString::number(armor_ess.prereq.race));
    ui->txt_prereq_class_label->setText(PlayerEditor::AddProfReqDesc(armor_ess.prereq.race));
    ui->txt_prereq_durab->setText(QString::number(armor_ess.prereq.durability / 100));
    ui->txt_prereq_energy->setText(QString::number(armor_ess.prereq.energy));
    ui->txt_prereq_level->setText(QString::number(armor_ess.prereq.level));
    ui->txt_prereq_maxdurab->setText(QString::number(armor_ess.prereq.max_durability / 100));
    ui->txt_prereq_strength->setText(QString::number(armor_ess.prereq.strength));
    ui->txt_prereq_vitality->setText(QString::number(armor_ess.prereq.vitality));

    ui->txt_armor->setText(QString::number(armor_ess.armor));
    ui->txt_defense->setText(QString::number(armor_ess.defense));
    ui->txt_hp_enhance->setText(QString::number(armor_ess.hp_enhance));
    ui->txt_mp_enhance->setText(QString::number(armor_ess.mp_enhance));
    ui->txt_resistance0->setText(QString::number(armor_ess.resistance[0]));
    ui->txt_resistance1->setText(QString::number(armor_ess.resistance[1]));
    ui->txt_resistance2->setText(QString::number(armor_ess.resistance[2]));
    ui->txt_resistance3->setText(QString::number(armor_ess.resistance[3]));
    ui->txt_resistance4->setText(QString::number(armor_ess.resistance[4]));

    ui->txt_made_by->setText(armor_ess.made_tag.tag_content.toName());
    ui->comboBox->setCurrentIndex(armor_ess.made_tag.tag_type);

    ui->txt_slot_flag->setText(QString::number(armor_ess.slot_flag));

    for(int i = 0; i < base.slot_count; i++)
    {
        ui->table_slots->insertRow(i);
        QTableWidgetItem *id = new QTableWidgetItem(QString::number(armor_ess.slot_list[i]));
        id->setForeground(Utils::getColorByID(4));
        QTableWidgetItem *name = new QTableWidgetItem(QIcon(Commands::GetItemImage(armor_ess.slot_list[i])), Commands::GetItemName(armor_ess.slot_list[i]));
        name->setFlags(name->flags() & ~Qt::ItemIsEditable);
        QColor color = Utils::getColorByID(pwAdmin::getInstance().listItemColor[ess.slot_list[i]]);
        name->setForeground(QBrush(color));
        ui->table_slots->setItem(i, 0, id);
        ui->table_slots->setItem(i, 1, name);
    }

    QTableWidgetItem *item = new QTableWidgetItem(Commands::GetItemName(59768));
    item->setForeground(QBrush(QColor(180, 0, 0)));
    QTableWidgetItem *item2 = new QTableWidgetItem(Commands::GetItemName(59713));
    item->setForeground(QBrush(QColor(180, 0, 0)));
    pwAdmin &pw = pwAdmin::getInstance();
    ui->escarlade->setText(pw.listItemDesc.value(ITEMDESC_CRISTALLUAR_ESCARLATE).chopped(3));
    ui->verdejante->setText(pw.listItemDesc.value(ITEMDESC_CRISTALLUAR_VERDEJANTE).chopped(3));
    ui->ceruleo->setText(pw.listItemDesc.value(ITEMDESC_CRISTALLUAR_CERULEO).chopped(3));
    ui->violeta->setText(pw.listItemDesc.value(ITEMDESC_CRISTALLUAR_VIOLETA).chopped(3));
    ui->amarelo->setText(pw.listItemDesc.value(ITEMDESC_CRISTALLUAR_AMARELO).chopped(3));

    auto cbs = ui->widget->findChildren<QCheckBox*>();
    foreach(auto cb, cbs)
    {

        for(int i = 0; i < base.addons_soul.estrelas[0]; i++)
        {
            if (cb->objectName() == QString("e%1").arg(i))
            {
                cb->setCheckState(Qt::Checked);
            }
        }
        for(int i = 0; i < base.addons_soul.estrelas[1]; i++)
        {
            if (cb->objectName() == QString("v%1").arg(i))
            {
                cb->setCheckState(Qt::Checked);
            }
        }
        for(int i = 0; i < base.addons_soul.estrelas[2]; i++)
        {
            if (cb->objectName() == QString("c%1").arg(i))
            {
                cb->setCheckState(Qt::Checked);
            }
        }
        for(int i = 0; i < base.addons_soul.estrelas[3]; i++)
        {
            if (cb->objectName() == QString("vi%1").arg(i))
            {
                cb->setCheckState(Qt::Checked);
            }
        }
        for(int i = 0; i < base.addons_soul.estrelas[4]; i++)
        {
            if (cb->objectName() == QString("a%1").arg(i))
            {
                cb->setCheckState(Qt::Checked);
            }
        }
    }

    UpdateAddons();

    if (armor_ess.addons_soul.sacred_addons.count() > 0)
    {
        ui->tableEspiritoSagrado->selectRow(0);
        emit on_tableEspiritoSagrado_cellClicked(0, 0);
    }

    loaded = true;
}

void DlgArmorEditor::UpdateAddons()
{
    ui->table_addons->setRowCount(0);
    for(int i = 0; i < base.addons.count(); i++)
    {
        ui->table_addons->insertRow(i);
        auto id = new QTableWidgetItem(QString::number(base.addons[i].id_addon));
        id->setForeground(QBrush(Utils::getColorByID(4)));
        ui->table_addons->setItem(i, 0, id);
        QTableWidgetItem *name = new QTableWidgetItem(QString::fromUtf8(PlayerEditor::GetAddonName(base.addons[i].id_addon, base.addons[i].arg[0], base.addons[i].arg[1], base.addons[i].arg[2]).toStdString().c_str()));
        name->setForeground(QBrush(Utils::getColorByID(3)));
        ui->table_addons->setItem(i, 1, name);
        int arg1 = base.addons[i].arg[0];
        int arg2 = base.addons[i].arg[1];
        int arg3 = base.addons[i].arg[2];
        arg1 = PlayerEditor::isFloatValue(arg1) ? PlayerEditor::VisualizeFloatPercent(arg1) : arg1;
        arg2 = PlayerEditor::isFloatValue(arg2) ? PlayerEditor::VisualizeFloatPercent(arg2) : arg2;
        arg3 = PlayerEditor::isFloatValue(arg3) ? PlayerEditor::VisualizeFloatPercent(arg3) : arg3;
        ui->table_addons->setItem(i, 2, new QTableWidgetItem(QString::number(arg1)));
        ui->table_addons->setItem(i, 3, new QTableWidgetItem(QString::number(arg2)));
        ui->table_addons->setItem(i, 4, new QTableWidgetItem(QString::number(arg3)));
    }

    if (whatIs == Utils::EQUIP_WEAPON) return;

    ui->tableAddonEspiritoSagrado->setRowCount(0);
    int i = 0;
    if (ui->tableEspiritoSagrado->currentRow() == 1)
    {
        foreach(auto addon, base.addons_soul.lunar_addons)
        {
            ui->tableAddonEspiritoSagrado->insertRow(i);
            auto id = new QTableWidgetItem(QString::number(addon.id_addon));
            id->setForeground(QBrush(Utils::getColorByID(4)));
            ui->tableAddonEspiritoSagrado->setItem(i, 0, id);
            auto name = new QTableWidgetItem(QString::fromUtf8(PlayerEditor::GetAddonName(addon.id_addon, addon.arg[0], addon.arg[1], addon.arg[2]).toStdString().c_str()));
            name->setForeground(QBrush(QColor(180, 0, 0)));
            ui->tableAddonEspiritoSagrado->setItem(i, 1, name);
            int arg1 = addon.arg[0];
            int arg2 = addon.arg[1];
            int arg3 = addon.arg[2];
            arg1 = PlayerEditor::isFloatValue(arg1) ? PlayerEditor::VisualizeFloatPercent(arg1) : arg1;
            arg2 = PlayerEditor::isFloatValue(arg2) ? PlayerEditor::VisualizeFloatPercent(arg2) : arg2;
            arg3 = PlayerEditor::isFloatValue(arg3) ? PlayerEditor::VisualizeFloatPercent(arg3) : arg3;
            ui->tableAddonEspiritoSagrado->setItem(i, 2, new QTableWidgetItem(QString::number(arg1)));
            ui->tableAddonEspiritoSagrado->setItem(i, 3, new QTableWidgetItem(QString::number(arg2)));
            ui->tableAddonEspiritoSagrado->setItem(i, 4, new QTableWidgetItem(QString::number(arg3)));
            i++;
        }
    }
    else if (ui->tableEspiritoSagrado->currentRow() == 0)
    {
        foreach(auto addon, base.addons_soul.sacred_addons)
        {
            ui->tableAddonEspiritoSagrado->insertRow(i);
            auto id = new QTableWidgetItem(QString::number(addon.id_addon));
            id->setForeground(QBrush(Utils::getColorByID(4)));
            ui->tableAddonEspiritoSagrado->setItem(i, 0, id);
            auto name = new QTableWidgetItem(QString::fromUtf8(PlayerEditor::GetAddonName(addon.id_addon, addon.arg[0], addon.arg[1], addon.arg[2]).toStdString().c_str()));
            name->setForeground(QBrush(QColor(180, 0, 0)));
            ui->tableAddonEspiritoSagrado->setItem(i, 1, name);
            int arg1 = addon.arg[0];
            int arg2 = addon.arg[1];
            int arg3 = addon.arg[2];
            arg1 = PlayerEditor::isFloatValue(arg1) ? PlayerEditor::VisualizeFloatPercent(arg1) : arg1;
            arg2 = PlayerEditor::isFloatValue(arg2) ? PlayerEditor::VisualizeFloatPercent(arg2) : arg2;
            arg3 = PlayerEditor::isFloatValue(arg3) ? PlayerEditor::VisualizeFloatPercent(arg3) : arg3;
            ui->tableAddonEspiritoSagrado->setItem(i, 2, new QTableWidgetItem(QString::number(arg1)));
            ui->tableAddonEspiritoSagrado->setItem(i, 3, new QTableWidgetItem(QString::number(arg2)));
            ui->tableAddonEspiritoSagrado->setItem(i, 4, new QTableWidgetItem(QString::number(arg3)));
            i++;
        }
    }

}


void DlgArmorEditor::on_btn_slot_add_clicked()
{
    if (ui->table_slots->rowCount() >= 4)
        return;
    int index = ui->table_slots->rowCount();
    ui->table_slots->insertRow(index);
    QTableWidgetItem *id = new QTableWidgetItem(QString::number(0));
    QTableWidgetItem *name = new QTableWidgetItem(QIcon(":/Icons/0.gif"), "");
    name->setFlags(name->flags() & ~Qt::ItemIsEditable);
    ui->table_slots->setItem(index, 0, id);
    ui->table_slots->setItem(index, 1, name);
}


void DlgArmorEditor::on_btn_slot_delete_clicked()
{
    if (ui->table_slots->currentRow() != -1)
        ui->table_slots->removeRow(ui->table_slots->currentRow());
}


void DlgArmorEditor::on_table_slots_cellChanged(int row, int column)
{
    if (!loaded) return;
    if (column == 1)
        return;
    int id = ui->table_slots->item(row, 0)->text().toInt();
    QTableWidgetItem *name = new QTableWidgetItem(QIcon(Commands::GetItemImage(id, Utils::Male, "STONE_ESSENCE")), Commands::GetItemName(id, "STONE_ESSENCE"));
    QColor color = Utils::getColorByID(pwAdmin::getInstance().listItemColor[id]);
    name->setForeground(QBrush(color));
    ui->table_slots->setItem(row, 1, name);
}


void DlgArmorEditor::on_tableEspiritoSagrado_cellClicked(int row, int column)
{
    ui->tableAddonEspiritoSagrado->setRowCount(0);

    if (row == 0)
    {
        ui->checkBox->setCheckState(base.addons_soul.sacred_activated == 0 ? Qt::Unchecked : Qt::Checked);
        ui->widget->setVisible(false);
        int i = 0;
        foreach(auto addon, base.addons_soul.sacred_addons)
        {
            ui->tableAddonEspiritoSagrado->insertRow(i);
            auto id = new QTableWidgetItem(QString::number(addon.id_addon));
            id->setForeground(QBrush(Utils::getColorByID(4)));
            ui->tableAddonEspiritoSagrado->setItem(i, 0, id);
            auto name = new QTableWidgetItem(QString::fromUtf8(PlayerEditor::GetAddonName(addon.id_addon, addon.arg[0], addon.arg[1], addon.arg[2]).toStdString().c_str()));
            name->setForeground(QBrush(QColor(180, 0, 0)));
            ui->tableAddonEspiritoSagrado->setItem(i, 1, name);
            ui->tableAddonEspiritoSagrado->setItem(i, 2, new QTableWidgetItem(QString::number(addon.arg[0])));
            ui->tableAddonEspiritoSagrado->setItem(i, 3, new QTableWidgetItem(QString::number(addon.arg[1])));
            ui->tableAddonEspiritoSagrado->setItem(i, 4, new QTableWidgetItem(QString::number(addon.arg[2])));
            i++;
        }

        ui->txtEspiritoSagradoId->setText(QString::number(base.addons_soul.sacred_id));
        ui->txtEspiritoSagradoNivel->setText(QString::number(base.addons_soul.sacred_level));
        ui->txtEspiritoSagradoPosicao->setText(QString::number(base.addons_soul.sacred_type));
    }

    if (row == 1)
    {
        ui->checkBox->setCheckState(base.addons_soul.lunar_activated == 0 ? Qt::Unchecked : Qt::Checked);
        ui->widget->setVisible(true);
        int i = 0;
        foreach(auto addon, base.addons_soul.lunar_addons)
        {
            ui->tableAddonEspiritoSagrado->insertRow(i);
            auto id = new QTableWidgetItem(QString::number(addon.id_addon));
            id->setForeground(QBrush(Utils::getColorByID(4)));
            ui->tableAddonEspiritoSagrado->setItem(i, 0, id);
            auto name = new QTableWidgetItem(QString::fromUtf8(PlayerEditor::GetAddonName(addon.id_addon, addon.arg[0], addon.arg[1], addon.arg[2]).toStdString().c_str()));
            name->setForeground(QBrush(QColor(180, 0, 0)));
            ui->tableAddonEspiritoSagrado->setItem(i, 1, name);
            ui->tableAddonEspiritoSagrado->setItem(i, 2, new QTableWidgetItem(QString::number(addon.arg[0])));
            ui->tableAddonEspiritoSagrado->setItem(i, 3, new QTableWidgetItem(QString::number(addon.arg[1])));
            ui->tableAddonEspiritoSagrado->setItem(i, 4, new QTableWidgetItem(QString::number(addon.arg[2])));
            i++;
        }

        ui->txtEspiritoSagradoId->setText(QString::number(base.addons_soul.lunar_id));
        ui->txtEspiritoSagradoNivel->setText(QString::number(base.addons_soul.lunar_level));
        ui->txtEspiritoSagradoPosicao->setText(QString::number(base.addons_soul.lunar_type));
    }

}


void DlgArmorEditor::on_tableEspiritoSagrado_itemChanged(QTableWidgetItem *item)
{
    ui->txtEspiritoSagradoId->setText(QString::number(base.addons_soul.sacred_addons[item->row()].id_addon));
    ui->txtEspiritoSagradoNivel->setText(QString::number(base.addons_soul.sacred_level));
    ui->txtEspiritoSagradoPosicao->setText(QString::number(base.addons_soul.sacred_type));
}


void DlgArmorEditor::on_pushButton_clicked()
{
    DlgClassMask mask;
    mask.Load(ui->txt_prereq_class->text().toUInt());
    if (mask.exec() == QDialog::Accepted)
    {
        ui->txt_prereq_class->setText(QString::number(mask.returnValue));
        ui->txt_prereq_class_label->setText(PlayerEditor::AddProfReqDesc(mask.returnValue));
    }
}


void DlgArmorEditor::on_btn_Save_clicked()
{
    base.prereq.agility = ui->txt_prereq_agility->text().toInt();
    base.prereq.race = ui->txt_prereq_class->text().toInt();
    base.prereq.durability = ui->txt_prereq_durab->text().toInt() * 100;
    base.prereq.energy = ui->txt_prereq_energy->text().toInt();
    base.prereq.level = ui->txt_prereq_level->text().toInt();
    base.prereq.max_durability = ui->txt_prereq_maxdurab->text().toInt() * 100;
    base.prereq.strength = ui->txt_prereq_strength->text().toInt();
    base.prereq.vitality = ui->txt_prereq_vitality->text().toInt();

    base.slot_flag = ui->txt_slot_flag->text().toInt();
    base.slot_count = ui->table_slots->rowCount();
    base.slot_list.clear();
    for (int i = 0; i < ui->table_slots->rowCount(); i++)
    {
        int slotid = ui->table_slots->item(i, 0)->text().toInt();
        base.slot_list.push_back(slotid);
    }

    OctetsStream os;
    if (whatIs == Utils::EQUIP_ARMOR)
    {
        base.made_tag.tag_content = Octets(ui->txt_made_by->text());
        base.made_tag.tag_type = ui->comboBox->currentIndex();

        armor_ess.armor = ui->txt_armor->text().toInt();
        armor_ess.defense = ui->txt_defense->text().toInt();
        armor_ess.hp_enhance = ui->txt_hp_enhance->text().toInt();
        armor_ess.mp_enhance = ui->txt_mp_enhance->text().toInt();
        armor_ess.resistance[0] = ui->txt_resistance0->text().toInt();
        armor_ess.resistance[1] = ui->txt_resistance1->text().toInt();
        armor_ess.resistance[2] = ui->txt_resistance2->text().toInt();
        armor_ess.resistance[3] = ui->txt_resistance3->text().toInt();
        armor_ess.resistance[4] = ui->txt_resistance4->text().toInt();

        armor_ess.SetBase(base);

        armor_ess.marshal(os);
    }
    if (whatIs ==Utils::EQUIP_WEAPON)
    {
        base.made_tag.tag_content = Octets(ui->txt_made_by->text());
        base.made_tag.tag_type = ui->comboBox_2->currentIndex();

        weapon_ess.attack_range = ui->txt_atkrange->text().toFloat();
        weapon_ess.attack_short_range = ui->txt_atkshortrange->text().toFloat();
        weapon_ess.attack_speed = ui->txt_atkspeed->text().toFloat();
        weapon_ess.damage_low = ui->txt_fdamage->text().toInt();
        weapon_ess.damage_high = ui->txt_fdamagemax->text().toInt();
        weapon_ess.magic_damage_low = ui->txt_mdamage->text().toInt();
        weapon_ess.magic_damage_high = ui->txt_mdamagemax->text().toInt();
        weapon_ess.require_projectile = ui->txt_projectile->text().toInt();
        weapon_ess.weapon_class = ui->txt_class->text().toInt();
        weapon_ess.weapon_delay = ui->txt_delay->text().toInt();
        weapon_ess.weapon_level = ui->txt_level->text().toInt();
        weapon_ess.weapon_type = ui->txt_type->text().toInt();

        weapon_ess.SetBase(base);

        weapon_ess.marshal(os, pwAdmin::getInstance().infos.ServerVersion);
    }
    returnedData = os.data;
    close();
    setResult(QDialog::Accepted);
}


void DlgArmorEditor::on_e0_stateChanged(int arg1)
{
    auto cbs = ui->widget->findChildren<QCheckBox*>();
    base.addons_soul.estrelas = {0,0,0,0,0};
    foreach(auto cb, cbs)
    {
        for(int i = 0; i < 5; i++)
        {
            if (cb->objectName() == QString("e%1").arg(i))
            {
                if (cb->checkState() == Qt::Checked)
                    base.addons_soul.estrelas[0] += 1;
            }
            if (cb->objectName() == QString("v%1").arg(i))
            {
                if (cb->checkState() == Qt::Checked)
                    base.addons_soul.estrelas[1] += 1;
            }
            if (cb->objectName() == QString("c%1").arg(i))
            {
                if (cb->checkState() == Qt::Checked)
                    base.addons_soul.estrelas[2] += 1;
            }
            if (cb->objectName() == QString("vi%1").arg(i))
            {
                if (cb->checkState() == Qt::Checked)
                    base.addons_soul.estrelas[3] += 1;
            }
            if (cb->objectName() == QString("a%1").arg(i))
            {
                if (cb->checkState() == Qt::Checked)
                    base.addons_soul.estrelas[4] += 1;
            }
        }
    }
}


void DlgArmorEditor::on_tableAddonEspiritoSagrado_itemClicked(QTableWidgetItem *item)
{
    int index = ui->tableAddonEspiritoSagrado->currentRow();
    if (index == -1)
        return;
    int row = ui->tableEspiritoSagrado->currentRow();
    int paramNum = row == 1 ? base.addons_soul.lunar_addons[index].paramNum : base.addons_soul.sacred_addons[index].paramNum;
    switch(paramNum)
    {
    case 1:
        ui->rdo_1->setChecked(true);
        break;
    case 2:
        ui->rdo_2->setChecked(true);
        break;
    case 3:
        ui->rdo_3->setChecked(true);
        break;
    default:
        ui->rdo_1->setChecked(true);
        break;
    }
}


void DlgArmorEditor::on_table_addons_itemClicked(QTableWidgetItem *item)
{
    if (item->row() == -1)
        return;
    switch(base.addons[item->row()].paramNum)
    {
    case 1:
        ui->rdoParam1->setChecked(true);
        break;
    case 2:
        ui->rdoParam2->setChecked(true);
        break;
    case 3:
        ui->rdoParam3->setChecked(true);
        break;
    default:
        ui->rdoParam1->setChecked(true);
        break;
    }
    if (base.addons[item->row()].isEmbedded)
        ui->cbEmbedded->setCheckState(Qt::Checked);
    else ui->cbEmbedded->setCheckState(Qt::Unchecked);
    if (base.addons[item->row()].isEngraved)
        ui->cbEngraved->setCheckState(Qt::Checked);
    else ui->cbEngraved->setCheckState(Qt::Unchecked);
    if (base.addons[item->row()].isInherited)
        ui->cbInherited->setCheckState(Qt::Checked);
    else ui->cbInherited->setCheckState(Qt::Unchecked);
    if (base.addons[item->row()].isSoul)
        ui->cbSoul->setCheckState(Qt::Checked);
    else ui->cbSoul->setCheckState(Qt::Unchecked);
}

void DlgArmorEditor::on_table_addons_cellChanged(int row, int column)
{
    if (!loaded) return;
    addon_data dt = base.addons.at(row);
    int id = ui->table_addons->item(row, 0)->text().toInt();
    int param1 = ui->table_addons->item(row, 2)->text().toInt();
    int param2 = ui->table_addons->item(row, 3)->text().toInt();
    int param3 = ui->table_addons->item(row, 4)->text().toInt();
    switch(column)
    {
    case 0:
    {
        dt.id_addon = id;
    }break;
    case 2:
    {
        dt.arg[0] = param1;
    }break;
    case 3:
    {
        dt.arg[1] = param2;
    }break;
    case 4:
    {
        dt.arg[2] = param3;
    }break;
    }
    ui->table_addons->item(row, 1)->setText(PlayerEditor::GetAddonName(id, param1, param2, param3));
    base.addons[row] = dt;
}

void DlgArmorEditor::on_cbSoul_stateChanged(int arg1)
{
    if (ui->table_addons->currentRow() >= 0)
    {
        base.addons[ui->table_addons->currentRow()].isSoul = arg1 == 2 ? true : false;
    }
}


void DlgArmorEditor::on_cbEngraved_stateChanged(int arg1)
{
    if (ui->table_addons->currentRow() >= 0)
    {
        base.addons[ui->table_addons->currentRow()].isEngraved = arg1 == 2 ? true : false;
    }
}


void DlgArmorEditor::on_cbEmbedded_stateChanged(int arg1)
{
    if (ui->table_addons->currentRow() >= 0)
    {
        base.addons[ui->table_addons->currentRow()].isEmbedded = arg1 == 2 ? true : false;
    }
}


void DlgArmorEditor::on_cbInherited_stateChanged(int arg1)
{
    if (ui->table_addons->currentRow() >= 0)
    {
        base.addons[ui->table_addons->currentRow()].isEmbedded = arg1 == 2 ? true : false;
    }
}

void DlgArmorEditor::on_tableAddonEspiritoSagrado_cellChanged(int row, int column)
{
    if (!loaded) return;
    if (ui->tableAddonEspiritoSagrado->currentRow() == -1) return;
    addon_data dt = ui->tableEspiritoSagrado->currentRow() == 0 ? base.addons_soul.sacred_addons.at(row) : base.addons_soul.lunar_addons.at(row);
    int id = ui->tableAddonEspiritoSagrado->item(row, 0)->text().toInt();
    int param1 = ui->tableAddonEspiritoSagrado->item(row, 2)->text().toInt();
    int param2 = ui->tableAddonEspiritoSagrado->item(row, 3)->text().toInt();
    int param3 = ui->tableAddonEspiritoSagrado->item(row, 4)->text().toInt();
    switch(column)
    {
    case 0:
    {
        dt.id_addon = ui->tableAddonEspiritoSagrado->item(row, column)->text().toInt();
    }break;
    case 2:
    {
        dt.arg[0] = ui->tableAddonEspiritoSagrado->item(row, column)->text().toInt();
    }break;
    case 3:
    {
        dt.arg[1] = ui->tableAddonEspiritoSagrado->item(row, column)->text().toInt();
    }break;
    case 4:
    {
        dt.arg[2] = ui->tableAddonEspiritoSagrado->item(row, column)->text().toInt();
    }break;
    }

    ui->tableAddonEspiritoSagrado->item(row, 1)->setText(PlayerEditor::GetAddonName(id, param1, param2, param3));
    if (ui->tableEspiritoSagrado->currentRow() == 0)
    {
        base.addons_soul.sacred_addons[row] = dt;
    } else base.addons_soul.lunar_addons[row] = dt;
}


void DlgArmorEditor::on_btn_addon_add_5_clicked()
{
    int index = ui->table_slots->currentRow();
    if (index == -1)
    {
        QMessageBox::warning(this, "Atenção!", "Selecione um item na tabela para adicionar/sobrescrever um novo item.");
        return;
    }
    DlgSearchEssence dlg;
    dlg.PopulateItems("STONE_ESSENCE");
    if (dlg.exec() > 0)
    {
        QTableWidgetItem *id = new QTableWidgetItem(QString::number(dlg.result()));
        id->setForeground(Utils::getColorByID(4));
        QTableWidgetItem *name = new QTableWidgetItem(QIcon(Commands::GetItemImage(dlg.result())), Commands::GetItemName(dlg.result()));
        name->setFlags(name->flags() & ~Qt::ItemIsEditable);
        QColor color = Utils::getColorByID(pwAdmin::getInstance().listItemColor[dlg.result()]);
        name->setForeground(QBrush(color));
        ui->table_slots->setItem(index, 0, id);
        ui->table_slots->setItem(index, 1, name);
    }
}


void DlgArmorEditor::on_btn_addon_add_4_clicked()
{
    loaded = false;
    pwAdmin &pw = pwAdmin::getInstance();
    DlgAddons dlg;
    if (dlg.exec() > 0)
    {
        foreach(auto addon, pw.listAddonsData)
        {
            if (addon.id_addon == dlg.result())
            {
                base.addons.push_back(addon);
                UpdateAddons();
                break;
            }
        }
        loaded = true;
    }
}


void DlgArmorEditor::on_btn_addon_add_6_clicked()
{
    loaded = false;
    pwAdmin &pw = pwAdmin::getInstance();
    DlgAddons dlg;
    if (dlg.exec() > 0)
    {
        foreach(auto addon, pw.listAddonsData)
        {
            if (addon.id_addon == dlg.result())
            {
                if (ui->tableEspiritoSagrado->currentRow() == 0)
                    base.addons_soul.sacred_addons.push_back(addon);
                else base.addons_soul.lunar_addons.push_back(addon);
                UpdateAddons();
                break;
            }
        }
        loaded = true;
    }
}


void DlgArmorEditor::on_btn_addon_delete_3_clicked()
{
    int index = ui->tableEspiritoSagrado->currentRow();
    if (index == -1) return;
    if (index == 0)
    {
        ui->tableEspiritoSagrado->setRowCount(0);
        ui->txtEspiritoSagradoId->setText("0");
        ui->txtEspiritoSagradoNivel->setText("0");
        ui->txtEspiritoSagradoPosicao->setText("0");
        ui->tableAddonEspiritoSagrado->setRowCount(0);
        base.addons_soul.sacred_activated = false;
        base.addons_soul.lunar_activated = false;
        base.addons_soul.sacred_addons.clear();
        base.addons_soul.sacred_id = 0;
        base.addons_soul.sacred_level = 0;
        base.addons_soul.sacred_type = 0;
        base.addons_soul.lunar_addons.clear();
        base.addons_soul.lunar_id = 0;
        base.addons_soul.lunar_level = 0;
        base.addons_soul.lunar_type = 0;
    } else if (index == 1)
    {
        ui->tableEspiritoSagrado->removeRow(index);
        ui->txtEspiritoSagradoId->setText("0");
        ui->txtEspiritoSagradoNivel->setText("0");
        ui->txtEspiritoSagradoPosicao->setText("0");
        ui->tableAddonEspiritoSagrado->setRowCount(0);
        ui->tableEspiritoSagrado->selectRow(0);
        ui->tableEspiritoSagrado->setFocus();
        base.addons_soul.lunar_activated = false;
        base.addons_soul.lunar_addons.clear();
        base.addons_soul.lunar_id = 0;
        base.addons_soul.lunar_level = 0;
        base.addons_soul.lunar_type = 0;
    }
}

void DlgArmorEditor::on_checkBox_stateChanged(int arg1)
{
    if (ui->tableEspiritoSagrado->currentRow() == 0)
    {
        if (arg1 == Qt::Checked)
            base.addons_soul.sacred_activated = 1;
        else
        {
            base.addons_soul.sacred_activated = 0;
            base.addons_soul.lunar_activated = 0;
        }
    }
    else if (ui->tableEspiritoSagrado->currentRow() == 1)
    {
        if (arg1 == Qt::Checked)
            base.addons_soul.lunar_activated = 1;
        else base.addons_soul.lunar_activated = 0;
    }
}


void DlgArmorEditor::on_rdo_1_clicked()
{
    int index = ui->tableAddonEspiritoSagrado->currentRow();
    if (ui->tableEspiritoSagrado->currentRow() == 0)
    {
        if (index >= 0)
        {
            addon_data data = base.addons_soul.sacred_addons.at(index);
            data.paramNum = 1;
            base.addons_soul.sacred_addons[index] = data;
        }
    }
    else if (ui->tableEspiritoSagrado->currentRow() == 1)
    {
        if (index >= 0)
        {
            addon_data data = base.addons_soul.lunar_addons.at(index);
            data.paramNum = 1;
            base.addons_soul.lunar_addons[index] = data;
        }
    }
}


void DlgArmorEditor::on_rdo_2_clicked()
{
    int index = ui->tableAddonEspiritoSagrado->currentRow();
    if (ui->tableEspiritoSagrado->currentRow() == 0)
    {
        if (index >= 0)
        {
            addon_data data = base.addons_soul.sacred_addons.at(index);
            data.paramNum = 2;
            base.addons_soul.sacred_addons[index] = data;
        }
    }
    else if (ui->tableEspiritoSagrado->currentRow() == 1)
    {
        if (index >= 0)
        {
            addon_data data = base.addons_soul.lunar_addons.at(index);
            data.paramNum = 2;
            base.addons_soul.lunar_addons[index] = data;
        }
    }
}


void DlgArmorEditor::on_rdo_3_clicked()
{
    int index = ui->tableAddonEspiritoSagrado->currentRow();
    if (ui->tableEspiritoSagrado->currentRow() == 0)
    {
        if (index >= 0)
        {
            addon_data data = base.addons_soul.sacred_addons.at(index);
            data.paramNum = 3;
            base.addons_soul.sacred_addons[index] = data;
        }
    }
    else if (ui->tableEspiritoSagrado->currentRow() == 1)
    {
        if (index >= 0)
        {
            addon_data data = base.addons_soul.lunar_addons.at(index);
            data.paramNum = 3;
            base.addons_soul.lunar_addons[index] = data;
        }
    }
}


void DlgArmorEditor::on_rdoParam1_clicked()
{
    int index = ui->table_addons->currentRow();
    if (index >= 0)
    {
        addon_data data = base.addons.at(index);
        data.paramNum = 1;
        base.addons[index] = data;
    }
}


void DlgArmorEditor::on_rdoParam2_clicked()
{
    int index = ui->table_addons->currentRow();
    if (index >= 0)
    {
        addon_data data = base.addons.at(index);
        data.paramNum = 2;
        base.addons[index] = data;
    }
}


void DlgArmorEditor::on_rdoParam3_clicked()
{
    int index = ui->table_addons->currentRow();
    if (index >= 0)
    {
        addon_data data = base.addons.at(index);
        data.paramNum = 3;
        base.addons[index] = data;
    }
}


void DlgArmorEditor::on_btn_Save_2_clicked()
{
    close();
    setResult(QDialog::Rejected);
}


void DlgArmorEditor::on_pushButton_2_clicked()
{
    DlgSearchEssence dlg;
    dlg.PopulateItems(ui->tableEspiritoSagrado->currentRow() == 0 ? "QIHUN_ESSENCE" : "QILING_ESSENCE");
    if (dlg.exec() > 0)
    {
        ui->txtEspiritoSagradoId->setText(QString::number(dlg.result()));
        ui->tableEspiritoSagrado->currentRow() == 0 ? base.addons_soul.sacred_id = dlg.result() : base.addons_soul.lunar_id = dlg.result();
    }
}


void DlgArmorEditor::on_txtEspiritoSagradoId_textChanged(const QString &arg1)
{
    int val = arg1.toUInt();
    ui->tableEspiritoSagrado->currentRow() == 0 ? base.addons_soul.sacred_id = val : base.addons_soul.lunar_id = val;
}


void DlgArmorEditor::on_txtEspiritoSagradoNivel_textChanged(const QString &arg1)
{
    int val = arg1.toUInt();
    ui->tableEspiritoSagrado->currentRow() == 0 ? base.addons_soul.sacred_level = val : base.addons_soul.lunar_level = val;
}


void DlgArmorEditor::on_txtEspiritoSagradoPosicao_cursorPositionChanged(int arg1, int arg2)
{

}


void DlgArmorEditor::on_txtEspiritoSagradoPosicao_textChanged(const QString &arg1)
{
    int val = arg1.toUInt();
    ui->tableEspiritoSagrado->currentRow() == 0 ? base.addons_soul.sacred_type = val : base.addons_soul.lunar_type = val;
}


void DlgArmorEditor::on_tableEspiritoSagrado_itemClicked(QTableWidgetItem *item)
{

}

