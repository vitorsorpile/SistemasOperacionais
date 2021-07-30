#ifndef _BANHEIRO_H
#define _BANHEIRO_H

#include <vector>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <thread>

class Banheiro {
   private:
      static const int N_BOXES = 3;
      std::vector<std::chrono::duration<double>> tempoTotalDeCadaGeneroNaFila;
      std::vector<std::chrono::duration<double>> tempoDeUsoDoBox;
      std::vector<int> totalPessoasPorGenero;
      std::vector<bool> boxes;                            // true significa que box está em uso e false que está livre
      std::vector<std::mutex> boxesMtxs;
      bool emUso = false;                                // estado do banheiro
      int nBoxesDisponiveis = N_BOXES;

   public:
      std::mutex banheiroMtx;

      // Contrutor e destrutor
      Banheiro();
      ~Banheiro();
      
      // Retorna o primeiro box disponível 
      int getStall();

      // A partir do time_point comecoDoUsoDoBox calcula por quanto tempo o box boxUsado foi utilizado, soma esse tempo 
      // no seu contador e libera-o para uso
      void leaveStall(int boxUsado, std::chrono::time_point<std::chrono::steady_clock> comecoDoUsoDoBox);

      // Funções para acessar as variáveis da classe ("setters e getters")
      int getN_BOXES();
      int getnBoxesDisponiveis();
      void setEmUso(bool estado);
      bool getEmUso();
      void addTempoNaFila(int genero, std::chrono::duration<double> tempo);
      double getTempoNaFila(int genero);
      void addPessoaDoGenero(int genero);
      int getTotalPessoasPorGenero(int genero);
      double getTempoDeUsoDoBox(int genero);

};

#endif