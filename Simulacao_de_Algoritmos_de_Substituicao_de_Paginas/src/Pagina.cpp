#include "Pagina.h"

// Construtor e Destrutor
Pagina::Pagina(unsigned int id) {
   this->_id = id;
}

Pagina::~Pagina() {}


void Pagina::addAcessoFuturo(unsigned int instante) const {
   this->ordemDeAcessos.emplace_back(instante);
}

void Pagina::increaseIndexProximoAcesso() const {
   this->indexProximoAcesso++;
}

// SETs
void Pagina::setUltimoAcesso(unsigned int instante) const {
   this->ultimoAcesso = instante;
}

// GETs
unsigned int Pagina::getId() const {
   return this->_id;
}

unsigned int Pagina::getUltimoAcesso() const {
   return this->ultimoAcesso;
}
// Retorna o instante do próximo acesso ou o maior unsigned int possível caso a página já tenha sido acessada todas as vezes
unsigned int Pagina::getProximoAcesso() const {
   if (this->indexProximoAcesso < this->ordemDeAcessos.size()) 
      return this->ordemDeAcessos[this->indexProximoAcesso];
   
   return std::numeric_limits <unsigned int>::max();
}

// Sobrecarga de Operador
bool Pagina::operator==(const Pagina& o) const
  {
    if (this->_id == o._id) return true;
    
    return false;
  }