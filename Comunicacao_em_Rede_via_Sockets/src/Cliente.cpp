#include "Cliente.h"


Cliente::Cliente(std::string address, short unsigned int port) 
         : Socket::Client(address, port)
      {
         char buffer[1024] = {0}; 
         read( sock , buffer, 1024);
         std::cout << buffer << std::endl;
      }

Cliente::~Cliente() {}

void Cliente::fazerPedido(int* pedido) {

   // Diminui 1 para fazer o acerto entre o número da bebida no menu
   // e no estoque da loja
   pedido[0] -= 1;
   this->sendMessage(pedido, 2*sizeof(int));
}

bool Cliente::receberResposta() {
   char buffer[1025];
   long int valread = read(this->sock, buffer, 1024);
   
   std::cout << valread << std::endl;
   if (valread == 0) return false;

   buffer[valread] = '\0';
   std::cout << buffer << std::endl;
   return true;
}