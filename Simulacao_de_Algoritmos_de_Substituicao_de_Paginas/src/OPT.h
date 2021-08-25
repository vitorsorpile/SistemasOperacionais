#ifndef _OPT_H
#define _OPT_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

#include "Pagina.h"

class OPT {
   unsigned int _quadros;
   unsigned int quadrosDisponiveis;
   std::unordered_set<Pagina, Pagina::HashFunction> *_paginas;
   std::vector<const Pagina*> paginasNaRAM;
   unsigned int faltasDePagina = 0;

   public:
      OPT(unsigned int quadros, std::unordered_set<Pagina, Pagina::HashFunction> *paginas);
      ~OPT();
      void acessarPagina(const Pagina* pagina/*, int instante*/);

      void executar();

      unsigned int getFaltasDePagina();
};

#endif