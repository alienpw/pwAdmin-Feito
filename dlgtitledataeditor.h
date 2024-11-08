#ifndef DLGTITLEDATAEDITOR_H
#define DLGTITLEDATAEDITOR_H

#include <QDialog>
#include <game_defs.h>
#include <utils.h>

struct Title
{
public:
    QString name;
    int color;
};

namespace Ui {
class DlgTitleDataEditor;
}

class DlgTitleDataEditor : public QDialog
{
    Q_OBJECT

public:
    explicit DlgTitleDataEditor(QWidget *parent = nullptr);
    ~DlgTitleDataEditor();

    QMap<int, Title> listTitle;
    QByteArray returnedData;
    void Load(QByteArray arr);
    title_data data;

private:
    Ui::DlgTitleDataEditor *ui;
};


#endif // DLGTITLEDATAEDITOR_H
