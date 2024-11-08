#ifndef INSTANCES_H
#define INSTANCES_H

#include <QDialog>
#include <QTableWidget>
#include <pwadmin.h>

namespace Ui {
class instances;
}

class Instances : public QDialog
{
    Q_OBJECT

public:
    explicit Instances(QWidget *parent = nullptr);
    ~Instances();

    QMap<QString, QString> maps;
    QStringList listMaps;
    void LoadMaps(QTableWidget *table);

private slots:
    void on_btnCancel_clicked();

    void on_btnSelectMaps_clicked();

private:
    Ui::instances *ui;
};

#endif // INSTANCES_H
