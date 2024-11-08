#ifndef DLGADDONS_H
#define DLGADDONS_H

#include <QDialog>
#include <QListWidgetItem>

namespace Ui {
class DlgAddons;
}

class DlgAddons : public QDialog
{
    Q_OBJECT

public:
    explicit DlgAddons(QWidget *parent = nullptr);
    ~DlgAddons();

    QMap<int, int> list_all;
    QList<int> list_all_idx;
    QList<int> list_refino_idx;
    QList<int> list_pedra_idx;
    QList<int> list_gravura_idx;
    QList<int> list_165_idx;
    QList<int> list_astrolabio_idx;

private slots:
    void on_addon_comum_tipos_itemClicked(QListWidgetItem *item);

    void on_addon_todos_tipos_itemClicked(QListWidgetItem *item);

    void on_addon_refino_tipos_itemClicked(QListWidgetItem *item);

    void on_addon_pedra_tipos_itemClicked(QListWidgetItem *item);

    void on_addon_gravura_tipos_itemClicked(QListWidgetItem *item);

    void on_addon_astrolabio_tipos_itemClicked(QListWidgetItem *item);

    void on_addon_165_tipos_itemClicked(QListWidgetItem *item);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_addon_todos_tipos_currentRowChanged(int currentRow);

    void on_addon_refino_tipos_currentRowChanged(int currentRow);

    void on_addon_pedra_tipos_currentRowChanged(int currentRow);

    void on_addon_gravura_tipos_currentRowChanged(int currentRow);

    void on_addon_astrolabio_tipos_currentRowChanged(int currentRow);

    void on_addon_165_tipos_currentRowChanged(int currentRow);

    void on_addon_todos_addons_itemClicked(QListWidgetItem *item);

private:
    Ui::DlgAddons *ui;
};

#endif // DLGADDONS_H
