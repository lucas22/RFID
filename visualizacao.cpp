/*
#include "visualizacao.h"

visualizacao::visualizacao()
{    

int c;
for (c=0; c<64; c++) {
     palette[c].r = c;
     palette[c].g = 0;
     palette[c].b = 0;
  }
  for (c=64; c<128; c++) {
     palette[c].r = 63;
     palette[c].g = c-64;
     palette[c].b = 0;
  }
  for (c=128; c<192; c++) {
     palette[c].r = 63;
     palette[c].g = 63;
     palette[c].b = c-128;
  }
  for (c=192; c<256; c++) {
     palette[c].r = 63;
     palette[c].g = 63;
     palette[c].b = 63;
  }

  set_palette(palette);


    const char *hos= "127.0.0.1";
    const char *user= "root";
    const char *pass= "root";
    const char *db= "rfid";
    const char *query2 = "select *from registros";
    unsigned int porta_=0;
    //  //  sprintf(query,"insert into registros(date,time,id,intensity) values(current_date(),NOW(),\"%i\",\"%i\")",TAGID,intensity);
    store.configura_bd(hos,user,pass,db,porta_);
    store.connect();
    //  store.envia_recebe(select *from registros);
}

int** visualizacao::set_cores(int **matriz1,int **matriz2){
    int **contador,**aux1,**aux2;
    aux1 = (int **) calloc (100,sizeof(int*));
    aux2 = (int **) calloc (100,sizeof(int*));
    contador = (int **) calloc (100,sizeof(int*));
    int k,i,j;
    k=0;
    // Salva em aux1 e aux2 as posições sem repetição
    for(i=0;i<=matriz1[0][1];i++){
        aux1[i] = (int *) calloc (100,sizeof(int));
        aux2[i] = (int *) calloc (100,sizeof(int));
        if(i==0 && k==0){
            aux1[k][0]=matriz1[i][0];
            //aux2[k][0]=matriz2[i][0];
            aux1[k][1]=matriz2[i][0];
            k=k+1;
        }else{
            if(aux1[k-1][0]!=matriz1[i][0] || aux1[k-1][1]!=matriz2[i][0] ){
                aux1[k][0]=matriz1[i][0];
                //aux2[k][0]=matriz2[i][0];
                aux1[k][1]=matriz2[i][0];
                k=k+1;
            }}}
    cout<<"VALOR DE KKKK->>"<<k<<endl;
    // Verifica o número de vezes que a posição se repete
    for(j=0;j<=k;j++){
        cout<<"TESTANDO->"<<aux1[j][0]<<"|-|-|"<<aux1[j][1]<<"()"<<j<<endl;
        contador[j] = (int *) calloc (100,sizeof(int));
        for(i=0;i<=matriz1[0][1];i++){
            if(aux1[j][0]==matriz1[i][0] && aux1[j][1]==matriz2[i][0]){
                contador[j][0]=contador[j][0]+1;
            }}}
    for(j=0;j<k;j++){
        if(contador[j][0]==1){
            aux1[j][2]=90;
        }
        if(contador[j][0]==2){
            aux1[j][2]=100;
        }
        if(contador[j][0]==3){
            aux1[j][2]=64;
        }
        if(contador[j][0]==4){
            aux1[j][2]=32;
        }
        if(contador[j][0]>4){
            aux1[j][2]=24;
        }
        cout<<"INTENSIDADE"<<k<<endl;
    }
    aux1[0][3]=k;

    return aux1;
}

void visualizacao::atualiza_ambiente(){
    int i;
    int **mat1,**mat2,**mat3;
    mat1 = (int **) calloc (100,sizeof(int*));
    mat2 = (int **) calloc (100,sizeof(int*));
    mat3 = (int **) calloc (100,sizeof(int*));

    mat1=store.recebe_capos("select posX from registros");
    mat2=store.recebe_capos("select posY from registros");
    mat3=set_cores(mat1,mat2);
    store.encerra();
//    set_palette(desktop_palette);
//    set_palette(pal[0]);
    for(i=0;i<=mat3[0][3];i++){
        //   if(*mat1[i][0]!=666){
        cout<<mat3[0][3]<<"|--|"<<mat3[i][2]<<endl;
        draw_sprite(screen,buffer,0,0);
        circlefill(buffer, mat3[i][0],mat3[i][1],8,pal[mat3[i][2]]);
    }
    //4 azul claro
    //12 verde claro
    //REVER HISTÓRIA DAS PALETAS
    free (mat1);
    free (mat2);
    readkey();
}

void visualizacao::set_ambiente(){
    allegro_init();
    install_keyboard();
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1000,720,0,0);
    clear_to_color(screen, makecol(25,25,50));
    buffer=create_bitmap(1000,720);
    //Desenha galpão Norte
    rect(screen, 90,0, 295,240, makecol(0,0,0 ));
    rectfill(screen, 91,1,294,239, makecol(200,200,200 ));
    rect(screen, 296,0, 500,240, makecol(0,0,0 ));
    rectfill(screen, 297,1,499,239, makecol(200,200,200 ));
    rect(screen, 501,0, 705,240, makecol(0,0,0 ));
    rectfill(screen, 502,1,704,239, makecol(200,200,200 ));
    rect(screen, 706,0, 910,240, makecol(0,0,0 ));
    rectfill(screen, 707,1,909,239, makecol(200,200,200 ));
    //Desenha galpão sul
    rect(screen, 90,490, 295,719, makecol(0,0,0 ));
    rectfill(screen, 91,491,294,718, makecol(200,200,200 ));
    rect(screen, 296,490, 500,719, makecol(0,0,0 ));
    rectfill(screen, 297,491,499,718, makecol(200,200,200 ));
    rect(screen, 501,490, 705,719, makecol(0,0,0 ));
    rectfill(screen, 502,491,704,718, makecol(200,200,200 ));
    rect(screen, 706,490, 910,719, makecol(0,0,0 ));
    rectfill(screen, 707,491,909,718, makecol(200,200,200 ));

    rect(screen, 90,345,910,375, makecol(0,0,0 ));
    rectfill(screen,91,346,909,374, makecol(200,200,200 ));
    textprintf_ex(screen, font, 200, 100,makecol(0,0,0),-1,"1",30);
    textprintf_ex(screen, font, 400, 100,makecol(0,0,0),-1,"2",30);
    textprintf_ex(screen, font, 600, 100,makecol(0,0,0),-1,"3",30);
    textprintf_ex(screen, font, 800, 100,makecol(0,0,0),-1,"4",30);
    draw_sprite(buffer,screen,0,0);
    // acquire_bitmap(buffer);
    //   while(1){}
}
*/
