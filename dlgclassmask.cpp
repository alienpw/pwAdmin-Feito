#include "dlgclassmask.h"
#include "ui_dlgclassmask.h"

DlgClassMask::DlgClassMask(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgClassMask)
{
    ui->setupUi(this);
    QList<QCheckBox*> checkBoxes = findChildren<QCheckBox*>();

    for (QCheckBox* checkBox : checkBoxes) {
        QObject::connect(checkBox, &QCheckBox::stateChanged, this, &DlgClassMask::checkBoxStateChanged);
    }
}

DlgClassMask::~DlgClassMask()
{
    delete ui;
}

void DlgClassMask::Load(int number)
{
    ui->txt_mask->setValue(number);
    if (number / BARDO > 0)
    {
        number = number % BARDO;
        ui->cb15->setCheckState(Qt::Checked);
    } else ui->cb15->setCheckState(Qt::Unchecked);

    if (number / MACACO > 0)
    {
        number = number % MACACO;
        ui->cb14->setCheckState(Qt::Checked);
    } else ui->cb14->setCheckState(Qt::Unchecked);

    if (number / PALADINO > 0)
    {
        number = number % PALADINO;
        ui->cb13->setCheckState(Qt::Checked);
    } else ui->cb13->setCheckState(Qt::Unchecked);

    if (number / ATIRADORA > 0)
    {
        number = number % ATIRADORA;
        ui->cb12->setCheckState(Qt::Checked);
    } else ui->cb12->setCheckState(Qt::Unchecked);

    if (number / TORMENTADOR > 0)
    {
        number = number % TORMENTADOR;
        ui->cb11->setCheckState(Qt::Checked);
    } else ui->cb11->setCheckState(Qt::Unchecked);

    if (number / RETALHADOR > 0)
    {
        number = number % RETALHADOR;
        ui->cb10->setCheckState(Qt::Checked);
    } else ui->cb10->setCheckState(Qt::Unchecked);

    if (number / MISTICO > 0)
    {
        number = number % MISTICO;
        ui->cb9->setCheckState(Qt::Checked);
    } else ui->cb9->setCheckState(Qt::Unchecked);

    if (number / ARCANO > 0)
    {
        number = number % ARCANO;
        ui->cb8->setCheckState(Qt::Checked);
    } else ui->cb8->setCheckState(Qt::Unchecked);

    if (number / SACERDOTE > 0)
    {
        number = number % SACERDOTE;
        ui->cb7->setCheckState(Qt::Checked);
    } else ui->cb7->setCheckState(Qt::Unchecked);

    if (number / ARQUEIRO > 0)
    {
        number = number % ARQUEIRO;
        ui->cb6->setCheckState(Qt::Checked);
    } else ui->cb6->setCheckState(Qt::Unchecked);

    if (number / MERCENARIO > 0)
    {
        number = number % MERCENARIO;
        ui->cb5->setCheckState(Qt::Checked);
    } else ui->cb5->setCheckState(Qt::Unchecked);

    if (number / BARBARO > 0)
    {
        number = number % BARBARO;
        ui->cb4->setCheckState(Qt::Checked);
    } else ui->cb4->setCheckState(Qt::Unchecked);

    if (number / FEITICEIRA > 0)
    {
        number = number % FEITICEIRA;
        ui->cb3->setCheckState(Qt::Checked);
    } else ui->cb3->setCheckState(Qt::Unchecked);

    if (number / ESPIRITUALISTA > 0)
    {
        number = number % ESPIRITUALISTA;
        ui->cb2->setCheckState(Qt::Checked);
    } else ui->cb2->setCheckState(Qt::Unchecked);

    if (number / MAGO > 0)
    {
        number = number % MAGO;
        ui->cb1->setCheckState(Qt::Checked);
    } else ui->cb1->setCheckState(Qt::Unchecked);

    if (number / GUERREIRO > 0)
    {
        number = number % GUERREIRO;
        ui->cb0->setCheckState(Qt::Checked);
    } else ui->cb0->setCheckState(Qt::Unchecked);
}

void DlgClassMask::on_listWidget_itemChanged(QListWidgetItem *item)
{

}

void DlgClassMask::UpdateList()
{

}

void DlgClassMask::on_pushButton_clicked()
{
    returnValue = ui->txt_mask->value();
    close();
    setResult(QDialog::Accepted);
}

void DlgClassMask::checkBoxStateChanged(int state)
{
    int number = 0;
    if (ui->cb0->checkState() == Qt::Checked)
    {
        number += GUERREIRO;
    }
    if (ui->cb1->checkState() == Qt::Checked)
    {
        number += MAGO;
    }
    if (ui->cb2->checkState() == Qt::Checked)
    {
        number += ESPIRITUALISTA;
    }
    if (ui->cb3->checkState() == Qt::Checked)
    {
        number += FEITICEIRA;
    }
    if (ui->cb4->checkState() == Qt::Checked)
    {
        number += BARBARO;
    }
    if (ui->cb5->checkState() == Qt::Checked)
    {
        number += MERCENARIO;
    }
    if (ui->cb6->checkState() == Qt::Checked)
    {
        number += ARQUEIRO;
    }
    if (ui->cb7->checkState() == Qt::Checked)
    {
        number += SACERDOTE;
    }
    if (ui->cb8->checkState() == Qt::Checked)
    {
        number += ARCANO;
    }
    if (ui->cb9->checkState() == Qt::Checked)
    {
        number += MISTICO;
    }
    if (ui->cb10->checkState() == Qt::Checked)
    {
        number += RETALHADOR;
    }
    if (ui->cb11->checkState() == Qt::Checked)
    {
        number += TORMENTADOR;
    }
    if (ui->cb12->checkState() == Qt::Checked)
    {
        number += ATIRADORA;
    }
    if (ui->cb13->checkState() == Qt::Checked)
    {
        number += PALADINO;
    }
    if (ui->cb14->checkState() == Qt::Checked)
    {
        number += MACACO;
    }
    if (ui->cb15->checkState() == Qt::Checked)
    {
        number += BARDO;
    }
    ui->txt_mask->setValue(number);
}


void DlgClassMask::on_cb13_stateChanged(int arg1)
{

}


void DlgClassMask::on_pushButton_2_clicked()
{
    QList<QCheckBox*> checkBoxes = findChildren<QCheckBox*>();

    for (QCheckBox* checkBox : checkBoxes) {
        checkBox->setCheckState(Qt::Checked);
    }
}


void DlgClassMask::on_pushButton_3_clicked()
{
    QList<QCheckBox*> checkBoxes = findChildren<QCheckBox*>();

    for (QCheckBox* checkBox : checkBoxes) {
        checkBox->setCheckState(Qt::Unchecked);
    }
}


void DlgClassMask::on_pushButton_4_clicked()
{
    close();
}

