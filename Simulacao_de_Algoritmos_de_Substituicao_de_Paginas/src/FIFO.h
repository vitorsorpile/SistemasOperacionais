#ifndef _FIFO_H
#define _FIFO_H

#include <iostream>
#include <vector>
#include <algorithm>

#include "Pagina.h"

// Classe que representa o algoritmo First In First Out, que retira da RAM a página que entrou primeiro.
class FIFO {
   unsigned int totalDeQuadros;                       // Número total de quadros na RAM
   unsigned int quadrosDisponiveis;                   // Número de quadros na RAM que não estão sendo utilizados
   std::vector<unsigned int> paginasNaRAM;            // Vector que armazena o id das páginas atualmente na RAM
   unsigned int posicaoDoQuadroASerSubstituido = 0;   // Contador de qual página deve ser substítuida 
   unsigned int faltasDePagina = 0;                   // Contador de faltas de página

   public:
      // Construtor e Destrutor
      FIFO(unsigned int quadros);
      ~FIFO();

      // Método que recebe um inteiro representando o id da página sendo acessada, colocando-a na RAM, caso já 
      // não esteja. Se a RAM já estiver cheia, subsititui a página que entrou primeiro na RAM.
      void acessarPagina(int pagina);

      // GETs
      unsigned int getFaltasDePagina();
};

#endif