#ifndef DLGSEARCHESSENCE_H
#define DLGSEARCHESSENCE_H

#include <QDialog>
#include <ElementEngine/elistcollection.h>
#include <QTableWidgetItem>

namespace Ui {
class DlgSearchEssence;
}

class DlgSearchEssence : public QDialog
{
    Q_OBJECT

public:
    explicit DlgSearchEssence(QWidget *parent = nullptr);
    ~DlgSearchEssence();

    struct ItemEssence
    {
        int id;
        QString name;
        QIcon icon;
    };

    QVector<eList> lista;
    bool returnOnlyOne = true;
    void PopulateItems(QString containsName = "_ESSENCE");
    QList<ItemEssence> *returnEssences;

private slots:
    void on_pushButton_2_clicked();

    void on_tableWidget_itemClicked(QTableWidgetItem *item);

    void on_comboBox_currentIndexChanged(int index);

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

private:
    Ui::DlgSearchEssence *ui;
};

#endif // DLGSEARCHESSENCE_H
