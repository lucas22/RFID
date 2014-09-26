#ifndef LEITOR_H
#define LEITOR_H
#include <armazenamento.h>
#include <comunicacao.h>
#include <posicao.h>
#include <boost/thread.hpp>
#include <rastreavel.h>

class leitor
{
private:
    const char *hos;
    const char *user;
    const char *pass;
    const char *db;
    unsigned int porta_;

    armazenamento store;
    comunicacao comunication;
    rastreavel rastreavel_[10];
    posicao pos;
    vector <unsigned int> tags;
    vector <unsigned char> ba;
   // rastreavel teste[10];
    vector <rastreavel> vet;
    int ntags;
public:
    leitor();
    void Graph();
    void Run();
    void OpenSerialComunication();

    //Serial genérico
    void ReadGeneric();
    void WriteGeneric();

    //Serial leitor AP-16
    void ReadAp16();
 //   void escrever_ap16();

    //Serial leitor LRX
    void ReadLrxFixedTag();
    void ReadLrxFixedReader();
    void WriteLrx();

    bool CheckTagExist(int id);
    int FindTagIndexByIdInt(long int id);
    int FindTagIndexByIdChar(const char *ide);
};

#endif // LEITOR_H
