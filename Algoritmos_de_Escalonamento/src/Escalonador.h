#ifndef _ESCALONADOR_H
#define _ESCALONADOR_H

#include <algorithm>
#include <vector>

#include "Processo.h"

class Escalonador {
   protected:
      std::vector<Processo*> _processos;
      Processo* processoAtual = nullptr;
      bool preemptavel = false;
      int _quantum = -1;
      int _fatorDeEnvelhecimento = 0;


   public:
      Escalonador();
      ~Escalonador();

      // virtual bool precisaEscalonar() = 0;
      virtual void escalonaProcessos() = 0; 
      void envelhecerProcessos(int fatorDeEnvelhecimento);

      Processo* getProcessoAtual();
      bool getPreemptavel();
      int getQuantum();
      int getFatorDeEnvelhecimento();

      void adicionarProcesso(Processo* processo);
      void removerProcesso(Processo* processo);
      
};


#endif