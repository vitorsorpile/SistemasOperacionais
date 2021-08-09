#ifndef _PROCESSO_H
#define _PROCESSO_H

#include <iostream>

enum ESTADO {NAO_PRONTO, PRONTO, EXECUTANDO, FINALIZADO};

class Processo {

   int id;
   int dataDeCriacao;
   int duracao;
   int prioridadeEstatica;
   int prioridadeDinamica;
   int tempoExecutado = 0;
   int tempoPronto = 0;
   ESTADO _estado = NAO_PRONTO;
   int ultimaExecucao = -1;

   public:
      Processo(int id, int criacao, int duracao, int prioridade);
      ~Processo();


      void realizarCiclo(int ciclo);
      // Sobrecargas de operador
      bool operator< (const Processo &other) const;
      friend std::ostream& operator<<(std::ostream& os, const Processo& processo);

      //GETs
      int getId();
      int getDataDeCriacao();
      int getDuracao() const;
      int getTempoExecutado();
      ESTADO getEstado();

      //SETs
      void setEstado(ESTADO estado);
};




#endif