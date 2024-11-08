#ifndef DLGAMULETEDITOR_H
#define DLGAMULETEDITOR_H

#include <QDialog>
#include <pwadmin.h>
#include <Structs/item.h>

namespace Ui {
class DlgAmuletEditor;
}

class DlgAmuletEditor : public QDialog
{
    Q_OBJECT

public:
    explicit DlgAmuletEditor(QWidget *parent = nullptr);
    ~DlgAmuletEditor();

    void LoadInfo(amulet_essence *ess);
    amulet_essence *ess;

private slots:
    void on_btnSave_clicked();

    void on_btnSave_2_clicked();

private:
    Ui::DlgAmuletEditor *ui;
};

#endif // DLGAMULETEDITOR_H
