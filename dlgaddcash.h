#ifndef DLGADDCASH_H
#define DLGADDCASH_H

#include <QDialog>
#include <Protocols/debugaddcash.h>
#include <game_defs.h>

namespace Ui {
class DlgAddCash;
}

class DlgAddCash : public QDialog
{
    Q_OBJECT

public:
    explicit DlgAddCash(QWidget *parent = nullptr);
    ~DlgAddCash();

    QList<int> usersID;
    int userID;

    void Load(int userID);
    void Load(QList<int> usersID);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::DlgAddCash *ui;
};

#endif // DLGADDCASH_H
