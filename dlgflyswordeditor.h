#ifndef DLGFLYSWORDEDITOR_H
#define DLGFLYSWORDEDITOR_H

#include <QDialog>
#include <Structs/item.h>
#include <pwadmin.h>

namespace Ui {
class DlgFlyswordEditor;
}

class DlgFlyswordEditor : public QDialog
{
    Q_OBJECT

public:
    explicit DlgFlyswordEditor(QWidget *parent = nullptr);
    ~DlgFlyswordEditor();

    flysword_essence *ess;
    void LoadInfo(flysword_essence *ess);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::DlgFlyswordEditor *ui;
};

#endif // DLGFLYSWORDEDITOR_H
