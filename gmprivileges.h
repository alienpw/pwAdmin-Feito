#ifndef GMPRIVILEGES_H
#define GMPRIVILEGES_H

#include <QDialog>

namespace Ui {
class GMPrivileges;
}

class GMPrivileges : public QDialog
{
    Q_OBJECT

public:
    explicit GMPrivileges(int tid, QList<int> lista,QWidget *parent = nullptr);
    ~GMPrivileges();

    QList<QString> list;
    int id;
    QList<int> privileges;
    QList<int> returnPrivileges;
    void Load();

private slots:
    void on_btnCancel_clicked();

    void on_btnConfirm_clicked();

    void on_btn_checkAll_clicked();

    void on_btn_uncheckAll_clicked();

private:
    Ui::GMPrivileges *ui;
};

#endif // GMPRIVILEGES_H
