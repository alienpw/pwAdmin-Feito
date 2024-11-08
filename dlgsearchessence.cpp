#include "dlgsearchessence.h"
#include "ui_dlgsearchessence.h"
#include <connection.h>

static bool loaded = false;

DlgSearchEssence::DlgSearchEssence(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgSearchEssence)
{
    ui->setupUi(this);
    ui->comboBox->clear();
    lista.clear();
    returnOnlyOne = true;
    loaded = false;
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnWidth(0, 60);
    ui->comboBox->setCurrentIndex(-1);
    if (returnOnlyOne)
        ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
}

DlgSearchEssence::~DlgSearchEssence()
{
    delete ui;
}

void DlgSearchEssence::PopulateItems(QString containsName)
{
    for(int i = 0; i < pwAdmin::getInstance().elc->Lists.count(); i++)
    {
        if (!pwAdmin::getInstance().elc->Lists.at(i).listName.contains(containsName))
            continue;
        ui->comboBox->addItem(pwAdmin::getInstance().elc->Lists.at(i).listName);
        lista.append(pwAdmin::getInstance().elc->Lists.at(i));
    }
    loaded = true;
    emit on_comboBox_currentIndexChanged(0);
}


void DlgSearchEssence::on_comboBox_currentIndexChanged(int l)
{
    if (!loaded)
        return;

    ui->tableWidget->setRowCount(0);

    int posName = -1;
    int posIcon = -1;

    for (int i = 0; i < lista[l].elementFields.length(); i++)
    {
        if (lista[l].elementFields[i] == "Name")
        {
            posName = i;
        }

        if (lista[l].elementFields[i] == "file_icon" || lista[l].elementFields[i] == "file_icon1")
        {
            posIcon = i;
        }
        if (posName != -1 && posIcon != -1) { break; }
    }

    for (int e = 0; e < lista[l].elementValues.length(); e++)
    {
        int id = lista[l].GetValue(e, 0).toInt();
        ui->tableWidget->insertRow(e);

        QPixmap img;
        QString path = QFileInfo(lista[l].GetValue(e, posIcon)).fileName();
        img = Commands::GetItemIcon(path, Utils::Male);
        QString name = lista[l].GetValue(e, posName);
        QTableWidgetItem *itemname = new QTableWidgetItem(img, name);
        QColor color = Utils::getColorByID(pwAdmin::getInstance().listItemColor[id]);
        itemname->setTextColor(color);
        ui->tableWidget->setItem(e, 1, itemname);
        ui->tableWidget->setItem(e, 0, new QTableWidgetItem(QString::number(id)));
    }
}


void DlgSearchEssence::on_pushButton_2_clicked()
{
    auto items = ui->tableWidget->selectedItems();
    for(int i = 0; i < items.count(); i++)
    {
        int id = ui->tableWidget->item(items[i]->row(), 0)->text().toInt();
        /*QIcon icon = ui->tableWidget->item(items[i]->row(), 0)->icon();
        QString name = ui->tableWidget->item(items[i]->row(), 1)->text();
        ItemEssence *item = new ItemEssence();
        item->id = id;
        item->icon = icon;
        item->name = name;
        returnEssences->append(*item);*/
        if (returnOnlyOne)
        {
            this->close();
            this->setResult(id);
        }
    }
}


void DlgSearchEssence::on_tableWidget_itemClicked(QTableWidgetItem *item)
{
    int id = ui->tableWidget->item(item->row(), 0)->text().toInt();
    QString htmlString =
            "<html>"
            "<style>"
            "body {margin: 0; padding: 3px; color:#ffffff; background-color:#101010; font-size:11px; font-family: verdana;	line-height:1.15em;} p, ul {margin:0; padding:0px;}"
            "ul {margin-left:20px; padding:1px;list-style-type: disc;}"
            "</style>"
            "<body>"
            "<font color=\"#FF6000\"><b> " + Utils::FormatColorText(pwAdmin::getInstance().listItemExtDesc[id]) + " </b></font></body</html>"                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           "</body></html>";
    ui->textBrowser->setHtml(htmlString);
}


void DlgSearchEssence::on_pushButton_3_clicked()
{
    close();
    setResult(QDialog::Rejected);
}


void DlgSearchEssence::on_pushButton_clicked()
{
    if (ui->lineEdit->text().isEmpty())
    {
        for (int i = 0; i < ui->tableWidget->rowCount(); ++i) {
            ui->tableWidget->setRowHidden(i, false);
        }
    } else
    {
        auto items = ui->tableWidget->findItems(ui->lineEdit->text(), Qt::MatchContains);
        QSet<int> rows;
        foreach (QTableWidgetItem* item, items) {
            rows.insert(item->row());
        }
        for (int i = 0; i < ui->tableWidget->rowCount(); ++i) {
            if (!rows.contains(i)) {
                ui->tableWidget->setRowHidden(i, true);
            }
        }
    }
}

