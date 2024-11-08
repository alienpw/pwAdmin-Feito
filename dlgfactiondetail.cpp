#include "dlgfactiondetail.h"
#include "ui_dlgfactiondetail.h"
#include <connection.h>

DlgFactionDetail::DlgFactionDetail(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgFactionDetail)
{
    ui->setupUi(this);

    int colunas[14] = {49, 90, 36, 73, 64, 70, 90, 41, 65, 83, 79, 90, 65, 66};
    for(int i = 0; i < 14; i++)
    {
        ui->tabelaMembros->setColumnWidth(i, colunas[i]);
    }
}

DlgFactionDetail::~DlgFactionDetail()
{
    delete ui;
}

void DlgFactionDetail::Load(QList<GFactionInfo> tmp)
{
    this->list = tmp;
    int i = 0;
    foreach(auto f, tmp)
    {
        ui->tableWidget->insertRow(i);
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(f.fid)));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(f.name.toName()));
        i++;
    }
}

void DlgFactionDetail::on_tableWidget_itemClicked(QTableWidgetItem *item)
{
    int row = item->row();
    if (row == -1) return;
    ui->tabelaMembros->setRowCount(0);
    pwAdmin &pw = pwAdmin::getInstance();
    OctetsStream arg;
    arg << -1;
    arg << list.at(row).fid;
    arg.socket = &pw.client;
    auto os = arg.SendReturn(opGetFactionDetail, true);
    GFactionDetail f;
    f.unmarshal(os);
    ui->txtId->setValue(f.fid);
    ui->txtNivel->setValue(f.level);
    ui->txtMarechal->setValue(f.master);
    ui->txtUltOp->setValue(f.last_op_time);
    ui->txtNome->setText(f.name.toName());
    ui->txtDescricao->setPlainText(f.announce.toName());
    ui->txtSysinfo->setText(f.sysinfo.toName());
    if (f.member.size())
    {
        int i = 0;
        foreach(auto m, f.member)
        {
            ui->tabelaMembros->insertRow(i);
            ui->tabelaMembros->setItem(i, 0, new QTableWidgetItem(QString::number(m.roleid)));
            ui->tabelaMembros->setItem(i, 1, new QTableWidgetItem(m.name.toName()));
            ui->tabelaMembros->setItem(i, 2, new QTableWidgetItem(QString::number(m.level)));
            ui->tabelaMembros->setItem(i, 3, new QTableWidgetItem(pw.listClasses[m.occupation]));
            ui->tabelaMembros->setItem(i, 4, new QTableWidgetItem(Utils::GeneroPersonagem((Utils::Gender)m.gender)));
            ui->tabelaMembros->setItem(i, 5, new QTableWidgetItem(pw.listFixedMsg.value(FIXMSG_FCRANK_MASTER + (int)m.froleid - _R_MASTER)));
            ui->tabelaMembros->setItem(i, 6, new QTableWidgetItem(m.nickname.toName()));
            ui->tabelaMembros->setItem(i, 7, new QTableWidgetItem(QString::number((int)m.online_status)));
            ui->tabelaMembros->setItem(i, 8, new QTableWidgetItem(QString::number(m.reputation)));
            ui->tabelaMembros->setItem(i, 9, new QTableWidgetItem(QString::number(m.contrib)));
            ui->tabelaMembros->setItem(i, 10, new QTableWidgetItem(QString::number(m.reincarn_times)));
            ui->tabelaMembros->setItem(i, 11, new QTableWidgetItem(Utils::SecondsToTimeFormat(m.loginday)));
            ui->tabelaMembros->setItem(i, 12, new QTableWidgetItem(QString::number(m.delayexpel)));
            ui->tabelaMembros->setItem(i, 13, new QTableWidgetItem(QString::number(m.expeltime)));
            i++;
        }
    }
}


void DlgFactionDetail::on_pushButton_clicked()
{
    for(int i = 0; i < ui->tabelaMembros->columnCount(); i++)
    {
        qDebug() << ui->tabelaMembros->columnWidth(i);
    }
}


void DlgFactionDetail::on_pushButton_2_clicked()
{        
    DlgSendMail dlg;
    for(int i = 0; i < ui->tabelaMembros->rowCount(); i++)
    {
        int id = ui->tabelaMembros->item(i, 0)->text().toUInt();
        dlg.ids.push_back(id);
    }
    if (dlg.exec())
    {
        qWarning("O email foi enviado para todos os membros do clã!");
    }
}


void DlgFactionDetail::on_pushButton_3_clicked()
{
    DlgSendMail dlg;
    foreach(auto item, ui->tabelaMembros->selectedItems())
    {
        if (item->column() == 0)
        {
            int id = item->text().toUInt();
            dlg.ids.push_back(id);
        }
    }
    if (dlg.exec())
    {
        qWarning("O email foi enviado para os membros selecionados do clã!");
    }
}


void DlgFactionDetail::on_pushButton_5_clicked()
{
    DlgAddCash dlg;
    for(int i = 0; i < ui->tabelaMembros->rowCount(); i++)
    {
        QString name = ui->tabelaMembros->item(i, 1)->text();
        //dlg.names.push_back(name);
    }
    if (dlg.exec())
    {
        qWarning("O ouro foi enviado para todos os membros do clã!");
    }
}


void DlgFactionDetail::on_pushButton_6_clicked()
{
    DlgAddCash dlg;
    foreach(auto item, ui->tabelaMembros->selectedItems())
    {
        if (item->column() == 1)
        {
            QString name = item->text();
            qDebug() << name;
            //dlg.names.push_back(name);
        }
    }
    if (dlg.exec())
    {
        qWarning("O ouro foi enviado para os membros selecionados do clã!");
    }
}

