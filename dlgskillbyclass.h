#ifndef DLGSKILLBYCLASS_H
#define DLGSKILLBYCLASS_H

#include <QDialog>
#include <utils.h>
#include <QListWidgetItem>
#include <QListWidget>
#include <pwadmin.h>

namespace Ui {
class DlgSkillByClass;
}

class DlgSkillByClass : public QDialog
{
    Q_OBJECT

public:
    explicit DlgSkillByClass(int _gender, int _race, QWidget *parent = nullptr);
    ~DlgSkillByClass();

    void SelectedByClass();
    QList<SkillData> returnedSkills;

private slots:
    void on_tableWidget_itemClicked(QTableWidgetItem *item);

    void on_listWidget_itemChanged(QListWidgetItem *item);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_cbEvil_stateChanged(int arg1);

    void on_cbGod_stateChanged(int arg1);

    void on_cbRuna_stateChanged(int arg1);

private:
    int gender;
    int race;
    Ui::DlgSkillByClass *ui;
};

#endif // DLGSKILLBYCLASS_H
