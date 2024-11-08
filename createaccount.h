#ifndef CREATEACCOUNT_H
#define CREATEACCOUNT_H

#include <QDialog>
#include <QMessageBox>
#include <game_defs.h>
#include <pwadmin.h>

namespace Ui {
class CreateAccount;
}

class CreateAccount : public QDialog
{
    Q_OBJECT

public:
    explicit CreateAccount(User u, bool edit, QWidget *parent = nullptr);
    ~CreateAccount();

    bool isEdit = false;
    User user;

private slots:
    void on_btnConfirm_clicked();

    void on_btnCancel_clicked();

private:
    Ui::CreateAccount *ui;
};

#endif // CREATEACCOUNT_H
