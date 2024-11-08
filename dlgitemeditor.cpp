#include "dlgitemeditor.h"
#include "ui_dlgitemeditor.h"

DlgItemEditor::DlgItemEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgItemEditor)
{
    ui->setupUi(this);

    ui->table_addons->setColumnWidth(0, 52);
    ui->table_addons->setColumnWidth(1, 290);
    ui->table_addons->setColumnWidth(2, 52);
    ui->table_addons->setColumnWidth(3, 52);
    ui->table_addons->setColumnWidth(4, 52);
}

DlgItemEditor::~DlgItemEditor()
{
    delete ui;
}

void DlgItemEditor::LoadArmor(armor_essence &essence)
{
    this->ess = essence;

    ui->txt_prereq_agility->setText(QString::number(ess.prereq.agility));
    ui->txt_prereq_class->setText(QString::number(ess.prereq.race));
    ui->txt_prereq_class_txt->setText(PlayerEditor::AddProfReqDesc(ess.prereq.race));
    ui->txt_prereq_durab->setText(QString::number(ess.prereq.durability / 100));
    ui->txt_prereq_energy->setText(QString::number(ess.prereq.energy));
    ui->txt_prereq_level->setText(QString::number(ess.prereq.level));
    ui->txt_prereq_maxdurab->setText(QString::number(ess.prereq.max_durability / 100));
    ui->txt_prereq_strength->setText(QString::number(ess.prereq.strength));
    ui->txt_prereq_vitality->setText(QString::number(ess.prereq.vitality));

    ui->txt_armor->setText(QString::number(ess.armor));
    ui->txt_defense->setText(QString::number(ess.defense));
    ui->txt_hp_enhance->setText(QString::number(ess.hp_enhance));
    ui->txt_mp_enhance->setText(QString::number(ess.mp_enhance));
    ui->txt_resistance0->setText(QString::number(ess.resistance[0]));
    ui->txt_resistance1->setText(QString::number(ess.resistance[1]));
    ui->txt_resistance2->setText(QString::number(ess.resistance[2]));
    ui->txt_resistance3->setText(QString::number(ess.resistance[3]));
    ui->txt_resistance4->setText(QString::number(ess.resistance[4]));

    ui->txt_made_by->setText(ess.made_tag.tag_content.toName());
    ui->comboBox->setCurrentIndex(ess.made_tag.tag_type);

    ui->txt_slot_flag->setText(QString::number(ess.slot_flag));

    for(int i = 0; i < ess.slot_count; i++)
    {
        ui->table_slots->insertRow(i);
        QTableWidgetItem *id = new QTableWidgetItem(QString::number(ess.slot_list[i]));
        id->setForeground(Utils::getColorByID(4));
        QTableWidgetItem *name = new QTableWidgetItem(QIcon(Commands::GetItemImage(ess.slot_list[i])), Commands::GetItemName(ess.slot_list[i]));
        name->setFlags(name->flags() & ~Qt::ItemIsEditable);
        QColor color = Utils::getColorByID(pwAdmin::getInstance().listItemColor[ess.slot_list[i]]);
        name->setForeground(QBrush(color));
        ui->table_slots->setItem(i, 0, id);
        ui->table_slots->setItem(i, 1, name);
    }

    /*QTableWidgetItem *item = new QTableWidgetItem(Commands::GetItemName(59768));
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

        for(int i = 0; i < ess.addons_soul.estrelas[0]; i++)
        {
            if (cb->objectName() == QString("e%1").arg(i))
            {
                cb->setCheckState(Qt::Checked);
            }
        }
        for(int i = 0; i < ess.addons_soul.estrelas[1]; i++)
        {
            if (cb->objectName() == QString("v%1").arg(i))
            {
                cb->setCheckState(Qt::Checked);
            }
        }
        for(int i = 0; i < ess.addons_soul.estrelas[2]; i++)
        {
            if (cb->objectName() == QString("c%1").arg(i))
            {
                cb->setCheckState(Qt::Checked);
            }
        }
        for(int i = 0; i < ess.addons_soul.estrelas[3]; i++)
        {
            if (cb->objectName() == QString("vi%1").arg(i))
            {
                cb->setCheckState(Qt::Checked);
            }
        }
        for(int i = 0; i < ess.addons_soul.estrelas[4]; i++)
        {
            if (cb->objectName() == QString("a%1").arg(i))
            {
                cb->setCheckState(Qt::Checked);
            }
        }
    }*/

    UpdateAddons();

    /*if (ess.addons_soul.sacred_addons.count() > 0)
    {
        ui->tableEspiritoSagrado->selectRow(0);
        emit on_tableEspiritoSagrado_cellClicked(0, 0);
    }*/

    loaded = true;
}

void DlgItemEditor::LoadNewArmor(new_armor_item &essence)
{
    this->newess = essence;
    this->ess = essence;

    ui->txt_prereq_agility->setText(QString::number(ess.prereq.agility));
    ui->txt_prereq_class->setText(QString::number(ess.prereq.race));
    ui->txt_prereq_class_txt->setText(PlayerEditor::AddProfReqDesc(ess.prereq.race));
    ui->txt_prereq_durab->setText(QString::number(ess.prereq.durability / 100));
    ui->txt_prereq_energy->setText(QString::number(ess.prereq.energy));
    ui->txt_prereq_level->setText(QString::number(ess.prereq.level));
    ui->txt_prereq_maxdurab->setText(QString::number(ess.prereq.max_durability / 100));
    ui->txt_prereq_strength->setText(QString::number(ess.prereq.strength));
    ui->txt_prereq_vitality->setText(QString::number(ess.prereq.vitality));

    ui->txt_armor->setText(QString::number(ess.armor));
    ui->txt_defense->setText(QString::number(ess.defense));
    ui->txt_hp_enhance->setText(QString::number(ess.hp_enhance));
    ui->txt_mp_enhance->setText(QString::number(ess.mp_enhance));
    ui->txt_resistance0->setText(QString::number(ess.resistance[0]));
    ui->txt_resistance1->setText(QString::number(ess.resistance[1]));
    ui->txt_resistance2->setText(QString::number(ess.resistance[2]));
    ui->txt_resistance3->setText(QString::number(ess.resistance[3]));
    ui->txt_resistance4->setText(QString::number(ess.resistance[4]));

    ui->txt_made_by->setText(ess.made_tag.tag_content.toName());
    ui->comboBox->setCurrentIndex(ess.made_tag.tag_type);

    ui->txt_slot_flag->setText(QString::number(ess.slot_flag));

    for(int i = 0; i < ess.slot_count; i++)
    {
        ui->table_slots->insertRow(i);
        QTableWidgetItem *id = new QTableWidgetItem(QString::number(ess.slot_list[i]));
        id->setForeground(Utils::getColorByID(4));
        QTableWidgetItem *name = new QTableWidgetItem(QIcon(Commands::GetItemImage(ess.slot_list[i])), Commands::GetItemName(ess.slot_list[i]));
        name->setFlags(name->flags() & ~Qt::ItemIsEditable);
        QColor color = Utils::getColorByID(pwAdmin::getInstance().listItemColor[ess.slot_list[i]]);
        name->setForeground(QBrush(color));
        ui->table_slots->setItem(i, 0, id);
        ui->table_slots->setItem(i, 1, name);
    }

    /*QTableWidgetItem *item = new QTableWidgetItem(Commands::GetItemName(59768));
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

        for(int i = 0; i < ess.addons_soul.estrelas[0]; i++)
        {
            if (cb->objectName() == QString("e%1").arg(i))
            {
                cb->setCheckState(Qt::Checked);
            }
        }
        for(int i = 0; i < ess.addons_soul.estrelas[1]; i++)
        {
            if (cb->objectName() == QString("v%1").arg(i))
            {
                cb->setCheckState(Qt::Checked);
            }
        }
        for(int i = 0; i < ess.addons_soul.estrelas[2]; i++)
        {
            if (cb->objectName() == QString("c%1").arg(i))
            {
                cb->setCheckState(Qt::Checked);
            }
        }
        for(int i = 0; i < ess.addons_soul.estrelas[3]; i++)
        {
            if (cb->objectName() == QString("vi%1").arg(i))
            {
                cb->setCheckState(Qt::Checked);
            }
        }
        for(int i = 0; i < ess.addons_soul.estrelas[4]; i++)
        {
            if (cb->objectName() == QString("a%1").arg(i))
            {
                cb->setCheckState(Qt::Checked);
            }
        }
    }*/

    /*if (ess.addons_soul.sacred_addons.count() > 0)
    {
        ui->tableEspiritoSagrado->selectRow(0);
        emit on_tableEspiritoSagrado_cellClicked(0, 0);
    }*/

    loaded = true;
    is_new_armor = true;
}

void DlgItemEditor::UpdateAddons()
{
    ui->table_addons->setRowCount(0);
    for(int i = 0; i < ess.addons.count(); i++)
    {
        ui->table_addons->insertRow(i);
        auto id = new QTableWidgetItem(QString::number(ess.addons[i].id_addon));
        id->setForeground(QBrush(Utils::getColorByID(4)));
        ui->table_addons->setItem(i, 0, id);
        QTableWidgetItem *name = new QTableWidgetItem(QString::fromUtf8(PlayerEditor::GetAddonName(ess.addons[i].id_addon, ess.addons[i].arg[0], ess.addons[i].arg[1], ess.addons[i].arg[2]).toStdString().c_str()));
        name->setForeground(QBrush(Utils::getColorByID(3)));
        ui->table_addons->setItem(i, 1, name);
        int arg1 = ess.addons[i].arg[0];
        int arg2 = ess.addons[i].arg[1];
        int arg3 = ess.addons[i].arg[2];
        arg1 = PlayerEditor::isFloatValue(arg1) ? PlayerEditor::VisualizeFloatPercent(arg1) : arg1;
        arg2 = PlayerEditor::isFloatValue(arg2) ? PlayerEditor::VisualizeFloatPercent(arg2) : arg2;
        arg3 = PlayerEditor::isFloatValue(arg3) ? PlayerEditor::VisualizeFloatPercent(arg3) : arg3;
        ui->table_addons->setItem(i, 2, new QTableWidgetItem(QString::number(arg1)));
        ui->table_addons->setItem(i, 3, new QTableWidgetItem(QString::number(arg2)));
        ui->table_addons->setItem(i, 4, new QTableWidgetItem(QString::number(arg3)));
    }
    /*
    ui->tableAddonEspiritoSagrado->setRowCount(0);
    int i = 0;
    if (ui->tableEspiritoSagrado->currentRow() == 1)
    {
        foreach(auto addon, ess.addons_soul.lunar_addons)
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
        foreach(auto addon, ess.addons_soul.sacred_addons)
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
    }*/

}

void DlgItemEditor::on_btn_slot_add_clicked()
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


void DlgItemEditor::on_btn_slot_delete_clicked()
{
    if (ui->table_slots->currentRow() != -1)
        ui->table_slots->removeRow(ui->table_slots->currentRow());
}


void DlgItemEditor::on_table_slots_cellChanged(int row, int column)
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


void DlgItemEditor::on_pushButton_clicked()
{
    DlgClassMask mask;
    mask.Load(ui->txt_prereq_class->text().toUInt());
    if (mask.exec() == QDialog::Accepted)
    {
        ui->txt_prereq_class->setText(QString::number(mask.returnValue));
        ui->txt_prereq_class_txt->setText(PlayerEditor::AddProfReqDesc(mask.returnValue));
    }
}


void DlgItemEditor::on_txt_prereq_class_textChanged(const QString &arg1)
{
    if (!arg1.isEmpty())
        ui->txt_prereq_class_txt->setText(PlayerEditor::AddProfReqDesc(arg1.toUInt()));
}


void DlgItemEditor::on_btnSave_clicked()
{
    ess.prereq.agility = ui->txt_prereq_agility->text().toInt();
    ess.prereq.race = ui->txt_prereq_class->text().toInt();
    ess.prereq.durability = ui->txt_prereq_durab->text().toInt() * 100;
    ess.prereq.energy = ui->txt_prereq_energy->text().toInt();
    ess.prereq.level = ui->txt_prereq_level->text().toInt();
    ess.prereq.max_durability = ui->txt_prereq_maxdurab->text().toInt() * 100;
    ess.prereq.strength = ui->txt_prereq_strength->text().toInt();
    ess.prereq.vitality = ui->txt_prereq_vitality->text().toInt();

    ess.slot_flag = ui->txt_slot_flag->text().toInt();
    ess.slot_count = ui->table_slots->rowCount();
    ess.slot_list.clear();
    for (int i = 0; i < ui->table_slots->rowCount(); i++)
    {
        int slotid = ui->table_slots->item(i, 0)->text().toInt();
        ess.slot_list.push_back(slotid);
    }

    ess.made_tag.tag_content = Octets(ui->txt_made_by->text());
    ess.made_tag.tag_type = ui->comboBox->currentIndex();
    ess.armor = ui->txt_armor->text().toInt();
    ess.defense = ui->txt_defense->text().toInt();
    ess.hp_enhance = ui->txt_hp_enhance->text().toInt();
    ess.mp_enhance = ui->txt_mp_enhance->text().toInt();
    ess.resistance[0] = ui->txt_resistance0->text().toInt();
    ess.resistance[1] = ui->txt_resistance1->text().toInt();
    ess.resistance[2] = ui->txt_resistance2->text().toInt();
    ess.resistance[3] = ui->txt_resistance3->text().toInt();
    ess.resistance[4] = ui->txt_resistance4->text().toInt();

    OctetsStream os;

    if (is_new_armor)
    {
        newess.SetNewArmor(ess);
        newess.marshal(os);
        returnedData = os.data;
        accept();
    }

    ess.marshal(os);
    returnedData = os.data;

    accept();
}


void DlgItemEditor::on_table_addons_itemClicked(QTableWidgetItem *item)
{
    if (item->row() == -1)
        return;
    switch(ess.addons[item->row()].paramNum)
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
    if (ess.addons[item->row()].isEmbedded)
        ui->cbEmbedded->setCheckState(Qt::Checked);
    else ui->cbEmbedded->setCheckState(Qt::Unchecked);
    if (ess.addons[item->row()].isEngraved)
        ui->cbEngraved->setCheckState(Qt::Checked);
    else ui->cbEngraved->setCheckState(Qt::Unchecked);
    if (ess.addons[item->row()].isInherited)
        ui->cbInherited->setCheckState(Qt::Checked);
    else ui->cbInherited->setCheckState(Qt::Unchecked);
    if (ess.addons[item->row()].isSoul)
        ui->cbSoul->setCheckState(Qt::Checked);
    else ui->cbSoul->setCheckState(Qt::Unchecked);
}


void DlgItemEditor::on_table_addons_cellChanged(int row, int column)
{
    if (!loaded) return;
    addon_data dt = ess.addons.at(row);
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
    ess.addons[row] = dt;
}


void DlgItemEditor::on_cbSoul_stateChanged(int arg1)
{
    if (ui->table_addons->currentRow() >= 0)
    {
        ess.addons[ui->table_addons->currentRow()].isSoul = arg1 == 2 ? true : false;
    }
}


void DlgItemEditor::on_cbEngraved_stateChanged(int arg1)
{
    if (ui->table_addons->currentRow() >= 0)
    {
        ess.addons[ui->table_addons->currentRow()].isEngraved = arg1 == 2 ? true : false;
    }
}


void DlgItemEditor::on_cbEmbedded_stateChanged(int arg1)
{
    if (ui->table_addons->currentRow() >= 0)
    {
        ess.addons[ui->table_addons->currentRow()].isEmbedded = arg1 == 2 ? true : false;
    }
}


void DlgItemEditor::on_cbInherited_stateChanged(int arg1)
{
    if (ui->table_addons->currentRow() >= 0)
    {
        ess.addons[ui->table_addons->currentRow()].isEmbedded = arg1 == 2 ? true : false;
    }
}


void DlgItemEditor::on_btn_addon_add_6_clicked()
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
                ess.addons.push_back(addon);
                UpdateAddons();
                break;
            }
        }
        loaded = true;
    }
}


void DlgItemEditor::on_btn_addon_add_5_clicked()
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


void DlgItemEditor::on_rdoParam1_clicked()
{
    int index = ui->table_addons->currentRow();
    if (index >= 0)
    {
        addon_data data = ess.addons.at(index);
        data.paramNum = 1;
        ess.addons[index] = data;
    }
}


void DlgItemEditor::on_rdoParam2_clicked()
{
    int index = ui->table_addons->currentRow();
    if (index >= 0)
    {
        addon_data data = ess.addons.at(index);
        data.paramNum = 2;
        ess.addons[index] = data;
    }
}


void DlgItemEditor::on_rdoParam3_clicked()
{
    int index = ui->table_addons->currentRow();
    if (index >= 0)
    {
        addon_data data = ess.addons.at(index);
        data.paramNum = 3;
        ess.addons[index] = data;
    }
}


void DlgItemEditor::on_btnClose_clicked()
{
    reject();
}

