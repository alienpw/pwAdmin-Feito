#include "dlgsendmail.h"
#include "ui_dlgsendmail.h"
#include <dlgsearchessence.h>
#include <connection.h>

DlgSendMail::DlgSendMail(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgSendMail)
{
    ui->setupUi(this);

    if (ids.size() == 1)
    {
        ui->txtDestino->setValue(ids.at(0));
    } else if (ids.size() > 1)
        ui->txtDestino->setEnabled(false);
}

DlgSendMail::~DlgSendMail()
{
    delete ui;
}

void DlgSendMail::MakeMail()
{
    mail.tid = 0;
    mail.sysid = 33;
    mail.sys_type = _MST_WEB;
    mail.receiver = 1024;
    mail.title = Octets(QString("Teste de titulo"));
    mail.context = Octets(QString("Teste de mensagem grande max 400 letras"));
    mail.attach_money = ui->txt_moedas->value();


}

void DlgSendMail::on_pushButton_7_clicked()
{
    DlgSearchEssence dlg;
    dlg.PopulateItems();
    if (dlg.exec() > 0)
    {
        int id = dlg.result();
        int pile_num_max = Commands::GetItemValue(id, "pile_num_max", "_ESSENCE").toInt();
        uint proc_type = Commands::GetItemValue(id, "proc_type", "_ESSENCE").toUInt();
        ui->txt_id->setValue(id);
        ui->txt_pos->setValue(0);
        ui->txt_count->setValue(1);
        ui->txt_maxcount->setValue(pile_num_max);
        ui->txt_guid1->setValue(0);
        ui->txt_guid2->setValue(0);
        ui->txt_proctype->setValue(proc_type);
        ui->txt_expiredata->setValue(0);
        ui->txt_mask->setValue(0);
        ui->txt_data->setText("");
    }
}


void DlgSendMail::on_pushButton_3_clicked()
{
    foreach(auto id, ids)
    {
        if (ui->txt_id->value() > 0)
        {
            GRoleInventory role;
            role.count = ui->txt_count->value();
            role.data = Octets(QByteArray::fromHex(ui->txt_data->text().toUtf8()));
            role.expire_date = ui->txt_expiredata->value();
            role.guid1 = ui->txt_guid1->value();
            role.guid2 = ui->txt_guid2->value();
            role.id = ui->txt_id->value();
            role.mask = ui->txt_mask->value();
            role.max_count = ui->txt_maxcount->value();
            role.pos = ui->txt_pos->value();
            role.proctype = ui->txt_proctype->value();
            mail.attach_obj = role;
        } else mail.attach_obj = GRoleInventory();
        mail.attach_money = ui->txt_moedas->value();
        mail.context = Octets(QByteArray::fromHex(ui->txtMensagem->toPlainText().toUtf8()));
        mail.receiver = id;
        mail.sys_type = ui->cbTipo->currentIndex();
        mail.sysid = ui->txtSistema->value();
        mail.tid = ui->txtIdEmail->value();
        mail.title = Octets(QByteArray::fromHex(ui->txtTitulo->text().toUtf8()));
        OctetsStream os;
        mail.marshal(os);
        os.socket = &pwAdmin::getInstance().client;
        auto res = os.SendReturn(opSysSendMail, false);
    }
}


void DlgSendMail::on_pushButton_2_clicked()
{
    close();
}

