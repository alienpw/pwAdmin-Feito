#ifndef DLGMANAGMENT_H
#define DLGMANAGMENT_H

#include <QDialog>
#include <Protocols/gmsetgameattri.h>
#include <QtConcurrent/QtConcurrent>
#include <QFutureWatcher>
#include <QTimer>
#include <QProgressBar>
#include <Worker.h>

namespace Ui {
class DlgManagment;
}

class DlgManagment : public QDialog
{
    Q_OBJECT

public:
    explicit DlgManagment(QWidget *parent = nullptr);
    ~DlgManagment();

    QMap<quint8, quint8> attr;
    bool loaded;
    int processNum;
    int processStarted;
    bool gdeliveryd;
    bool glinkd;
    int cnt;

private slots:
    void InitServer();
    void InitFinish(int progress);
    void StopServer();
    void StopFinish(int progress);
    void checkBoxStateChanged(int state);
    void on_txtExp_valueChanged(const QString &arg1);

    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

signals:
    void processCompleted();
    void startWork(int msleep, int progress);
private:
    Worker *worker;
    QThread workerThread;
    Ui::DlgManagment *ui;
    void processInitServer();
    void processStopServer();
};

#endif // DLGMANAGMENT_H
