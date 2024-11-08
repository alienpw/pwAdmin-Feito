#ifndef DLGSKILLS_H
#define DLGSKILLS_H

#include <QDialog>
#include <Structs/skill.h>
#include <pwadmin.h>
#include "dlgskillbyclass.h"
#include "QTableWidgetItem"
#include "utils.h"

namespace Ui {
class DlgSkills;
}

class DlgSkills : public QDialog
{
    Q_OBJECT

public:
    explicit DlgSkills(QWidget *parent = nullptr);
    ~DlgSkills();
    QList<SkillData> listSkill;
    void LoadSkills(Octets o, int _gender, int _race);
    void LoadSkillsInfos();
    void UpdateSkillList();
    OctetsStream returnedOctets;
private slots:
    void on_pushButton_2_clicked();

    void on_tableWidget_itemClicked(QTableWidgetItem *item);

    void on_btn_add_by_class_clicked();

    void on_btn_remove_selected_clicked();

    void on_btn_max_level_clicked();

    void on_tableWidget_cellChanged(int row, int column);

    void on_tableWidget_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::DlgSkills *ui;
};

#endif // DLGSKILLS_H
