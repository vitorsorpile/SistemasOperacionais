#ifndef _SISTEMA_H
#define _SISTEMA_H

#include <vector>
#include <chrono>
#include <thread>
#include <memory>
#include <iomanip>

#include "Processo.h"
#include "Escalonador.h"

class Sistema {
   private:
      int ciclo = 0;
      int nProcessosRestantes;
      int trocasDeContexto = 0;
      std::vector<std::shared_ptr<Processo>> _processos;
      Escalonador* _escalonador;

      bool enviarNovosProcessosProntosAoEscalonador();
      void incrementarTemposDeEspera();

   public:
      Sistema(std::vector<std::shared_ptr<Processo>> processos, Escalonador *escalonador);
      ~Sistema();

      void executar();
      void printCicloAtual();
};


#endif