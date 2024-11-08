#include "dlgteste.h"
#include "ui_dlgteste.h"
#include "PCKEngine/PCKEngine.h"
#include "PCKEngine/PCKStream.h"

DlgTeste::DlgTeste(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgTeste)
{
    ui->setupUi(this);
}

DlgTeste::~DlgTeste()
{
    delete ui;
}

void DlgTeste::on_pushButton_clicked()
{
    QString str = ui->lineEdit->text();
    PCKStream stream(str);
    PCKEngine eng;
    auto list = eng.ReadFileEntrys(stream);

    qDebug() << eng.GetFilesCount(stream) << list.size();
    for(auto f : list)
    {
        if (f.Path == "configs\\skillstr.txt")
        {
            auto icon = eng.ReadFile(stream, f);
            qDebug() << f.CompressedSize << f.Offset << f.Path << f.Size;
        }
    }
}

