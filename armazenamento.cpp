#include "armazenamento.h"

armazenamento::armazenamento()
{
}


// Salva os valores dos argumentos para conexão no banco de dados
void armazenamento::configura_bd(const char *host,const char *user,const char *pass,const char *database,unsigned int porta){
    set_host(host);
    set_user(user);
    set_password(pass);
    set_database(database);
    set_port(porta);
}

// Faz conexão com o banco de dados
void armazenamento::connect(){
    //    cout<<"CHEGOU AQUI || HOST->"<<get_host()<<endl;
    //    cout<<"CHEGOU AQUI || USER->"<<get_user()<<endl;
    //    cout<<"CHEGOU AQUI || PASSword->"<<get_password()<<endl;
    //    cout<<"CHEGOU AQUI || BANCO DE DADOS->"<<get_database()<<endl;
    mysql_init(&conexao);
    if( mysql_real_connect(&conexao,get_host(),get_user(),get_password(),get_database(),get_port(), NULL, 0) )
        cout<<"conectado com sucesso"<<endl;
    else{
        cout<<"Falha de conexao\n"<<endl;
        //   printf("Erro %d : %s\n", mysql_errno(&conexao), mysql_error(&conexao));
    }
}

// Método envia query que deve ser mensagem que não exiga retorno de dados
void armazenamento::envia(const char *query){
    if (mysql_query(&conexao, query)) {
        cout<<stderr<<"\n"<<mysql_error(&conexao);
    }
    mysql_close(&conexao);
}

// Método envia query2 que deve ser uma solicitação de dados e recebe os dados dentro do while
void armazenamento::envia_recebe(const char *query2){
    if (mysql_query(&conexao, query2)) {
        cout<<stderr<<"\n"<<mysql_error(&conexao);
    }
    res = mysql_use_result(&conexao);
    int num_fields = mysql_num_fields(res);
    while ((row = mysql_fetch_row(res)) != NULL){
        for(int i = 0; i < num_fields; i++)
        {
            //   printf("%s ", row[i] ? row[i] : "NULL");
            printf("%s ", row[i]);
        }
        printf("\n");
    }
    mysql_free_result(res);
    mysql_close(&conexao);
}

int**  armazenamento::recebe_capos(const char *query2){
    int aux1,aux2,cont=0;
    int **teste;
    teste = (int **) calloc (100,sizeof(int*));

    if (mysql_query(&conexao, query2)) {
        cout<<stderr<<"\n"<<mysql_error(&conexao);
    }
    int i;
    res = mysql_use_result(&conexao);
    int num_fields = mysql_num_fields(res);
    while ((row = mysql_fetch_row(res)) != NULL){
        for(i=0; i < num_fields; i++){
            teste[cont]=(int *) calloc (100,sizeof(int ));
            printf("%s \n", row[i]);
            aux1=atoi(row[i]);
            //   aux2=atoi(row[4]);
            teste[cont][0]=aux1;
            teste[0][1]=cont;
            //  teste[cont][1]=aux2;
          //  cout<< teste[cont][0]<<"CARAII ->"<<i<<"--"<<cont<<endl;
            //   printf("\n");
        cont+=1;
        }
       // teste[i][0]=666;
    }
    return teste;
}

//SETS
void armazenamento::set_host(const char *hosT){
    host=hosT;
}
void armazenamento::set_user(const char *useR){
    user=useR;
}
void armazenamento::set_password(const char *pass){
    password=pass;
}
void armazenamento::set_database(const char *db){
    database=db;
}
void armazenamento::set_port(unsigned int porta){
    port=porta;
}
//GETS
const char* armazenamento::get_host(){
    return host;
}
const char* armazenamento::get_user(){
    return user;
}
const char* armazenamento::get_password(){
    return password;
}
const char* armazenamento::get_database(){
    return database;
}
unsigned int armazenamento::get_port(){
    return port;
}

void armazenamento::encerra(){
    mysql_free_result(res);
    mysql_close(&conexao);
}

MYSQL armazenamento::get_mysql(){
    return this->conexao;
}
