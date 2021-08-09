#ifndef _SISTEMA_H
#define _SISTEMA_H

#include <vector>
#include <chrono>
#include <thread>
#include <memory>

#include "Processo.h"
#include "Escalonador.h"

class Sistema {
   private:
      int ciclo = 0;
      int nProcessosRestantes;
      std::vector<std::shared_ptr<Processo>> _processos;
      Escalonador* _escalonador;

      void enviarNovosProcessosProntosAoEscalonador();

   public:
      Sistema(std::vector<std::shared_ptr<Processo>> processos, Escalonador *escalonador);
      ~Sistema();

      void executar();
      void printCicloAtual();
};


#endif