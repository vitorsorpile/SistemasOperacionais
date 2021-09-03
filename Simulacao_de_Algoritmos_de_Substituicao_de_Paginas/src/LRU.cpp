#include "LRU.h"

LRU::LRU(unsigned int quadros) 
   : paginasNaRAM(quadros) 
{
   this->quadrosDisponiveis = quadros;
}

LRU::~LRU() {}

void LRU::acessarPagina(const Pagina* pagina, unsigned int instante) {

   // Página já está na RAM
   pagina->setUltimoAcesso(instante);
   if (std::find(this->paginasNaRAM.begin(), this->paginasNaRAM.end(), pagina) != this->paginasNaRAM.end()) {
      return;
   }

   this->faltasDePagina++;

   // Existem quadros dísponíveis
   if (quadrosDisponiveis != 0) {
      this->paginasNaRAM[this->paginasNaRAM.size() - quadrosDisponiveis] = pagina;
      quadrosDisponiveis--;
 
      return;
   }

   // Encontra a página na RAM que foi acessada há mais tempo
   auto min = std::min_element(paginasNaRAM.begin(), paginasNaRAM.end(),
                             []( const Pagina *a, const Pagina *b )
                             {   
                                 return a->getUltimoAcesso() < b->getUltimoAcesso();
                             } );
   
   // Substitui a página encontrada
   this->paginasNaRAM[min - paginasNaRAM.begin()] = pagina;
   return;
   
}


unsigned int LRU::getFaltasDePagina() {
   return this->faltasDePagina;
}