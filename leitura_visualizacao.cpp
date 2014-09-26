#include "objetos.h"
#include <QMessageBox>
#include <iostream>
//#include <mysql/mysql.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <interfacearmz.h>
//#include <qdebug.h>

using namespace std;

const char SERVER[30]="127.0.0.1";
const char USER[30]="root";
const char PASSWORD[30]="root";
const char DATABASE[30]="rfid";
int chaves[1000000];
const int MAX = 10000;
const char *REQ01 = "SELECT * FROM ap16";
const char *REQ02 = "SELECT CHAVE FROM leitura";

int leitura_visualizacao::conectar(dadosBD *retorno){
    dealQuery queryObj;
    MYSQL_RES *res; /* Create a pointer to recieve the return value.*/
    MYSQL_ROW row;  /* Assign variable for rows. */
    MYSQL connect; // Create a pointer to the MySQL instance

    mysql_init(&connect);
    //fprintf(stderr, "QUERY: %s\n", queryObj.get().c_str());

     if( mysql_real_connect(&connect,SERVER,USER,PASSWORD,DATABASE,0,NULL,0) )
         cout<<"conectado com sucesso"<<endl;
     else{
         cout<<"Falha de conexao\n"<<endl;
         //   printf("Erro %d : %s\n", mysql_errno(&conexao), mysql_error(&conexao));
     }
     if (mysql_query(&connect, queryObj.get().c_str())) {
         cout<<stderr<<"\n"<<mysql_error(&connect);
     }
    //mysql_query(&connect, REQ01);
    unsigned int i = 0;
    res = mysql_use_result(&connect);
    //int num_fields = mysql_num_fields(res);
   // cout<<"VALOR DE ROW->"<<row<<endl;
    while ((row = mysql_fetch_row(res)))
    {
    //    unsigned long *lengths;
     //   lengths = mysql_fetch_lengths(res);
    //    cout<<"ID LIDO->"<<row[1]<<"|valor de i-> "<<i<<endl;
    //    cout<<"X LIDO->"<<row[2]<<"|valor de i-> "<<i<<endl;
    //    cout<<"Y LIDO->"<<row[3]<<"|valor de i-> "<<i<<endl;
        retorno[i].ID = row[1];
        retorno[i].x = atoi(row[3]);
        retorno[i].y = atoi(row[4]);
        i++;
    }
    retorno[i].ID = "---";
    mysql_free_result(res);
    mysql_close(&connect);
    return i;
 
}
