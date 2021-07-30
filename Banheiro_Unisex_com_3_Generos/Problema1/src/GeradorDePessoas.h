#ifndef _GERADOR_DE_PESSOAS_H
#define _GERADOR_DE_PESSOAS_H

#include <vector>
#include <thread>
#include <chrono>
#include <memory>
#include <random>

#include "Pessoa.h"
#include "Banheiro.h"

class GeradorDePessoas : public std::thread {

   private:
      int _nPessoas;
      bool _nPessoasIgualEntreOsGeneros;
      Banheiro *_banheiro;                   // Ponteiro para o banheiro para poder criar as Pessoas

      std::default_random_engine generator;
      std::uniform_int_distribution<int> generos;
      std::uniform_int_distribution<int> tempoParaChegar;

      void behavior();
   public:

      GeradorDePessoas(int nPessoas, Banheiro *banheiro, bool nPessoasIgualEntreOsGeneros = false);
      ~GeradorDePessoas();


      static void threadFunction(GeradorDePessoas *This);

};

#endif