#ifndef DLGFORCEDATAEDITOR_H
#define DLGFORCEDATAEDITOR_H

#include <QDialog>
#include "game_defs.h"
#include "pwadmin.h"
#include <dlgsearchessence.h>

struct force_data
{
    uint id;
    QString name;
    uint color;
};

namespace Ui {
class DlgForceDataEditor;
}

class DlgForceDataEditor : public QDialog
{
    Q_OBJECT

public:
    explicit DlgForceDataEditor(QWidget *parent = nullptr);
    ~DlgForceDataEditor();

    QByteArray returnedData;
    void Load(QByteArray data);
    forcedata_list force;
    QList<force_data> listForce;;

    void UpdateList();
private slots:
    void textChanged(QString str);
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_tableWidget_itemClicked(QTableWidgetItem *item);

    void on_txtOrdemAtual_valueChanged(const QString &arg1);

    void on_btn_search_clicked();

    void on_txtOrdemAtual_valueChanged(int arg1);

    void on_txtOrdem_valueChanged(const QString &arg1);

    void on_txtPrestigio_valueChanged(const QString &arg1);

    void on_txtContribuicao_valueChanged(const QString &arg1);

    void on_btn_add_clicked();

    void on_btn_delete_clicked();

private:
    Ui::DlgForceDataEditor *ui;
};

#endif // DLGFORCEDATAEDITOR_H
