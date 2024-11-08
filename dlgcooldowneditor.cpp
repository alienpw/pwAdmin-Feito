#include "dlgcooldowneditor.h"
#include "ui_dlgcooldowneditor.h"

DlgCooldownEditor::DlgCooldownEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgCooldownEditor)
{
    ui->setupUi(this);
}

DlgCooldownEditor::~DlgCooldownEditor()
{
    delete ui;
}

void DlgCooldownEditor::changeList()
{
    qDebug() << "Editor";
    int index = ui->tableWidget->currentIndex().row();
    if (index == -1) return;
    cooldown_data cd;
    listCooldown[index].id = ui->txt_id->value();
    listCooldown[index].interval = ui->txt_interval->value();
    listCooldown[index].time = ui->txt_time->value() * 1000;
    listCooldown[index].timestamp = ui->txt_timestamp->value();
    ui->tableWidget->setItem(index, 0, new QTableWidgetItem(QString::number(ui->txt_id->value())));
    ui->txt_time_label->setText(Utils::SecondsToTimeFormat(ui->txt_time->value()));
    ui->txt_timestamp_label->setText(QDateTime::fromSecsSinceEpoch(ui->txt_timestamp->value()).toString("dd/MM/yyyy hh:mm:ss"));
    ui->txt_interval_label->setText(Utils::SecondsToTimeFormat(ui->txt_interval->value()));
}

void DlgCooldownEditor::Load(QByteArray arr)
{
    OctetsStream os(arr, false, false);
    int retcode;
    int count;
    os >> retcode;
    os >> count;
    for (int i = 0; i < count; i++)
    {
        cooldown_data data;
        data.unmarshal(&os);
        listCooldown.push_back(data);
        ui->tableWidget->insertRow(i);
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(data.id)));
    }
}

void DlgCooldownEditor::on_tableWidget_cellClicked(int row, int column)
{
    try{
    auto cd = listCooldown.at(row);
    ui->txt_id->setValue(cd.id);
    ui->txt_interval->setValue(cd.interval);
    ui->txt_interval_label->setText(Utils::SecondsToTimeFormat(cd.interval));
    ui->txt_time->setValue(cd.time / 1000);
    ui->txt_time_label->setText(Utils::SecondsToTimeFormat(cd.time / 1000));
    ui->txt_timestamp->setValue(cd.timestamp);
    ui->txt_timestamp_label->setText(Utils::TimestampToLocalDateTime(cd.timestamp));
    }catch(QException e){qDebug() << e.what();}
}


void DlgCooldownEditor::on_btn_slot_add_clicked()
{
    cooldown_data data;
    data.id = 0;
    data.interval = 0;
    data.time = 0;
    data.timestamp = QDateTime::currentSecsSinceEpoch();
    listCooldown.push_back(data);
    int index = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(index);
    ui->tableWidget->setItem(index, 0, new QTableWidgetItem(QString::number(data.id)));
}


void DlgCooldownEditor::on_btn_slot_delete_clicked()
{
    // Get a list of selected rows
    QList<QTableWidgetItem*> selectedItems = ui->tableWidget->selectedItems();

    QSet<int> rowsToRemove;

    // Collect the row numbers
    for(QTableWidgetItem* item : selectedItems) {
        rowsToRemove.insert(item->row());
    }

    // Convert to a list and sort in descending order
    QList<int> sortedRows = rowsToRemove.toList();
    std::sort(sortedRows.begin(), sortedRows.end(), std::greater<int>());

    // Remove rows
    for(int row : sortedRows) {
        ui->tableWidget->removeRow(row);
        listCooldown.removeAt(row);
    }
}


void DlgCooldownEditor::on_pushButton_clicked()
{
    OctetsStream os;
    os.qds->setByteOrder(QDataStream::BigEndian);
    os << -1;
    os << listCooldown.count();
    foreach(auto cd, listCooldown)
        cd.marshal(&os);
    returnedData = os.data;
    close();
    setResult(QDialog::Accepted);
}


void DlgCooldownEditor::on_btnClose_clicked()
{
    close();
    setResult(QDialog::Rejected);
}


void DlgCooldownEditor::on_txt_id_valueChanged(const QString &arg1)
{
    changeList();
}


void DlgCooldownEditor::on_txt_timestamp_valueChanged(const QString &arg1)
{
    changeList();
}


void DlgCooldownEditor::on_txt_interval_valueChanged(const QString &arg1)
{
    changeList();
}


void DlgCooldownEditor::on_txt_time_valueChanged(const QString &arg1)
{
    changeList();
}

