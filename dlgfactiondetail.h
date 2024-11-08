#ifndef DLGFACTIONDETAIL_H
#define DLGFACTIONDETAIL_H

#include <QDialog>
#include <QTableWidgetItem>
#include <Protocols/GFactionDetail.h>
#include <dlgsendmail.h>
#include <dlgaddcash.h>

namespace Ui {
class DlgFactionDetail;
}

class DlgFactionDetail : public QDialog
{
    Q_OBJECT

public:
    explicit DlgFactionDetail(QWidget *parent = nullptr);
    ~DlgFactionDetail();

    QList<GFactionInfo> list;
    void Load(QList<GFactionInfo> tmp);

private slots:
    void on_tableWidget_itemClicked(QTableWidgetItem *item);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::DlgFactionDetail *ui;
};

#endif // DLGFACTIONDETAIL_H
