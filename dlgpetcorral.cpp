#include "dlgpetcorral.h"
#include "ui_dlgpetcorral.h"
#include "connection.h"

bool updateList = false;
int prow = -1;
int pet_essence_list = -1;
int pet_evolved_list = -1;

DlgPetCorral::DlgPetCorral( QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgPetCorral)
{
    ui->setupUi(this);
    connectLineEdits();

    ui->tablePetCorral->setColumnWidth(0, 60);
    ui->tablePetCorral->setColumnWidth(1, 150);
    ui->tablePetCorral->setColumnWidth(2, 40);
    ui->tablePetCorral->setColumnWidth(3, 70);
    pwAdmin &pw = pwAdmin::getInstance();
    for(int i = 0; i < pw.elc->Lists.count(); i++)
    {
        if (pw.elc->Lists[i].listName.contains("PET_ESSENCE"))
            pet_essence_list = i;
        if (pet_essence_list != -1)
            break;
    }
    for(int i = 0; i < pw.elc->Lists.count(); i++)
    {
        if (pw.elc->Lists[i].listName.contains("PET_EVOLVED"))
            pet_evolved_list = i;;
        if (pet_evolved_list != -1)
            break;
    }
}

DlgPetCorral::~DlgPetCorral()
{
    delete ui;
}

void DlgPetCorral::UpdateList()
{
    ui->tablePetCorral->setRowCount(0);
    for(int i = 0; i < petCorral.listPet.count(); i++)
    {
        GPetInfo info;
        info.Version = pwAdmin::getInstance().infos.ServerVersion;
        OctetsStream newOs(petCorral.listPet[i].data.value, false, false);
        info.unmarshal(newOs);
        listPetInfo.push_back(info);
        ui->tablePetCorral->insertRow(i);
        QTableWidgetItem *name = new QTableWidgetItem(Commands::GetItemImage(info.pet_tid, Utils::Male, "PET_ESSENCE"), Commands::GetItemName(info.pet_tid, "PET_ESSENCE"));
        ui->tablePetCorral->setItem(i, 0, new QTableWidgetItem(QString::number(info.pet_tid)));
        ui->tablePetCorral->setItem(i, 1, name);
        ui->tablePetCorral->setItem(i, 2, new QTableWidgetItem(QString::number(info.level)));
        ui->tablePetCorral->setItem(i, 3, new QTableWidgetItem(Utils::TipoDeMascote((Utils::PetType)info.pet_class)));
    }
}

void DlgPetCorral::UpdateValues()
{
    pwAdmin &pw = pwAdmin::getInstance();
    int i = ui->tablePetCorral->currentRow();
    if (i == -1)
        return;
    auto p = petCorral.listPet[i];
    GPetInfo info;
    info.Version = pwAdmin::getInstance().infos.ServerVersion;
    OctetsStream newOs(p.data.value, false, false);
    info.unmarshal(newOs);
    info.color = ui->txtColor->text().toUInt();
    info.exp = ui->txtExp->text().toUInt();
    info.feed_time = ui->txtFoodTime->text().toUInt();
    info.honor_point = ui->txtHonorPoints->text().toUInt();
    info.hp_factor = ui->txtHpFactor->text().toUInt();
    info.hunger = ui->txtHunger->text().toUInt();
    info.is_bind = ui->txtBind->text().toUInt();
    info.level = ui->txtLevel->text().toUInt();
    info.name = Octets(ui->txtName->text(), QString(""));
    info.pet_class = ui->txtPetClass->text().toUInt();
    info.pet_egg_tid = ui->txtPetEggId->text().toUInt();
    info.pet_tid = ui->txtPetId->text().toUInt();
    info.pet_vis_tid = ui->txtVisPetId->text().toUInt();
    ui->imgPetId->setPixmap(Commands::GetItemImage(info.pet_tid, Utils::Male, "PET_ESSENCE"));
    ui->txtPetIdName->setText(Commands::GetItemName(info.pet_tid, "PET_ESSENCE"));
    ui->imgPetVisId->setPixmap(Commands::GetItemImage(info.pet_vis_tid, Utils::Male, "PET_ESSENCE"));
    ui->txtPetVisIdName->setText(Commands::GetItemName(info.pet_vis_tid, "PET_ESSENCE"));
    ui->imgPetEggId->setPixmap(Commands::GetItemImage(info.pet_egg_tid, Utils::Male, "PET_EGG_ESSENCE"));
    ui->txtPetEggIdName->setText(Commands::GetItemName(info.pet_egg_tid, "PET_EGG_ESSENCE"));
    for(int i = 0; i < 10; i++)
        info.reserved[i] = 0;
    info.skill_point = ui->txtSkillPoint->text().toUInt();
    info.unused = ui->txtUnused->text().toUInt();
    info.skills[0].id = ui->txtSkill1->text().toUInt();
    info.skills[1].id = ui->txtSkill2->text().toUInt();
    info.skills[2].id = ui->txtSkill3->text().toUInt();
    info.skills[3].id = ui->txtSkill4->text().toUInt();
    info.skills[4].id = ui->txtSkill5->text().toUInt();
    info.skills[5].id = ui->txtSkill6->text().toUInt();
    info.skills[6].id = ui->txtSkill7->text().toUInt();
    info.skills[7].id = ui->txtSkill8->text().toUInt();
    info.skills[0].level = ui->txtSkillLevel1->text().toUInt();
    info.skills[1].level = ui->txtSkillLevel2->text().toUInt();
    info.skills[2].level = ui->txtSkillLevel3->text().toUInt();
    info.skills[3].level = ui->txtSkillLevel4->text().toUInt();
    info.skills[4].level = ui->txtSkillLevel5->text().toUInt();
    info.skills[5].level = ui->txtSkillLevel6->text().toUInt();
    info.skills[6].level = ui->txtSkillLevel7->text().toUInt();
    info.skills[7].level = ui->txtSkillLevel8->text().toUInt();
    ui->txtSkillName1->setText(pw.listSkillName[info.skills[0].id]);
    ui->txtSkillName2->setText(pw.listSkillName[info.skills[1].id]);
    ui->txtSkillName3->setText(pw.listSkillName[info.skills[2].id]);
    ui->txtSkillName4->setText(pw.listSkillName[info.skills[3].id]);
    ui->txtSkillName5->setText(pw.listSkillName[info.skills[4].id]);
    ui->txtSkillName6->setText(pw.listSkillName[info.skills[5].id]);
    ui->txtSkillName7->setText(pw.listSkillName[info.skills[6].id]);
    ui->txtSkillName8->setText(pw.listSkillName[info.skills[7].id]);
    ui->imgSkill1->setPixmap(Commands::GetSkillIcon(pw.listSkillInfo[info.skills[0].id].icon_name));
    ui->imgSkill2->setPixmap(Commands::GetSkillIcon(pw.listSkillInfo[info.skills[1].id].icon_name));
    ui->imgSkill3->setPixmap(Commands::GetSkillIcon(pw.listSkillInfo[info.skills[2].id].icon_name));
    ui->imgSkill4->setPixmap(Commands::GetSkillIcon(pw.listSkillInfo[info.skills[3].id].icon_name));
    ui->imgSkill5->setPixmap(Commands::GetSkillIcon(pw.listSkillInfo[info.skills[4].id].icon_name));
    ui->imgSkill6->setPixmap(Commands::GetSkillIcon(pw.listSkillInfo[info.skills[5].id].icon_name));
    ui->imgSkill7->setPixmap(Commands::GetSkillIcon(pw.listSkillInfo[info.skills[6].id].icon_name));
    ui->imgSkill8->setPixmap(Commands::GetSkillIcon(pw.listSkillInfo[info.skills[7].id].icon_name));
    info.evo_prop.nature = ui->txtNature->text().toUInt();
    info.evo_prop.r_atk_lvl = ui->txtAtkLevel->text().toUInt();
    info.evo_prop.r_attack = ui->txtAtk->text().toUInt();
    info.evo_prop.r_def_lvl = ui->txtDefLevel->text().toUInt();
    info.evo_prop.r_defense = ui->txtDef->text().toUInt();
    info.evo_prop.r_hp = ui->txtHp->text().toUInt();
    ui->progressAtk->setValue(info.evo_prop.r_attack);
    ui->progressDef->setValue(info.evo_prop.r_defense);
    ui->progressAtkLevel->setValue(info.evo_prop.r_atk_lvl);
    ui->progressDefLevel->setValue(info.evo_prop.r_def_lvl);
    ui->progressHP->setValue(info.evo_prop.r_hp);
    for (int e = 0; e < pw.elc->Lists[pet_evolved_list].elementValues.length(); e++)
    {
        if (pw.elc->GetValue(pet_evolved_list, e, 0).toInt() == info.evo_prop.nature)
        {
            ui->txtNatureName->setText(pw.elc->GetValue(pet_evolved_list, e, 1));
            break;
        } else ui->txtNatureName->setText("");
    }

    QTableWidgetItem *name = new QTableWidgetItem(Commands::GetItemImage(info.pet_tid, Utils::Male, "PET_ESSENCE"), Commands::GetItemName(info.pet_tid, "PET_ESSENCE"));
    ui->tablePetCorral->setItem(i, 0, new QTableWidgetItem(QString::number(info.pet_tid)));
    ui->tablePetCorral->setItem(i, 1, name);
    ui->tablePetCorral->setItem(i, 2, new QTableWidgetItem(QString::number(info.level)));
    ui->tablePetCorral->setItem(i, 3, new QTableWidgetItem(Utils::TipoDeMascote((Utils::PetType)info.pet_class)));


    OctetsStream os(QByteArray(), false, false);
    info.marshal(os);
    p.data = Octets(os.data);
    petCorral.listPet[ui->tablePetCorral->currentRow()] = p;
}

void DlgPetCorral::Load(QByteArray o)
{
    pwAdmin &pw = pwAdmin::getInstance();
    OctetsStream os(o, false, true);
    petCorral.unmarshal(os);

    ui->txtCapacity->setText(QString::number(petCorral.capacity));
    UpdateList();
}

void DlgPetCorral::on_tablePetCorral_cellClicked(int row, int column)
{
    pwAdmin &pw = pwAdmin::getInstance();
    GPetInfo info;
    info.Version = pwAdmin::getInstance().infos.ServerVersion;
    OctetsStream newOs(petCorral.listPet[row].data.value, false, false);
    info.unmarshal(newOs);
    ui->txtPetClass->setText(QString::number(info.pet_class));
    ui->txtPosition->setText(QString::number(petCorral.listPet[row].index));
    ui->txtBind->setText(QString::number(info.is_bind));
    ui->txtUnused->setText(QString::number(info.unused));
    ui->txtSkillPoint->setText(QString::number(info.skill_point));
    ui->txtPetId->setText(QString::number(info.pet_tid));
    ui->imgPetId->setPixmap(Commands::GetItemImage(info.pet_tid, Utils::Male, "PET_ESSENCE"));
    ui->txtPetIdName->setText(Commands::GetItemName(info.pet_tid, "PET_ESSENCE"));
    ui->txtVisPetId->setText(QString::number(info.pet_vis_tid));
    ui->imgPetVisId->setPixmap(Commands::GetItemImage(info.pet_vis_tid,Utils::Male, "PET_ESSENCE"));
    ui->txtPetVisIdName->setText(Commands::GetItemName(info.pet_vis_tid, "PET_ESSENCE"));
    ui->txtPetEggId->setText(QString::number(info.pet_egg_tid));
    ui->imgPetEggId->setPixmap(Commands::GetItemImage(info.pet_egg_tid, Utils::Male,"PET_EGG_ESSENCE"));
    ui->txtPetEggIdName->setText(Commands::GetItemName(info.pet_egg_tid, "PET_EGG_ESSENCE"));
    ui->txtLevel->setText(QString::number(info.level));
    ui->txtExp->setText(QString::number(info.exp));
    ui->txtName->setText(info.name.toName());
    ui->txtHonorPoints->setText(QString::number(info.honor_point));
    ui->txtColor->setText(QString::number(info.color));
    ui->txtFoodTime->setText(QString::number(info.feed_time));
    ui->txtHunger->setText(QString::number(info.hunger));
    ui->txtHpFactor->setText(QString::number(info.hp_factor));
    ui->txtSkill1->setText(QString::number(info.skills[0].id));
    ui->txtSkill2->setText(QString::number(info.skills[1].id));
    ui->txtSkill3->setText(QString::number(info.skills[2].id));
    ui->txtSkill4->setText(QString::number(info.skills[3].id));
    ui->txtSkill5->setText(QString::number(info.skills[4].id));
    ui->txtSkill6->setText(QString::number(info.skills[5].id));
    ui->txtSkill7->setText(QString::number(info.skills[6].id));
    ui->txtSkill8->setText(QString::number(info.skills[7].id));
    ui->txtSkillLevel1->setText(QString::number(info.skills[0].level));
    ui->txtSkillLevel2->setText(QString::number(info.skills[1].level));
    ui->txtSkillLevel3->setText(QString::number(info.skills[2].level));
    ui->txtSkillLevel4->setText(QString::number(info.skills[3].level));
    ui->txtSkillLevel5->setText(QString::number(info.skills[4].level));
    ui->txtSkillLevel6->setText(QString::number(info.skills[5].level));
    ui->txtSkillLevel7->setText(QString::number(info.skills[6].level));
    ui->txtSkillLevel8->setText(QString::number(info.skills[7].level));
    ui->txtSkillName1->setText(pw.listSkillName[info.skills[0].id]);
    ui->txtSkillName2->setText(pw.listSkillName[info.skills[1].id]);
    ui->txtSkillName3->setText(pw.listSkillName[info.skills[2].id]);
    ui->txtSkillName4->setText(pw.listSkillName[info.skills[3].id]);
    ui->txtSkillName5->setText(pw.listSkillName[info.skills[4].id]);
    ui->txtSkillName6->setText(pw.listSkillName[info.skills[5].id]);
    ui->txtSkillName7->setText(pw.listSkillName[info.skills[6].id]);
    ui->txtSkillName8->setText(pw.listSkillName[info.skills[7].id]);
    ui->imgSkill1->setPixmap(Commands::GetSkillIcon(pw.listSkillInfo[info.skills[0].id].icon_name));
    ui->imgSkill2->setPixmap(Commands::GetSkillIcon(pw.listSkillInfo[info.skills[1].id].icon_name));
    ui->imgSkill3->setPixmap(Commands::GetSkillIcon(pw.listSkillInfo[info.skills[2].id].icon_name));
    ui->imgSkill4->setPixmap(Commands::GetSkillIcon(pw.listSkillInfo[info.skills[3].id].icon_name));
    ui->imgSkill5->setPixmap(Commands::GetSkillIcon(pw.listSkillInfo[info.skills[4].id].icon_name));
    ui->imgSkill6->setPixmap(Commands::GetSkillIcon(pw.listSkillInfo[info.skills[5].id].icon_name));
    ui->imgSkill7->setPixmap(Commands::GetSkillIcon(pw.listSkillInfo[info.skills[6].id].icon_name));
    ui->imgSkill8->setPixmap(Commands::GetSkillIcon(pw.listSkillInfo[info.skills[7].id].icon_name));
    if (info.pet_class == Utils::PET_CLASS_EVOLUTION)
    {

        int hp, atk, def, atklevel, deflevel;
        for (int e = 0; e < pw.elc->Lists[pet_essence_list].elementValues.length(); e++)
        {
            if (pw.elc->GetValue(pet_essence_list, e, 0).toInt() == info.pet_tid)
            {
                hp = pw.elc->GetValue(pet_essence_list, e, 56).toUInt();
                atk = pw.elc->GetValue(pet_essence_list, e, 57).toUInt();
                def = pw.elc->GetValue(pet_essence_list, e, 58).toUInt();
                atklevel = pw.elc->GetValue(pet_essence_list, e, 59).toUInt();
                deflevel = pw.elc->GetValue(pet_essence_list, e, 60).toUInt();
            }
        }
        ui->txtAtk->setText(QString::number(info.evo_prop.r_attack));
        ui->progressAtk->setValue(info.evo_prop.r_attack);
        ui->progressAtk->setMaximum(atk);
        ui->txtDef->setText(QString::number(info.evo_prop.r_defense));
        ui->progressDef->setValue(info.evo_prop.r_defense);
        ui->progressDef->setMaximum(def);
        ui->txtAtkLevel->setText(QString::number(info.evo_prop.r_atk_lvl));
        ui->progressAtkLevel->setValue(info.evo_prop.r_atk_lvl);
        ui->progressAtkLevel->setMaximum(atklevel);
        ui->txtDefLevel->setText(QString::number(info.evo_prop.r_def_lvl));
        ui->progressDefLevel->setValue(info.evo_prop.r_def_lvl);
        ui->progressDefLevel->setMaximum(deflevel);
        ui->txtHp->setText(QString::number(info.evo_prop.r_hp));
        ui->progressHP->setValue(info.evo_prop.r_hp);
        ui->progressHP->setMaximum(hp);
        ui->txtNature->setText(QString::number(info.evo_prop.nature));
        for (int e = 0; e < pw.elc->Lists[pet_evolved_list].elementValues.length(); e++)
        {
            if (pw.elc->GetValue(pet_evolved_list, e, 0).toInt() == info.evo_prop.nature)
            {
                ui->txtNatureName->setText(pw.elc->GetValue(pet_evolved_list, e, 1));
                break;
            } else ui->txtNatureName->setText("");
        }

    }
    else
    {
        ui->txtAtk->setText(QString::number(0));
        ui->progressAtk->setValue(0);
        ui->progressAtk->setMaximum(100);
        ui->txtDef->setText(QString::number(0));
        ui->progressDef->setValue(0);
        ui->progressDef->setMaximum(100);
        ui->txtAtkLevel->setText(QString::number(0));
        ui->progressAtkLevel->setValue(0);
        ui->progressAtkLevel->setMaximum(100);
        ui->txtDefLevel->setText(QString::number(0));
        ui->progressDefLevel->setValue(0);
        ui->progressDefLevel->setMaximum(100);
        ui->txtHp->setText(QString::number(0));
        ui->progressHP->setValue(0);
        ui->progressHP->setMaximum(100);
        ui->txtNature->setText(QString::number(0));
        ui->txtNatureName->setText("");
    }
}


void DlgPetCorral::on_btnAddPet_clicked()
{
    GPet pet;
    pet.index = CheckID();
    GPetInfo info;
    info.Version = pwAdmin::getInstance().infos.ServerVersion;
    OctetsStream os(QByteArray(), false, true);
    info.marshal(os);
    pet.data = Octets(os.data);
    petCorral.listPet.push_back(pet);
    int index = ui->tablePetCorral->rowCount();
    ui->tablePetCorral->insertRow(index);
    ui->tablePetCorral->setItem(index, 0, new QTableWidgetItem(QString::number(info.pet_tid)));
    ui->tablePetCorral->setItem(index, 1, new QTableWidgetItem(""));
    ui->tablePetCorral->setItem(index, 2, new QTableWidgetItem(QString::number(info.level)));
    ui->tablePetCorral->setItem(index, 3, new QTableWidgetItem(Utils::TipoDeMascote((Utils::PetType)info.pet_class)));
    ui->tablePetCorral->selectRow(index);
    emit on_tablePetCorral_cellClicked(index, 0);
    //UpdateList();
}


void DlgPetCorral::on_btnClose_clicked()
{
    close();
    setResult(QDialog::Rejected);
}


void DlgPetCorral::on_btnSave_clicked()
{
    OctetsStream os(QByteArray(), false, true);
    petCorral.marshal(os);
    this->returnedData = os;
    this->close();
    this->setResult(QDialog::Accepted);
}

void DlgPetCorral::on_textEdited(const QString &arg1)
{
    UpdateValues();
}

void DlgPetCorral::on_tablePetCorral_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    prow = previousRow;
}


void DlgPetCorral::on_btnPetId_clicked()
{
    DlgSearchEssence dlg;
    dlg.PopulateItems("PET_ESSENCE");
    dlg.returnOnlyOne = true;
    if (dlg.exec() > 0)
    {
        ui->txtPetId->setText(QString::number(dlg.result()));
        UpdateValues();
    }
}


void DlgPetCorral::on_btnPetVisId_clicked()
{
    DlgSearchEssence dlg;
    dlg.PopulateItems("PET_ESSENCE");
    dlg.returnOnlyOne = true;
    if (dlg.exec() > 0)
    {
        ui->txtVisPetId->setText(QString::number(dlg.result()));
        UpdateValues();
    }
}


void DlgPetCorral::on_btnPetEggId_clicked()
{
    DlgSearchEssence dlg;
    dlg.PopulateItems("PET_EGG_ESSENCE");
    dlg.returnOnlyOne = true;
    if (dlg.exec() > 0)
    {
        ui->txtPetEggId->setText(QString::number(dlg.result()));
        UpdateValues();
    }
}


void DlgPetCorral::on_btnDeletePet_clicked()
{
    int index = ui->tablePetCorral->currentRow();
    if (index == -1) return;
    petCorral.listPet.removeAt(index);
    UpdateList();
}

