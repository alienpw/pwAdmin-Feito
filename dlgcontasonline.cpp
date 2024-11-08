#include "dlgcontasonline.h"
#include "ui_dlgcontasonline.h"

#include <connection.h>

DlgContasOnline::DlgContasOnline(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgContasOnline)
{
    ui->setupUi(this);

    int columnWidth[] = {63,88,103,37,44,54,140,82,100,106,111,90};
    for(int i = 0; i < ui->tableWidget->columnCount(); i++)
    {
        ui->tableWidget->setColumnWidth(i, columnWidth[i]);
    }
}

DlgContasOnline::~DlgContasOnline()
{
    delete ui;
}

void DlgContasOnline::Load(QList<GMPlayerInfo> tmp, DBGetConsumeInfoRes tmpinfo)
{
    this->list.clear();
    ui->tableWidget->setRowCount(0);
    this->list = tmp;
    this->listInfo = tmpinfo;
    int i = 0;
    foreach(auto p, list)
    {
        ui->tableWidget->insertRow(i);        
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(p.userid)));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString::number(p.roleid)));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(p.name.toName()));
        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(QString::number(p.linkid)));
        ui->tableWidget->setItem(i, 5, new QTableWidgetItem(QString::number(p.localsid)));
        ui->tableWidget->setItem(i, 6, new QTableWidgetItem(QString::number(p.gsid)));
        ui->tableWidget->setItem(i, 7, new QTableWidgetItem(QString::number(p.status)));
        foreach(auto info, listInfo.infos)
        {
            if (info.roleid == p.roleid)
            {                
                ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QString::number(info.level)));
                ui->tableWidget->setItem(i, 8, new QTableWidgetItem(QHostAddress(qToBigEndian(info.login_ip)).toString()));
                ui->tableWidget->setItem(i, 9, new QTableWidgetItem(QString::number(info.cash_add)));
                ui->tableWidget->setItem(i, 10, new QTableWidgetItem(QString::number(info.mall_consumption)));
                ui->tableWidget->setItem(i, 11, new QTableWidgetItem(Utils::SecondsToTimeFormat(info.avg_online_time)));
                break;
            } else continue;
        }
        i++;
    }
}

void DlgContasOnline::on_pushButton_clicked()
{
    Commands::GetRoleListOnline();
    DBGetConsumeInfoArg arg;
    arg.retcode = -1;
    arg.ids = pwAdmin::getInstance().listRoleOnline.keys();
    OctetsStream os;
    arg.marshal(os);
    os.socket = &pwAdmin::getInstance().client;
    auto res = os.SendReturn(opDBGetConsumeInfos, true);
    DBGetConsumeInfoRes r;
    r.unmarshal(res);
    emit Load(pwAdmin::getInstance().listRoleOnline.values(), r);
}


void DlgContasOnline::on_pushButton_3_clicked()
{

}


void DlgContasOnline::on_pushButton_6_clicked()
{
    QList<int> tmp;
    foreach(auto r, ui->tableWidget->selectedItems())
    {
        if (r->row() == 0)
            tmp.push_back(r->text().toInt());
    }
    DlgAddCash dlg;
    dlg.Load(tmp);
    dlg.exec();
}

