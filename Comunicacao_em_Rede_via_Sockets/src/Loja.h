#ifndef _LOJA_H
#define _LOJA_H

#include "Socket.h"

enum Bebidas {AGUA, CERVEJA, REFRIGERANTE};

class Loja: public Socket::Server {
   private:
      unsigned int estoque[3] = {0};


      bool tratarPedido(int bebida, unsigned int quantidade);
      void imprimeEstoque();
      bool estoqueVazio(); 

   public:

      Loja(short unsigned int porta, unsigned int qtdAgua, unsigned int qtdCerveja, unsigned int qtdRefrigerante, unsigned int maxClientes = 30);
      ~Loja();

      void comecarExpediente();      
};

#endif