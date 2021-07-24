#ifndef _BANHEIRO_H
#define _BANHEIRO_H

#include <vector>
#include <chrono>
#include <mutex>
#include <condition_variable>
// #include <queue>
#include <thread>
#include "Pessoa.h"

class Pessoa;

class Banheiro {
   private:
      static const int N_BOXES = 1;
      std::vector<std::condition_variable> generosCVs;
      std::vector<std::chrono::duration<double>> tempoTotalDeCadaGeneroNaFila;
      std::vector<int> totalPessoasPorGenero;
      std::chrono::time_point<std::chrono::steady_clock> comecoDoUso;
      int generoUsando;
      bool emUso = false;

   public:
      int nBoxesDisponiveis = N_BOXES;
      // std::queue<Pessoa*> fila; 
      std::vector<bool> boxes;
      std::vector<std::mutex> boxesMtxs;
      std::vector<std::chrono::seconds> boxUsedTime;
      std::vector<std::vector <Pessoa *>> filas;
      std::mutex banheiroMtx, filaMtx;
      Banheiro();
      ~Banheiro();

      void comecarUso();
      std::chrono::time_point<std::chrono::steady_clock> getComecoDoUso();
      int getN_BOXES();
      void setGeneroUsando(int genero);
      int getGeneroUsando();
      void setEmUso(bool estado);
      bool getEmUso();
      void addTempoNaFila(int genero, std::chrono::duration<double> tempo);
      double getTempoNaFila(int genero);
      void addPessoaDoGenero(int genero);
      int getTotalPessoasPorGenero(int genero);
};

#endif