#ifndef DLGWEAPONEDITOR_H
#define DLGWEAPONEDITOR_H

#include <QDialog>
#include <Structs/item.h>
#include <pwadmin.h>

namespace Ui {
class DlgWeaponEditor;
}

class DlgWeaponEditor : public QDialog
{
    Q_OBJECT

public:
    explicit DlgWeaponEditor(QWidget *parent = nullptr);
    ~DlgWeaponEditor();

    void LoadInfo(weapon_essence &ess);
    weapon_essence ess;
    QByteArray returnedData;
    bool loaded = false;

private slots:
    void UpdateAddons();

    void on_tableWidget_cellClicked(int row, int column);

    void on_tableWidget_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

    void on_btn_slot_add_clicked();

    void on_btn_slot_delete_clicked();

    void on_table_slots_cellChanged(int row, int column);

    void on_btn_Save_2_clicked();

    void on_e0_stateChanged(int arg1);

    void on_tableEspiritoSagrado_cellClicked(int row, int column);

    void on_tableEspiritoSagrado_itemChanged(QTableWidgetItem *item);

    void on_pushButton_clicked();

    void on_btn_Save_clicked();

    void on_tableAddonEspiritoSagrado_itemClicked(QTableWidgetItem *item);

    void on_table_addons_itemClicked(QTableWidgetItem *item);

    void on_table_addons_cellChanged(int row, int column);

    void on_cbSoul_stateChanged(int arg1);

    void on_cbEngraved_stateChanged(int arg1);

    void on_cbEmbedded_stateChanged(int arg1);

    void on_cbInherited_stateChanged(int arg1);

    void on_tableAddonEspiritoSagrado_cellChanged(int row, int column);

    void on_btn_addon_add_clicked();

    void on_btn_addon_add_4_clicked();

    void on_btn_addon_add_6_clicked();

    void on_btn_addon_delete_2_clicked();

    void on_checkBox_stateChanged(int arg1);

    void on_rdo_1_clicked();

    void on_rdo_2_clicked();

    void on_rdo_3_clicked();

    void on_rdoParam1_clicked();

    void on_rdoParam2_clicked();

    void on_rdoParam3_clicked();

private:
    Ui::DlgWeaponEditor *ui;
};

#endif // DLGWEAPONEDITOR_H
