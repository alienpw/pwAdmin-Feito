#include "instances.h"
#include "ui_instances.h"

Instances::Instances(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::instances)
{
    ui->setupUi(this);
}

Instances::~Instances()
{
    delete ui;
}

void Instances::LoadMaps(QTableWidget *table)
{
    pwAdmin &pw = pwAdmin::getInstance();
    maps = pw.maps;
    for (int i = 0; i < table->rowCount(); i++)
    {
        maps.remove(table->item(i, 0)->text());
    }
    int p = 0;
    QMap<QString, QString>::iterator it;
    for(it = maps.begin(); it != maps.end(); it++)
    {
        ui->tableMapas->insertRow(p);
        QTableWidgetItem *tag = new QTableWidgetItem(it.key());
        tag->setForeground(QBrush(QColor(0, 200, 200)));
        tag->setTextAlignment(Qt::AlignCenter);
        QTableWidgetItem *nome = new QTableWidgetItem(it.value());
        nome->setForeground(QBrush(QColor(255, 180, 0)));
        nome->setTextAlignment(Qt::AlignCenter);
        ui->tableMapas->setItem(p, 0, tag);
        ui->tableMapas->setItem(p, 1, nome);
        p++;
    }
}

void Instances::on_btnCancel_clicked()
{
    close();
    setResult(QDialog::Rejected);
}


void Instances::on_btnSelectMaps_clicked()
{
    foreach(auto sel, ui->tableMapas->selectedItems())
    {
        if(sel->column() == 0)
            listMaps << sel->text();
    }
    close();
    setResult(QDialog::Accepted);
}

