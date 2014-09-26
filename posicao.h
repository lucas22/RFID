#ifndef POSICAO_H
#define POSICAO_H
#include <vector>
#include <rastreavel.h>
using namespace std;

class posicao
{
private:
    float x;
    float y;
     // vector <long int>
public:
    posicao();
    float get_pos_calculada_X();
    float get_pos_calculada_Y();
    void set_pos_calculada_XY(float valx, float valy);
    void calcula_posicao(vector<rastreavel> vetor,int size);
    void calcula1();
    void calcula2(float x1,float y1,float intensidade1,float x2,float y2,float intensidade2);
    void calcula3(int x1,int y1,int intensidade1,int x2,int y2,int intensidade2,int x3,int y3,int intensidade3);
};

#endif // POSICAO_H
