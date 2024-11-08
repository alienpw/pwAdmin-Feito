#ifndef PWADMIN_H
#define PWADMIN_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include <QTcpSocket>
#include <QSettings>
#include <QTextCodec>
#include <QMessageBox>
#include <QTime>
#include <QTimer>
#include <QtConcurrent>
#include <QFuture>
#include <QButtonGroup>
#include <QFileDialog>

#include <createaccount.h>
#include <server_defs.h>
#include <utils.h>
#include <game_defs.h>
#include <playereditor.h>
#include <Protocols/GFactionDetail.h>
#include <Protocols/dbautolock.h>
#include <gmprivileges.h>
#include <instances.h>
#include <Structs/addons.h>
#include <Structs/item.h>
#include <Structs/skill.h>
#include <PCKEngine/PCKEngine.h>
#include <ElementEngine/elistcollection.h>
#include <dlgclassmask.h>
#include <dlgmanagment.h>
#include <dlgaddons.h>
#include <dlgfactiondetail.h>
#include <dlgaddcash.h>
#include <dlgcontasonline.h>
#include <Protocols/GetConsumeInfo.h>
#include <Workers.h>
#include <ServerConnection.h>

QT_BEGIN_NAMESPACE
namespace Ui { class pwAdmin; }
QT_END_NAMESPACE

class pwAdmin : public QMainWindow
{
    Q_OBJECT

public:
    pwAdmin(QWidget *parent = nullptr);
    static pwAdmin& getInstance() {
        static pwAdmin instance;
        return instance;
    }
    pwAdmin(const pwAdmin&) = delete;
    void operator=(const pwAdmin&) = delete;
    ~pwAdmin();

    int i;
    QThread *t1;
    Worker *w1;
    QTcpSocket client;
    void LogServer(QString msg, bool ret = false, bool time = true, QColor color = QColor("white"));
    ServerInfos infos;
    QVector<Processes> processes;
    QMap<QString, QString> maps;
    QStringList tmpListMap;
    QTimer timerStartMap;
    int currentIndex = 0;
    QList<User> listUser;
    QMap<int, QString> listClasses;
    QMap<int, GMPlayerInfo> listRoleOnline;

    bool configsLoaded;
    bool processesLoaded;
    bool mapsLoaded;
    void TimerUpdate();

    Profile profile;

    QMap<int, QString> images_m;
    QMap<int, QString> images_f;
    QMap<int, QString> images_skill;
    QMap<int, QString> images_guild;

    QMap<QString, QPoint> imageposition_m;
    QMap<QString, QPoint> imageposition_f;
    QMap<QString, QPoint> imageposition_skill;
    QMap<QString, QPoint> imageposition_guild;

    QMap<QString, QImage> imagesCache_m;
    QMap<QString, QImage> imagesCache_f;
    QMap<QString, QImage> imagesCache_skill;
    QMap<QString, QImage> imagesCache_guild;

    QPixmap icon_profession;
    QPixmap iconlist_ivtrm;
    QPixmap iconlist_ivtrf;
    QPixmap iconlist_skill;
    QPixmap iconlist_guild;

    QMap<int, int> listItemColor;
    QMap<int, SkillInfo> listSkillInfo;
    QMap<int, QString> listSkillName;
    QMap<int, QString> listSkillDesc;
    QMap<int, QString> listItemDesc;
    QMap<int, QString> listItemExtDesc;
    QMap<int, QString> listFixedMsg;

    QMap<QString, QString> listAddons;
    QMap<int, QList<int>> listAddonsGroup;
    QList<addon_data> listAddonsData;
    QMap<QString, QString> addonsList;

    bool loadedData;
    bool loadedPck;
    eListCollection *elc;

    void closeSelectedTab();

    bool SelectProfile();

    bool connected;
private:
    void DefineButtonColors();
    bool ConnectToServer();
    QList<Profile> profiles;
    void LoadProfiles();
    void UpdateProfiles();
    QTimer timer;

private slots:

    void onRadioButtonClicked(int id);
    void on_btnConnection_clicked();

    void on_lpanel_currentRowChanged(int currentRow);

    void on_listProfiles_currentRowChanged(int currentRow);

    void on_btnAddProfile_clicked();

    void on_btnDeleteProfile_clicked();

    void on_btnConnection_2_clicked();

    void on_tableProcessos_itemDoubleClicked(QTableWidgetItem *item);

    void on_btnCleanCache_clicked();

    void on_btnStartMap_clicked();

    void on_btnShutdownMap_clicked();

    void on_txtPesquisar_returnPressed();

    void on_btnPesquisar_clicked();

    void on_btnCriarConta_clicked();

    void on_btnEditarConta_clicked();

    void on_btnContasOnline_clicked();

    void on_btnGM_clicked();

    void on_tableContas_clicked(const QModelIndex &index);

    void on_pushButton_8_clicked();

    void on_tableContas_doubleClicked(const QModelIndex &index);

    void on_tableRoles_doubleClicked(const QModelIndex &index);

    void on_btnManagement_clicked();

    void on_tableContasGM_itemDoubleClicked(QTableWidgetItem *item);

    void ConnectToAll();

    void on_tableRoles_itemDoubleClicked(QTableWidgetItem *item);

    void on_btnSelectElementsPath_triggered(QAction *arg1);

    void on_btnLoadElements_clicked();

    void on_btnLoadConfigs_triggered(QAction *arg1);

    void on_btnLoadConfigs_clicked();

    void on_btnLoadSurfaces_clicked();

    void on_btnSelectElementsPath_clicked();


    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_btnContasOnline_2_clicked();

    void on_pushButton_3_clicked();

    void on_tableMapas_itemDoubleClicked(QTableWidgetItem *item);

    void on_pushButton_2_clicked();

    void on_btnAutoLock_clicked();

signals:
    void readyPck();
    void readyElements();
    void readyConnection();

private:
    Ui::pwAdmin *ui;

protected:
    void closeEvent(QCloseEvent *event) override;
};
#endif // PWADMIN_H
