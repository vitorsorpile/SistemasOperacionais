#ifndef _PESSOA_H
#define _PESSOA_H

#include <thread>
#include <iostream>
#include <condition_variable>
#include <algorithm>
#include <chrono>

#include "Banheiro.h"

// #define TEMPO_PARA_USAR_O_BANHEIRO std::chrono::seconds(2)

enum GENEROS {HOMEM, MULHER, OUTROS};

class Banheiro;

class Pessoa : public std::thread {
   private:
      // auto x = 2s;
      static std::chrono::seconds TEMPO_PARA_USAR_O_BANHEIRO;
      static std::vector<std::vector<Pessoa*>> filas;
      static std::mutex filaMtx;
      // static std::vector<GENEROS> ordemDeChegadaDosGeneros;

      // static std::vector<std::chrono::seconds> tempoTotalNaFila;
      int _id;
      int boxUsado = -1;
      // std::chrono::seconds tempoUsandoBox = std::chrono::seconds(0);
      std::chrono::time_point<std::chrono::steady_clock> comecoDoUsoDoBox;
      std::chrono::time_point<std::chrono::steady_clock> entradaNaFila;
      bool liberadoParaUsarBanheiro = false;
      
      GENEROS _genero;
      Banheiro *_banheiro;
      std::condition_variable cv;

      void behavior();
      void enterRestroom();
      void getStall();
      void sairDaFila();

   public:
      
      Pessoa(int pessoaId, GENEROS genero, Banheiro* banheiro);
      ~Pessoa();

      void liberarParaUsarBanheiro();


      static void threadFunction(Pessoa *This);
};

#endif