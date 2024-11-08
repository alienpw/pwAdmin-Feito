#ifndef DLGCOMBOBOX_H
#define DLGCOMBOBOX_H

#include <QDialog>

namespace Ui {
class DlgComboBox;
}

class DlgComboBox : public QDialog
{
    Q_OBJECT

public:
    explicit DlgComboBox(QString title, QString text, QStringList cbList, QWidget *parent = nullptr);
    ~DlgComboBox();
    QString returnedValue;

private slots:
    void on_pushButton_clicked();

private:
    Ui::DlgComboBox *ui;
};

#endif // DLGCOMBOBOX_H
