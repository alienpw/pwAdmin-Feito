#include "dlgforcedataeditor.h"
#include "ui_DlgForceDataEditor.h"

DlgForceDataEditor::DlgForceDataEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgForceDataEditor)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnWidth(0, 71);

    QList<QLineEdit*> lineEdits = findChildren<QLineEdit*>();

    for (QLineEdit* lineEdit : lineEdits) {
        QObject::connect(lineEdit, &QLineEdit::textChanged, this, &DlgForceDataEditor::textChanged);
    }
}

DlgForceDataEditor::~DlgForceDataEditor()
{
    delete ui;
}

void DlgForceDataEditor::textChanged(QString str)
{
    int index = ui->tableWidget->currentIndex().row();
    if (index == -1) return;
    auto f = force.list.at(index);
    f.reserved1 = ui->txtR1->text().toUInt();
    f.reserved2 = ui->txtR2->text().toUInt();
    f.reserved3 = ui->txtR3->text().toUInt();
    f.reserved4 = ui->txtR4->text().toUInt();
    f.reserved5 = ui->txtR5->text().toUInt();
    f.reserved6 = ui->txtR6->text().toUInt();
    f.reserved7 = ui->txtR7->text().toUInt();
    force.list[index] = f;
}

void DlgForceDataEditor::on_pushButton_clicked()
{
    OctetsStream os;
    force.marshal(os, pwAdmin::getInstance().infos.ServerVersion);
    returnedData = os.data;
    close();
    setResult(QDialog::Accepted);
}


void DlgForceDataEditor::on_pushButton_2_clicked()
{
    close();
    setResult(QDialog::Rejected);
}

void DlgForceDataEditor::Load(QByteArray data)
{
    OctetsStream os(data, false, true);
    force.unmarshal(os, pwAdmin::getInstance().infos.ServerVersion);
    auto elc = pwAdmin::getInstance().elc;
    for (int l = 0; l < elc->Lists.length(); l++)
    {

            if (!elc->Lists[l].listName.contains("FORCE_CONFIG"))
                continue;
            int pos = -1;
            for (int i = 0; i < elc->Lists[l].elementFields.length(); i++)
            {
                if (elc->Lists[l].elementFields[i] == "Name")
                {
                    pos = i;
                }
                if (pos != -1) { break; }
            }

            for (int e = 0; e < elc->Lists[l].elementValues.length(); e++)
            {
                if (elc->Lists[l].elementFields[0] == "ID")
                {
                    force_data data;
                    data.id = elc->GetValue(l, e, 0).toUInt();
                    data.name = elc->GetValue(l, e, pos);
                    data.color = elc->GetValue(l, e, 3).toUInt();
                    listForce.push_back(data);
                }
            }

    }

    ui->txtOrdemAtual->setValue(force.cur_force_id);
    foreach(auto f, listForce)
    {
        if (f.id == (uint)force.cur_force_id)
        {
            ui->txtOrdemAtualLabel->setText(f.name);
        }
    }
    if (force.list.count() > 0)
    {
        UpdateList();
    }

}

void DlgForceDataEditor::on_tableWidget_itemClicked(QTableWidgetItem *item)
{
    int index = item->row();
    if (index == -1) return;
    auto f = force.list.at(index);
    ui->txtOrdem->setValue(f.force_id);
    foreach(auto ff, listForce)
    {
        if (ff.id == (uint)f.force_id)
        {
            ui->txtOrdemLabel->setText(ff.name);
        }
    }
    ui->txtContribuicao->setValue(f.contribution);
    ui->txtPrestigio->setValue(f.reputation);
    ui->txtR1->setText(QString::number(f.reserved1));
    ui->txtR2->setText(QString::number(f.reserved2));
    ui->txtR3->setText(QString::number(f.reserved3));
    ui->txtR4->setText(QString::number(f.reserved4));
    ui->txtR5->setText(QString::number(f.reserved5));
    ui->txtR6->setText(QString::number(f.reserved6));
    ui->txtR7->setText(QString::number(f.reserved7));
}


void DlgForceDataEditor::on_txtOrdemAtual_valueChanged(const QString &arg1)
{
    foreach(auto ff, listForce)
    {
        if (ff.id == arg1.toUInt())
        {
            ui->txtOrdemAtualLabel->setText(ff.name);
        }
    }
    force.cur_force_id = arg1.toInt();
}


void DlgForceDataEditor::on_btn_search_clicked()
{
    DlgSearchEssence dlg;
    dlg.PopulateItems("FORCE_CONFIG");
    dlg.returnOnlyOne = true;
    ui->txtOrdemAtual->setValue(dlg.exec());
}


void DlgForceDataEditor::on_txtOrdemAtual_valueChanged(int arg1)
{
    foreach(auto ff, listForce)
    {
        if (ff.id == (uint)arg1)
        {
            ui->txtOrdemAtualLabel->setText(ff.name);
        }
    }
    force.cur_force_id = arg1;
}


void DlgForceDataEditor::on_txtOrdem_valueChanged(const QString &arg1)
{
    int index = ui->tableWidget->currentIndex().row();
    if (index == -1) return;
    auto f = force.list.at(index);
    f.force_id = arg1.toUInt();
    ui->tableWidget->setItem(index, 0, new QTableWidgetItem(arg1));
    foreach(auto ff, listForce)
    {
        if (ff.id == arg1.toUInt())
        {
            ui->txtOrdemLabel->setText(ff.name);
            ui->tableWidget->setItem(index, 1, new QTableWidgetItem(ff.name));
        }
    }
    force.list[index] = f;
}


void DlgForceDataEditor::on_txtPrestigio_valueChanged(const QString &arg1)
{
    int index = ui->tableWidget->currentIndex().row();
    if (index == -1) return;
    auto f = force.list.at(index);
    f.reputation = arg1.toUInt();
    force.list[index] = f;
}


void DlgForceDataEditor::on_txtContribuicao_valueChanged(const QString &arg1)
{
    int index = ui->tableWidget->currentIndex().row();
    if (index == -1) return;
    auto f = force.list.at(index);
    f.contribution = arg1.toUInt();
    force.list[index] = f;
}


void DlgForceDataEditor::on_btn_add_clicked()
{
    forcedata data;
    data.force_id = 0;
    data.contribution = 0;
    data.reputation = 0;
    data.reserved1 = 0;
    data.reserved2 = 0;
    data.reserved3 = 0;
    data.reserved4 = 0;
    data.reserved5 = 0;
    data.reserved6 = 0;
    data.reserved7 = 0;
    force.list.push_back(data);
    UpdateList();
}

void DlgForceDataEditor::UpdateList()
{
    ui->tableWidget->setRowCount(0);
    int i = 0;
    foreach(auto ff, force.list)
    {
        ui->tableWidget->insertRow(i);
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(ff.force_id)));
        foreach(auto f, listForce)
        {
            if (f.id == (uint)ff.force_id)
            {
                QTableWidgetItem *item = new QTableWidgetItem(f.name);
                ui->tableWidget->setItem(i, 1, item);
            }
        }
        i++;
    }
}


void DlgForceDataEditor::on_btn_delete_clicked()
{
    int index = ui->tableWidget->currentIndex().row();
    if (index == -1) return;
    force.list.removeAt(index);
    UpdateList();
}

