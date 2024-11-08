#ifndef DLGCOUNTRYDATAEDITOR_H
#define DLGCOUNTRYDATAEDITOR_H

#include <QDialog>
#include "game_defs.h"

struct country_data
{
    int country_id;
    int country_expire_time;
};

namespace Ui {
class DlgCountryDataEditor;
}

class DlgCountryDataEditor : public QDialog
{
    Q_OBJECT

public:
    explicit DlgCountryDataEditor(QWidget *parent = nullptr);
    ~DlgCountryDataEditor();
    QByteArray returnedData;
    void Load(QByteArray data);
    country_data country;
private slots:
    void on_btnClose_clicked();

    void on_btnSave_clicked();

    void on_txtId_valueChanged(const QString &arg1);

    void on_txtExpire_valueChanged(const QString &arg1);

private:
    Ui::DlgCountryDataEditor *ui;
};

#endif // DLGCOUNTRYDATAEDITOR_H
