   #include "Escalonador.h"
      
Escalonador::Escalonador() {}

Escalonador::~Escalonador() {}


Processo* Escalonador::getProcessoAtual() {
   return this->processoAtual;
}

bool Escalonador::getPreemptavel() {
   return this->preemptavel;
}

int Escalonador::getQuantum() {
   return this->_quantum;
}

int Escalonador::getFatorDeEnvelhecimento() {
   return this->_fatorDeEnvelhecimento;
}

void Escalonador::adicionarProcesso(Processo* processo) {
   this->_processos.push_back(processo);
}


void Escalonador::removerProcesso(Processo* processo) {
   _processos.erase(std::remove(_processos.begin(), _processos.end(), processo), _processos.end());
   if (processo == this->processoAtual)
      this->processoAtual = nullptr;
}

void Escalonador::envelhecerProcessos(int fatorDeEnvelhecimento) {
   for (auto & processo: this->_processos) {
      if (processo != processoAtual)
         processo->envelhecer(fatorDeEnvelhecimento);
   }
}
// bool compare(const )

// void Escalonador::escalonaProcessos() {
   // std::sort(_processos.begin(), _processos.end(), 
            // [](const Processo *x, const Processo *y) {
            //    return x->getDuracao() < y->getDuracao();

            // });

//    this->processoAtual = this->_processos[0];
// }