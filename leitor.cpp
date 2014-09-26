#include "leitor.h"
#include <iomanip>
//#include <QDebug>
#include <QLineEdit>
#include <QLineEdit>
#include <QApplication>
#include <QString>
#include <objetos.h>
#define NTAGS 4         //NUMERO DE TAGS CADASTRADAS (EXATO)

//**************************************************************************
//
// Nome     :  leitor
// Descrição:  Constructor Method
//
//**************************************************************************
leitor::leitor(){
    //ESCOLHER BANCO DE DADOS E SETAR IDS E POSIÇÕES DAS TAGS
    hos= "127.0.0.1";
    user= "root";
    pass= "root";
    db= "rfid";
    porta_=0;
    ntags = 0;
    /*
    FILE *arq;
    arq = fopen ("/home/lucas/Computação/Qt Creator/amrz010/rastreaveis", "r");
    fscanf(arq, "%s", SERVER);
    fscanf(arq, "%s", USER);
    fscanf(arq, "%s", PASSWORD);
    fscanf(arq, "%s", DATABASE);

    fclose(arq);
      */
    rastreavel_[99].set_id_INT(1616); //Leitor fixo AP-16

    rastreavel_[0].set_posXY(30,20);
    rastreavel_[0].set_id_CHAR("2B001EC4DF");

    rastreavel_[1].set_posXY(60,80);
    rastreavel_[1].set_id_CHAR("2B001EB50B");

    rastreavel_[2].set_posXY(120,70);
    rastreavel_[2].set_id_CHAR("2B001ED765");

    rastreavel_[3].set_posXY(30,20);
    rastreavel_[3].set_id_CHAR("2B001EC4DF");

    int ii;
    ii=FindTagIndexByIdChar(rastreavel_[2].get_id_CHAR());
    cout<<"VALOR RECEBIDO COMO INDICE->"<<ii<<endl;
    // rastreavel_[3].set_posXY(2,14);
    // rastreavel_[4].set_id(123454);
    // rastreavel_[4].set_posXY(2,20);
    // rastreavel_[5].set_id(123455);
    // rastreavel_[5].set_posXY(2,26);
    //considerar primeira tag/leitor (0,0)
}

//**************************************************************************
//
// Nome     :  Run
// Descrição:  Call Serial Comunication
//
//**************************************************************************
void leitor::Run(){
    OpenSerialComunication();
}

//**************************************************************************
//
// Nome     :  Graph
// Descrição:  Start Graphic Visualization Module
//
//**************************************************************************
void leitor::Graph(){
    graphics graf;
    graf.graphics_main(2); //DEFAULT = 1.0
}

//**************************************************************************
//
// Nome     :  OpenSerialComunication
// Descrição:  Open serial comunication and manages change messages
//
//**************************************************************************
void leitor::OpenSerialComunication(){
    //ttyACM0
    //ttyUSB0
    //115200
    comunication.abre_serial("/dev/ttyUSB0",9600);
    //   boost::thread thread_escrita(&leitor::escrever_lrx,this);
    boost::thread thread_leitura(&leitor::ReadAp16,this);
    //   boost::thread thread_graph(&leitor::graph,this);
    Graph();
    //thread_graph.join();
    // thread_escrita.join();
    thread_leitura.join();
}

//**************************************************************************
//
// Nome     :  WriteLrx
// Descrição:  Do writing to Reader LRX201
//
//**************************************************************************
void leitor::WriteLrx(){
    int i;
    //    sleep(5);
    vector <unsigned char> ba2;
    // Monta mensagem com o comando digitado
    //ba2.push_back(0xFF);//header
    //ba2.push_back('*');//lenght
    ba2.push_back(0xAA);//header
    ba2.push_back(0x00);//lenght
    ba2.push_back(0);//networkid
    ba2.push_back(0);//receiverid
    ba2.push_back(0);//nodeid
    ba2.push_back(0x01);//command
    for(int i=0;i<0;i++)   //data
    {
        ba2.push_back(0);
    }
    ba2.push_back(0);
    //Envia mensagem
    for(i=0;i<10;i++){
        cout<<"Escrevendo na serial"<<endl;
        comunication.escrever_serial(ba2);
    }
    //Limpa pacote
    ba2.clear();
}

//**************************************************************************
//
// Nome     :  ReadLrxFixedTag
// Descrição:  Do reading from Reader LRX201 with Fixed Tags
//
//**************************************************************************
void leitor::ReadLrxFixedTag(){
    //Faz leitura protocolo lrx
    for(;;){
        vector<unsigned char> aux(1);
        //int flag=0
        int cont=0;
        ba.clear();
        ba.resize(200);
        comunication.ler_serial(aux,1);
        ba.at(0)=aux.at(0);
        cont++;
        if(ba.at(0)== 0x55)
        {
            //qDebug()<<"Cabecalho recebido"<<hex<<ba.at(0)<<endl;
            for(int i=0;i<5;i++)
            {
                comunication.ler_serial(aux,1);
                ba.at(cont) = aux.at(0);
                cont++;
            }
            //qDebug()<<"Tamanho do pacote-> "<<(int)ba.at(1)<<"| NeID-> "<<ba.at(2)<<"| RecID-> "<<ba.at(3)<<"| NodeID-> "<<ba.at(4)<<"| Comandodo-> "<<ba.at(5)<<endl;
            for(int i=0;i<(int)ba.at(1);i++)
            {
                comunication.ler_serial(aux,1);
                ba.at(cont) = aux.at(0);
                //       flag=1;
                cont++;
            }
            if(ba.at(1)>0 && ba.at(5)==0x06){
                unsigned int TAGID,intensity;
                //teste=(unsigned char)ba.at(22)<<24|(unsigned char)ba.at(23) <<16 | (unsigned char)ba.at(24) << 8 ;
                cout<<(unsigned int)ba.at(22)<<"<->"<<(unsigned int)ba.at(23)<<"<->"<<(unsigned int)ba.at(24)<<"<->"<<(unsigned int)ba.at(25)<<endl;
                TAGID = (unsigned char)ba.at(22) << 24 | (unsigned char)ba.at(23) <<16 | (unsigned char)ba.at(24) << 8 | (unsigned char)ba.at(25);
                cout<<"tag id = " << TAGID<< endl;
                intensity=(unsigned) ba.at(28);
                cout <<  "Intensidade do sinal = " << intensity << endl;
                ///////////////////////////////////////////////////////////////////////////////////////////////////
                // Se leitores ficarem estáticos e tags se mexerem, guardar os Ids dos leitores, quando         ///
                // ntags>=4 então calcular posição da tag, enviando o vetor de rastreável, mas antes setar valor///
                //de intensidade do letor(da pra dizer que é raio de leitura).                                  ///
                //salvar no bd a posição calculada e o ID da tag                                                ///
                ///////////////////////////////////////////////////////////////////////////////////////////////////
                //Verifica se a tag lida é nova ou ja foi salva
                int verificacao,indice;
                verificacao=CheckTagExist(TAGID);
                if(verificacao==0){ //Se nova tag lida e ainda não armazenada, armazena
                    tags.push_back(TAGID);
                    indice=FindTagIndexByIdInt(TAGID); //Descobre o indice do objeto que tem o ID lido
                    rastreavel_[indice].set_intensity(intensity);
                    vet.push_back(rastreavel_[indice]); //Salva o objeto no vetor de objetos posição
                }
                if(ntags>=4){    //Depois de receber 4 tags é calculada a posiçãodo leitor
                    float x_calc,y_calc;
                    ntags=0;
                    cout<<"TAMANHO DO VETOR->"<<vet.size();
                    pos.calcula_posicao(vet,vet.size()); //Calcula a posição passando o vetor de posicao e o tamanho dele
                    x_calc=pos.get_pos_calculada_X();//PEGAR pos.getX
                    y_calc=pos.get_pos_calculada_Y();//PEGAR pos.getY
                    cout<<"VALOR DE x ->"<<x_calc<<" VALOR DE Y->"<<y_calc<<endl;
                    //MUDAR DADO SALVO NO BD, USAR VALOR CALCULADO AO INVÉS DA POSIÇÃO DA TAG, SALVAR O ID DO LEITOR TMB
                    char query[200];
                    //Mudar string para os parâmetros corretos
                    sprintf(query,"insert into ap16(date,id,intensity,posX,posY) values(NOW(),1234,\"%f\",\"%f\",000)",x_calc,y_calc);
                    store.configura_bd(hos,user,pass,db,porta_);
                    store.connect();
                    store.envia(query);
                    // store.envia_recebe(query2);
                    //limpar vetor com rastreáveis
                    vet.clear();
                    tags.clear();
                }
                ntags=ntags+1;
            }
            comunication.ler_serial(aux,1);
            ba.at(cont) = aux.at(0);
            cont++;
        }
    }
}

//**************************************************************************
//
// Nome     :  ReadLrxFixedReader
// Descrição:  Do reading from Reader LRX201 with Fixed Readers
//
//**************************************************************************
void leitor::ReadLrxFixedReader(){
    for(;;){
        vector<unsigned char> aux(1);
        //int flag=0
        int cont=0;
        ba.clear();
        ba.resize(200);
        comunication.ler_serial(aux,1);
        ba.at(0)=aux.at(0);
        cont++;
        if(ba.at(0)== 0x55)
        {
            //qDebug()<<"Cabecalho recebido"<<hex<<ba.at(0)<<endl;
            for(int i=0;i<5;i++)
            {
                comunication.ler_serial(aux,1);
                ba.at(cont) = aux.at(0);
                cont++;
            }
            //qDebug()<<"Tamanho do pacote-> "<<(int)ba.at(1)<<"| NeID-> "<<ba.at(2)<<"| RecID-> "<<ba.at(3)<<"| NodeID-> "<<ba.at(4)<<"| Comandodo-> "<<ba.at(5)<<endl;
            for(int i=0;i<(int)ba.at(1);i++)
            {
                comunication.ler_serial(aux,1);
                ba.at(cont) = aux.at(0);
                //       flag=1;
                cont++;
            }
            if(ba.at(1)>0 && ba.at(5)==0x06){
                unsigned int TAGID,intensity;
                //teste=(unsigned char)ba.at(22)<<24|(unsigned char)ba.at(23) <<16 | (unsigned char)ba.at(24) << 8 ;
                cout<<(unsigned int)ba.at(22)<<"<->"<<(unsigned int)ba.at(23)<<"<->"<<(unsigned int)ba.at(24)<<"<->"<<(unsigned int)ba.at(25)<<endl;
                TAGID = (unsigned char)ba.at(22) << 24 | (unsigned char)ba.at(23) <<16 | (unsigned char)ba.at(24) << 8 | (unsigned char)ba.at(25);
                cout<<"tag id = " << TAGID<< endl;
                intensity=(unsigned) ba.at(28);
                cout <<  "Intensidade do sinal = " << intensity << endl;
                ///////////////////////////////////////////////////////////////////////////////////////////////////
                // Se leitores ficarem estáticos e tags se mexerem, guardar os IDS DOS LEITORES, quando         ///
                // ntags>=4 então calcular posição da tag, enviando o vetor de rastreável, mas antes setar valor///
                //de intensidade do letor(da pra dizer que é raio de leitura).                                  ///
                //salvar no bd a posição calculada e o ID da tag                                                ///
                ///////////////////////////////////////////////////////////////////////////////////////////////////
                //Verifica se a tag lida é nova ou ja foi salva
                int verificacao,indice;
                verificacao=CheckTagExist(TAGID);
                if(verificacao==0){ //Se nova tag lida e ainda não armazenada, armazena
                    tags.push_back(TAGID);
                    indice=FindTagIndexByIdInt(TAGID); //Descobre o indice do objeto que tem o ID lido
                    rastreavel_[indice].set_intensity(intensity);
                    vet.push_back(rastreavel_[indice]); //Salva o objeto no vetor de objetos posição
                }
                if(ntags>=4){    //Depois de receber 4 tags é calculada a posiçãodo leitor
                    float x_calc,y_calc;
                    ntags=0;
                    cout<<"TAMANHO DO VETOR->"<<vet.size();
                    pos.calcula_posicao(vet,vet.size()); //Calcula a posição passando o vetor de posicao e o tamanho dele
                    x_calc=pos.get_pos_calculada_X();//PEGAR pos.getX
                    y_calc=pos.get_pos_calculada_Y();//PEGAR pos.getY
                    cout<<"VALOR DE x ->"<<x_calc<<" VALOR DE Y->"<<y_calc<<endl;
                    //MUDAR DADO SALVO NO BD, USAR VALOR CALCULADO AO INVÉS DA POSIÇÃO DA TAG, SALVAR O ID DO LEITOR TMB
                    char query[200];
                    //Mudar string para os parâmetros corretos
                    sprintf(query,"insert into ap16(date,id,intensity,posX,posY) values(NOW(),1234,\"%f\",\"%f\",000)",x_calc,y_calc);
                    store.configura_bd(hos,user,pass,db,porta_);
                    store.connect();
                    store.envia(query);
                    // store.envia_recebe(query2);
                    //limpar vetor com rastreáveis
                    vet.clear();
                    tags.clear();
                }
                ntags=ntags+1;
            }
            comunication.ler_serial(aux,1);
            ba.at(cont) = aux.at(0);
            cont++;
        }
    }
}

//**************************************************************************
//
// Nome     :  WriteGeneric
// Descrição:  Do writing to Generic Reader
//
//
//**************************************************************************
void leitor::WriteGeneric(){
    int i;
    vector <unsigned char> ba;
    //Monta mensagem com o comando
    // ba.push_back(0xFF);//header
    // ba.push_back('*');//lenght
    //  ba.push_back(0);//networkid
    //  ba.push_back(0);//receiverid
    //  ba.push_back(0);//nodeid
    //  ba.push_back(0x01);//command
    //  for(int i=0;i<0;i++)   //data
    //  {
    //      ba.push_back(0);
    //  }
    //  ba.push_back(0);
    //Envia mensagem
    for(i=0;i<5;i++){
        cout<<"Escrevendo na serial"<<endl;
        comunication.escrever_serial(ba);
    }
}

//**************************************************************************
//
// Nome     :  ReadGeneric
// Descrição:  Do Reading from Generic Reader
//
//**************************************************************************
void leitor::ReadGeneric(){
    vector<unsigned char> aux(1);
    //int x;
    for(;;){
        comunication.ler_serial(aux,1);
    }
}

//**************************************************************************
//
// Nome     :  ReadAp16
// Descrição:  Do Reading from Reader AP-16
//
//**************************************************************************
void leitor::ReadAp16(){
    char ident[10];
    // char ide[10];
    // ide = (const char*)malloc(10*sizeof(const char));
    vector<unsigned char> aux(1);
    int indice,q;
    for(;;){
        comunication.ler_serial(aux,1);
        if((int)aux.at(0)==2){
            //  cout<<"Tag id ->";
            for(q=0;q<10;q++){
                comunication.ler_serial(aux,1);
                cout<<endl;
                //    cout<<aux.at(0);
                ident[q]=(aux.at(0));
                cout<<ident[q];
            }
            ident[q] = '\0';

            //  strcpy(ide,ident);
            //  cout<<endl;
            // cout<<ide<<endl;
            fprintf(stderr, "IDENT: %s\n", ident);
            indice=FindTagIndexByIdChar(ident);// PASSAR ID DA TAG LIDO PELO LEITOR, RECEBE INDICE
            //fprintf(stderr, "CHECKPOINT BRAVO\n");
            cout<<"VALOR DO INDICE = "<<indice<<endl;
            char query[200];
            sprintf(query,"insert into ap16 values(NOW(),\"%s\",\"99\",\"%f\",\"%f\")",rastreavel_[indice].get_id_CHAR(),rastreavel_[indice].get_posX(),rastreavel_[indice].get_posY());
            cout<<query<<endl;
            //fprintf(stderr, "%s\nCHECKPOINT CHARLIE\n", query);
            store.configura_bd(hos,user,pass,db,porta_);
            store.connect();
            store.envia(query);
        }
    }
}

//**************************************************************************
//
// Nome     :  CheckTagExist
// Descrição:  Check if Tag id is into vector
//
//**************************************************************************
bool leitor::CheckTagExist(int id){
    for(int f=0;f<(int)tags.size();f++){
        if(id == (int)tags.at(f)){

            return 1;
        }
    }
    return 0;
}

//**************************************************************************
//
// Nome     :  FindTagIndexByIdInt
// Descrição:  Find index of Tag ID Integer
//
//**************************************************************************
int leitor::FindTagIndexByIdInt(long int id){
    for(int i=1;i<10;i++){
        if(rastreavel_[i].get_id_INT()==id){
            return i;
        }
    }
    fprintf(stderr, "FindTagIndexByIdInt says: TAG NOT FOUND\n");
    return 0;
}

//**************************************************************************
//
// Nome     :  FindTagIndexByIdChar
// Descrição:  Find index of Tag ID Integer
//
//**************************************************************************
int leitor::FindTagIndexByIdChar(const char *ide){
    fprintf(stderr, "IDE em FindTagIndexByIdChar: %s\n", ide);
    for(int i=1;i<NTAGS;i++){
        if(!strcmp(rastreavel_[i].get_id_CHAR(),ide)){
            return i;
        }
    }
    fprintf(stderr, "FindTagIndexByIdChar says: TAG NOT FOUND\n");
    return 0;
}

