#include "dlgaddons.h"
#include "ui_dlgaddons.h"
#include "pwadmin.h"
#include <QRegularExpression>

DlgAddons::DlgAddons(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgAddons)
{
    ui->setupUi(this);

    connect(ui->addon_pedra_addons, &QListWidget::itemClicked, this, &DlgAddons::on_addon_todos_addons_itemClicked);
    connect(ui->addon_refino_addons, &QListWidget::itemClicked, this, &DlgAddons::on_addon_todos_addons_itemClicked);
    connect(ui->addon_gravura_addons, &QListWidget::itemClicked, this, &DlgAddons::on_addon_todos_addons_itemClicked);
    connect(ui->addon_165_addons, &QListWidget::itemClicked, this, &DlgAddons::on_addon_todos_addons_itemClicked);
    connect(ui->addon_astrolabio_addons, &QListWidget::itemClicked, this, &DlgAddons::on_addon_todos_addons_itemClicked);

    pwAdmin &pw = pwAdmin::getInstance();
    foreach(auto addon, pw.listAddonsData)
    {
        auto it = pw.addonsList.find(QString::number(addon.id_addon));
        if(it != pw.addonsList.end())
        {
            if (!list_all.contains(it.value().toInt()))
            {
                list_all.insert(it.value().toInt(), it.key().toInt());
                list_all_idx.push_back(it.value().toInt());
            }
        }
    }
    std::sort(list_all_idx.begin(), list_all_idx.end());
    QMap<int, int>::iterator it2;
    for(it2 = list_all.begin(); it2 != list_all.end(); it2++)
    {
        QString name = it2.key() == 55 ? "[55] Habilidades" : QString("[%1] %2").arg(it2.key()).arg(PlayerEditor::GetAddonName(it2.value(), 0, 0, 0));
        name.replace("0%", "(%)");
        name.replace("0.00", "");
        name.replace("+0", "");
        name.replace(" 0", "");
        name.replace("+", "");
        ui->addon_todos_tipos->addItem(name);
        if (PlayerEditor::IsNewProperty(it2.key()))
        {
            ui->addon_165_tipos->addItem(name);
            list_165_idx.push_back(it2.key());
        }
        if (PlayerEditor::IsEngraveProperty(it2.key()))
        {
            ui->addon_gravura_tipos->addItem(name);
            list_gravura_idx.push_back(it2.key());
        }
        if (PlayerEditor::IsRefineProperty(it2.key()))
        {
            ui->addon_refino_tipos->addItem(name);
            list_refino_idx.push_back(it2.key());
        }
        if (PlayerEditor::IsSharpenerProperty(it2.key()))
        {
            ui->addon_pedra_tipos->addItem(name);
            list_pedra_idx.push_back(it2.key());
        }
        if (PlayerEditor::IsAstrolabeProperty(it2.key()))
        {
            ui->addon_astrolabio_tipos->addItem(name);
            list_astrolabio_idx.push_back(it2.key());
        }
        std::sort(list_165_idx.begin(), list_165_idx.end());
        std::sort(list_gravura_idx.begin(), list_gravura_idx.end());
        std::sort(list_refino_idx.begin(), list_refino_idx.end());
        std::sort(list_pedra_idx.begin(), list_pedra_idx.end());
    }
}



DlgAddons::~DlgAddons()
{
    delete ui;
}

void DlgAddons::on_addon_comum_tipos_itemClicked(QListWidgetItem *item)
{
    int index = ui->addon_todos_tipos->currentRow();
    if (index == -1) return;

}


void DlgAddons::on_addon_todos_tipos_itemClicked(QListWidgetItem *item)
{
    int index = ui->addon_todos_tipos->currentRow();
    if (index == -1) return;
    pwAdmin &pw = pwAdmin::getInstance();
    ui->addon_todos_addons->clear();
    foreach(auto ad, pw.listAddonsData)
    {
        if (ad.propNum == list_all_idx[index])
            ui->addon_todos_addons->addItem(QString("[%1] %2").arg(ad.id_addon).arg(PlayerEditor::GetAddonName(ad.id_addon, ad.arg[0], ad.arg[1], ad.arg[2])));
    }
}

void DlgAddons::on_addon_refino_tipos_itemClicked(QListWidgetItem *item)
{
    int index = ui->addon_refino_tipos->currentRow();
    if (index == -1) return;
    pwAdmin &pw = pwAdmin::getInstance();
    ui->addon_refino_addons->clear();
    foreach(auto addon, pw.listAddonsData)
    {
        if (addon.propNum == list_refino_idx[index])
            ui->addon_refino_addons->addItem(QString("[%1] %2").arg(addon.id_addon).arg(PlayerEditor::GetAddonName(addon.id_addon, addon.arg[0], addon.arg[1], addon.arg[2])));
    }
}


void DlgAddons::on_addon_pedra_tipos_itemClicked(QListWidgetItem *item)
{
    int index = ui->addon_pedra_tipos->currentRow();
    if (index == -1) return;
    pwAdmin &pw = pwAdmin::getInstance();
    ui->addon_pedra_addons->clear();
    foreach(auto addon, pw.listAddonsData)
    {
        if (addon.propNum == list_pedra_idx[index])
            ui->addon_pedra_addons->addItem(QString("[%1] %2").arg(addon.id_addon).arg(PlayerEditor::GetAddonName(addon.id_addon, addon.arg[0], addon.arg[1], addon.arg[2])));
    }
}


void DlgAddons::on_addon_gravura_tipos_itemClicked(QListWidgetItem *item)
{
    int index = ui->addon_gravura_tipos->currentRow();
    if (index == -1) return;
    pwAdmin &pw = pwAdmin::getInstance();
    ui->addon_gravura_addons->clear();
    foreach(auto addon, pw.listAddonsData)
    {
        if (addon.propNum == list_gravura_idx[index])
            ui->addon_gravura_addons->addItem(QString("[%1] %2").arg(addon.id_addon).arg(PlayerEditor::GetAddonName(addon.id_addon, addon.arg[0], addon.arg[1], addon.arg[2])));
    }
}


void DlgAddons::on_addon_astrolabio_tipos_itemClicked(QListWidgetItem *item)
{
    int index = ui->addon_astrolabio_tipos->currentRow();
    if (index == -1) return;
    pwAdmin &pw = pwAdmin::getInstance();
    ui->addon_astrolabio_addons->clear();
    foreach(auto addon, pw.listAddonsData)
    {
        if (addon.propNum == list_astrolabio_idx[index])
            ui->addon_astrolabio_addons->addItem(QString("[%1] %2").arg(addon.id_addon).arg(PlayerEditor::GetAddonName(addon.id_addon, addon.arg[0], addon.arg[1], addon.arg[2])));
    }
}


void DlgAddons::on_addon_165_tipos_itemClicked(QListWidgetItem *item)
{
    int index = ui->addon_165_tipos->currentRow();
    if (index == -1) return;
    pwAdmin &pw = pwAdmin::getInstance();
    ui->addon_165_addons->clear();
    foreach(auto addon, pw.listAddonsData)
    {
        if (addon.propNum == list_165_idx[index])
            ui->addon_165_addons->addItem(QString("[%1] %2").arg(addon.id_addon).arg(PlayerEditor::GetAddonName(addon.id_addon, addon.arg[0], addon.arg[1], addon.arg[2])));
    }
}


void DlgAddons::on_pushButton_clicked()
{
    close();
    setResult(QDialog::Rejected);
}


void DlgAddons::on_pushButton_2_clicked()
{
    close();
    setResult(ui->spinBox->value());
}


void DlgAddons::on_addon_todos_tipos_currentRowChanged(int currentRow)
{
    emit on_addon_todos_tipos_itemClicked(ui->addon_todos_tipos->currentItem());
}


void DlgAddons::on_addon_refino_tipos_currentRowChanged(int currentRow)
{
    emit on_addon_refino_tipos_itemClicked(ui->addon_refino_tipos->currentItem());
}


void DlgAddons::on_addon_pedra_tipos_currentRowChanged(int currentRow)
{
    emit on_addon_pedra_tipos_itemClicked(ui->addon_pedra_tipos->currentItem());
}


void DlgAddons::on_addon_gravura_tipos_currentRowChanged(int currentRow)
{
    emit on_addon_gravura_tipos_itemClicked(ui->addon_gravura_tipos->currentItem());
}


void DlgAddons::on_addon_astrolabio_tipos_currentRowChanged(int currentRow)
{
    emit on_addon_astrolabio_tipos_itemClicked(ui->addon_astrolabio_tipos->currentItem());
}


void DlgAddons::on_addon_165_tipos_currentRowChanged(int currentRow)
{
    emit on_addon_165_tipos_itemClicked(ui->addon_165_tipos->currentItem());
}


void DlgAddons::on_addon_todos_addons_itemClicked(QListWidgetItem *item)
{
    QRegularExpression re("\\[(\\d+)\\]\\s*(.*)");
    QRegularExpressionMatch match = re.match(item->text());
    if (match.hasMatch()) {
        int number = match.captured(1).toInt();
        QString text = match.captured(2);
        ui->label->setText(text);
        ui->spinBox->setValue(number);
    }
}

