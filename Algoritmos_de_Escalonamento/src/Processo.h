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
   int tempoPronto = 0;
   ESTADO _estado = NAO_PRONTO;
   int ultimaExecucao = -1; // POSSIVELMENTE NÀO SERVE PARA NADA
   int dataDeFinalizacao;
   int tempoDeEspera = 0;

   public:
      int tempoExecutado = 0;
      Processo(int id, int criacao, int duracao, int prioridade);
      ~Processo();

      void realizarCiclo(int ciclo);
      void envelhecer(int fatorDeEnvelhecimento);
      void incrementarTempoDeEspera();

      // Sobrecargas de operador
      bool operator< (const Processo &other) const;
      friend std::ostream& operator<<(std::ostream& os, const Processo& processo);

      //GETs
      int getId();
      int getDataDeCriacao() const;
      int getDuracao() const;
      int getPrioridadeEstatica() const;
      int getPrioridadeDinamica() const;
      int getTempoExecutado() const;
      int getDataDeFinalizacao() const;
      int getTempoDeEspera() const;
      ESTADO getEstado();

      //SETs
      void setEstado(ESTADO estado);
      void setDataDeFinalizacao(int data);
      void resetarPrioridadeDinamica();
};




#endif