#ifndef DLGTESTEOCTETES_H
#define DLGTESTEOCTETES_H

#include <QDialog>

namespace Ui {
class DlgTesteOctetes;
}

class DlgTesteOctetes : public QDialog
{
    Q_OBJECT

public:
    explicit DlgTesteOctetes(QWidget *parent = nullptr);
    ~DlgTesteOctetes();

private slots:
    void on_pushButton_clicked();

private:
    Ui::DlgTesteOctetes *ui;
};

#endif // DLGTESTEOCTETES_H
