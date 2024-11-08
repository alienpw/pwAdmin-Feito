#include "dlgqihunessenceeditor.h"
#include "ui_dlgqihunessenceeditor.h"
#include <QBrush>
#include <QTableWidgetItem>

// Construtor da classe
DlgQihunEssenceEditor::DlgQihunEssenceEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgQihunEssenceEditor),
    loaded(false)
{
    ui->setupUi(this);
    initializeTable();
}

// Destrutor da classe
DlgQihunEssenceEditor::~DlgQihunEssenceEditor()
{
    delete ui;
}

// Inicializa a tabela com larguras de coluna predefinidas
void DlgQihunEssenceEditor::initializeTable()
{
    const QVector<int> columnWidths = {52, 290, 52, 52, 52};
    for (int i = 0; i < columnWidths.size(); ++i) {
        ui->table_addons->setColumnWidth(i, columnWidths[i]);
    }
}

// Carrega os dados da essência na interface
void DlgQihunEssenceEditor::Load(socket_qihun &essence)
{
    ess = essence;
    ui->txt_id->setValue(ess.id);
    ui->txt_level->setValue(ess._level);
    ui->txt_moon_phase_level->setValue(ess._moon_phase_level);

    ui->table_addons->setRowCount(0);
    ui->table_addons->setRowCount(ess._total_addon.count());

    for (int i = 0; i < ess._total_addon.count(); ++i) {
        setTableRow(i);
    }
    loaded = true;
}

// Configura uma linha da tabela com os dados do addon
void DlgQihunEssenceEditor::setTableRow(int row)
{
    const auto& addon = ess._total_addon[row];

    auto id = new QTableWidgetItem(QString::number(addon.id_addon));
    id->setForeground(QBrush(Utils::getColorByID(4)));
    ui->table_addons->setItem(row, 0, id);

    auto name = new QTableWidgetItem(QString::fromUtf8(PlayerEditor::GetAddonName(addon.id_addon, addon.arg[0], addon.arg[1], addon.arg[2]).toStdString().c_str()));
    name->setForeground(QBrush(Utils::getColorByID(3)));
    ui->table_addons->setItem(row, 1, name);

    for (int i = 0; i < 3; ++i) {
        int arg = PlayerEditor::isFloatValue(addon.arg[i]) ? PlayerEditor::VisualizeFloatPercent(addon.arg[i]) : addon.arg[i];
        ui->table_addons->setItem(row, i + 2, new QTableWidgetItem(QString::number(arg)));
    }
}

// Manipulador do botão Salvar
void DlgQihunEssenceEditor::on_btnSave_clicked()
{
    ess._level = ui->txt_level->value();
    ess._lock = ui->cb_lock->isChecked() ? (char)1 : (char)0;
    ess._moon_phase_level = ui->txt_moon_phase_level->value();
    ess.id = ui->txt_id->value();
    accept();
}

// Manipulador do botão Fechar
void DlgQihunEssenceEditor::on_btnClose_clicked()
{
    reject();
}

// Manipulador de clique em um item da tabela
void DlgQihunEssenceEditor::on_table_addons_itemClicked(QTableWidgetItem *item)
{
    if (!loaded || item->row() == -1) return;

    const auto& addon = ess._total_addon[item->row()];

    ui->rdoParam1->setChecked(addon.paramNum == 1);
    ui->rdoParam2->setChecked(addon.paramNum == 2);
    ui->rdoParam3->setChecked(addon.paramNum == 3);

    ui->cbEmbedded->setChecked(addon.isEmbedded);
    ui->cbEngraved->setChecked(addon.isEngraved);
    ui->cbInherited->setChecked(addon.isInherited);
    ui->cbSoul->setChecked(addon.isSoul);
}

// Manipulador de mudança de célula na tabela
void DlgQihunEssenceEditor::on_table_addons_cellChanged(int row, int column)
{
    if (!loaded) return;

    auto& addon = ess._total_addon[row];
    int id = ui->table_addons->item(row, 0)->text().toInt();

    if (column >= 0 && column <= 4) {
        if (column == 0) {
            addon.id_addon = id;
        } else if (column >= 2) {
            addon.arg[column - 2] = ui->table_addons->item(row, column)->text().toInt();
        }

        ui->table_addons->item(row, 1)->setText(PlayerEditor::GetAddonName(id, addon.arg[0], addon.arg[1], addon.arg[2]));
    }
}

// Função auxiliar para atualizar propriedades booleanas do addon
void DlgQihunEssenceEditor::updateAddonProperty(int row, bool (addon_data::*property), int state)
{
    if (row >= 0) {
        ess._total_addon[row].*property = (state == Qt::Checked);
    }
}

// Manipuladores para mudanças de estado das caixas de seleção
void DlgQihunEssenceEditor::on_cbSoul_stateChanged(int state)
{
    updateAddonProperty(ui->table_addons->currentRow(), &addon_data::isSoul, state);
}

void DlgQihunEssenceEditor::on_cbEngraved_stateChanged(int state)
{
    updateAddonProperty(ui->table_addons->currentRow(), &addon_data::isEngraved, state);
}

void DlgQihunEssenceEditor::on_cbEmbedded_stateChanged(int state)
{
    updateAddonProperty(ui->table_addons->currentRow(), &addon_data::isEmbedded, state);
}

void DlgQihunEssenceEditor::on_cbInherited_stateChanged(int state)
{
    updateAddonProperty(ui->table_addons->currentRow(), &addon_data::isInherited, state);
}

// Função auxiliar para atualizar o número de parâmetros do addon
void DlgQihunEssenceEditor::updateParamNum(int paramNum)
{
    int index = ui->table_addons->currentRow();
    if (index >= 0) {
        ess._total_addon[index].paramNum = paramNum;
    }
}

// Manipuladores para cliques nos botões de rádio de parâmetros
void DlgQihunEssenceEditor::on_rdoParam1_clicked()
{
    updateParamNum(1);
}

void DlgQihunEssenceEditor::on_rdoParam2_clicked()
{
    updateParamNum(2);
}

void DlgQihunEssenceEditor::on_rdoParam3_clicked()
{
    updateParamNum(3);
}
