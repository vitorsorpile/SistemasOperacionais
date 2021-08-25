#ifndef _LRU_H
#define _LRU_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

#include "Pagina.h"

class LRU {
   unsigned int _quadros;
   unsigned int quadrosDisponiveis;
   std::vector<unsigned int> _paginas;
   std::vector<const Pagina*> paginasNaRAM;
   unsigned int faltasDePagina = 0;

   public:
      LRU(unsigned int quadros);
      ~LRU();
      void acessarPagina(const Pagina* pagina, unsigned int instante);

      void executar();

      unsigned int getFaltasDePagina();
};

#endif