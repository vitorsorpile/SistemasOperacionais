#include "FIFO.h"


FIFO::FIFO(unsigned int quadros/*, std::vector<unsigned int> paginas*/) 
   : paginasNaRAM(quadros, -1) 
{
   this->_quadros = quadros;
   this->quadrosDisponiveis = quadros;
   // this->_paginas = paginas;
}

FIFO::~FIFO() {}

// void FIFO::executar() {
//    auto i = std::max_element(this->_paginas.begin(), this->_paginas.end());
//    std::cout << "max: " << *i << std::endl;
// }

void FIFO::acessarPagina(int pagina) {
   static unsigned int pos = 0;
   // Página já está na RAM
   if (std::find(this->paginasNaRAM.begin(), this->paginasNaRAM.end(), pagina) != this->paginasNaRAM.end()) {
      return;
   }

   faltasDePagina++;
   // Existem quadros dísponíveis
   if (quadrosDisponiveis != 0) {
      this->paginasNaRAM[this->paginasNaRAM.size() - quadrosDisponiveis] = pagina;
      quadrosDisponiveis--;
      pos++;
      return;
   }
   // Todos os quadros estão ocupados'
   pos++;
   if (pos >= this->_quadros) pos = 0;
   this->paginasNaRAM[pos] = pagina;   
}

unsigned int FIFO::getFaltasDePagina() {
   return this->faltasDePagina;
}