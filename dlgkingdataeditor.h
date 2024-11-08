#ifndef DLGKINGDATAEDITOR_H
#define DLGKINGDATAEDITOR_H

#include <QDialog>
#include "game_defs.h"

namespace Ui {
class DlgKingDataEditor;
}

class DlgKingDataEditor : public QDialog
{
    Q_OBJECT

public:
    explicit DlgKingDataEditor(QWidget *parent = nullptr);
    ~DlgKingDataEditor();

    QByteArray returnedData;
    void Load(QByteArray data);

private slots:
    void on_btnClose_clicked();

    void on_btnSave_clicked();

private:
    Ui::DlgKingDataEditor *ui;
};

#endif // DLGKINGDATAEDITOR_H
