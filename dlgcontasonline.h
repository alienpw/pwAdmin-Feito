#ifndef DLGCONTASONLINE_H
#define DLGCONTASONLINE_H

#include <QDialog>
#include <game_defs.h>
#include <Protocols/GetConsumeInfo.h>
#include <QHostAddress>
#include <QtEndian>
#include <utils.h>

namespace Ui {
class DlgContasOnline;
}

class DlgContasOnline : public QDialog
{
    Q_OBJECT

public:
    explicit DlgContasOnline(QWidget *parent = nullptr);
    ~DlgContasOnline();

    QList<GMPlayerInfo> list;
    DBGetConsumeInfoRes listInfo;
    void Load(QList<GMPlayerInfo> tmp, DBGetConsumeInfoRes tmpinfo);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::DlgContasOnline *ui;
};

#endif // DLGCONTASONLINE_H
