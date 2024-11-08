#ifndef DLGSENDMAIL_H
#define DLGSENDMAIL_H

#include <QDialog>
#include <Protocols/GRoleInventory.h>

enum MAIL_ATTR
{
    _MA_UNREAD=0,
    _MA_ATTACH_OBJ,
    _MA_ATTACH_MONEY,
    _MA_ATTACH_BOTH,
    _MA_PRESERVE,
    _MA_TYPE_NUM,
};

enum MAIL_SENDER_TYPE
{
    _MST_PLAYER=0,
    _MST_NPC,
    _MST_AUCTION,
    _MST_WEB,
    _MST_BATTLE,
    _MST_TYPE_NUM,
};

struct SysSendMail
{
public:
    unsigned int tid = 0;
    int sysid = 33;
    quint8 sys_type = 3;
    int receiver;
    Octets title;
    Octets context;
    GRoleInventory attach_obj;
    unsigned int attach_money;

    void marshal(OctetsStream &os)
    {
        os << tid;
        os << sysid;
        os << sys_type;
        os << receiver;
        os << title;
        os << context;
        attach_obj.marshal(os);
        os << attach_money;
    }
};

namespace Ui {
class DlgSendMail;
}

class DlgSendMail : public QDialog
{
    Q_OBJECT

public:
    explicit DlgSendMail(QWidget *parent = nullptr);
    ~DlgSendMail();

    SysSendMail mail;
    QList<int> ids;
    void MakeMail();
private slots:
    void on_pushButton_7_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::DlgSendMail *ui;
};

#endif // DLGSENDMAIL_H
