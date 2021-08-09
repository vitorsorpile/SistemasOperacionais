#ifndef _ESCALONADOR_H
#define _ESCALONADOR_H

#include <algorithm>
#include <vector>

#include "Processo.h"

class Escalonador {
   private:
      std::vector<Processo*> _processos;
      Processo* processoAtual = nullptr;
      bool preemptavel = false;


   public:
      Escalonador();
      ~Escalonador();

      // virtual void escalonaProcessos() = 0; 
      void escalonaProcessos();

      Processo* getProcessoAtual();
      bool getPreemptavel();

      void adicionarProcesso(Processo* processo);
      void removerProcesso(Processo* processo);
      
};


#endif