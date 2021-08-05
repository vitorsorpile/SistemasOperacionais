#ifndef _PROCESSO_H
#define _PROCESSO_H

#include <iostream>

class Processo {
   
   int id;
   int dataDeCriacao;
   int duracao;
   int prioridade;
   int tempoExecutado = 0;
   int tempoPronto = 0;

   public:
      Processo(int id, int criacao, int duracao, int prioridade);
      ~Processo();

      // Sobrecargas de operador
      bool operator< (const Processo &other) const;
      friend std::ostream& operator<<(std::ostream& os, const Processo& processo);
};




#endif