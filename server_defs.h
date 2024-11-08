#ifndef SERVER_DEFS_H
#define SERVER_DEFS_H

#include <QString>

struct Profile
{
    QString name = "Default";
    QString elements = "";
    QString configs = "";
    QString surfaces = "";
    QString server_ip = "";
    int server_port = 600;
    QString server_password = "";
    int interval = 2000;
    int key1 = -1466731422;
    int key2 = -240896429;
    int asig1 = -33685778;
    int asig2 = -267534609;
    int fsig1 = 1305093103;
    int fsig2 = 1453361591;
};

struct ServerInfos
{
    QString servname;
    QString password;
    int port;
    QString homepath;
    QString gs_name;
    QString gs_conf_path;
    QString gs_path;
    int aid;
    int zoneid;
    int servid;
    QString default_icon;
    int log_row_count;
    QString logpath;
    int ServerVersion;
    QString pidfile;
    int PauseStartInstanceFixed;
    int PauseStartPerInstance;
    int MaxChatRow;
    int MaxFormatLogRow;
    int MaxWorld2LogRow;
    int AuthDType;
    QString ShellAdd;
    QString GameBackupPath;
    QString MysqlBackupPath;
    int MysqlBackupType;
    QString mysql_user;
    QString mysql_pass;
    int mysql_port;
    QString mysql_base;
    QString mysql_host;
    QString gdeliveryd_ip;
    int gdeliveryd_port;
    int gprovider_port;
    QString gamedbd_ip;
    int gamedbd_port;
    QString uniquenamed_ip;
    int uniquenamed_port;
};

#endif // SERVER_DEFS_H
