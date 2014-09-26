#include "rastreavel.h"
#include <iostream>

rastreavel::rastreavel() {}

void rastreavel::set_id_INT(long int value){        id=value;}

void rastreavel::set_id_CHAR(const char *value){    ide=value;}

void rastreavel::set_intensity(float value){        intensity=value;}

void rastreavel::set_posXY(float value, float value2){
    posX=value;
    posY=value2;
}

int rastreavel::get_id_INT(){           return id;}

const char* rastreavel::get_id_CHAR(){  return ide;}

float rastreavel::get_posX(){           return posX;}

float rastreavel::get_posY(){           return posY;}

float rastreavel::get_intensity(){      return intensity;}
