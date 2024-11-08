#include "dlgskillbyclass.h"
#include "ui_dlgskillbyclass.h"
#include <connection.h>

DlgSkillByClass::DlgSkillByClass(int _gender, int _race, QWidget *parent) :
    QDialog(parent), gender(_gender), race(_race),
    ui(new Ui::DlgSkillByClass)
{
    ui->setupUi(this);

    for (int i = 0; i < pwAdmin::getInstance().listClasses.count(); ++i)
    {
        QString name = pwAdmin::getInstance().listClasses[i];
        qDebug() << name;
        QIcon img = Utils::iconClass(i, gender);
        QListWidgetItem* item = new QListWidgetItem(img, name, ui->listWidget);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Unchecked);
    }

    QIcon craftsImg; // Assuming you load the image somewhere else
    QListWidgetItem* craftsItem = new QListWidgetItem(craftsImg, "Crafts", ui->listWidget);
    craftsItem->setFlags(craftsItem->flags() | Qt::ItemIsUserCheckable);
    craftsItem->setCheckState(Qt::Unchecked);

    ui->listWidget->setCurrentRow(race);
    ui->listWidget->item(race)->setCheckState(Qt::Checked);

    ui->tableWidget->setColumnWidth(0, 80);

    ui->tableWidget->hideColumn(2);
}

DlgSkillByClass::~DlgSkillByClass()
{
    delete ui;
}


void DlgSkillByClass::SelectedByClass()
{
    pwAdmin &pw = pwAdmin::getInstance();
    ui->tableWidget->setRowCount(0);
    for(int i = 0; i < ui->listWidget->count(); i++)
    {
        auto item = ui->listWidget->item(i);
        if (item->checkState() == Qt::Checked)
        {
            QMap<int, SkillInfo>::iterator it;
            int row = 0;
            if (i == pwAdmin::getInstance().listClasses.count()) i = 255;
            QList<int> ids = {158, 159, 160, 161, 164, 165, 167, 1402, 1722};
            for(it = pw.listSkillInfo.begin(); it != pw.listSkillInfo.end(); it++)
            {
                if (i == 255 && !ids.contains(it.key()))
                    continue;
                if(it.value().cls != i)
                    continue;
                ui->tableWidget->insertRow(row);
                QTableWidgetItem *icon = new QTableWidgetItem(QIcon(Commands::GetSkillIcon(it.value().icon_name)), pw.listSkillName[it.key()]);
                icon->setToolTip(QString::number(it.value().rank));
                ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(it.key())));
                ui->tableWidget->setItem(row, 1, icon);
                ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(it.value().rank)));
                row++;
            }
        }
    }
}

void DlgSkillByClass::on_tableWidget_itemClicked(QTableWidgetItem *item)
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
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         "</body></html>";
    ui->textBrowser->setHtml(htmlString);
}


void DlgSkillByClass::on_listWidget_itemChanged(QListWidgetItem *item)
{
    SelectedByClass();
}


void DlgSkillByClass::on_pushButton_clicked()
{
    returnedSkills.clear();
    for(auto item : ui->tableWidget->selectedItems())
    {
        if(item->column() == 0)
        {
            int id = ui->tableWidget->item(item->row(), 0)->text().toInt();
            SkillData sd;
            sd.id = id;
            sd.level = 1;
            sd.progress = 0;
            returnedSkills.push_back(sd);
        }
    }
    this->close();
    this->setResult(QDialog::Accepted);
}


void DlgSkillByClass::on_pushButton_2_clicked()
{
    close();
    setResult(QDialog::Rejected);
}


void DlgSkillByClass::on_cbEvil_stateChanged(int arg1)
{
    for(int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        auto item = ui->tableWidget->item(i, 2)->text().toInt();
        if (item < 30 || item > 32)
            ui->tableWidget->setRowHidden(i, arg1 == Qt::Checked ? true : false);
    }
}


void DlgSkillByClass::on_cbGod_stateChanged(int arg1)
{
    for(int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        auto item = ui->tableWidget->item(i, 2)->text().toInt();
        if (item < 20 || item > 22)
            ui->tableWidget->setRowHidden(i, arg1 == Qt::Checked ? true : false);
    }
}


void DlgSkillByClass::on_cbRuna_stateChanged(int arg1)
{
    for(int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        auto item = ui->tableWidget->item(i, 2)->text().toInt();
        if (item < 40)
            ui->tableWidget->setRowHidden(i, arg1 == Qt::Checked ? true : false);
    }
}

