#ifndef ARMAZENAMENTO_H
#define ARMAZENAMENTO_H
#include <vector>
#include <mysql/mysql.h>
#include <iostream>
#include <fstream>
#include <string.h>

#include <allegro5/allegro.h>

using namespace std;

class armazenamento
{
private:
   const char* host;
   const char* user;
   const char* password;
   const char* database;
   unsigned int port;
   const char* socket;
   const char* client_flag;
    MYSQL_RES *res;
    MYSQL_ROW row;
    MYSQL conexao;

  //  char campos[10000][2];

public:
    armazenamento();
    void envia(const char *);
    void envia_recebe(const char *);
    void configura_bd(const char *,const char *,const char * ,const char *,unsigned int porta);
    int** recebe_capos(const char *);

    void encerra();
    //sets
    void set_host(const char *);
    void set_user(const char *);
    void set_password(const char *);
    void set_database(const char *);
    void set_port(unsigned int porta);
    void set_socket(const char *);
    void set_client_flag(const char *);

    //gets
    const char* get_host();
   const char* get_user();
   const char* get_password();
   const char* get_database();
   unsigned int get_port();
   const char* get_socket();
   const char* get_client_flag();
    MYSQL   get_mysql();
    void connect();
};

#endif // ARMAZENAMENTO_H
