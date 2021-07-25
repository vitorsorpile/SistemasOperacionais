#ifndef _PESSOA_H
#define _PESSOA_H

#include <thread>
#include <iostream>
#include <condition_variable>
#include <algorithm>
#include <chrono>

#include "Banheiro.h"

enum GENEROS {HOMEM, MULHER, OUTROS};

class Banheiro;

class Pessoa : public std::thread {
   private:
      static std::chrono::seconds TEMPO_PARA_USAR_O_BANHEIRO;
      static std::vector<std::vector<Pessoa*>> filas;
      static std::mutex filaMtx;
      
      int _id;
      int boxUsado = -1;
      std::chrono::time_point<std::chrono::steady_clock> comecoDoUsoDoBox;
      std::chrono::time_point<std::chrono::steady_clock> entradaNaFila;
      bool liberadoParaUsarBanheiro = false;
      
      GENEROS _genero;
      Banheiro *_banheiro;
      std::condition_variable cv;

      void behavior();
      void enterRestroom();
      long int calcularProximoGenero();
      void sairDaFila();
      void liberarParaUsarBanheiro();

   public:
      
      Pessoa(int pessoaId, GENEROS genero, Banheiro* banheiro);
      ~Pessoa();

      static void threadFunction(Pessoa *This);
};

#endif