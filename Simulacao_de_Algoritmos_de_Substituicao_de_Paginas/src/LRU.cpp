#include "LRU.h"

LRU::LRU(unsigned int quadros/*, std::vector<unsigned int> paginas*/) 
   : paginasNaRAM(quadros) 
{
   this->_quadros = quadros;
   this->quadrosDisponiveis = quadros;
   // this->_paginas = paginas;
}

LRU::~LRU() {}

// void LRU::executar() {
//    auto i = std::max_element(this->_paginas.begin(), this->_paginas.end());
//    std::cout << "max: " << *i << std::endl;
// }

void LRU::acessarPagina(const Pagina* pagina, unsigned int instante) {
   // static unsigned int pos = 0;
   // Página já está na RAM
   // std::cout << "recebeu pagina: " << pagina << std::endl;
   pagina->setUltimoAcesso(instante);
   if (std::find(this->paginasNaRAM.begin(), this->paginasNaRAM.end(), pagina) != this->paginasNaRAM.end()) {
      return;
   }

   faltasDePagina++;
   // std::cout << "Faltou pagina: " << pagina << std::endl;
   // Existem quadros dísponíveis

   if (quadrosDisponiveis != 0) {
      this->paginasNaRAM[this->paginasNaRAM.size() - quadrosDisponiveis] = pagina;
      quadrosDisponiveis--;
      // pos++;
      return;
   }

   // Ordena as páginas na RAM em ordem crescente de último acesso
   // std::sort(paginasNaRAM.begin(), paginasNaRAM.end(), 
   //    [](const Pagina *x, const Pagina *y) {
   //       return x->getUltimoAcesso() < y->getUltimoAcesso();
   // });

   auto min = std::min_element(paginasNaRAM.begin(), paginasNaRAM.end(),
                             []( const Pagina *a, const Pagina *b )
                             {   
                              //   std::cout << "a: " << a->getUltimoAcesso() << " | b: " << b->getUltimoAcesso() << std::endl; 
                                 return a->getUltimoAcesso() < b->getUltimoAcesso();
                             } );
   
   // std::cout << min - paginasNaRAM.begin() << std::endl;
   this->paginasNaRAM[min - paginasNaRAM.begin()] = pagina;
   return;
   // Todos os quadros estão ocupados'
   // pos++;
   // if (pos >= this->_quadros) pos = 0;
   // this->paginasNaRAM[pos] = pagina;
   
}


unsigned int LRU::getFaltasDePagina() {
   return this->faltasDePagina;
}