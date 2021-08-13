#include "Escalonador.h"

class FCFS : public Escalonador {

   void escalonaProcessos() override {
      std::sort(_processos.begin(), _processos.end(), 
         [](const Processo *x, const Processo *y) {
            return x->getDataDeCriacao() < y->getDataDeCriacao();
         });

      this->processoAtual = this->_processos.size() != 0 ? this->_processos[0] : nullptr;
      // this->processoAtual = this->_processos[0];
   }
};

class ShortestJobFirst : public Escalonador {
  
   void escalonaProcessos() override {
      std::sort(_processos.begin(), _processos.end(), 
         [](const Processo *x, const Processo *y) {
            return x->getDuracao() < y->getDuracao();
      });

      this->processoAtual = this->_processos.size() != 0 ? this->_processos[0] : nullptr;
   }
};


class PrioridadeSemPreempcao : public Escalonador {
   void escalonaProcessos() override {

       std::sort(_processos.begin(), _processos.end(), 
         [](const Processo *x, const Processo *y) {
            return x->getPrioridadeEstatica() > y->getPrioridadeEstatica();
      });

      this->processoAtual = this->_processos.size() != 0 ? this->_processos[0] : nullptr;
    }
};

class PrioridadeComPreempcao : public Escalonador {
   public:
      PrioridadeComPreempcao() 
         : Escalonador() 
      {
         this->preemptavel = true;
      }

   void escalonaProcessos() override {

      std::sort(_processos.begin(), _processos.end(), 
         [](const Processo *x, const Processo *y) {
         return x->getPrioridadeEstatica() > y->getPrioridadeEstatica();
      });

      this->processoAtual = this->_processos.size() != 0 ? this->_processos[0] : nullptr;
    }

};

class RoundRobin : public Escalonador {
   public:
      RoundRobin(int quantum)
         : Escalonador()
      {
         this->preemptavel = true;
         this->_quantum = quantum;
      }

      void escalonaProcessos() override {
         // if processoAtual
         Processo *primeiro;
         
         if (this->_processos.size() != 0) {
            if (!this->processoAtual) {
               this->processoAtual = this->_processos[0];
               return;
            }

            primeiro = this->_processos[0];
            this->_processos.erase(this->_processos.begin());
            this->_processos.push_back(primeiro);
            // std::move(this->_processos.begin(), this->_processos.begin() + 1, this->_processos.end());
            this->processoAtual = this->_processos[0];
         }
         else {
            this->processoAtual = nullptr;
         }
         // this->_processos.
      }
};

class RoundRobinComEnvelhecimento : public Escalonador {
   public:
      RoundRobinComEnvelhecimento(int quantum, int fatorDeEnvelhecimento) 
         : Escalonador()
      {
         this->preemptavel = true;
         this->_quantum = quantum;
         this->_fatorDeEnvelhecimento = fatorDeEnvelhecimento;
      }

      void escalonaProcessos() override {

         std::sort(_processos.begin(), _processos.end(), 
         [](const Processo *x, const Processo *y) {
         return x->getPrioridadeDinamica() > y->getPrioridadeDinamica();
      });

      this->processoAtual = this->_processos.size() != 0 ? this->_processos[0] : nullptr;
         
      }
};
