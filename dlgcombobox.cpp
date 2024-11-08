#include "dlgcombobox.h"
#include "ui_dlgcombobox.h"

DlgComboBox::DlgComboBox(QString title, QString text, QStringList cbList, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgComboBox)
{
    ui->setupUi(this);
    this->setWindowTitle(title);
    ui->label->setText(text);
    ui->comboBox->addItems(cbList);
}

DlgComboBox::~DlgComboBox()
{
    delete ui;
}

void DlgComboBox::on_pushButton_clicked()
{
    if (ui->comboBox->currentText().length() <= 0 || ui->comboBox->count() <= 0)
        return;
    returnedValue = ui->comboBox->currentText();
    close();
    setResult(QDialog::Accepted);
}

