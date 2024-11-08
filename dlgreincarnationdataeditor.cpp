#include "dlgreincarnationdataeditor.h"
#include "ui_dlgreincarnationdataeditor.h"

DlgReincarnationDataEditor::DlgReincarnationDataEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgReincarnationDataEditor)
{
    ui->setupUi(this);
}

DlgReincarnationDataEditor::~DlgReincarnationDataEditor()
{
    delete ui;
}

void DlgReincarnationDataEditor::Load(QByteArray arr)
{
    OctetsStream os(arr, false, true);
    data.unmarshal(os);
    ui->txtTomeExp->setValue(data.tome_exp);
    ui->cbTomeActive->setCheckState(data.tome_active == 0 ? Qt::Unchecked : Qt::Checked);
    if (data.records.count() > 0)
    {
        foreach(auto r, data.records)
        {
            QString str = QString("Nível: %1\tExperiência: %2").arg(r.level).arg(r.exp);
            ui->listWidget->addItem(str);
        }
    }
}

void DlgReincarnationDataEditor::on_listWidget_clicked(const QModelIndex &index)
{
    if (index.row() == -1) return;
    reincarnation_record r = data.records.at(index.row());
    ui->txtExp->setValue(r.exp);
    ui->txtLevel->setValue(r.level);
    ui->txtTimestamp->setValue(r.timestamp);
    ui->lbTimestamp->setText(Utils::TimestampToLocalDateTime(r.timestamp));
}


void DlgReincarnationDataEditor::on_btnAdd_clicked()
{
    reincarnation_record r;
    r.exp = 0;
    r.level = 100;
    r.timestamp = QDateTime::currentDateTime().toSecsSinceEpoch();
    data.records.push_back(r);
    ui->listWidget->addItem(QString("Nível: %1\tExperiência: %2").arg(r.level).arg(r.exp));
}


void DlgReincarnationDataEditor::on_btnDelete_clicked()
{
    int index = ui->listWidget->currentIndex().row();
    if (index == -1) return;
    data.records.removeAt(index);
    ui->listWidget->takeItem(index);
}


void DlgReincarnationDataEditor::on_btnClose_clicked()
{
    close();
    setResult(QDialog::Rejected);
}


void DlgReincarnationDataEditor::on_btnSave_clicked()
{
    data.tome_active = ui->cbTomeActive->checkState() == 2 ? 1 : 0;
    data.tome_exp = ui->txtTomeExp->value();
    OctetsStream os;
    data.marshal(os);
    returnedData = os.data;
    close();
    setResult(QDialog::Accepted);
}


void DlgReincarnationDataEditor::on_txtLevel_valueChanged(const QString &arg1)
{
    int index = ui->listWidget->currentIndex().row();
    if (index == -1) return;
    reincarnation_record r;
    r.level = ui->txtLevel->value();
    r.exp = ui->txtExp->value();
    r.timestamp = ui->txtTimestamp->value();
    ui->listWidget->currentItem()->setText(QString("Nível: %1\tExperiência: %2").arg(ui->txtLevel->value()).arg(ui->txtExp->value()));
    data.records[index] = r;
}


void DlgReincarnationDataEditor::on_txtExp_valueChanged(const QString &arg1)
{
    int index = ui->listWidget->currentIndex().row();
    if (index == -1) return;
    reincarnation_record r;
    r.level = ui->txtLevel->value();
    r.exp = ui->txtExp->value();
    r.timestamp = ui->txtTimestamp->value();
    ui->listWidget->currentItem()->setText(QString("Nível: %1\tExperiência: %2").arg(ui->txtLevel->value()).arg(ui->txtExp->value()));
    data.records[index] = r;
}


void DlgReincarnationDataEditor::on_txtTimestamp_valueChanged(const QString &arg1)
{
    int index = ui->listWidget->currentIndex().row();
    if (index == -1) return;
    ui->lbTimestamp->setText(Utils::TimestampToLocalDateTime(arg1.toUInt()));
    reincarnation_record r;
    r.level = ui->txtLevel->value();
    r.exp = ui->txtExp->value();
    r.timestamp = ui->txtTimestamp->value();
    data.records[index] = r;
}


void DlgReincarnationDataEditor::on_txtTomeExp_valueChanged(const QString &arg1)
{
    data.tome_exp = ui->txtTomeExp->value();
}


void DlgReincarnationDataEditor::on_cbTomeActive_stateChanged(int arg1)
{
    data.tome_active = arg1 == Qt::Checked ? 1 : 0;
}

