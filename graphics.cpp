//ESCOLHER INTERVALO DE TEMPO PARA EXIBICAO NO MAPA
//CARREGAR MAPA
#include "interfacearmz.h"
#include "objetos.h"
//#include <QApplication>
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <QtCore/QCoreApplication>

const int SCREEN_W = 1024;
const int SCREEN_H = 600;
const int VALORES = 100000;
const float FPS = 30;
const int MULT = 10;        // MULTIPLICADOR DE X E Y DO BD PARA ÍCONES NO MAPA

const char font01[] = "/home/lucas/Computação/Qt Creator/frameworkRFIDv6/Neuton.ttf";
const char font02[] = "/home/lucas/Computação/Qt Creator/frameworkRFIDv6/Aver.ttf";
const char planta01[] = "/home/lucas/Computação/Qt Creator/frameworkRFIDv6/img/planta01.png";
const char malhaPath[] = "/home/lucas/Computação/Qt Creator/frameworkRFIDv6/img/malha.png";
const char rCirclePath[] = "/home/lucas/Computação/Qt Creator/frameworkRFIDv6/img/areas/rCircle.png";
const char gCirclePath[] = "/home/lucas/Computação/Qt Creator/frameworkRFIDv6/img/areas/gCircle.png";
const char bCirclePath[] = "/home/lucas/Computação/Qt Creator/frameworkRFIDv6/img/areas/bCircle.png";
const char yCirclePath[] = "/home/lucas/Computação/Qt Creator/frameworkRFIDv6/img/areas/yCircle.png";
const char bSquarePath[] = "/home/lucas/Computação/Qt Creator/frameworkRFIDv6/img/areas/bSquare.png";
const char mark1Path[] = "/home/lucas/Computação/Qt Creator/frameworkRFIDv6/img/objetos/mark1.png";
const char mark2Path[] = "/home/lucas/Computação/Qt Creator/frameworkRFIDv6/img/objetos/mark2.png";
const char mark3Path[] = "/home/lucas/Computação/Qt Creator/frameworkRFIDv6/img/objetos/mark3.png";
const char mark4Path[] = "/home/lucas/Computação/Qt Creator/frameworkRFIDv6/img/objetos/mark4.png";

int grid[400][400];     //GRID DO MAPA DE CALOR
int gridPeak;           //VALOR MÁXIMO NO GRID (PICO)

////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
void graphics::drawTextBox(ALLEGRO_FONT *font, ALLEGRO_COLOR color, const char *text, int x, int y){
    al_draw_text(font, color, x, y, ALLEGRO_ALIGN_LEFT, text);
    return;
}
////////////////////////////////////////////////////////

void updateGrid(int x, int y){

    int adic=50;
    int i, j;
    grid[x][y]=grid[x][y]+50;
    for(i=x-15; i<=x+15; i++){
        for(j=y-15; j<=y+15; j++){
            if(!(i==x && j==y)){
                    grid[i][j] += 16*adic / ( abs(i-x)*abs(i-x) + abs(j-y)*abs(j-y) );
            }
        }
    }
    if(grid[x][y] > gridPeak){
        gridPeak = grid[x][y];
    }
}

void zerarGrid(){
    for(int i=0; i<200; i++)
        for(int j=0; j<200; j++)
            grid[i][j] = 0;
    gridPeak=1;
}

ALLEGRO_COLOR criarRGB(int num){
    double ratio;
    int r, g, b;
    if(num > gridPeak) ratio = 1;
    else ratio = (double) num/gridPeak;
    if(ratio <= 0.5){
        r = 0;
        g = ratio*510;
        b = 255-g;
    }
    else{
        b = 0;
        g = ((1/ratio)-1) * 255;
        r = 255-g;
    }
    //fprintf(stderr, "\n gridPeak: %d, num: %d, ratio: %lf, rgb: %d %d %d\t",gridPeak, num, ratio, r, g, b);
    ALLEGRO_COLOR novaCor = al_map_rgb(r, g, b);
    return novaCor;
}



int graphics::graphics_main(const float segundosBD)
{

    //================================
    //DECLARAÇÃO DE VARIÁVEIS E OBJETOS
    dadosBD dados[VALORES];
    leitura_visualizacao ler;
    //int maxExib = 150;      //MÁXIMO DE ITENS A SER EXIBIDO NO MAPA

    ALLEGRO_DISPLAY     *display        = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue    = NULL;
    ALLEGRO_TIMER       *timer          = NULL;
    ALLEGRO_TIMER       *BDtimer        = NULL;
    ALLEGRO_BITMAP      *backgd         = NULL;
    ALLEGRO_BITMAP      *malha          = NULL;
    //ALLEGRO_BITMAP      *rCircle        = NULL;
    //ALLEGRO_BITMAP      *gCircle        = NULL;
    //ALLEGRO_BITMAP      *bCircle        = NULL;
    //ALLEGRO_BITMAP      *yCircle        = NULL;
    //ALLEGRO_BITMAP      *bSquare        = NULL;
    //ALLEGRO_BITMAP      *mark1          = NULL;
    //ALLEGRO_BITMAP      *mark2          = NULL;
    ALLEGRO_BITMAP      *mark3          = NULL;
    //ALLEGRO_BITMAP      *mark4          = NULL;
    ALLEGRO_BITMAP      *area           = NULL;

    bool redraw = true;

    al_init_font_addon();
    al_init_ttf_addon();

    if (!al_init()) {
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize allegro!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return 0;
    }

    if(!al_install_mouse()) {
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize mouse!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return 0;
    }

    if(!al_init_image_addon()) {
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize al_init_image_addon!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return 0;
    }

    BDtimer = al_create_timer(segundosBD);
    timer = al_create_timer(1.0 / FPS);
    if(!timer || !BDtimer) {
        al_show_native_message_box(display, "Error", "Error", "Failed to create timer!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return 0;
    }

    ALLEGRO_FONT *aFont01 = al_load_font(font01,26,0);
    ALLEGRO_COLOR cFont01 = al_map_rgb(255,150,0);

    if(!aFont01){
        fprintf(stderr, "Failed to load font.\n");
        return -1;
    }

    display = al_create_display(SCREEN_W, SCREEN_H);
    if (!display) {
        al_show_native_message_box(display, "Error", "Error", "Failed to create display!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_timer(BDtimer);
        al_destroy_timer(timer);
        return 0;
    }
    area = al_create_bitmap(5, 5);

    backgd = al_load_bitmap(planta01);
    if(!backgd) {
        al_show_native_message_box(display, "Error", "Error", "Failed to load image!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_timer(timer);
        al_destroy_timer(BDtimer);
        al_destroy_display(display);
        return 0;
    }

    malha = al_load_bitmap(malhaPath);

    //rCircle = al_load_bitmap(rCirclePath);
    //gCircle = al_load_bitmap(gCirclePath);
    //bCircle = al_load_bitmap(bCirclePath);
    //yCircle = al_load_bitmap(yCirclePath);
    //bSquare = al_load_bitmap(bSquarePath);

    //mark1 = al_load_bitmap(mark1Path);
    //mark2 = al_load_bitmap(mark2Path);
    mark3 = al_load_bitmap(mark3Path);
    //mark4 = al_load_bitmap(mark4Path);

    event_queue = al_create_event_queue();
    if(!event_queue){
        fprintf(stderr, "failed to create event_queue!\n");
        al_destroy_timer(timer);
        al_destroy_timer(BDtimer);
        al_destroy_bitmap(backgd);
        al_destroy_display(display);
        return 0;
    }

    //================================
    //INICIALIZAÇÃO DOS GRÁFICOS, EVENTOS E TIMERS

    al_draw_bitmap(backgd,0,0,0);
    int n_reads;
    n_reads=ler.conectar(dados);

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_timer_event_source(BDtimer));
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_clear_to_color(al_map_rgb(0,0,0));
    al_flip_display();
    al_start_timer(BDtimer);
    al_start_timer(timer);

    //================================
    //REPETIÇÃO E ATUALIZAÇÃO

    int i,j;

    while(1) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            interfaceArmz interfObj;
            if (interfObj.sair()==1) break;
        }
        else if(ev.type == ALLEGRO_EVENT_TIMER){
            if(ev.timer.source == BDtimer){
                n_reads = ler.conectar(dados);
                redraw = true;
            }
            if(ev.timer.source == timer) {
                qApp -> processEvents();
                // qApp -> processEvents();
            }
        }

        if(redraw && al_is_event_queue_empty(event_queue)) {
            redraw=false;
            zerarGrid();
            gridPeak = 0;
            al_clear_to_color(al_map_rgb(0,0,255));
            for(i=0; i<n_reads; i++){
                if(dados[i].ID == "---") break;
                if(dados[i].x >= 0 && dados[i].y >= 0)  updateGrid(dados[i].x, dados[i].y);
            }
            for(i=0; i<200; i++){
                for(j=0; j<200; j++){
                    al_set_target_bitmap(area);
                    if(grid[i][j] != 0){
                        al_clear_to_color(criarRGB(grid[i][j]));
                        al_set_target_bitmap(al_get_backbuffer(display));
                        al_draw_bitmap(area, i*5, j*5, 0);
                    }
                }
            }
            al_set_target_bitmap(al_get_backbuffer(display));

            //            al_clear_to_color(al_map_rgb(200,200,200));
            al_draw_bitmap(backgd, 0,0,0);
            al_draw_bitmap(malha, 0,0,0);
            al_draw_text(aFont01, cFont01, 180, 100, ALLEGRO_ALIGN_LEFT, "OFICINA 01");
            al_draw_text(aFont01, cFont01, 360, 100, ALLEGRO_ALIGN_LEFT, "OFICINA 02");
            al_draw_text(aFont01, cFont01, 540, 100, ALLEGRO_ALIGN_LEFT, "OFICINA 03");
            al_draw_text(aFont01, cFont01, 720, 100, ALLEGRO_ALIGN_LEFT, "OFICINA 04");
            al_draw_text(aFont01, cFont01, 180, 500, ALLEGRO_ALIGN_LEFT, "OFICINA 05");
            al_draw_text(aFont01, cFont01, 360, 500, ALLEGRO_ALIGN_LEFT, "OFICINA 06");
            al_draw_text(aFont01, cFont01, 540, 500, ALLEGRO_ALIGN_LEFT, "OFICINA 07");
            al_draw_text(aFont01, cFont01, 720, 500, ALLEGRO_ALIGN_LEFT, "OFICINA 08");
  //          for(i=0; i<maxExib; i++){
  //              if(dados[i].ID == "---") break;
             //   al_draw_bitmap(bSquare, (MULT*dados[i].x)-30, (MULT*dados[i].y)-30,0);
//            }
           al_draw_bitmap(mark3,200,150,0);
           al_draw_bitmap(mark3,400,150,0);
           al_draw_bitmap(mark3,600,150,0);
           al_draw_bitmap(mark3,800,150,0);
           al_draw_bitmap(mark3,1000,280,0);


            al_flip_display();
            qApp -> processEvents();
        }
    }

    //================================
    //FINALIZACAO

    al_destroy_bitmap(backgd);
    al_destroy_timer(timer);
    al_destroy_timer(BDtimer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    return 0;
    //*/
}

