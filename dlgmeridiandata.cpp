#include "dlgmeridiandata.h"
#include "ui_dlgmeridiandata.h"
#include <pwadmin.h>

DlgMeridianData::DlgMeridianData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgMeridianData)
{
    ui->setupUi(this);
}

DlgMeridianData::~DlgMeridianData()
{
    delete ui;
}

void DlgMeridianData::Load(QByteArray value)
{
    meridian_data data;
    data.version = pwAdmin::getInstance().infos.ServerVersion;
    data.unmarshal(new OctetsStream(value, false));
    ui->txtLevel->setText(QString::number(data.meridian_level));
    ui->txtContinuLogin->setText(QString::number(data.continu_login_days));
    ui->txtDeathgate->setText(QString::number(data.deathgate_times));
    ui->txtFreeRefine->setText(QString::number(data.free_refine_times));
    ui->txtLifegate->setText(QString::number(data.lifegate_times));
    ui->txtPaidRefine->setText(QString::number(data.paid_refine_times));
    ui->txtPlayerLogin->setText(QString::number(data.player_login_time));
    ui->txtTrigram1->setText(QString::number(data.trigrams_map[0]));
    ui->txtTrigram2->setText(QString::number(data.trigrams_map[1]));
    ui->txtTrigram3->setText(QString::number(data.trigrams_map[2]));
}

void DlgMeridianData::on_btnSave_clicked()
{
    meridian_data newdata;
    newdata.version = pwAdmin::getInstance().infos.ServerVersion;
    newdata.meridian_level = ui->txtLevel->text().toUInt();
    newdata.continu_login_days = ui->txtContinuLogin->text().toUInt();
    newdata.deathgate_times = ui->txtDeathgate->text().toUInt();
    newdata.free_refine_times = ui->txtFreeRefine->text().toUInt();
    newdata.lifegate_times = ui->txtLifegate->text().toUInt();
    newdata.paid_refine_times = ui->txtPaidRefine->text().toUInt();
    newdata.player_login_time = ui->txtPlayerLogin->text().toUInt();
    newdata.trigrams_map[0] = ui->txtTrigram1->text().toUInt();
    newdata.trigrams_map[1] = ui->txtTrigram2->text().toUInt();
    newdata.trigrams_map[2] = ui->txtTrigram3->text().toUInt();
    newdata.marshal(&returnedData);
    this->close();
    this->setResult(QDialog::Accepted);
}


void DlgMeridianData::on_btnSave_2_clicked()
{
    close();
    setResult(QDialog::Rejected);
}

