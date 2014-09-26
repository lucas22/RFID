#ifndef RASTREAVEL_H
#define RASTREAVEL_H
#include <vector>

using namespace std;

class rastreavel
{
private:
    const char *ide;
    float intensity;
    long int id;
    float posX;
    float posY;
public:
    void set_id_INT(long int value);
    void set_id_CHAR(const char *ide);
    void set_intensity(float value);
    void set_posXY(float value, float value2);
    float get_posX();
    float get_posY();
    int get_id_INT();
    const char* get_id_CHAR();
    float get_intensity();
    rastreavel();
};

#endif // RASTREAVEL_H
