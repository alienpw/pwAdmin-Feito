#include "dlgextrapropeditor.h"
#include "ui_dlgextrapropeditor.h"

DlgExtraPropEditor::DlgExtraPropEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgExtraPropEditor)
{
    ui->setupUi(this);
}

DlgExtraPropEditor::~DlgExtraPropEditor()
{
    delete ui;
}

void DlgExtraPropEditor::Load(QByteArray arr)
{
    OctetsStream os(arr, false, true);
    int size = os.readByte();
    for (int i = 0; i < size; i++)
    {
        int a = os.readUInt32();
        Octets b = os.readOctet();
        lista.insert(a, b);
        switch(a)
        {
        case	GROLE_STATUS_EXTRAPROP_TOUCH_HALF_TRADE:
        {
            str << "TOUCH_HALF_TRADE";
            break;
            ;}
        case    GROLE_STATUS_EXTRAPROP_DAILY_SIGN_IN:
        {
            str << "DAILY_SIGN_IN";
            break;
            ;}
        case    GROLE_STATUS_EXTRAPROP_GIFTCARD_HALF_REDEEM:
        {
            str << "GIFTCARD_HALF_REDEEM";
            break;
            ;}
        case    GROLE_STATUS_EXTRAPROP_LEADERSHIP:
        {
            str << "LEADERSHIP";
            break;
            ;}
        case    GROLE_STATUS_EXTRAPROP_GENERALCARD_COLLECTION:
        {
            str << "GENERALCARD_COLLECTION";
            break;
            ;}
        case    GROLE_STATUS_EXTRAPROP_FATERING:
        {
            str << "FATERING";
            break;
            ;}
        case    GROLE_STATUS_EXTRAPROP_CLOCK_DATA:
        {
            str << "CLOCK_DATA";
            break;
            ;}
        case    GROLE_STATUS_EXTRAPROP_RAND_MALL_DATA:
        {
            str << "RAND_MALL_DATA";
            break;
            ;}
        case    GROLE_STATUS_EXTRAPROP_WORLD_CONTRIBUTION:
        {
            str << "WORLD_CONTRIBUTION";
            break;
            ;}
        case    GROLE_STATUS_EXTRAPROP_ASTROLABE_EXTERN:
        {
            str << "ASTROLABE_EXTERN";
            break;
            ;}
        }
    }
    ui->listWidget->addItems(str);
}

void DlgExtraPropEditor::on_listWidget_itemClicked(QListWidgetItem *item)
{
    for(int i = 0; i < ui->stackedWidget->count(); i++)
    {
        if (ui->stackedWidget->widget(i)->objectName() == item->text())
        {
            ui->stackedWidget->setCurrentIndex(i);
            continue;
        }
    }
}


void DlgExtraPropEditor::on_pushButton_clicked()
{
    QStringList tmp;
    tmp << "TOUCH_HALF_TRADE" << "DAILY_SIGN_IN" << "GIFTCARD_HALF_REDEEM" << "LEADERSHIP" << "GENERALCARD_COLLECTION" << "FATERING" << "CLOCK_DATA" << "RAND_MALL_DATA" << "WORLD_CONTRIBUTION" << "ASTROLABE_EXTERN";
    foreach(QString s, tmp)
    {
        if (str.contains(s))
        {
            tmp.removeOne(s);
        }
    }
    DlgComboBox dlg("Adicionar Prop. Extras", "Selecionar propriedade extra:", tmp);
    if (dlg.exec() == QDialog::Accepted)
    {
        int value;
        Octets o;
        if (dlg.returnedValue == "TOUCH_HALF_TRADE")
        {
            value = GROLE_STATUS_EXTRAPROP_TOUCH_HALF_TRADE;
            touch_trade val;
            OctetsStream os;
            val.marshal(os);
            o = Octets(os.data);
        }
        else if (dlg.returnedValue == "DAILY_SIGN_IN")
        {
            value = GROLE_STATUS_EXTRAPROP_DAILY_SIGN_IN;
            daily_signin val;
            OctetsStream os;
            val.marshal(os);
            o = Octets(os.data);
        }
        else if (dlg.returnedValue == "GIFTCARD_HALF_REDEEM")
        {
            value = GROLE_STATUS_EXTRAPROP_GIFTCARD_HALF_REDEEM;
            giftcard_redeem val;
            OctetsStream os;
            val.marshal(os);
            o = Octets(os.data);
        }
        else if (dlg.returnedValue == "LEADERSHIP")
        {
            value = GROLE_STATUS_EXTRAPROP_LEADERSHIP;
            OctetsStream os;
            os << 0;
            o = Octets(os.data);
        }
        else if (dlg.returnedValue == "GENERALCARD_COLLECTION")
        {
            value = GROLE_STATUS_EXTRAPROP_GENERALCARD_COLLECTION;
            OctetsStream os;
            os.compact_uint32(0);
            o = Octets(os.data);
        }
        else if (dlg.returnedValue == "FATERING")
        {
            value = GROLE_STATUS_EXTRAPROP_FATERING;
            OctetsStream os;
            os.compact_uint32(0);
            o = Octets(os.data);
        }
        else if (dlg.returnedValue == "CLOCK_DATA")
        {
            value = GROLE_STATUS_EXTRAPROP_CLOCK_DATA;
            OctetsStream os;
            os.compact_uint32(0);
            o = Octets(os.data);
        }
        else if (dlg.returnedValue == "RAND_MALL_DATA")
        {
            value = GROLE_STATUS_EXTRAPROP_RAND_MALL_DATA;
            OctetsStream os;
            os.compact_uint32(0);
            o = Octets(os.data);
        }
        else if (dlg.returnedValue == "WORLD_CONTRIBUTION")
        {
            value = GROLE_STATUS_EXTRAPROP_WORLD_CONTRIBUTION;
            world_contribution val;
            OctetsStream os;
            val.marshal(os);
            o = Octets(os.data);
        }
        else if (dlg.returnedValue == "ASTROLABE_EXTERN")
        {
            value = GROLE_STATUS_EXTRAPROP_ASTROLABE_EXTERN;
            astrolabe_extern val;
            OctetsStream os;
            val.marshal(os);
            o = Octets(os.data);
        }
        str.push_back(dlg.returnedValue);
        ui->listWidget->addItem(dlg.returnedValue);
        lista.insert(value, o);
    }
}


void DlgExtraPropEditor::on_pushButton_2_clicked()
{
    str.removeOne(ui->listWidget->selectedItems()[0]->text());
    ui->listWidget->takeItem(ui->listWidget->currentRow());
}


void DlgExtraPropEditor::on_pushButton_3_clicked()
{
    QMap<int, Octets>::iterator it;
    OctetsStream os;
    os.compact_uint32(ui->listWidget->count());
    for(it = lista.begin(); it != lista.end(); it++)
    {
        os << it.key();
        os << it.value();
    }
    returnedData = Octets(os.data).value;
    close();
    setResult(QDialog::Accepted);
}


void DlgExtraPropEditor::on_pushButton_4_clicked()
{
    close();
    setResult(QDialog::Rejected);
}

