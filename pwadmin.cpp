#include "pwadmin.h"
#include "ui_pwadmin.h"
#include "connection.h"
#include <QtConcurrent>
#include <QMetaType>


pwAdmin::pwAdmin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::pwAdmin)
{
    ui->setupUi(this);

    qRegisterMetaType<arquivos>("arquivos");
    qRegisterMetaType<QVector<int>>("QVector<int>");
    qRegisterMetaType<QTextCursor>("QTextCursor");

    i = 0;
    ui->tableContasGM->setColumnWidth(0, 58);
    ui->tableContasGM->setColumnWidth(1, 190);
    ui->tableContasGM->setColumnWidth(2, 58);
    ui->tableProcessos->setColumnWidth(0, 189);
    ui->tableProcessos->setColumnWidth(1, 60);
    ui->tableProcessos->setColumnWidth(2, 60);
    ui->tableMapas->setColumnWidth(0, 47);
    ui->tableMapas->setColumnWidth(1, 273);
    ui->tableMapas->setColumnWidth(2, 70);
    ui->tableMapas->setColumnWidth(3, 70);
    ui->tableContas->setColumnWidth(0, 82);
    ui->tableContas->setColumnWidth(1, 100);
    ui->tableContas->setColumnWidth(2, 157);
    ui->tableContas->setColumnWidth(3, 192);
    ui->tableContas->setColumnWidth(4, 96);
    ui->tableContas->setColumnWidth(5, 151);
    ui->tableRoles->setColumnWidth(0, 75);
    ui->tableRoles->setColumnWidth(1, 102);
    ui->tableRoles->setColumnWidth(2, 35);
    ui->tableRoles->setColumnWidth(3, 103);
    ui->tableRoles->setColumnWidth(4, 130);
    ui->tableRoles->setColumnWidth(5, 158);
    ui->tableRoles->setColumnWidth(6, 65);
    ui->tableRoles->setColumnWidth(7, 121);

    configsLoaded = false;
    processesLoaded = false;
    mapsLoaded = true;

    ui->lpanel->setCurrentRow(0);
    ui->rpanel->setCurrentIndex(0);
    connected = false;
    DefineButtonColors();
    LoadProfiles();

    connect(&timer, &QTimer::timeout, this, &pwAdmin::TimerUpdate);
    connect(&timerStartMap, &QTimer::timeout, this, &Commands::StartMaps);

    // Conectar sinal de desconexão a um novo slot
    connect(&client, &QTcpSocket::disconnected, [&]()
    {
        LogServer("Desconectado!", true, true, QColor(255, 0, 0));
        connected = false;
        loadedData = false;
        loadedPck = false;
        configsLoaded = false;
        timer.stop();
        timerStartMap.stop();
        DefineButtonColors();
    });
    // Conectar sinais
    connect(&client, &QTcpSocket::connected, [&]() {
        if (client.state() == QTcpSocket::ConnectedState)
        {
            LogServer("SUCESSO!", true, false, QColor(0, 255, 0));
            connected = true;
            Commands::GetServerInfos();
            if (configsLoaded)
            {
                ui->lbAID->setText(QString::number(infos.aid));
                ui->lbServerVersion->setText(QString::number(infos.ServerVersion));
                ui->lbZoneID->setText(QString::number(infos.zoneid));
                ui->lbServerName->setText(infos.servname);
                Commands::GetMapNames();
                Commands::GetGMAccounts(ui->tableContasGM);
                timer.start(ui->listProfiles->currentRow() != -1 ? profiles[ui->listProfiles->currentRow()].interval : profiles[0].interval);
            }
            if (!loadedPck)
            {
                Commands::ReadItemIcon();
            }
            if (!loadedData)
            {
                LogServer("Carregando arquivos data...", true);
                LogServer("elements.data: ");
                elc = new eListCollection(profile.elements);
                if (elc->loaded)
                {
                    LogServer("SUCESSO!", true, false, QColor(0, 255, 0));
                    listClasses.clear();
                    for(int i = 0; i < elc->Lists.size(); i++)
                    {
                        if (elc->Lists[i].listName.contains("RACTER_CLASS_CONFIG"))
                        {
                            for(int b = 0; b < elc->Lists[i].elementValues.size(); b++)
                            {
                                listClasses[elc->GetValue(i, b, 2).toInt()] = elc->GetValue(i, b, 1);
                            }
                        }
                    }
                    Commands::LoadElementsAddons();
                    loadedData = true;
                }
                else LogServer("ERRO!", true, false, QColor(255, 0, 0));
            }
        }
    });

    /* QObject::connect(&client, QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::error),
                     [&](QAbstractSocket::SocketError socketError) {
        LogServer("ERRO! " + client.errorString(), true, false, QColor(255, 0, 0));
    });*/

    if (!profiles.isEmpty())
    {
        ui->listProfiles->setCurrentRow(0);
        on_listProfiles_currentRowChanged(0);
    }


}

pwAdmin::~pwAdmin()
{
    delete ui;
}

void pwAdmin::closeEvent(QCloseEvent *event) {
    timer.stop();
    timerStartMap.stop();
    client.disconnectFromHost();
    QMainWindow::closeEvent(event);
}

void pwAdmin::closeSelectedTab()
{
    QListWidgetItem* item = ui->lpanel->currentItem();
    if(item != nullptr) {
        int row = ui->lpanel->row(item);
        ui->lpanel->takeItem(row);
    }
}

void pwAdmin::onRadioButtonClicked(int id)
{

}

void pwAdmin::DefineButtonColors()
{
    ui->lpanel->item(0)->setIcon(connected ? QIcon(":/iconpack/business_finance_data/data_green.ico") : QIcon(":/iconpack/business_finance_data/data_red.ico"));
    ui->btnConnection->setText(!connected ? "Conectar" : "Desconectar");
    ui->btnConnection->setStyleSheet(!connected ? "background-color: rgb(0, 45, 0);color: rgb(255, 255, 255);" : "background-color: rgb(45, 0, 0);color: rgb(255, 255, 255);");
    ui->btnConnection->setIcon(!connected ? QIcon(":/iconpack/basic_foundation/bullet_triangle_glass_green.ico") : QIcon(":/iconpack/basic_foundation/bullet_square_glass_red.ico"));
}

bool pwAdmin::ConnectToServer()
{
    /*if (profiles.isEmpty())
    {
        QMessageBox::warning(this, "Erro", "Defina um perfil de configuração.");
        return false;
    }
    int index = ui->listProfiles->currentRow();
    if (index == -1) {
        index = 0;
    }
    profile = profiles.at(index);
*/
    client.connectToHost(profile.server_ip, profile.server_port);
    if (client.waitForConnected(3000))
    {
        return true;
    }
    return false;
}

void pwAdmin::LogServer(QString msg, bool ret, bool time, QColor color)
{
    ui->txtLog->insertHtml(QString("<font color=#505050>%1</font><font color=%2> %3</font> %4").arg(time ? QTime::currentTime().toString("[HH:mm:ss]") : "").arg(color.name(QColor::HexRgb)).arg(msg).arg(ret ? "<br>" : ""));
}


void pwAdmin::on_btnConnection_clicked()
{
    if (profiles.isEmpty())
    {
        QMessageBox::warning(this, "Erro", "Defina um perfil de configuração.");
        return;
    }
    int index = ui->listProfiles->currentRow();
    if (index == -1) {
        index = 0;
    }
    profile = profiles.at(index);

    t1 = new QThread();
    w1 = new Worker(&profile, &client, profile.server_ip, profile.server_port);
    w1->moveToThread(t1);

    if (!connected)
    {
        LogServer("Conectando ao servidor...");
        if (ConnectToServer())
        {
            connected = true;
        }
        else
        {
            connected = false;
            LogServer("Erro de comunicação com o servidor!", true, false, QColor::fromRgb(255, 0, 0));
        }
    }
    else
    {
        client.disconnectFromHost();
    }
    DefineButtonColors();


    connect(w1, &Worker::connectedServer, [&]()
    {
        /*connected = true;
        LogServer("SUCESSO!", true, false, QColor::fromRgb(0, 255, 0));
        Commands::GetServerInfos();
        if (configsLoaded)
        {
            ui->lbAID->setText(QString::number(infos.aid));
            ui->lbServerVersion->setText(QString::number(infos.ServerVersion));
            ui->lbZoneID->setText(QString::number(infos.zoneid));
            ui->lbServerName->setText(infos.servname);
            Commands::GetMapNames();
            Commands::GetGMAccounts(ui->tableContasGM);
            timer.start(ui->listProfiles->currentRow() != -1 ? profiles[ui->listProfiles->currentRow()].interval : profiles[0].interval);
        }*/
        w1->WorkerReadPcks();
    });

    connect(w1, &Worker::readPcksFinished, [&](arquivos &pw)
    {
        images_m = pw.images_m;
        images_f = pw.images_f;
        images_skill = pw.images_skill;
        images_guild = pw.images_guild;

        imageposition_m = pw.imageposition_m;
        imageposition_f = pw.imageposition_f;
        imageposition_skill = pw.imageposition_skill;
        imageposition_guild = pw.imageposition_guild;

        imagesCache_m = pw.imagesCache_m;
        imagesCache_f = pw.imagesCache_f;
        imagesCache_skill = pw.imagesCache_skill;
        imagesCache_guild = pw.imagesCache_guild;

        icon_profession = pw.icon_profession;
        iconlist_ivtrm = pw.iconlist_ivtrm;
        iconlist_ivtrf = pw.iconlist_ivtrf;
        iconlist_skill = pw.iconlist_skill;
        iconlist_guild = pw.iconlist_guild;

        listItemColor = pw.listItemColor;
        listSkillInfo = pw.listSkillInfo;
        listSkillName = pw.listSkillName;
        listSkillDesc = pw.listSkillDesc;
        listItemDesc = pw.listItemDesc;
        listItemExtDesc = pw.listItemExtDesc;
        listFixedMsg = pw.listFixedMsg;

        listAddons = pw.listAddons;
        listAddonsGroup = pw.listAddonsGroup;
        addonsList = pw.addonsList;
        listClasses = pw.listClasses;
        w1->WorkerReadData();
    });

    connect(w1, &Worker::readElementsFinished, [&](arquivos &pw)
    {
        listAddonsData = pw.listAddonsData;
        elc = pw.elc;
    });

    connect(w1, &Worker::logWork, [&](QString log, bool ret, bool time, QColor color) {
        LogServer(log, ret, time, color);
    });

    t1->start();
    //ConnectToAll();
    /*if (!connected)
    {
        LogServer("Conectando ao servidor...");
        if (ConnectToServer())
        {
            connected = true;
            LogServer("SUCESSO!", true, false, QColor::fromRgb(0, 255, 0));
            Commands::GetServerInfos();
            if (configsLoaded)
            {
                ui->lbAID->setText(QString::number(infos.aid));
                ui->lbServerVersion->setText(QString::number(infos.ServerVersion));
                ui->lbZoneID->setText(QString::number(infos.zoneid));
                ui->lbServerName->setText(infos.servname);
                Commands::GetMapNames();
                Commands::GetGMAccounts(ui->tableContasGM);
                timer.start(ui->listProfiles->currentRow() != -1 ? profiles[ui->listProfiles->currentRow()].interval : profiles[0].interval);
            }
        }
        else
        {
            connected = false;
            LogServer("Erro de comunicação com o servidor!", true, false, QColor::fromRgb(255, 0, 0));
        }
        if (!loadedPck)
        {
            Commands::ReadItemIcon();
        }
        if (!loadedData)
        {
            LogServer("Carregando arquivos data...", true);
            LogServer("elements.data: ");
            elc = new eListCollection(profile.elements);
            if (elc->loaded)
            {
                LogServer("SUCESSO!", true, false, QColor(0, 255, 0));
                listClasses.clear();
                for(int i = 0; i < elc->Lists.size(); i++)
                {
                    if (elc->Lists[i].listName.contains("RACTER_CLASS_CONFIG"))
                    {
                        for(int b = 0; b < elc->Lists[i].elementValues.size(); b++)
                        {
                            listClasses[elc->GetValue(i, b, 2).toInt()] = elc->GetValue(i, b, 1);
                        }
                    }
                }
                Commands::LoadElementsAddons();
                loadedData = true;
            }
            else LogServer("ERRO!", true, false, QColor(255, 0, 0));
        }
    }
    else
    {
        client.disconnectFromHost();
    }
    DefineButtonColors();*/

}


void pwAdmin::on_lpanel_currentRowChanged(int currentRow)
{
    ui->rpanel->setCurrentIndex(currentRow);
}


void pwAdmin::on_listProfiles_currentRowChanged(int currentRow)
{
    if (currentRow != -1)
    {
        Profile p = profiles[currentRow];
        ui->txtElements->setText(p.elements);
        ui->txtConfigs->setText(p.configs);
        ui->txtSurfaces->setText(p.surfaces);
        ui->txtServerIp->setText(p.server_ip);
        ui->txtServerPassword->setText(p.server_password);
        ui->txtServerPort->setText(QString::number(p.server_port));
        ui->txtIntervaloDados->setText(QString::number(p.interval));
        ui->txtKey1->setText(QString::number(p.key1));
        ui->txtKey2->setText(QString::number(p.key2));
        ui->txtAsig1->setText(QString::number(p.asig1));
        ui->txtAsig2->setText(QString::number(p.asig2));
        ui->txtFsig1->setText(QString::number(p.fsig1));
        ui->txtFsig2->setText(QString::number(p.fsig2));
        ui->txtProfileName->setText(p.name);
    }
}

void pwAdmin::TimerUpdate()
{
    // Get mem from server
    Commands::GetServerMemory(ui->tableMemoriaTroca);
    // Get processes from server
    Commands::GetServerProcesses(ui->tableProcessos, ui->tableMapas);
}

void pwAdmin::LoadProfiles()
{
    profiles.clear();
    ui->listProfiles->clear();
    QSettings cfg("profile.ini", QSettings::IniFormat);
    cfg.setIniCodec(QTextCodec::codecForName("UTF-8"));
    QStringList profileGroups = cfg.childGroups().filter(QRegExp("^PROFILE_\\d+$"));
    foreach(const QString &group, profileGroups) {
        cfg.beginGroup(group);
        Profile p;
        p.name = cfg.value("name").toString();
        p.elements = cfg.value("elements").toString();
        p.configs = cfg.value("configs").toString();
        p.surfaces = cfg.value("surfaces").toString();
        p.server_ip = cfg.value("server_ip").toString();
        p.server_port = cfg.value("server_port").toInt();
        p.server_password = cfg.value("server_password").toString();
        p.interval = cfg.value("interval").toInt();
        p.key1 = cfg.value("key1").toInt();
        p.key2 = cfg.value("key2").toInt();
        p.asig1 = cfg.value("asig1").toInt();
        p.asig2 = cfg.value("asig2").toInt();
        p.fsig1 = cfg.value("fsig1").toInt();
        p.fsig2 = cfg.value("fsig2").toInt();
        profiles.append(p);
        ui->listProfiles->addItem(p.name);
        cfg.endGroup();
    }
}

void pwAdmin::UpdateProfiles()
{
    if (ui->listProfiles->currentRow() == -1)
        return;
    Profile p;
    p.name = ui->txtProfileName->text();
    p.elements = ui->txtElements->text();
    p.configs = ui->txtConfigs->text();
    p.surfaces = ui->txtSurfaces->text();
    p.server_ip = ui->txtServerIp->text();
    p.server_password = ui->txtServerPassword->text();
    p.server_port = ui->txtServerPort->text().toInt();
    p.interval = ui->txtIntervaloDados->text().toInt();
    p.key1 = ui->txtKey1->text().toInt();
    p.key2 = ui->txtKey2->text().toInt();
    p.fsig1 = ui->txtFsig1->text().toInt();
    p.fsig2 = ui->txtFsig2->text().toInt();
    p.asig1 = ui->txtAsig1->text().toInt();
    p.asig2 = ui->txtAsig2->text().toInt();
    profiles[ui->listProfiles->currentRow()] = p;
    QSettings cfg("profile.ini", QSettings::IniFormat);
    cfg.setIniCodec(QTextCodec::codecForName("UTF-8"));
    cfg.clear();
    for(int i = 0; i < profiles.size(); i++)
    {
        cfg.beginGroup(QString("PROFILE_%1").arg(i + 1));
        cfg.setValue("name", profiles[i].name);
        cfg.setValue("elements", profiles[i].elements);
        cfg.setValue("configs", profiles[i].configs);
        cfg.setValue("surfaces", profiles[i].surfaces);
        cfg.setValue("server_ip", profiles[i].server_ip);
        cfg.setValue("server_password", profiles[i].server_password);
        cfg.setValue("server_port", profiles[i].server_port);
        cfg.setValue("interval", profiles[i].interval);
        cfg.setValue("key1", profiles[i].key1);
        cfg.setValue("key2", profiles[i].key2);
        cfg.setValue("fsig1", profiles[i].fsig1);
        cfg.setValue("fsig2", profiles[i].fsig2);
        cfg.setValue("asig1", profiles[i].asig1);
        cfg.setValue("asig2", profiles[i].asig2);
        cfg.endGroup();
    }
    cfg.sync();
    LoadProfiles();
}

void pwAdmin::on_btnAddProfile_clicked()
{
    Profile p;
    profiles.append(p);
    ui->listProfiles->addItem(p.name);
}


void pwAdmin::on_btnDeleteProfile_clicked()
{
    profiles.removeAt(ui->listProfiles->currentRow());
    ui->listProfiles->takeItem(ui->listProfiles->currentRow());
}


void pwAdmin::on_btnConnection_2_clicked()
{
    UpdateProfiles();
}


void pwAdmin::on_tableProcessos_itemDoubleClicked(QTableWidgetItem *item)
{
    int row = item->row();
    if (processes[row].pid == 0)
        Commands::StartProcess(row);
    else if (processes[row].pid > 0 && QMessageBox::question(this, "Atenção!", "Deseja parar o serviço " + processes[row].processName.toName().toUpper() + "?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
        Commands::StopProcess(row);
}


void pwAdmin::on_btnCleanCache_clicked()
{
    Commands::ClearCache();
}


void pwAdmin::on_btnStartMap_clicked()
{
    Instances dlg;
    dlg.LoadMaps(ui->tableMapas);
    if (dlg.exec() == QDialog::Accepted)
    {
        tmpListMap = dlg.listMaps;
        currentIndex = 0;
        if (!tmpListMap.isEmpty()) {
            timerStartMap.start(infos.PauseStartInstanceFixed * 1000); // Configura o timer para disparar a cada 1 segundo
        }
    }
}


void pwAdmin::on_btnShutdownMap_clicked()
{
    if (ui->tableMapas->selectedItems().count() > 0)
    {
        tmpListMap.clear();
        foreach(auto item, ui->tableMapas->selectedItems())
        {
            QString id;
            QString mapName;

            if (item->column() == 0)
                id = item->text();
            if (item->column() == 1)
                mapName = item->text();

            foreach(auto p, processes)
            {
                if (p.processParams.toName().contains(id))
                {
                    QString str = QString("%1||%2||%3").arg(p.pid).arg(id).arg(mapName);
                    //tmpListMap << QString::number(p.pid);
                    tmpListMap << str;
                    Commands::StopMap();
                    return;
                }
            }
        }
    }
}


void pwAdmin::on_txtPesquisar_returnPressed()
{
    emit on_btnPesquisar_clicked();
}


void pwAdmin::on_btnPesquisar_clicked()
{
    Commands::GetUser(ui->txtPesquisar->text(), ui->tableContas);
}


void pwAdmin::on_btnCriarConta_clicked()
{
    CreateAccount dlg(User(), false);
    dlg.exec();
}


void pwAdmin::on_btnEditarConta_clicked()
{
    int index = ui->tableContas->currentIndex().row();
    if (index == -1)
    {
        QMessageBox::information(this, "Atenção!", "Selecione uma conta para editar");
        return;
    }
    CreateAccount dlg(listUser[index], true);
    if (dlg.exec() == QDialog::Accepted)
        emit on_btnPesquisar_clicked();
}


void pwAdmin::on_btnContasOnline_clicked()
{
    Commands::GetOnlineUsers(ui->tableContas);
}


void pwAdmin::on_btnGM_clicked()
{
    int index = ui->tableContas->currentIndex().row();
    if (index == -1)
    {
        QMessageBox::information(this, "Atenção!", "Selecione uma conta");
        return;
    }
    Commands::GetGMPrivileges(listUser[index].id, ui->tableContas);
}


void pwAdmin::on_tableContas_clicked(const QModelIndex &index)
{
    if (index.row() != -1)
        Commands::GetAutoLock(listUser[index.row()].id, ui->btnAutoLock);
}


void pwAdmin::on_pushButton_8_clicked()
{
    Commands::GetInitClasses(ui->tableContas, ui->tableRoles);
}


void pwAdmin::on_tableContas_doubleClicked(const QModelIndex &index)
{
    if (index.row() == -1 || listUser[index.row()].id <= 0)
        return;

    Commands::GetUserRoles(listUser[index.row()].id, ui->tableRoles);
}


void pwAdmin::on_tableRoles_doubleClicked(const QModelIndex &index)
{
    if (index.row() == -1) return;
    int id = ui->tableRoles->item(index.row(), 0)->text().toInt();
    Commands::GetRoleData(id, ui->lpanel, ui->rpanel);
}


void pwAdmin::on_btnManagement_clicked()
{
    DlgManagment dlg;
    dlg.exec();
}

void pwAdmin::on_tableContasGM_itemDoubleClicked(QTableWidgetItem *item)
{
    ui->lpanel->setCurrentRow(1);
    ui->txtPesquisar->setText( ui->tableContasGM->item(item->row(), 1)->text());
    Commands::GetUser2(ui->tableContasGM->item(item->row(), 0)->text(), ui->tableContas);
    Commands::GetUserRoles(ui->tableContasGM->item(item->row(), 0)->text().toInt(), ui->tableRoles);
}




void pwAdmin::on_tableRoles_itemDoubleClicked(QTableWidgetItem *item)
{

}


void pwAdmin::on_btnSelectElementsPath_triggered(QAction *arg1)
{

}



void pwAdmin::on_btnLoadElements_clicked()
{
    QString filtro = "Arquivo elements.data (elements.data);;Arquivos data (*.data);;Todos os Arquivos (*.*)";
    QString arquivoSelecionado = QFileDialog::getOpenFileName(this, tr("Selecione um Arquivo"), "/", filtro);
    if (!arquivoSelecionado.isEmpty())
        ui->txtElements->setText(arquivoSelecionado);
}


void pwAdmin::on_btnLoadConfigs_triggered(QAction *arg1)
{

}


void pwAdmin::on_btnLoadConfigs_clicked()
{
    QString filtro = "Arquivo configs.pck (configs.pck);;Arquivos pck (*.pck);;Todos os Arquivos (*.*)";
    QString arquivoSelecionado = QFileDialog::getOpenFileName(this, tr("Selecione um Arquivo"), "/", filtro);
    if (!arquivoSelecionado.isEmpty())
        ui->txtConfigs->setText(arquivoSelecionado);
}


void pwAdmin::on_btnLoadSurfaces_clicked()
{
    QString filtro = "Arquivo surfaces.pck (surfaces.pck);;Arquivos pck (*.pck);;Todos os Arquivos (*.*)";
    QString arquivoSelecionado = QFileDialog::getOpenFileName(this, tr("Selecione um Arquivo"), "/", filtro);
    if (!arquivoSelecionado.isEmpty())
        ui->txtSurfaces->setText(arquivoSelecionado);
}


void pwAdmin::on_btnSelectElementsPath_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Selecione a pasta element"), "/", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (!dir.isEmpty())
    {
        ui->txtElements->setText(QString("%1/data/elements.data").arg(dir));
        ui->txtConfigs->setText(QString("%1/configs.pck").arg(dir));
        ui->txtSurfaces->setText(QString("%1/surfaces.pck").arg(dir));
    }
}


void pwAdmin::on_pushButton_9_clicked()
{
    auto lista = Commands::GetFactionList();
    DlgFactionDetail dlg;
    dlg.Load(lista);
    dlg.exec();
}


void pwAdmin::on_pushButton_10_clicked()
{
    auto item = ui->tableContas->selectedItems()[0];
    if (item->column() == 0)
    {
        DlgAddCash dlg;
        dlg.Load(item->text().toInt());
        dlg.exec();
    }
}

void pwAdmin::on_btnContasOnline_2_clicked()
{
    DBGetConsumeInfoArg arg;
    arg.retcode = -1;
    arg.ids = pwAdmin::getInstance().listRoleOnline.keys();
    OctetsStream os;
    arg.marshal(os);
    os.socket = &pwAdmin::getInstance().client;
    auto res = os.SendReturn(opDBGetConsumeInfos, true);
    DBGetConsumeInfoRes r;
    r.unmarshal(res);
    DlgContasOnline dlg;
    dlg.Load(pwAdmin::getInstance().listRoleOnline.values(), r);
    dlg.exec();
}


void pwAdmin::ConnectToAll()
{
    arquivos pw;

    if (profiles.isEmpty())
    {
        QMessageBox::warning(this, "Erro", "Defina um perfil de configuração.");
        return;
    }
    int index = ui->listProfiles->currentRow();
    if (index == -1) {
        index = 0;
    }
    profile = profiles.at(index);

    QThread* thread = new QThread();
    Worker* worker = new Worker(&profile);
    worker->moveToThread(thread);

    connect(thread, &QThread::started, [&](){
        worker->WorkerReadDatas();
    });

    connect(worker, &Worker::logWork, [&](QString log, bool ret, bool time, QColor color) {
        LogServer(log, ret, time, color);
    });
    /*
        connect(worker, &Worker::readElementsFinished, [&](arquivos *pw) {
            if (!loadedData || !loadedPck)
            {
                this->elc = pw->elc;
                listClasses = pw->listClasses;
                listAddonsData = pw->listAddonsData;
                images_m = pw->images_m;
                images_f = pw->images_f;
                images_skill = pw->images_skill;
                images_guild = pw->images_guild;
                imageposition_m = pw->imageposition_m;
                imageposition_f = pw->imageposition_f;
                imageposition_skill = pw->imageposition_skill;
                imageposition_guild = pw->imageposition_guild;
                imagesCache_m = pw->imagesCache_m;
                imagesCache_f = pw->imagesCache_f;
                imagesCache_skill = pw->imagesCache_skill;
                imagesCache_guild = pw->imagesCache_guild;
                icon_profession = pw->icon_profession;
                iconlist_ivtrm = pw->iconlist_ivtrm;
                iconlist_ivtrf = pw->iconlist_ivtrf;
                iconlist_skill = pw->iconlist_skill;
                iconlist_guild = pw->iconlist_guild;
                listItemColor = pw->listItemColor;
                listSkillInfo = pw->listSkillInfo;
                listSkillName = pw->listSkillName;
                listSkillDesc = pw->listSkillDesc;
                listItemDesc = pw->listItemDesc;
                listItemExtDesc = pw->listItemExtDesc;
                listFixedMsg = pw->listFixedMsg;
                listAddons = pw->listAddons;
                listAddonsGroup = pw->listAddonsGroup;
                addonsList = pw->addonsList;
                loadedData = true;
                loadedPck = true;
            }
        });
    */
    connect(worker, &Worker::readElementsFinished, thread, &QThread::quit);
    connect(thread, &QThread::finished, worker, &QObject::deleteLater);
    connect(thread, &QThread::finished, thread, &QObject::deleteLater);

    if (!connected)
    {
        LogServer("Conectando ao servidor...");

        if (ConnectToServer())
        {
            connected = true;
            Commands::GetServerInfos();
            if (configsLoaded)
            {
                ui->lbAID->setText(QString::number(infos.aid));
                ui->lbServerVersion->setText(QString::number(infos.ServerVersion));
                ui->lbZoneID->setText(QString::number(infos.zoneid));
                ui->lbServerName->setText(infos.servname);
                Commands::GetMapNames();
                Commands::GetGMAccounts(ui->tableContasGM);
                timer.start(ui->listProfiles->currentRow() != -1 ? profiles[ui->listProfiles->currentRow()].interval : profiles[0].interval);
            }
        }
        else
        {
            connected = false;
            LogServer("ERRO!", true, false, QColor::fromRgb(255, 0, 0));
        }

        thread->start();
    }
    else
    {
        connected = false;
        loadedData = false;
        loadedPck = false;
        configsLoaded = false;
        timer.stop();
        timerStartMap.stop();
        client.disconnectFromHost();
        LogServer("Desconectado", true, true, QColor(255, 0, 0));
    }
    DefineButtonColors();
}

void pwAdmin::on_pushButton_3_clicked()
{
    arquivos pw;

    if (profiles.isEmpty())
    {
        QMessageBox::warning(this, "Erro", "Defina um perfil de configuração.");
        return;
    }
    int index = ui->listProfiles->currentRow();
    if (index == -1) {
        index = 0;
    }
    profile = profiles.at(index);

    QThread* thread = new QThread();
    Worker* worker = new Worker(&profile);
    worker->moveToThread(thread);

    connect(thread, &QThread::started, [&](){
        worker->WorkerReadDatas();
    });

    connect(worker, &Worker::logWork, [&](QString log, bool ret, bool time, QColor color) {
        LogServer(log, ret, time, color);
    });
    /*
        connect(worker, &Worker::readElementsFinished, [&](arquivos *pw) {
            if (!loadedData || !loadedPck)
            {
                this->elc = pw->elc;
                listClasses = pw->listClasses;
                listAddonsData = pw->listAddonsData;
                images_m = pw->images_m;
                images_f = pw->images_f;
                images_skill = pw->images_skill;
                images_guild = pw->images_guild;
                imageposition_m = pw->imageposition_m;
                imageposition_f = pw->imageposition_f;
                imageposition_skill = pw->imageposition_skill;
                imageposition_guild = pw->imageposition_guild;
                imagesCache_m = pw->imagesCache_m;
                imagesCache_f = pw->imagesCache_f;
                imagesCache_skill = pw->imagesCache_skill;
                imagesCache_guild = pw->imagesCache_guild;
                icon_profession = pw->icon_profession;
                iconlist_ivtrm = pw->iconlist_ivtrm;
                iconlist_ivtrf = pw->iconlist_ivtrf;
                iconlist_skill = pw->iconlist_skill;
                iconlist_guild = pw->iconlist_guild;
                listItemColor = pw->listItemColor;
                listSkillInfo = pw->listSkillInfo;
                listSkillName = pw->listSkillName;
                listSkillDesc = pw->listSkillDesc;
                listItemDesc = pw->listItemDesc;
                listItemExtDesc = pw->listItemExtDesc;
                listFixedMsg = pw->listFixedMsg;
                listAddons = pw->listAddons;
                listAddonsGroup = pw->listAddonsGroup;
                addonsList = pw->addonsList;
                loadedData = true;
                loadedPck = true;
            }
        });
    */
    connect(worker, &Worker::readElementsFinished, thread, &QThread::quit);
    connect(thread, &QThread::finished, worker, &QObject::deleteLater);
    connect(thread, &QThread::finished, thread, &QObject::deleteLater);

    if (!connected)
    {
        LogServer("Conectando ao servidor...");

        if (ConnectToServer())
        {
            connected = true;
            Commands::GetServerInfos();
            if (configsLoaded)
            {
                ui->lbAID->setText(QString::number(infos.aid));
                ui->lbServerVersion->setText(QString::number(infos.ServerVersion));
                ui->lbZoneID->setText(QString::number(infos.zoneid));
                ui->lbServerName->setText(infos.servname);
                Commands::GetMapNames();
                Commands::GetGMAccounts(ui->tableContasGM);
                timer.start(ui->listProfiles->currentRow() != -1 ? profiles[ui->listProfiles->currentRow()].interval : profiles[0].interval);
            }
        }
        else
        {
            connected = false;
            LogServer("ERRO!", true, false, QColor::fromRgb(255, 0, 0));
        }

        thread->start();
    }
    else
    {
        connected = false;
        loadedData = false;
        loadedPck = false;
        configsLoaded = false;
        timer.stop();
        timerStartMap.stop();
        client.disconnectFromHost();
        LogServer("Desconectado", true, true, QColor(255, 0, 0));
    }
    DefineButtonColors();
}


void pwAdmin::on_tableMapas_itemDoubleClicked(QTableWidgetItem *item)
{
    if (ui->tableMapas->selectedItems().count() > 0)
    {
        tmpListMap.clear();

        QString id;
        QString mapName;

        if (item->column() == 0)
            id = item->text();
        if (item->column() == 1)
            mapName = item->text();

        foreach(auto p, processes)
        {
            if (p.processParams.toName().contains(id))
            {
                QString str = QString("%1||%2||%3").arg(p.pid).arg(id).arg(mapName);
                //tmpListMap << QString::number(p.pid);
                tmpListMap << str;
                Commands::StopMap();
                return;
            }
        }

    }
}


void pwAdmin::on_pushButton_2_clicked()
{

}


void pwAdmin::on_btnAutoLock_clicked()
{

}

