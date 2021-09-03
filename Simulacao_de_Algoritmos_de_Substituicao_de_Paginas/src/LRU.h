#ifndef _LRU_H
#define _LRU_H

#include <iostream>
#include <vector>
#include <algorithm>

#include "Pagina.h"

// Classe que representa o algoritmo Least Recent Used, que retira da RAM a página que foi acessada há mais tempo.
class LRU {
   unsigned int quadrosDisponiveis;             // Número de quadros na RAM que não estão sendo utilizados
   std::vector<const Pagina*> paginasNaRAM;     // Vector que armazena as páginas atualmente na RAM
   unsigned int faltasDePagina = 0;             // Contador de faltas de página

   public:
      // Construtor e Destrutor
      LRU(unsigned int quadros);
      ~LRU();

      // Método que recebe um ponteiro para a página sendo acessada e o instante atual e coloca a página na RAM, caso já 
      // não esteja. Se a RAM já estiver cheia, subsititui a página que foi acessada há mais tempo.
      void acessarPagina(const Pagina* pagina, unsigned int instante);

      // GETs
      unsigned int getFaltasDePagina();
};

#endif