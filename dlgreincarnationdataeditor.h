#ifndef DLGREINCARNATIONDATAEDITOR_H
#define DLGREINCARNATIONDATAEDITOR_H

#include <QDialog>
#include <game_defs.h>
#include <utils.h>
#include <QListWidgetItem>

namespace Ui {
class DlgReincarnationDataEditor;
}

class DlgReincarnationDataEditor : public QDialog
{
    Q_OBJECT

public:
    explicit DlgReincarnationDataEditor(QWidget *parent = nullptr);
    ~DlgReincarnationDataEditor();

    QByteArray returnedData;
    void Load(QByteArray arr);

    reincarnation_data data;

private slots:
    void on_listWidget_clicked(const QModelIndex &index);

    void on_btnAdd_clicked();

    void on_btnDelete_clicked();

    void on_btnClose_clicked();

    void on_btnSave_clicked();

    void on_txtLevel_valueChanged(const QString &arg1);

    void on_txtExp_valueChanged(const QString &arg1);

    void on_txtTimestamp_valueChanged(const QString &arg1);

    void on_txtTomeExp_valueChanged(const QString &arg1);

    void on_cbTomeActive_stateChanged(int arg1);

private:
    Ui::DlgReincarnationDataEditor *ui;
};

#endif // DLGREINCARNATIONDATAEDITOR_H
