#include "comunicacao.h"

using namespace boost::asio;

comunicacao::comunicacao():io() , serial(io)
{
}
////////// Abre comunicação serial ////////////
void comunicacao::abre_serial(string dispositivo,int baud_rate){
    unsigned int tam = 8;
    try{
        serial.open(dispositivo);
        serial.set_option(serial_port_base::baud_rate(baud_rate));
        serial.set_option(serial_port_base::character_size(tam));
    }catch(boost::system::system_error error){
        std::cout << "Erro ao abrir ou configurar o dispositivo serial. " << error.what() << endl;
    }
}
////////// Fecha comunicação serial ////////////
void comunicacao::fecha_serial(){
    if(serial.is_open()){
        serial.close();
    }
}

////////// Faz leitura serial ////////////
void comunicacao::ler_serial(vector<unsigned char> &buf, int quantidade){
    serial.read_some(buffer(buf, quantidade));
}

////////// Faz escrita serial ////////////
void comunicacao::escrever_serial(const vector<unsigned char> &buf){
    serial.write_some(buffer(buf, buf.size()));
}
