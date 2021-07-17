#include "Pessoa.h"

Pessoa::Pessoa(int pessoaId) 
   : std::thread(threadFunction, this)
{
   this->_id = pessoaId;
}

Pessoa::~Pessoa() {}

void Pessoa::behavior() {
   
   std::cout << "dale" << this->_id << std::endl;
   return;
}

void Pessoa::threadFunction(Pessoa *This) {
   return This->behavior();
}