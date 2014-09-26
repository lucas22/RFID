#include <QtCore/QCoreApplication>
#include <leitor.h>
#include <string.h>
#include <iostream>
#include <time.h>
#include <comunicacao.h>
#include <visualizacao.h>
#include <objetos.h>
#include "interfacearmz.h"
#include <QApplication>
std::string dealQuery::query_;
int main(int argc, char *argv[])
{
    //visualizacao vi;
    //vi.set_ambiente();
    //vi.atualiza_ambiente();

    //leitor reader;
    //reader.run();

    //  graphics graf;
    // graf.graphics_main(4); //DEFAULT = 1.0

    QApplication a(argc, argv);
    interfaceArmz w;
    w.show();
    w.iniciarUi();

    dealQuery deal_query;
    deal_query.set_str("SELECT * FROM ap16");
    leitor reader;
    reader.Run();

    graphics graf;
    graf.graphics_main(2); //ATUALIAÇÃO BD DEFAULT = 0.5

    //   return a.exec();


}
