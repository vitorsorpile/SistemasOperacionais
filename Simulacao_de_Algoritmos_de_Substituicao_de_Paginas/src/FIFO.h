#ifndef _SISTEMA_H
#define _SISTEMA_H

#include <iostream>
#include <vector>
#include <algorithm>
// #include <unordered_map>

#include "Pagina.h"

class FIFO {
   unsigned int _quadros;
   unsigned int quadrosDisponiveis;
   // std::vector<unsigned int> _paginas;
   std::vector<unsigned int> paginasNaRAM;
   unsigned int faltasDePagina = 0;

   public:
      FIFO(unsigned int quadros /*, std::vector<unsigned int> paginas */);
      ~FIFO();
      void acessarPagina(int pagina);

      void executar();

      unsigned int getFaltasDePagina();
};

#endif