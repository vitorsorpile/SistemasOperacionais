#include "Mensagem.h"

Mensagem::Mensagem(tipoDaMensagem tipo, unsigned int bebida, unsigned int qtd) {
      this->_tipo = tipo;
      this->_bebida = bebida;
      this->quantidade = qtd;
   }

   Mensagem::~Mensagem() {}

   tipoDaMensagem Mensagem::getTipo() {
      return this->_tipo;
   }

   unsigned int Mensagem::getBebida() {
      return this->_bebida;
   }

   unsigned int Mensagem::getQuantidade() {
      return this->quantidade;
   }