#include "posicao.h"
#include "math.h"
#include <iostream>
posicao::posicao()
{
}

void posicao::calcula_posicao(vector<rastreavel> vetor,int size){
    //rastreavel* trac =vetor.data();
    // trac[0]->get_posX()
    // trac->get_posX();
    //    vetor.at(0).get_posX();
    switch(size){
    case 1:
        cout<<"VALOR DE X DENTRO DO CALCULA="<<vetor.at(0).get_posX()<<endl;
        this->set_pos_calculada_XY(vetor.at(0).get_posX(),vetor.at(0).get_posY()+(10/(vetor.at(0).get_intensity()/2)));
        break;
    case 2:
        calcula2(vetor.at(0).get_posX(),vetor.at(0).get_posY(),vetor.at(0).get_intensity(),vetor.at(1).get_posX(),vetor.at(1).get_posY(),vetor.at(1).get_intensity()); //passar x e y dos 2 primeiros objetos e a intensidade dos 2 tmb
        break;
    default:
        calcula3(vetor.at(0).get_posX(),vetor.at(0).get_posY(),vetor.at(0).get_intensity(),vetor.at(1).get_posX(),vetor.at(1).get_posY(),vetor.at(1).get_intensity(),vetor.at(2).get_posX(),vetor.at(2).get_posY(),vetor.at(2).get_intensity());//passar x e y dos 3 primeiros objetos e a intensidade dos 3 tmb
        break;
    }
}

void posicao::calcula1(){}

void posicao::calcula2(float x1,float y1,float intensidade1,float x2,float y2,float intensidade2){
    float aux1,aux2,d,a,xM,yM,h,x3,y3,x4,y4;
    d=sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));    //distância de ponto a ponto
    while(d>aux1+aux2){
        if(intensidade1>intensidade2){
            aux2=aux2+ (intensidade1/intensidade2);
            aux1=aux1+ (1);
        }
        else if(intensidade1<intensidade2){
            aux1=aux1+ (intensidade2/intensidade1);
            aux2=aux2+ (1);
        }
    }
    intensidade1=aux1;
    intensidade2=aux2;
    a=((intensidade1)*(intensidade1)-(intensidade2)*(intensidade2)+(d*d))/(2*d);
    h=sqrt((intensidade1)*(intensidade1)-(a)*(a));
    //   P2 = P0 + a ( P1 - P0 ) / d
    xM=x1+(a*(x2-x1)/d);    //ponto médio
    yM=y1+(a*(y2-y1)/d);    //ponto médio
    x3=xM+(h*(y2-y1)/d);
    y3=yM-(h*(x2-x1)/d);
    x4=xM-(h*(y2-y1)/d);
    y4=yM+(h*(x2-x1)/d);
    this->set_pos_calculada_XY(xM,yM);
}
void posicao::calcula3(int x1,int y1,int intensidade1,int x2,int y2,int intensidade2,int x3,int y3,int intensidade3){
    float inte1,inte2,inte3,aux3=1,aux1=1,aux2=1,d=0,a=0,xM1=0,yM1=0,h=0,px3=0,py3=0,px4=0,py4=0,xM2=0,yM2=0,xM3=0,yM3=0;
    inte1=intensidade1;
    inte2=intensidade2;
    inte3=intensidade3;
    d=sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));    //distância de ponto a ponto
    while(d>aux1+aux2){
        if(intensidade1>intensidade2){
            aux2=aux2+ (intensidade1/intensidade2);
            aux1=aux1+ (1);
        }
        else if(intensidade1<intensidade2){
            aux1=aux1+ (intensidade2/intensidade1);
            aux2=aux2+ (1);
        }
        else{
            aux1+=1;
            aux2+=1;
        }
    }
    intensidade1=aux1;
    intensidade2=aux2;
    //printf("DISTANCIA PONTO A PONTO-> %f \n",d);
    a=((((intensidade1)*(intensidade1))-((intensidade2)*(intensidade2))+(d*d)))/(2*d);
    //printf("VALOR DE A-> %f \n",a);
    h=sqrt((intensidade1)*(intensidade1)-(a)*(a));
    xM1=x1+(a*(x2-x1)/d);    //ponto médio
    yM1=y1+(a*(y2-y1)/d);    //ponto médio
    //printf("PONTO MÉDIO -> (%f,%f)  \n",xM1,yM1);
    px3=xM1+(h*(y2-y1)/d);
    py3=yM1-(h*(x2-x1)/d);
    //printf("PONTO 1-> (%f,%f)  \n",px3,py3);
    px4=xM1-(h*(y2-y1)/d);
    py4=yM1+(h*(x2-x1)/d);
    //printf("PONTO 2 -> (%f,%f)  \n",px4,py4);
    //////////////////////////////////////////////////////////////////////////////////////////////////
    intensidade1=inte1;
    //intensidade2=inte2;
    intensidade3=inte3;
    aux1=1;aux3=1;
    d=sqrt((x3-x1)*(x3-x1)+(y3-y1)*(y3-y1));    //distância de ponto a ponto
    while(d>aux1+aux3){
        //printf("VALOR DE AUX1-> %f | VALOR DE AUX30> %f \n",aux1,aux3);
        if(intensidade1>intensidade3){
            aux3=aux3+ (intensidade1/intensidade3);
            aux1=aux1+ (1);
        }
        else if(intensidade1<intensidade3){
            aux1=aux1+ (intensidade3/intensidade1);
            aux3=aux3+ (1);
        }
        else{
            aux1+=1;
            aux3+=1;
        }
    }
    intensidade1=aux1;
    intensidade3=aux3;
    //printf("DISTANCIA PONTO A PONTO-> %f \n",d);
    a=((((intensidade1)*(intensidade1))-((intensidade3)*(intensidade3))+(d*d)))/(2*d);
    //printf("VALOR DE A-> %f \n",a);
    h=sqrt((intensidade1)*(intensidade1)-(a)*(a));
    xM2=x1+(a*(x3-x1)/d);    //ponto médio
    yM2=y1+(a*(y3-y1)/d);    //ponto médio
    //printf("PONTO MÉDIO -> (%f,%f)  \n",xM2,yM2);
    px3=xM2+(h*(y3-y1)/d);
    py3=yM2-(h*(x3-x1)/d);
    //printf("PONTO 1-> (%f,%f)  \n",px3,py3);
    px4=xM2-(h*(y3-y1)/d);
    py4=yM2+(h*(x3-x1)/d);
    //printf("PONTO 2 -> (%f,%f)  \n",px4,py4);
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    //intensidade1=inte1;
    intensidade2=inte2;
    intensidade3=inte3;
    aux2=1;aux3=1;
    d=sqrt((x3-x2)*(x3-x2)+(y3-y2)*(y3-y2));    //distância de ponto a ponto
    while(d>aux2+aux3){
       // printf("VALOR DE AUX2-> %f | VALOR DE AUX3> %f \n",aux2,aux3);
        if(intensidade2>intensidade3){
            aux3=aux3+ (intensidade2/intensidade3);
            aux2=aux2+ (1);
        }
        else if(intensidade2<intensidade3){
            aux2=aux2+ (intensidade3/intensidade2);
            aux3=aux3+ (1);
        }
        else{
            aux2+=1;
            aux3+=1;
        }
    }
    intensidade2=aux2;
    intensidade3=aux3;
    //printf("DISTANCIA PONTO A PONTO-> %f \n",d);
    a=((((intensidade2)*(intensidade2))-((intensidade3)*(intensidade3))+(d*d)))/(2*d);
    //printf("VALOR DE A-> %f \n",a);
    h=sqrt((intensidade2)*(intensidade2)-(a)*(a));
    xM3=x2+(a*(x3-x2)/d);    //ponto médio
    yM3=y2+(a*(y3-y2)/d);    //ponto médio
    //printf("PONTO MÉDIO -> (%f,%f)  \n",xM3,yM3);
    px3=xM3+(h*(y3-y2)/d);
    py3=yM3-(h*(x3-x2)/d);
    //printf("PONTO 1-> (%f,%f)  \n",px3,py3);
    px4=xM3-(h*(y3-y2)/d);
    py4=yM3+(h*(x3-x2)/d);
    //printf("PONTO 2 -> (%f,%f)  \n",px4,py4);
    /////CALCULO FINAL/////////////////////////////////
    xM1=(xM1+xM2+xM3)/3;
    yM1=(yM1+yM2+yM3)/3;
    //printf("PONTO MÉDIO TOTAL-> (%f,%f)  \n",xM1,yM1);
    this->set_pos_calculada_XY(xM1,yM1);
}

void posicao::set_pos_calculada_XY(float valx, float valy){
    x=valx;
    y=valy;
}
float posicao::get_pos_calculada_X(){
    return x;
}
float posicao::get_pos_calculada_Y(){
    return y;
}
