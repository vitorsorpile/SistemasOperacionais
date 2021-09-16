#ifndef _CLIENTE_H
#define _CLIENTE_H

#include "Socket.h"

class Cliente: public Socket::Client {
   public:
      Cliente(std::string address, short unsigned int port) ;
      ~Cliente();

      void fazerPedido(int* pedido);
      bool receberResposta();
};

#endif