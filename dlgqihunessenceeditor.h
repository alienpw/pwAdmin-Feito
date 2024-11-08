#ifndef DLGQIHUNESSENCEEDITOR_H
#define DLGQIHUNESSENCEEDITOR_H

#include <QDialog>
#include <Structs/item.h>
#include "dlgclassmask.h"
#include "dlgaddons.h"

namespace Ui {
class DlgQihunEssenceEditor;
}

// Classe principal do editor de essência Qihun
class DlgQihunEssenceEditor : public QDialog
{
    Q_OBJECT

public:
    // Construtor e destrutor
    explicit DlgQihunEssenceEditor(QWidget *parent = nullptr);
    ~DlgQihunEssenceEditor();

    // Método para carregar dados da essência
    void Load(socket_qihun &essence);

    // Membros públicos para armazenar dados da essência e retorno
    socket_qihun ess;
    QByteArray returnedData;

private slots:
    // Slots para manipular eventos de UI
    void on_btnSave_clicked();
    void on_btnClose_clicked();
    void on_table_addons_itemClicked(QTableWidgetItem *item);
    void on_table_addons_cellChanged(int row, int column);
    void on_cbSoul_stateChanged(int arg1);
    void on_cbEngraved_stateChanged(int arg1);
    void on_cbEmbedded_stateChanged(int arg1);
    void on_cbInherited_stateChanged(int arg1);
    void on_rdoParam1_clicked();
    void on_rdoParam2_clicked();
    void on_rdoParam3_clicked();

private:
    // Membros privados
    bool loaded = false; // Flag para indicar se os dados foram carregados
    Ui::DlgQihunEssenceEditor *ui; // Ponteiro para a interface de usuário

    // Método privado para atualizar o número de parâmetros
    void updateParamNum(int paramNum);
    void initializeTable();
    void setTableRow(int row);
    void updateAddonProperty(int row, bool addon_data::*property, int state);
};

#endif // DLGQIHUNESSENCEEDITOR_H
