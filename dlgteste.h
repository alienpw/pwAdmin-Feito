#ifndef DLGTESTE_H
#define DLGTESTE_H

#include <QDialog>

namespace Ui {
class DlgTeste;
}

class DlgTeste : public QDialog
{
    Q_OBJECT

public:
    explicit DlgTeste(QWidget *parent = nullptr);
    ~DlgTeste();

private slots:
    void on_pushButton_clicked();

private:
    Ui::DlgTeste *ui;
};

#endif // DLGTESTE_H
