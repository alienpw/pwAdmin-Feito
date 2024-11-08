#include "dlgflyswordeditor.h"
#include "ui_dlgflyswordeditor.h"

DlgFlyswordEditor::DlgFlyswordEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgFlyswordEditor)
{
    ui->setupUi(this);
}

DlgFlyswordEditor::~DlgFlyswordEditor()
{
    delete ui;
}

void DlgFlyswordEditor::LoadInfo(flysword_essence *ess)
{
    this->ess = ess;
    ui->txt_crc->setText(QString::number(ess->crc));
    ui->txt_cur_time->setText(QString::number(ess->cur_time));
    ui->txt_level->setText(QString::number(ess->level));
    ui->txt_make_flag->setText(QString::number(ess->made.tag_type));
    ui->txt_make_name->setText(ess->made.tag_content.toName());
    ui->txt_max_time->setText(QString::number(ess->max_time));
    ui->txt_require_class->setText(QString::number(ess->require_class));
    ui->txt_require_level->setText(QString::number(ess->require_level));
    ui->txt_speed_increase->setText(QString::number(ess->speed_increase));
    ui->txt_speed_increase2->setText(QString::number(ess->speed_increase2));
    ui->txt_time_per_element->setText(QString::number(ess->time_per_element));

}

void DlgFlyswordEditor::on_pushButton_clicked()
{
    ess->crc = ui->txt_crc->text().toShort();
    ess->cur_time = ui->txt_cur_time->text().toInt();
    ess->level = ui->txt_level->text().toInt();
    ess->made.tag_type = ui->txt_make_flag->text().toInt();
    ess->made.tag_content = Utils::fromUtf8(ui->txt_make_name->text().toUtf8());
    ess->max_time = ui->txt_max_time->text().toInt();
    ess->require_class = ui->txt_require_class->text().toInt();
    ess->require_level = ui->txt_require_level->text().toShort();
    ess->speed_increase = ui->txt_speed_increase->text().toFloat();
    ess->speed_increase2 = ui->txt_speed_increase2->text().toFloat();
    ess->time_per_element = ui->txt_time_per_element->text().toUInt();
    this->close();
    this->setResult(QDialog::Accepted);
}


void DlgFlyswordEditor::on_pushButton_2_clicked()
{
    close();
    setResult(QDialog::Rejected);
}

