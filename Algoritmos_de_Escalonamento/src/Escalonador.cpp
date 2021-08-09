   #include "Escalonador.h"
      
Escalonador::Escalonador() {}

Escalonador::~Escalonador() {}


Processo* Escalonador::getProcessoAtual() {
   return this->processoAtual;
}

bool Escalonador::getPreemptavel() {
   return this->preemptavel;
}

void Escalonador::adicionarProcesso(Processo* processo) {
   this->_processos.push_back(processo);
}


void Escalonador::removerProcesso(Processo* processo) {
   _processos.erase(std::remove(_processos.begin(), _processos.end(), processo), _processos.end());
   if (processo == this->processoAtual)
      this->processoAtual = nullptr;
}

// bool compare(const )

void Escalonador::escalonaProcessos() {
   // std::sort(_processos.begin(), _processos.end(), 
   //          [](const Processo *x, const Processo *y) {
   //             return x->getDuracao() < y->getDuracao();

   //          });

   this->processoAtual = this->_processos[0];
}