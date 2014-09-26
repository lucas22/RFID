#ifndef OBJETOS_H
#define OBJETOS_H
#include <string>
#include <iostream>
#include <mysql/mysql.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>


const int NUM_POS_GRAVADAS = 2000;
const int HIS_POS = 3;

using namespace std;

class dadosBD {
public:
    int x, y;
    std::string ID;
};

class leitura_visualizacao{
public:
    void envia(const char *query);
    int conectar(dadosBD*); 
};

class graphics{
public:
    void drawTextBox (ALLEGRO_FONT *font, ALLEGRO_COLOR color, const char *text, int x, int y);
    void drawCircle (int x, int y);
    int graphics_main(const float segundosBD = 1);
};

class Historico {
public:
    int hor, min, seg;
    string ancora;
};


template <class myType>
myType imprimirInfo (const myType a){
    cout << a.ID;
}

#endif // OBJETOS_H
