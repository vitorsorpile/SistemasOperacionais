#include "OPT.h"

OPT::OPT(unsigned int quadros) 
   : paginasNaRAM(quadros, nullptr) 
{
   this->quadrosDisponiveis = quadros;
}

OPT::~OPT() {}

void OPT::acessarPagina(const Pagina* pagina) {

   // Página já está na RAM
   if (std::find(this->paginasNaRAM.begin(), this->paginasNaRAM.end(), pagina) != this->paginasNaRAM.end()) {
      pagina->increaseIndexProximoAcesso();
      return;
   }

   this->faltasDePagina++;
 
   // Existem quadros dísponíveis
   if (quadrosDisponiveis != 0) {
      this->paginasNaRAM[this->paginasNaRAM.size() - quadrosDisponiveis] = pagina;
      quadrosDisponiveis--;
      pagina->increaseIndexProximoAcesso();
      return;
   }

   // Encontra a página na RAM que ficará mais tempo sem ser acessada 
   auto it = std::max_element(paginasNaRAM.begin(), paginasNaRAM.end(),
                             []( const Pagina *a, const Pagina *b )
                             {   
                                 return a->getProximoAcesso() < b->getProximoAcesso();
                             } );

   // Substitui a página encontrada
   this->paginasNaRAM[it - paginasNaRAM.begin()] = pagina;

   pagina->increaseIndexProximoAcesso();
   return;
}


unsigned int OPT::getFaltasDePagina() {
   return this->faltasDePagina;
}