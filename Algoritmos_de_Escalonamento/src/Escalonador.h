#ifndef _ESCALONADOR_H
#define _ESCALONADOR_H

#include <algorithm>
#include <vector>

#include "Processo.h"

/* Classe abstrata usada para facilitar a implementação de escalonadores, é preciso apenas sobrecarregar
 * a função escalonaProcessos e inicializar os atributos conforme desejado para que o Sistema chame o escalonador 
 * na hora certa */
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

      /* Função que precisa ser sobrecarregada */
      virtual void escalonaProcessos() = 0; 

      /* Aumenta a prioridade dinâmica de todos os processos que estão prontos e não estão sendo executados */
      void envelhecerProcessos(int fatorDeEnvelhecimento);

      /* Adiciona um processo no vetor de processos a serem escalonados */
      void adicionarProcesso(Processo* processo);

      /* Remove um processo no vetor de processos a serem escalonados */
      void removerProcesso(Processo* processo);
      

      // GETs
      Processo* getProcessoAtual();
      bool getPreemptavel();
      int getQuantum();
      int getFatorDeEnvelhecimento();

};

#endif