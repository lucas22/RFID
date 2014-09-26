#ifndef COMUNICACAO_H
#define COMUNICACAO_H
#include <string.h>
#include<boost/asio.hpp>
#include<vector>
#include<fstream>
#include<iostream>
using namespace std;

class comunicacao
{
private:
    boost::asio::io_service io;
    boost::asio::serial_port serial;
    vector<unsigned char> buf;
public:
    comunicacao();
    //SERIAL
    void abre_serial(string,int);
    void fecha_serial();
    void ler_serial(vector <unsigned char> &buf, int quantidade);
    void escrever_serial(const vector <unsigned char> &buf);

    //ETHERNET
};

#endif // COMUNICACAO_H
