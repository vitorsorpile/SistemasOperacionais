#ifndef _OPT_H
#define _OPT_H

#include <iostream>
#include <vector>
#include <algorithm>

#include "Pagina.h"

// Classe que representa o algoritmo ótimo, que retira da RAM a página que ficará mais tempo sem ser acessada.
class OPT {
   
   unsigned int quadrosDisponiveis;             // Número de quadros na RAM que não estão sendo utilizados
   std::vector<const Pagina*> paginasNaRAM;     // Vector que armazena as páginas atualmente na RAM
   unsigned int faltasDePagina = 0;             // Contador de faltas de página

   public:
      // Construtor e Destrutor
      OPT(unsigned int quadros);
      ~OPT();

      // Método que recebe um ponteiro para a página sendo acessada, colocando-a na RAM, caso já não esteja. Se a RAM já
      // estiver cheia, subsititui a página que demorará mais para ser acessada.
      void acessarPagina(const Pagina* pagina);

      // GETs
      unsigned int getFaltasDePagina();
};

#endif