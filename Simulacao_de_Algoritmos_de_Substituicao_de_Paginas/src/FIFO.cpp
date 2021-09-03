#include "FIFO.h"

// Construtor e Destrutor
FIFO::FIFO(unsigned int quadros) 
   : paginasNaRAM(quadros, -1) 
{
   this->totalDeQuadros = quadros;
   this->quadrosDisponiveis = quadros;
}

FIFO::~FIFO() {}


void FIFO::acessarPagina(int pagina) {
   // Página já está na RAM
   if (std::find(this->paginasNaRAM.begin(), this->paginasNaRAM.end(), pagina) != this->paginasNaRAM.end()) {
      return;
   }

   this->faltasDePagina++;

   // Existem quadros dísponíveis
   if (quadrosDisponiveis != 0) {
      this->paginasNaRAM[this->paginasNaRAM.size() - quadrosDisponiveis] = pagina;
      quadrosDisponiveis--;
      posicaoDoQuadroASerSubstituido++;
      return;
   }

   // Todos os quadros estão ocupados
   posicaoDoQuadroASerSubstituido++;
   if (posicaoDoQuadroASerSubstituido >= this->totalDeQuadros) posicaoDoQuadroASerSubstituido = 0;
   this->paginasNaRAM[posicaoDoQuadroASerSubstituido] = pagina;   
}


// GETs
unsigned int FIFO::getFaltasDePagina() {
   return this->faltasDePagina;
}