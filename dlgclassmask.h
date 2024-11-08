#ifndef DLGCLASSMASK_H
#define DLGCLASSMASK_H

#include <QDialog>
#include "pwadmin.h"
#include "QListWidgetItem"

enum
{
    GUERREIRO		= 1,
    MAGO			= 2,
    ESPIRITUALISTA	= 4,
    FEITICEIRA		= 8,
    BARBARO         = 16,
    MERCENARIO		= 32,
    ARQUEIRO		= 64,
    SACERDOTE		= 128,
    ARCANO          = 256,
    MISTICO         = 512,
    RETALHADOR		= 1024,
    TORMENTADOR		= 2048,
    ATIRADORA       = 4096,
    PALADINO        = 8192,
    MACACO          = 16384,
    BARDO           = 32768
};

namespace Ui {
class DlgClassMask;
}

class DlgClassMask : public QDialog
{
    Q_OBJECT

public:
    explicit DlgClassMask( QWidget *parent = nullptr);
    ~DlgClassMask();

    void Load(int number);
    QList<int> list;
    void UpdateList();
    int returnValue;

private slots:
    void checkBoxStateChanged(int state);
    void on_listWidget_itemChanged(QListWidgetItem *item);

    void on_pushButton_clicked();

    void on_cb13_stateChanged(int arg1);

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::DlgClassMask *ui;
};

#endif // DLGCLASSMASK_H
