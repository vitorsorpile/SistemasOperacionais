#ifndef _PROCESSO_H
#define _PROCESSO_H

#include <iostream>

enum ESTADO {NAO_PRONTO, PRONTO, EXECUTANDO, FINALIZADO};

/* Classe responsável por representar um processo, possui majoritariamente funções para acessar seus atributos */
class Processo {
   int id;
   int dataDeCriacao;
   int duracao;
   int prioridadeEstatica;
   int prioridadeDinamica;
   int tempoPronto = 0;
   int tempoExecutado = 0;
   ESTADO _estado = NAO_PRONTO;
   int dataDeFinalizacao;
   int tempoDeEspera = 0;

   public:
      Processo(int id, int criacao, int duracao, int prioridade);
      ~Processo();

      /* Muda o estado do processo para EXECUTANDO e aumenta o tempo executado */
      void realizarCiclo();
      
      /* Aumenta a prioridade dinâmica do processo */
      void envelhecer(int fatorDeEnvelhecimento);

      /* Aumenta o tempo de espera do processo */
      void incrementarTempoDeEspera();

      /* Volta a prioridade dinâmica do processo para a prioridade estática */
      void resetarPrioridadeDinamica();

      //GETs
      int getId() const;
      int getDataDeCriacao() const;
      int getDuracao() const;
      int getPrioridadeEstatica() const;
      int getPrioridadeDinamica() const;
      int getTempoExecutado() const;
      int getDataDeFinalizacao() const;
      int getTempoDeEspera() const;
      ESTADO getEstado() const;

      //SETs
      void setEstado(ESTADO estado);
      void setDataDeFinalizacao(int data);
      
};




#endif