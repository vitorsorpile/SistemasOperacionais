#ifndef _ESCALONADOR_H
#define _ESCALONADOR_H

#include <vector>

#include "Processo.h"

class Escalonador {
   private:
      std::vector<Processo> _processos;

   public:
      Escalonador(std::vector<Processo> processos);
      ~Escalonador();
};


#endif