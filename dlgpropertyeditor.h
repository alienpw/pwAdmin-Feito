#ifndef DLGPROPERTYEDITOR_H
#define DLGPROPERTYEDITOR_H

#include <QDialog>
#include <game_defs.h>

namespace Ui {
class DlgPropertyEditor;
}

class DlgPropertyEditor : public QDialog
{
    Q_OBJECT

public:
    explicit DlgPropertyEditor(QWidget *parent = nullptr);
    ~DlgPropertyEditor();

    void UpdateTxtValues();
    void Load(QByteArray value);
    OctetsStream returnedData;

private slots:

    void on_btnCancel_clicked();

    void on_btnSave_clicked();

    void on_txtVelAtq_valueChanged(const QString &arg1);

    void on_txtAp_valueChanged(const QString &arg1);

private:
    Ui::DlgPropertyEditor *ui;
};

#endif // DLGPROPERTYEDITOR_H
