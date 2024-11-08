#include "dlgcountrydataeditor.h"
#include "ui_dlgcountrydataeditor.h"

DlgCountryDataEditor::DlgCountryDataEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgCountryDataEditor)
{
    ui->setupUi(this);
}

DlgCountryDataEditor::~DlgCountryDataEditor()
{
    delete ui;
}

void DlgCountryDataEditor::Load(QByteArray data)
{
    OctetsStream os(data, false, true);
    os >> country.country_id;
    os >> country.country_expire_time;
    ui->txtId->setValue(country.country_id);
    ui->txtExpire->setValue(country.country_expire_time);
}

void DlgCountryDataEditor::on_btnClose_clicked()
{
    close();
    setResult(QDialog::Rejected);
}


void DlgCountryDataEditor::on_btnSave_clicked()
{
    OctetsStream os;
    os << country.country_id;
    os << country.country_expire_time;
    returnedData = os.data;
    close();
    setResult(QDialog::Accepted);
}


void DlgCountryDataEditor::on_txtId_valueChanged(const QString &arg1)
{
    country.country_id = arg1.toUInt();
}


void DlgCountryDataEditor::on_txtExpire_valueChanged(const QString &arg1)
{
    country.country_expire_time = arg1.toUInt();
}

