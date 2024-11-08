#ifndef DLGCOOLDOWNEDITOR_H
#define DLGCOOLDOWNEDITOR_H

#include <QDialog>
#include <game_defs.h>
#include <utils.h>

namespace Ui {
class DlgCooldownEditor;
}

class DlgCooldownEditor : public QDialog
{
    Q_OBJECT

public:
    explicit DlgCooldownEditor(QWidget *parent = nullptr);
    ~DlgCooldownEditor();

    QByteArray returnedData;
    void Load(QByteArray arr);
    QList<cooldown_data> listCooldown;

private slots:
    void changeList();
    void on_tableWidget_cellClicked(int row, int column);

    void on_btn_slot_add_clicked();

    void on_btn_slot_delete_clicked();

    void on_pushButton_clicked();

    void on_btnClose_clicked();

    void on_txt_id_valueChanged(const QString &arg1);

    void on_txt_timestamp_valueChanged(const QString &arg1);

    void on_txt_interval_valueChanged(const QString &arg1);

    void on_txt_time_valueChanged(const QString &arg1);

private:
    Ui::DlgCooldownEditor *ui;
};

#endif // DLGCOOLDOWNEDITOR_H
