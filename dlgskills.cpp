#include "dlgskills.h"
#include "ui_dlgskills.h"
#include <connection.h>

int gender, race;
bool loaded = false;

DlgSkills::DlgSkills(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgSkills)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnWidth(0, 60);
    ui->tableWidget->setColumnWidth(1, 200);
    ui->tableWidget->setColumnWidth(2, 60);
    ui->tableWidget->setColumnWidth(3, 60);
}

DlgSkills::~DlgSkills()
{
    delete ui;
}

void DlgSkills::on_pushButton_2_clicked()
{
    SkillList list;
    list.count = listSkill.count();
    list.listSkills = listSkill;
    returnedOctets.setData(QByteArray(), false, false);
    list.marshal(&returnedOctets);
    this->close();
    this->setResult(QDialog::Accepted);
}


void DlgSkills::on_tableWidget_itemClicked(QTableWidgetItem *item)
{
    int id = ui->tableWidget->item(item->row(), 0)->text().toInt();
    QString htmlString = QString(R"(
        <html>
            <style>
                body {margin: 0; padding: 0px; color:#ffffff; background-color:#101010; font-size:11px; font-family: verdana;	line-height:1.15em;} p, ul {margin:0; padding:0px;}
                ul {margin-left:20px; padding:1px;list-style-type: disc;}
            </style>
            <body>
                <img src="%1" width="32" height="32"/>
                <font color="#FF6000"><b>%2</b></font>
            </body>
        </html>
    )").arg(Utils::iconToBase64(ui->tableWidget->item(item->row(), 1)->icon())).arg(Utils::FormatColorText(pwAdmin::getInstance().listSkillDesc[id]));
    ui->textBrowser->setHtml(htmlString);
}

void DlgSkills::LoadSkills(Octets o, int _gender, int _race)
{
    gender = _gender;
    race = _race;
    pwAdmin &pw = pwAdmin::getInstance();
    OctetsStream os(o.value, false, false);
    SkillList list;
    list.unmarshal(&os);
    listSkill.append(list.listSkills);
    UpdateSkillList();
    loaded = true;
}

void DlgSkills::UpdateSkillList()
{
    ui->tableWidget->setRowCount(0);
    pwAdmin &pw = pwAdmin::getInstance();
    int i = 0;
    for(auto l : listSkill)
    {
        ui->tableWidget->insertRow(i);
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(l.id)));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QIcon(Commands::GetSkillIcon(pw.listSkillInfo[l.id].icon_name)), pw.listSkillName[l.id]));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QString::number(l.progress)));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QString::number(l.level)));
        i++;
    }
}

void DlgSkills::on_btn_add_by_class_clicked()
{
    DlgSkillByClass s(gender, race);
    if(s.exec() == QDialog::Accepted)
    {
        listSkill.append(s.returnedSkills);
        UpdateSkillList();
    }
}



void DlgSkills::on_btn_remove_selected_clicked()
{
    // Get a list of selected rows
    QList<QTableWidgetItem*> selectedItems = ui->tableWidget->selectedItems();

    QSet<int> rowsToRemove;

    // Collect the row numbers
    for(QTableWidgetItem* item : selectedItems) {
        rowsToRemove.insert(item->row());
    }

    // Convert to a list and sort in descending order
    QList<int> sortedRows = rowsToRemove.toList();
    std::sort(sortedRows.begin(), sortedRows.end(), std::greater<int>());

    // Remove rows
    for(int row : sortedRows) {
        ui->tableWidget->removeRow(row);
        listSkill.removeAt(row);
    }
}


void DlgSkills::on_btn_max_level_clicked()
{
    pwAdmin &pw = pwAdmin::getInstance();
    foreach(auto sel, ui->tableWidget->selectedItems())
    {
        int idx = sel->row();
        listSkill[idx].level = pw.listSkillInfo[listSkill[idx].id].max_level;
    }
    UpdateSkillList();
}


void DlgSkills::on_tableWidget_cellChanged(int row, int column)
{
    if (!loaded)
        return;
    if (row == -1 || column == -1)
        return;
    int id = ui->tableWidget->item(row, 0)->text().toUInt();
    switch(column)
    {
    case 0:
    {
        listSkill[row].id = id;
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QIcon(Commands::GetSkillIcon(pwAdmin::getInstance().listSkillInfo[id].icon_name)), pwAdmin::getInstance().listSkillName[id]));
        break;
    }
    case 2:
    {
        listSkill[row].progress = ui->tableWidget->item(row, 2)->text().toUInt();
        break;
    }
    case 3:
    {
        int level = ui->tableWidget->item(row, 3)->text().toUInt();
        if (level > pwAdmin::getInstance().listSkillInfo[id].max_level)
        {
            level = pwAdmin::getInstance().listSkillInfo[id].max_level;
            ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(level)));
        }
        listSkill[row].level = level;
        break;
    }
    }

}


void DlgSkills::on_tableWidget_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{

}


void DlgSkills::on_pushButton_clicked()
{
    if (ui->lineEdit->text().isEmpty())
    {
        for (int i = 0; i < ui->tableWidget->rowCount(); ++i) {
            ui->tableWidget->setRowHidden(i, false);
        }
    } else
    {
        auto items = ui->tableWidget->findItems(ui->lineEdit->text(), Qt::MatchContains);
        QSet<int> rows;
        foreach (QTableWidgetItem* item, items) {
            rows.insert(item->row());
        }
        for (int i = 0; i < ui->tableWidget->rowCount(); ++i) {
            if (!rows.contains(i)) {
                ui->tableWidget->setRowHidden(i, true);
            }
        }
    }
}


void DlgSkills::on_pushButton_3_clicked()
{
    close();
}

