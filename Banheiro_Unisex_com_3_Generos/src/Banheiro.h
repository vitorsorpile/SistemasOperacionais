#ifndef _BANHEIRO_H
#define _BANHEIRO_H

#include <vector>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <thread>
#include "Pessoa.h"

class Pessoa;

class Banheiro {
   private:
      static const int N_BOXES = 1;
      std::vector<std::chrono::duration<double>> tempoTotalDeCadaGeneroNaFila;
      std::vector<std::chrono::duration<double>> tempoDeUsoDoBox;
      std::vector<int> totalPessoasPorGenero;
      std::vector<bool> boxes;
      std::vector<std::mutex> boxesMtxs;
      std::chrono::time_point<std::chrono::steady_clock> comecoDoUso;
      // int generoUsando;
      bool emUso = false;

   public:
      int nBoxesDisponiveis = N_BOXES;
      std::mutex banheiroMtx;

      Banheiro();
      ~Banheiro();

      int getStall();
      void leaveStall(int boxUsado, std::chrono::time_point<std::chrono::steady_clock> comecoDoUsoDoBox);
      void comecarUso();

      std::chrono::time_point<std::chrono::steady_clock> getComecoDoUso();
      int getN_BOXES();
      // void setGeneroUsando(int genero);
      // int getGeneroUsando();
      void setEmUso(bool estado);
      bool getEmUso();
      void addTempoNaFila(int genero, std::chrono::duration<double> tempo);
      double getTempoNaFila(int genero);
      void addPessoaDoGenero(int genero);
      int getTotalPessoasPorGenero(int genero);
      double getTempoDeUsoDoBox(int genero);

};

#endif