#ifndef DLGMERIDIANDATA_H
#define DLGMERIDIANDATA_H

#include <QDialog>
#include <game_defs.h>

namespace Ui {
class DlgMeridianData;
}

class DlgMeridianData : public QDialog
{
    Q_OBJECT

public:
    explicit DlgMeridianData(QWidget *parent = nullptr);
    ~DlgMeridianData();

    void Load(QByteArray value);
    OctetsStream returnedData;

private slots:
    void on_btnSave_clicked();

    void on_btnSave_2_clicked();

private:
    Ui::DlgMeridianData *ui;
};

#endif // DLGMERIDIANDATA_H
