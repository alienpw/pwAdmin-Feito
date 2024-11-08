#include "dlgrealmdataeditor.h"
#include "ui_dlgrealmdataeditor.h"

DlgRealmDataEditor::DlgRealmDataEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgRealmDataEditor)
{
    ui->setupUi(this);

    QList<QSpinBox*> lineEdits = findChildren<QSpinBox*>();

    for (QSpinBox* lineEdit : lineEdits) {
        QObject::connect(lineEdit, QOverload<const QString&>::of(&QSpinBox::valueChanged), this, &DlgRealmDataEditor::on_txtLevel_valueChanged);
    }
}

DlgRealmDataEditor::~DlgRealmDataEditor()
{
    delete ui;
}

void DlgRealmDataEditor::Load(QByteArray arr)
{
    OctetsStream os(arr, false, true);
    data.unmarshal(os);
    ui->txtExp->setValue(data.exp);
    ui->txtLevel->setValue(data.level);
    ui->txtR1->setValue(data.reserved1);
    ui->txtR2->setValue(data.reserved2);
}

void DlgRealmDataEditor::on_txtLevel_valueChanged(const QString &arg1)
{
    data.exp = ui->txtExp->value();
    data.level = ui->txtLevel->value();
    data.reserved1 = ui->txtR1->value();
    data.reserved2 = ui->txtR2->value();
}


void DlgRealmDataEditor::on_btnSave_clicked()
{
    OctetsStream os;
    data.marshal(os);
    returnedData = os.data;
    close();
    setResult(QDialog::Accepted);
}


void DlgRealmDataEditor::on_btnClose_clicked()
{
    close();
    setResult(QDialog::Rejected);
}

