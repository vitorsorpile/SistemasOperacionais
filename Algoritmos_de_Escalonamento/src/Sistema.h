#ifndef _SISTEMA_H
#define _SISTEMA_H

#include <vector>
#include <chrono>
#include <thread>
#include <memory>
#include <iomanip>

#include "Processo.h"
#include "Escalonador.h"


/* Classe responsável por controlar os processos e passá-los para o escalonador, assim como chamar o escalonador quando for
 * necessário escalonar e imprimir as estatísticas da execução */
class Sistema {
   private:
      int ciclo = 0;
      int nProcessosRestantes;
      int trocasDeContexto = 0;
      std::vector<std::shared_ptr<Processo>> _processos;
      Escalonador* _escalonador;

      // Envia para o escalonador os processos que ficam prontos no ciclo atual
      bool enviarNovosProcessosProntosAoEscalonador();

      // Incrementa o tempo de espera de todos os processos que estão prontos e não estão sendo executados
      void incrementarTemposDeEspera();

   public:
      
      Sistema(std::vector<std::shared_ptr<Processo>> processos, Escalonador *escalonador);
      ~Sistema();
      
      /* Executa até que todos os processos tenham terminado, faz chamadas ao escalonador quando necessário e imprime
       * o estado de todos os estados em cada ciclo e as estatísticas da execução no final */
      void executar();

      /* Imprime o estado de todos os processos no ciclo atual */
      void printCicloAtual();

      /* Imprime turnaround time e tempo de espera de cada processo e as médias de todos os processos, assim como o
       * número de trocas de contexto */
      void printEstatisticas();
};


#endif