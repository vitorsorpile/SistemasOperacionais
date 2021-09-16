#ifndef _MENSAGEM_H
#define _MENSAGEM_H

enum class tipoDaMensagem {ENTRADA, PEDIDO, SAIDA};
   class Mensagem {

      private:
         tipoDaMensagem _tipo;
         unsigned int _bebida;
         unsigned int quantidade;


      public:
         Mensagem(tipoDaMensagem tipo= tipoDaMensagem::ENTRADA, unsigned int bebida = 0, unsigned int qtd = 0);
         ~Mensagem();

         // GETs
         tipoDaMensagem getTipo();
         unsigned int getBebida();
         unsigned int getQuantidade();
   };

#endif