#include "dlgaddcash.h"
#include "ui_dlgaddcash.h"
#include "pwadmin.h"

DlgAddCash::DlgAddCash(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgAddCash)
{
    ui->setupUi(this);

    userID = -1;

    if (!usersID.isEmpty())
        ui->txtUsuario->setEnabled(false);
}

DlgAddCash::~DlgAddCash()
{
    delete ui;
}

void DlgAddCash::Load(QList<int> usersIDs)
{
    this->userID = -1;
    this->usersID = usersIDs;
}

void DlgAddCash::Load(int id)
{
    userID = id;
    usersID.clear();
    ui->txtUsuario->setValue(id);
    ui->txtUsuario->setEnabled(false);
}

void DlgAddCash::on_pushButton_clicked()
{
    auto &p = pwAdmin::getInstance();
    if (!ui->txtUsuario->isEnabled())
    {
        if (userID > 0)
        {
            if (ui->rdoProtocolo->isChecked())
            {
                DebugAddCash arg;
                arg.userid = userID;
                arg.cash = ui->txtOuro->value();
                OctetsStream oss;
                arg.marshal(oss);
                oss.socket = &p.client;
                auto res2 = oss.SendReturn(opDebugAddCash, false);
                qDebug () << res2.data.toHex();
            }
            else
            {
                QString usecash = QString("'call usecash (%1, %2, 0, %3, 0, %4, 1, @error)'")
                        .arg(userID).arg(p.infos.zoneid).arg(p.infos.aid).arg(ui->txtOuro->value());
                QString mysql = QString("mysql -h%1 -u%2 -p%3 -P%4 -D%5 -e%6")
                        .arg(p.infos.mysql_host)
                        .arg(p.infos.mysql_user)
                        .arg(p.infos.mysql_pass)
                        .arg(p.infos.mysql_port)
                        .arg(p.infos.mysql_base)
                        .arg(usecash);
                Octets o(mysql.toUtf8());
                OctetsStream arg;
                arg.socket = &p.client;
                arg.compact_uint32(1);
                arg << o;
                arg.Send(13);
            }
        }
    }
    else {
        foreach(auto userID, usersID)
        {
            if (userID > 0)
            {
                if (ui->rdoProtocolo->isChecked())
                {
                    DebugAddCash arg;
                    arg.userid = userID;
                    arg.cash = ui->txtOuro->value();
                    OctetsStream oss;
                    arg.marshal(oss);
                    oss.socket = &p.client;
                    auto res2 = oss.SendReturn(opDebugAddCash, false);
                    qDebug () << res2.data.toHex();
                }
                else
                {
                    QString usecash = QString("'call usecash (%1, %2, 0, %3, 0, %4, 1, @error)'")
                            .arg(userID).arg(p.infos.zoneid).arg(p.infos.aid).arg(ui->txtOuro->value());
                    QString mysql = QString("mysql -h%1 -u%2 -p%3 -P%4 -D%5 -e%6")
                            .arg(p.infos.mysql_host)
                            .arg(p.infos.mysql_user)
                            .arg(p.infos.mysql_pass)
                            .arg(p.infos.mysql_port)
                            .arg(p.infos.mysql_base)
                            .arg(usecash);
                    Octets o(mysql.toUtf8());
                    OctetsStream arg;
                    arg.socket = &p.client;
                    arg.compact_uint32(1);
                    arg << o;
                    arg.Send(13);
                }
            }
        }
    }
}


void DlgAddCash::on_pushButton_2_clicked()
{
    close();
}

