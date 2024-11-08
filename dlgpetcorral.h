#ifndef DLGPETCORRAL_H
#define DLGPETCORRAL_H

#include <QDialog>
#include "Protocols/GPetCorral.h"
#include <QLineEdit>
#include <QSpinBox>
#include "dlgsearchessence.h"

namespace Ui {
class DlgPetCorral;
}

class DlgPetCorral : public QDialog
{
    Q_OBJECT

public:
    explicit DlgPetCorral(QWidget *parent = nullptr);
    ~DlgPetCorral();

    GPetCorral petCorral;
    QList<GPetInfo> listPetInfo;
    void Load(QByteArray o);
    int CheckID()
    {
        int id = 0;
        for(int i = 0; i < petCorral.listPet.count(); i++)
        {
            if (petCorral.listPet[i].index != i)
                return id;
            id++;
        }
        return id;
    }

    void UpdateList();
    void UpdateValues();
    OctetsStream returnedData;

private slots:
    void on_textEdited(const QString &arg1);

    void connectLineEdits() {
        const auto lineEdits = findChildren<QLineEdit*>();
        for (QLineEdit *lineEdit : lineEdits) {
            connect(lineEdit, &QLineEdit::textEdited, this, &DlgPetCorral::on_textEdited);
        }
    }
    void on_tablePetCorral_cellClicked(int row, int column);

    void on_btnAddPet_clicked();

    void on_btnClose_clicked();

    void on_btnSave_clicked();

    void on_tablePetCorral_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

    void on_btnPetId_clicked();

    void on_btnPetVisId_clicked();

    void on_btnPetEggId_clicked();

    void on_btnDeletePet_clicked();

private:
    Ui::DlgPetCorral *ui;
};

#endif // DLGPETCORRAL_H
