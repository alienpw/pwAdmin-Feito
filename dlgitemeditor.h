#ifndef DLGITEMEDITOR_H
#define DLGITEMEDITOR_H

#include <QDialog>

#include <Structs/item.h>
#include "playereditor.h"
#include "connection.h"

namespace Ui {
class DlgItemEditor;
}

class DlgItemEditor : public QDialog
{
    Q_OBJECT

public:
    explicit DlgItemEditor(QWidget *parent = nullptr);
    ~DlgItemEditor();

    void LoadArmor(armor_essence &essence);
    armor_essence ess;
    new_armor_item newess;
    QByteArray returnedData;

    void LoadNewArmor(new_armor_item &essence);
private slots:
    void on_btn_slot_add_clicked();

    void on_btn_slot_delete_clicked();

    void on_table_slots_cellChanged(int row, int column);

    void on_pushButton_clicked();

    void on_txt_prereq_class_textChanged(const QString &arg1);

    void on_btnSave_clicked();

    void on_table_addons_itemClicked(QTableWidgetItem *item);

    void on_table_addons_cellChanged(int row, int column);

    void on_cbSoul_stateChanged(int arg1);

    void on_cbEngraved_stateChanged(int arg1);

    void on_cbEmbedded_stateChanged(int arg1);

    void on_cbInherited_stateChanged(int arg1);

    void on_btn_addon_add_6_clicked();

    void on_btn_addon_add_5_clicked();

    void on_rdoParam1_clicked();

    void on_rdoParam2_clicked();

    void on_rdoParam3_clicked();

    void on_btnClose_clicked();

private:
    bool loaded = false;
    bool is_new_armor = false;
    Ui::DlgItemEditor *ui;
    void UpdateAddons();
};

#endif // DLGITEMEDITOR_H
