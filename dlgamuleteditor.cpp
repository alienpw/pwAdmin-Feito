#include "dlgamuleteditor.h"
#include "ui_dlgamuleteditor.h"

DlgAmuletEditor::DlgAmuletEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgAmuletEditor)
{
    ui->setupUi(this);
}

DlgAmuletEditor::~DlgAmuletEditor()
{
    delete ui;
}

void DlgAmuletEditor::LoadInfo(amulet_essence *ess)
{
    this->ess = ess;
    ui->txt_point->setValue(ess->point);
    ui->txt_trigger_percent->setValue(ess->trigger_percent * 100);
}

void DlgAmuletEditor::on_btnSave_clicked()
{
    ess->point = ui->txt_point->value();
    ess->trigger_percent = ui->txt_trigger_percent->value() / 100;
    this->close();
    this->setResult(QDialog::Accepted);
}

void DlgAmuletEditor::on_btnSave_2_clicked()
{
    close();
    setResult(QDialog::Rejected);
}

