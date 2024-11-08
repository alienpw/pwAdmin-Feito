#include "dlgtesteoctetes.h"
#include "ui_dlgtesteoctetes.h"
#include "GNET/octetsstream.h"

DlgTesteOctetes::DlgTesteOctetes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgTesteOctetes)
{
    ui->setupUi(this);
}

DlgTesteOctetes::~DlgTesteOctetes()
{
    delete ui;
}

void DlgTesteOctetes::on_pushButton_clicked()
{
    OctetsStream os;
    os.setData(QByteArray::fromHex(ui->plainTextEdit->toPlainText().toUtf8()), false, false);
    qDebug() << os.uncompact_uint32() << os.uncompact_uint32() << os.readUInt32();
}

