#include "dlgtesteoctetes.h"
#include "pwadmin.h"
#include "teste.h"
#include <QApplication>
#include <QStyleFactory>
#include <Structs/map.h>
#include <DlgTeste.h>
#include <QFile>
#include <mainwindow.h>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  a.setStyle(QStyleFactory::create("Fusion"));
  //MainWindow w;
  //DlgTesteOctetes w;
  pwAdmin &w = pwAdmin::getInstance();
  // NpcGen editor comentado abaixo
  /*EventFilter *filter = new EventFilter();
  a.installEventFilter(filter);
  Teste w;*/
  //DlgTeste w;
  w.setFixedSize(w.size());
  w.show();
  return a.exec();
}
