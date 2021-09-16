#ifndef _LOJA_H
#define _LOJA_H

#include "Socket.h"
#include "Mensagem.h"

enum Bebidas {AGUA, CERVEJA, REFRIGERANTE};

class Loja: public Socket::Server {
   private:
      unsigned int estoque[3] = {0};
      // unsigned int nAguasDisponiveis;
      // unsigned int nCervejasDisponiveis;

      bool tratarPedido(int bebida, unsigned int quantidade);
      void imprimeEstoque();
      // void answerMessage(void *msg) override;

   public:
      // unsigned int nRefrigerantesDisponiveis;
      Loja(short unsigned int porta, unsigned int qtdAgua, unsigned int qtdCerveja, unsigned int qtdRefrigerante, unsigned int maxClientes = 30);
      ~Loja();

      void comecarExpediente();
   //   std::thread* receberMensagem() override;
   bool estoqueVazio(); 
      
};

#endif