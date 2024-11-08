#include "dlgkingdataeditor.h"
#include "ui_dlgkingdataeditor.h"

DlgKingDataEditor::DlgKingDataEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgKingDataEditor)
{
    ui->setupUi(this);
}

DlgKingDataEditor::~DlgKingDataEditor()
{
    delete ui;
}

void DlgKingDataEditor::Load(QByteArray data)
{
    OctetsStream os(data, false, true);
    int is_king, king_expire_time;
    os >> is_king;
    os >> king_expire_time;
    ui->checkBox->setChecked(is_king > 0 ? true : false);
    ui->txtExpire->setValue(king_expire_time);
}

void DlgKingDataEditor::on_btnClose_clicked()
{
    close();
    setResult(QDialog::Rejected);
}


void DlgKingDataEditor::on_btnSave_clicked()
{
    OctetsStream os;
    os << (int)(ui->checkBox->checkState() == Qt::Checked ? 1 : 0);
    os << (int)ui->txtExpire->value();
    returnedData = os.data;
    close();
    setResult(QDialog::Accepted);
}

