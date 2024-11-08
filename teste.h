#ifndef TESTE_H
#define TESTE_H

#include <QDialog>
#include <QPainter>
#include <QLabel>
#include <QScrollArea>
#include <Structs/map.h>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QCursor>

namespace Ui {
class Teste;
}

class Teste : public QDialog
{
    Q_OBJECT

public:
    explicit Teste(QWidget *parent = nullptr);
    ~Teste();

    QList<GameMapInfo> Maps;
    void LinkMaps(QList<PCKFileEntry> l, QString MapName);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Teste *ui;
};

#endif // TESTE_H
