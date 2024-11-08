#ifndef DLGEXTRAPROPEDITOR_H
#define DLGEXTRAPROPEDITOR_H

#include <QDialog>
#include <QListWidgetItem>
#include <QStackedWidget>
#include <game_defs.h>
#include <dlgcombobox.h>

namespace Ui {
class DlgExtraPropEditor;
}

class DlgExtraPropEditor : public QDialog
{
    Q_OBJECT

public:
    explicit DlgExtraPropEditor(QWidget *parent = nullptr);
    ~DlgExtraPropEditor();

    void Load(QByteArray arr);
    QStringList str;
    QMap<int, Octets> lista;
    QByteArray returnedData;
private slots:
    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::DlgExtraPropEditor *ui;
};

#endif // DLGEXTRAPROPEDITOR_H
