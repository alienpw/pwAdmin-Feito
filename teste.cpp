#include "teste.h"
#include "ui_teste.h"
#include <qdebug.h>
#include "gnet/octets.h"

Teste::Teste(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Teste)
{
    ui->setupUi(this);
}

Teste::~Teste()
{
    delete ui;
}

void Teste::on_pushButton_clicked()
{    
    QList<PCKFileEntry> AllFiles;
    QString path = "F:\\pw165ratebaixa\\element\\surfaces.pck";
    PCKStream stream(path);
    PCKEngine eng;
    auto list = eng.ReadFileEntrys(stream);
    foreach (auto& item, list) {
        if (item.Path.contains("minimaps") && !item.Path.contains("surfaces\\minimaps\\world")) {
            AllFiles.append(item);
        }
    }
    QList<QString> AlreadyExistion;
    foreach (PCKFileEntry fs, AllFiles) {
        GameMapInfo map;
        QStringList st = QString(fs.Path).split('\\');
        map.MapName = st.at(st.count() - 2);
        st.removeLast();
        map.MapPath = st.join("\\");

        if (!AlreadyExistion.contains(map.MapPath)) {
            QList<PCKFileEntry> filteredFiles;
            std::copy_if(AllFiles.begin(), AllFiles.end(), std::back_inserter(filteredFiles),
                         [&map](PCKFileEntry& entry) { return entry.Path.contains(map.MapPath); });

            std::sort(filteredFiles.begin(), filteredFiles.end(),
                      [](PCKFileEntry& a, PCKFileEntry& b) { return a.Path < b.Path; });

            map.MapFragments = filteredFiles;
            Maps.append(map);
            AlreadyExistion.append(map.MapPath);
            std::sort(Maps.begin(), Maps.end(), [](const GameMapInfo& a, const GameMapInfo& b) {
                return a.MapName.compare(b.MapName, Qt::CaseInsensitive) < 0;
            });
        }
    }

    if (!Maps.isEmpty()) {
        GameMapInfo map1;
        map1.MapName = "World";
        map1.MapPath = "surfaces\\maps\\";
        foreach (PCKFileEntry entry, list) {
            if (entry.Path.contains(map1.MapPath)) {
                map1.MapFragments.append(entry);
            }
        }
        Maps.append(map1);
        ui->comboBox->clear();
        for (int i = 0; i < Maps.count(); ++i) {
            ui->comboBox->addItem(Maps[i].MapName);
        }
        ui->comboBox->setCurrentIndex(ui->comboBox->count() - 1);
    }
    ui->comboBox->setMaxVisibleItems(10);
}


void Teste::on_pushButton_2_clicked()
{
    if (!Maps.isEmpty()) {
        int SelectedIndex = ui->comboBox->currentIndex();
        auto mapFragments = Maps[SelectedIndex].MapFragments;
        auto mapName = Maps[SelectedIndex].MapName;
        LinkMaps(mapFragments, mapName);

    }
}



void Teste::LinkMaps(QList<PCKFileEntry> l, QString MapName)
{
    QString path = "F:\\pw165ratebaixa\\element\\surfaces.pck";
    PCKStream stream(path);
    PCKEngine eng;
    auto list = eng.ReadFileEntrys(stream);
    int val = (l.count() == 88) ? 1024 : 256;
    QImage bm(8192, 11264, QImage::Format_ARGB32);
    QPainter gr(&bm);
    std::sort(l.begin(), l.end(), [](const auto& a, const auto& b) { return a.Path < b.Path; });

    int x = 0, y = 0;
    for (int i = 0; i < l.count(); ++i) {
        QByteArray imgData = eng.ReadFile(stream, l[i]); // Assuming this returns QByteArray
        QImage img;
        if (img.loadFromData(imgData)) { // Load the image from imgData
            gr.drawImage(QPoint(x, y), img); // Draw img onto bm at the calculated position
        } else {
            // Handle the error, maybe log it or use a placeholder image
        }

        x += val;
        if (x >= bm.width()) { // Use >= to cover the case where x equals the width exactly
            y += val;
            x = 0;
        }
    }
    CliqueLabel *label = new CliqueLabel;
    label->setPixmap(QPixmap::fromImage(bm));
    label->setAlignment(Qt::AlignCenter);
    ui->scrollArea->setWidget(label);
    ui->scrollArea->setWidgetResizable(false);
    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
}
