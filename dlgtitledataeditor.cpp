#include "dlgtitledataeditor.h"
#include "ui_dlgtitledataeditor.h"

#include "pwadmin.h"
#include <dlgsearchessence.h>



DlgTitleDataEditor::DlgTitleDataEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgTitleDataEditor)
{
    ui->setupUi(this);    
}

DlgTitleDataEditor::~DlgTitleDataEditor()
{
    delete ui;
}

void DlgTitleDataEditor::Load(QByteArray arr)
{
    if (pwAdmin::getInstance().elc != NULL)
    {
        for(int i = 0; i < pwAdmin::getInstance().elc->Lists.size(); i++)
        {
            if (pwAdmin::getInstance().elc->Lists[i].listName.contains("TITLE_CONFIG"))
            {
                for(int b = 0; b < pwAdmin::getInstance().elc->Lists[i].elementValues.size(); b++)
                {
                    Title t;
                    int id = pwAdmin::getInstance().elc->GetValue(i, b, 0).toUInt();
                    t.name = pwAdmin::getInstance().elc->GetValue(i, b, 1);
                    t.color = pwAdmin::getInstance().elc->GetValue(i, b, 4).toUInt();
                    listTitle[id] = t;
                }
            }
            else if (pwAdmin::getInstance().elc->Lists[i].listName.contains("COMPLEX_TITLE_CONFIG"))
            {
                for(int b = 0; b < pwAdmin::getInstance().elc->Lists[i].elementValues.size(); b++)
                {
                    Title t;
                    int id = pwAdmin::getInstance().elc->GetValue(i, b, 0).toUInt();
                    t.name = pwAdmin::getInstance().elc->GetValue(i, b, 1);
                    t.color = pwAdmin::getInstance().elc->GetValue(i, b, 4).toUInt();
                    listTitle[id] = t;
                }
            }
        }
    }
    OctetsStream os(arr, false, true);
    data.unmarshal(os);
    ui->txtTitleCurrent->setValue(data.current_title);
    ui->lblTitleCurrent->setText(listTitle[data.current_title].name);
    if (data.delivered_titles.count() > 0)
    {
        foreach(auto dt, data.delivered_titles)
        {
            QString str = QString("[%1] %2").arg(dt).arg(listTitle[dt].name);
            ui->listDelivery->addItem(str);
        }
    }
    if (data.expire_titles.count() > 0)
    {
        foreach(auto dt, data.expire_titles)
        {
            QString str = QString("[%1] %2").arg(dt).arg(listTitle[dt].name);
            ui->listDelivery->addItem(str);
        }
    }
}
