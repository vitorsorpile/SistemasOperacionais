#ifndef _PESSOA_H
#define _PESSOA_H

#include <thread>
#include <iostream>
#include <condition_variable>
#include <algorithm>
#include <chrono>

#include "Banheiro.h"

enum GENEROS {HOMEM, MULHER, OUTROS};

class Pessoa : public std::thread {
   private:
      static std::chrono::seconds TEMPO_PARA_USAR_O_BANHEIRO;
      static std::vector<std::vector<Pessoa*>> filas;                            // Uma fila para cada gênero
      static std::mutex filaMtx;
      
      int _id;
      int boxUsado = -1;
      std::chrono::time_point<std::chrono::steady_clock> comecoDoUsoDoBox;       // Quando começou a utilizar o box
      std::chrono::time_point<std::chrono::steady_clock> entradaNaFila;          // Quando começou a esperar na fila
      bool liberadoParaUsarBanheiro = false;
      
      GENEROS _genero;
      Banheiro *_banheiro;
      std::condition_variable cv;         // Variável condificonal para ser notificada de quando pode usar o banheiro

      // Comportamento da thread
      void behavior();

      // Tenta entrar no banheiro, caso não consiga fica esperando até ser notificado na sua variável condicional
      void enterRestroom();

      // Calcula o tempo médio de espera dos gêneros que possuem pessoas na fila e retorna o que possui o maior tempo médio
      long int calcularProximoGenero();

      // Sai da fila e passa para o banheiro quando começou a esperar para que o banheiro calcule o tempo total de espera
      // de cada gênero
      void sairDaFila();

      // Muda a váriavel liberadoParaUsarBanheiro para true
      void liberarParaUsarBanheiro();

   public:
      
      // Construtor e destrutor
      Pessoa(int pessoaId, GENEROS genero, Banheiro* banheiro);
      ~Pessoa();

      static void threadFunction(Pessoa *This);
};

#endif