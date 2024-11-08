#ifndef DLGREALMDATAEDITOR_H
#define DLGREALMDATAEDITOR_H

#include <QDialog>
#include <game_defs.h>
#include <utils.h>

namespace Ui {
class DlgRealmDataEditor;
}

class DlgRealmDataEditor : public QDialog
{
    Q_OBJECT

public:
    explicit DlgRealmDataEditor(QWidget *parent = nullptr);
    ~DlgRealmDataEditor();

    QByteArray returnedData;
    void Load(QByteArray arr);
    realm_data data;

private slots:
    void on_txtLevel_valueChanged(const QString &arg1);

    void on_btnSave_clicked();

    void on_btnClose_clicked();

private:
    Ui::DlgRealmDataEditor *ui;
};

#endif // DLGREALMDATAEDITOR_H
