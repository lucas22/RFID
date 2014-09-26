/*
#ifndef VISUALIZACAO_H
#define VISUALIZACAO_H
#include <allegro5/allegro.h>
#include "armazenamento.h"
#include <mysql/mysql.h>

class visualizacao
{
private:
    armazenamento store;
    ALLEGRO_BITMAP* buffer;
    MYSQL_RES *res;
    MYSQL_ROW row;
    MYSQL aux;
   int pal[128];
   //PALETTE palette;
   ALLEGRO_COLOR palette;
public:
    visualizacao();
    int** set_cores(int **,int **);
    void set_ambiente();
    void atualiza_ambiente();
};

#endif // VISUALIZACAO_H
*/
