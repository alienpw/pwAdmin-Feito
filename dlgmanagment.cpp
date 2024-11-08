#include "dlgmanagment.h"
#include "ui_dlgmanagment.h"
#include <connection.h>

static bool gs = false;

DlgManagment::DlgManagment(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgManagment)
{
    ui->setupUi(this);
    pwAdmin &pw = pwAdmin::getInstance();
    gdeliveryd = false;
    cnt = 0;
    glinkd = false;
    loaded = false;
    processNum = 0;
    foreach(auto p, pw.processes)
    {
        if (p.processFileName.toName().compare("gdeliveryd") == 0)
        {
            gdeliveryd = p.pid > 0 ? true : false;
        }
        if (p.processFileName.toName().compare("glinkd") == 0)
            glinkd = p.pid > 0 ? true : false;
        if (p.processDir.toName().length() > 0)
            processNum++;
    }

    ui->progressBar->setMaximum(processNum);
    QList<QCheckBox*> checkBoxes = findChildren<QCheckBox*>();
    for (QCheckBox* checkBox : checkBoxes)
    {
        if (checkBox->objectName().compare("force") == 0) continue;
        QObject::connect(checkBox, &QCheckBox::stateChanged, this, &DlgManagment::checkBoxStateChanged);
    }
    if (gdeliveryd && glinkd)
    {
        OctetsStream os;
        os.socket = &pwAdmin::getInstance().client;
        OctetsStream nos = os.SendReturn(opGMGetGameAttri, true, 100, 100);

        Attributes at;
        at.unmarshal(nos);
        for(auto a : at.attributes)
        {
            attr[a.attribute] = a.value;
        }
    }
    ui->txtExp->setValue(static_cast<double>(attr[PRV_DOUBLEEXP]) / 10.0);
    ui->checkDinheiro->setCheckState(attr[PRV_DOUBLEMONEY] == 1 ? Qt::Checked : Qt::Unchecked);
    ui->checkDrop->setCheckState(attr[PRV_DOUBLEOBJECT] == 1 ? Qt::Checked : Qt::Unchecked);
    ui->checkAlma->setCheckState(attr[PRV_DOUBLESP] == 1 ? Qt::Checked : Qt::Unchecked);
    ui->checkLambda->setCheckState(attr[PRV_LAMBDA] == 1 ? Qt::Checked : Qt::Unchecked);
    ui->checkLeilao->setCheckState(attr[PRV_NOAUCTION] == 1 ? Qt::Checked : Qt::Unchecked);
    ui->checkFaction->setCheckState(attr[PRV_NOFACTION] == 1 ? Qt::Checked : Qt::Unchecked);
    ui->checkCorreio->setCheckState(attr[PRV_NOMAIL] == 1 ? Qt::Checked : Qt::Unchecked);
    ui->checkComercio->setCheckState(attr[PRV_NOSELLPOINT] == 1 ? Qt::Checked : Qt::Unchecked);
    ui->checkNegociacao->setCheckState(attr[PRV_NOTRADE] == 1 ? Qt::Checked : Qt::Unchecked);

    loaded = true;
}

DlgManagment::~DlgManagment()
{
    workerThread.quit();
    workerThread.wait();
    delete ui;
}

void DlgManagment::StopFinish(int progress)
{
    QTimer::singleShot(0, this, &DlgManagment::StopServer);
}

void DlgManagment::StopServer()
{
    pwAdmin &pw = pwAdmin::getInstance();
    if (cnt < processNum)
    {
        Processes p = pw.processes.at(cnt);

        if (p.processKill.toName().length() > 0)
        {
            ui->progressBar->setFormat("Desligando " + p.processFileName.toName().toUpper() + " %p%");
            OctetsStream arg;
            arg.socket = &pw.client;
            arg.compact_uint32(1);
            Octets cmd = QString("%1").arg(p.processKill.toName()).toUtf8();
            arg << cmd;
            arg.Send(13);
            qDebug() << cmd.toName();
            emit startWork(p.stopSleep * 1000, cnt++);
            ui->progressBar->setValue(cnt);
        }
        if (cnt == processNum)
        {
            ui->progressBar->setFormat(QString("Desligando GS %p%"));
            OctetsStream arg;
            arg.socket = &pwAdmin::getInstance().client;
            arg.compact_uint32(1);
            Octets cmd = QString("pkill -9 gs").toUtf8();
            arg << cmd;
            arg.Send(13);
            qDebug() << cmd.toName();
            emit startWork(p.stopSleep * 1000, cnt++);
            ui->progressBar->setValue(cnt);
            gs = true;
        }
        if (gs)
        {
            ui->progressBar->setFormat("Servidor desligado com sucesso! %p%");
        }
    }
}

void DlgManagment::on_txtExp_valueChanged(const QString &arg1)
{
    if (!gdeliveryd || !glinkd) return;
    if (!loaded) return;
    OctetsStream os;
    os << (quint8)PRV_DOUBLEEXP;
    os << static_cast<quint8>(ui->txtExp->value() * 10);
    os.socket = &pwAdmin::getInstance().client;
    os.Send(opGMSetGameAttri);
}

void DlgManagment::checkBoxStateChanged(int state)
{
    qDebug() << gdeliveryd << glinkd << loaded;
    if (!gdeliveryd || !glinkd) return;
    if (!loaded) return;

    qDebug() << state;
    QCheckBox* checkBox = qobject_cast<QCheckBox*>(sender());
    if (checkBox)
    {
        quint8 id = checkBox->accessibleName().toUInt();
        OctetsStream os;
        os << (quint8)id;
        os << (quint8)(checkBox->checkState() == Qt::Checked ? (quint8)1 : (quint8)0);
        os.socket = &pwAdmin::getInstance().client;
        os.Send(opGMSetGameAttri);
        qDebug() << "Enviado! " << os.data.toHex();
    }
}


void DlgManagment::on_pushButton_clicked()
{
    pwAdmin &pw = pwAdmin::getInstance();
    if (!pw.processes.isEmpty())
    {
        processInitServer();
    }
}


void DlgManagment::on_pushButton_2_clicked()
{
    workerThread.quit();
    workerThread.wait();
    cnt = 0;
    gs = false;
    ui->progressBar->resetFormat();
    ui->progressBar->setValue(0);
    ui->progressBar->setMaximum(processNum + 1);
    worker = new Worker;
    worker->moveToThread(&workerThread);
    connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
    connect(this, &DlgManagment::startWork, worker, &Worker::doWork);
    connect(worker, &Worker::workFinished, this, &DlgManagment::StopFinish);
    workerThread.start();
    QTimer::singleShot(0, this, &DlgManagment::StopServer);
}

void DlgManagment::InitFinish(int progress)
{
    QTimer::singleShot(0, this, &DlgManagment::InitServer);
}

void DlgManagment::InitServer()
{
    pwAdmin &pw = pwAdmin::getInstance();
    if (cnt < processNum)
    {
        Processes p = pw.processes.at(cnt);
        ui->progressBar->setFormat("Iniciando " + p.processFileName.toName().toUpper() + " %p%");
        OctetsStream arg;
        arg.socket = &pw.client;
        arg.compact_uint32(1);
        QString dir = p.processDir.toName().replace("$HOME$", pw.infos.homepath + "/");
        Octets cmd = QString("cd %1;%2 > %3/logs/%4.log &")
                .arg(dir)
                .arg(p.processStart.toName())
                .arg(pw.infos.homepath)
                .arg(p.processFileName.toName()).toUtf8();
        Octets cmd2 = QString("cd %1;./%2 %3 > %4/logs/%5.log &")
                .arg(dir)
                .arg(p.processFileName.toName())
                .arg(p.processParams.toName())
                .arg(pw.infos.homepath)
                .arg(p.processFileName.toName()).toUtf8();

        if (p.processStart.toName().length() > 0)
        {
            arg << cmd;
            arg.Send(13);
            qDebug() << cmd.toName();
        }
        else
        {
            arg << cmd2;
            arg.Send(13);
            qDebug() << cmd2.toName();
        }
        emit startWork(p.startSleep * 1000, cnt++);
        ui->progressBar->setValue(cnt);
    }
    if (cnt == processNum)
    {
        ui->progressBar->setFormat(QString("Iniciando GS %p%"));
        OctetsStream arg;
        arg.socket = &pwAdmin::getInstance().client;
        arg.compact_uint32(1);
        QString dir = pw.infos.gs_path.replace("$HOME$", pw.infos.homepath + "/");
        char buffer[300];
        sprintf(buffer, "./%s gs01 gs.conf gmserver.conf gsalias.conf %s > %s/%s.log &", pw.infos.gs_name.toStdString().c_str(),
                QString("is61").toStdString().c_str(),
                QString(pw.infos.logpath.replace("$HOME$", pw.infos.homepath + "/")).toStdString().c_str(),
                QString("maps").toStdString().c_str());
        char buffer2[500];
        sprintf(buffer2, pw.infos.ShellAdd.replace("\\\\", ";").toStdString().c_str(), buffer);
        QString gs = pw.infos.gs_path.replace("$HOME$", pw.infos.homepath + "/");
        Octets cmd = QString("cd %1;%2")
                .arg(gs)
                .arg(QString(buffer2)).toUtf8();
        arg << cmd;
        arg.Send(13);
        qDebug() << cmd.toName();
        emit startWork(5000, cnt++);
        ui->progressBar->setValue(cnt);
        gs = true;
    }
    if (cnt > processNum)
    {
        ui->progressBar->setFormat("Servidor iniciado com sucesso! %p%");
    }
}

void DlgManagment::processInitServer()
{
    workerThread.quit();
    workerThread.wait();
    cnt = 0;
    gs = false;
    ui->progressBar->resetFormat();
    ui->progressBar->setValue(0);
    ui->progressBar->setMaximum(processNum);
    worker = new Worker;
    worker->moveToThread(&workerThread);
    connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
    connect(this, &DlgManagment::startWork, worker, &Worker::doWork);
    connect(worker, &Worker::workFinished, this, &DlgManagment::InitFinish);
    workerThread.start();
    QTimer::singleShot(0, this, &DlgManagment::InitServer);
}


void DlgManagment::on_pushButton_3_clicked()
{

}

