#include "Pagina.h"

Pagina::Pagina(unsigned int id) {
   this->_id = id;
}

// Pagina::Pagina(const Pagina& pag) {
//    this->_id = pag._id;
//    this->ultimoAcesso = pag.ultimoAcesso;
// }

Pagina::~Pagina() {}


void Pagina::setUltimoAcesso(unsigned int instante) const {
   this->ultimoAcesso = instante;
}

void Pagina::addAcessoFuturo(unsigned int instante) const {
   this->ordemDeAcessos.emplace_back(instante);
}

void Pagina::increaseIndexProximoAcesso() const {
   this->indexProximoAcesso++;
}

unsigned int Pagina::getId() const {
   return this->_id;
}

unsigned int Pagina::getUltimoAcesso() const {
   return this->ultimoAcesso;
}

unsigned int Pagina::getProximoAcesso() const {
   if (this->indexProximoAcesso < this->ordemDeAcessos.size()) 
      return this->ordemDeAcessos[this->indexProximoAcesso];
   
   return std::numeric_limits <unsigned int>::max();
}


bool Pagina::operator==(const Pagina& o) const
  {
    if (this->_id == o._id) return true;
    
    return false;
  }