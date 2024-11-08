#ifndef DLGARMOREDITOR_H
#define DLGARMOREDITOR_H

#include <QDialog>
#include <Structs/item.h>
#include "dlgclassmask.h"
#include "dlgaddons.h"

namespace Ui {
class DlgArmorEditor;
}

class DlgArmorEditor : public QDialog
{
    Q_OBJECT

public:
    explicit DlgArmorEditor(QWidget *parent = nullptr);
    ~DlgArmorEditor();

    void LoadArmor(armor_essence &ess);
    void LoadWeapon(weapon_essence &ess);
    item_base base;
    armor_essence armor_ess;
    weapon_essence weapon_ess;
    bool loaded = false;
    QByteArray returnedData;
    int whatIs;

private slots:
    void on_tableWidget_cellClicked(int row, int column);    

    void on_tableAddonEspiritoSagrado_itemClicked(QTableWidgetItem *item);

    void on_tableWidget_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

    void on_btn_slot_add_clicked();

    void on_btn_slot_delete_clicked();

    void on_table_slots_cellChanged(int row, int column);

    void on_tableEspiritoSagrado_cellClicked(int row, int column);

    void on_tableEspiritoSagrado_itemChanged(QTableWidgetItem *item);

    void on_pushButton_clicked();

    void on_btn_Save_clicked();

    void on_e0_stateChanged(int arg1);

    void on_table_addons_itemClicked(QTableWidgetItem *item);

    void on_table_addons_cellChanged(int row, int column);

    void on_cbSoul_stateChanged(int arg1);

    void on_cbEngraved_stateChanged(int arg1);

    void on_cbEmbedded_stateChanged(int arg1);

    void on_cbInherited_stateChanged(int arg1);

    void on_tableAddonEspiritoSagrado_cellChanged(int row, int column);

    void on_btn_addon_add_5_clicked();

    void on_btn_addon_add_4_clicked();

    void on_btn_addon_add_6_clicked();

    void on_btn_addon_delete_3_clicked();

    void on_checkBox_stateChanged(int arg1);

    void on_rdo_1_clicked();

    void on_rdo_2_clicked();

    void on_rdo_3_clicked();

    void on_rdoParam1_clicked();

    void on_rdoParam2_clicked();

    void on_rdoParam3_clicked();

    void on_btn_Save_2_clicked();

    void on_pushButton_2_clicked();

    void on_txtEspiritoSagradoId_textChanged(const QString &arg1);

    void on_txtEspiritoSagradoNivel_textChanged(const QString &arg1);

    void on_txtEspiritoSagradoPosicao_cursorPositionChanged(int arg1, int arg2);

    void on_txtEspiritoSagradoPosicao_textChanged(const QString &arg1);

    void on_tableEspiritoSagrado_itemClicked(QTableWidgetItem *item);

private:
    Ui::DlgArmorEditor *ui;
    void UpdateAddons();
};

#endif // DLGARMOREDITOR_H
