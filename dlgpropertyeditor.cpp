#include "dlgpropertyeditor.h"
#include "ui_dlgpropertyeditor.h"

DlgPropertyEditor::DlgPropertyEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgPropertyEditor)
{
    ui->setupUi(this);



    UpdateTxtValues();
}

DlgPropertyEditor::~DlgPropertyEditor()
{
    delete ui;
}

void DlgPropertyEditor::UpdateTxtValues()
{
    if (ui->txtVelAtq->value() > 0)
        ui->txt_velatk->setText(QString("%1 atq/seg.").arg(1 / (ui->txtVelAtq->value() * 0.05), 0, 'f', 2));
    switch (ui->txtAp->value())
    {
    case 99:
        ui->txt_ap->setText("Nenhuma barra de chi");
        break;
    case 199:
        ui->txt_ap->setText("1 barra de chi");
        break;
    case 299:
        ui->txt_ap->setText("2 barras de chi");
        break;
    case 399:
        ui->txt_ap->setText("3 barras de chi");
        break;
    }
}

void DlgPropertyEditor::Load(QByteArray value)
{
    OctetsStream os(value, false, false);
    PlayerProperty p;
    p.unmarshal(&os);
    ui->txtCon->setValue(p.vitality);
    ui->txtDes->setValue(p.agility);
    ui->txtInt->setValue(p.energy);
    ui->txtFor->setValue(p.strength);
    ui->txtHpMax->setText(QString::number(p.max_hp));
    ui->txtMpMax->setText(QString::number(p.max_mp));
    ui->txtAp->setValue(p.max_ap);
    ui->txtHpRegen->setText(QString::number(p.hp_gen));
    ui->txtMpRegen->setText(QString::number(p.mp_gen));
    ui->txtSwim->setValue(p.swim_speed);
    ui->txtWalk->setValue(p.walk_speed);
    ui->txtRun->setValue(p.run_speed);
    ui->txtFly->setValue(p.flight_speed);
    ui->txtAcerto->setText(QString::number(p.attack));
    ui->txtEsquiva->setText(QString::number(p.defense));
    ui->txtDefF->setText(QString::number(p.armor));
    ui->txtDefMetal->setText(QString::number(p.resistence0));
    ui->txtDefMadeira->setText(QString::number(p.resistence1));
    ui->txtDefAgua->setText(QString::number(p.resistence2));
    ui->txtDefFogo->setText(QString::number(p.resistence3));
    ui->txtDefTerra->setText(QString::number(p.resistence4));
    ui->txtAtqMetalMax->setText(QString::number(p.damage_high0));
    ui->txtAtqMadeiraMax->setText(QString::number(p.damage_high1));
    ui->txtAtqAguaMax->setText(QString::number(p.damage_high2));
    ui->txtAtqFogoMax->setText(QString::number(p.damage_high3));
    ui->txtAtqTerraMax->setText(QString::number(p.damage_high4));
    ui->txtAtqMetalMin->setText(QString::number(p.damage_low0));
    ui->txtAtqMadeiraMin->setText(QString::number(p.damage_low1));
    ui->txtAtqAguaMin->setText(QString::number(p.damage_low2));
    ui->txtAtqFogoMin->setText(QString::number(p.damage_low3));
    ui->txtAtqTerraMin->setText(QString::number(p.damage_low4));
    ui->txtAtqFisMin->setText(QString::number(p.damage_low));
    ui->txtAtqFisMax->setText(QString::number(p.damage_high));
    ui->txtAtqMagMin->setText(QString::number(p.damage_magic_low));
    ui->txtAtqMagMax->setText(QString::number(p.damage_magic_high));
    ui->txtVelAtq->setValue(p.attack_speed);
    ui->txtAtqRange->setValue(p.attack_range);
    UpdateTxtValues();
}


void DlgPropertyEditor::on_btnCancel_clicked()
{
    close();
    setResult(QDialog::Rejected);
}


void DlgPropertyEditor::on_btnSave_clicked()
{
    PlayerProperty p;
    p.vitality = ui->txtCon->value();
    p.energy = ui->txtInt->value();
    p.strength = ui->txtFor->value();
    p.agility = ui->txtDes->value();
    p.max_hp = ui->txtHpMax->text().toUInt();
    p.max_mp = ui->txtMpMax->text().toUInt();
    p.hp_gen = ui->txtHpRegen->text().toUInt();
    p.mp_gen = ui->txtMpRegen->text().toUInt();
    p.walk_speed = ui->txtWalk->value();
    p.run_speed = ui->txtRun->value();
    p.swim_speed = ui->txtSwim->value();
    p.flight_speed = ui->txtFly->value();
    p.attack = ui->txtAcerto->text().toUInt();
    p.damage_low = ui->txtAtqFisMin->text().toUInt();
    p.damage_high = ui->txtAtqFisMax->text().toUInt();
    p.attack_speed = ui->txtVelAtq->value();
    p.attack_range = ui->txtAtqRange->value();
    p.damage_low0 = ui->txtAtqMetalMin->text().toUInt();
    p.damage_high0 = ui->txtAtqMetalMax->text().toUInt();
    p.damage_low1 = ui->txtAtqMadeiraMin->text().toUInt();
    p.damage_high1 = ui->txtAtqMadeiraMax->text().toUInt();
    p.damage_low2 = ui->txtAtqAguaMin->text().toUInt();
    p.damage_high2 = ui->txtAtqAguaMax->text().toUInt();
    p.damage_low3 = ui->txtAtqFogoMin->text().toUInt();
    p.damage_high3 = ui->txtAtqFogoMax->text().toUInt();
    p.damage_low4 = ui->txtAtqTerraMin->text().toUInt();
    p.damage_high4 = ui->txtAtqTerraMax->text().toUInt();
    p.damage_magic_low = ui->txtAtqMagMin->text().toUInt();
    p.damage_magic_high = ui->txtAtqMagMax->text().toUInt();
    p.resistence0 = ui->txtDefMetal->text().toUInt();
    p.resistence1 = ui->txtDefMadeira->text().toUInt();
    p.resistence2 = ui->txtDefAgua->text().toUInt();
    p.resistence3 = ui->txtDefFogo->text().toUInt();
    p.resistence4 = ui->txtDefTerra->text().toUInt();
    p.defense = ui->txtDefF->text().toUInt();
    p.armor = ui->txtEsquiva->text().toUInt();
    p.max_ap = ui->txtAp->text().toUInt();

    returnedData.qds->setByteOrder(QDataStream::BigEndian);
    p.marshal(&returnedData);

    close();
    setResult(QDialog::Accepted);
}


void DlgPropertyEditor::on_txtVelAtq_valueChanged(const QString &arg1)
{
    UpdateTxtValues();
}


void DlgPropertyEditor::on_txtAp_valueChanged(const QString &arg1)
{
    UpdateTxtValues();
}

