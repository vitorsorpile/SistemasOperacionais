#include "Processo.h"

Processo::Processo(int processoId, int criacao, int dur, int prioridade) {
   this->id = processoId;
   this->dataDeCriacao = criacao;
   this->duracao = dur;
   this->prioridadeEstatica = prioridade;
}

Processo::~Processo() {}

void Processo::realizarCiclo(int ciclo) {

   if (this->_estado == PRONTO) {
      this->_estado = EXECUTANDO;
   }

   this->tempoExecutado++;
   this->ultimaExecucao = ciclo;

   // if (this->tempoExecutado == this->duracao) {
   //    this->_estado = FINALIZADO;
   // }

}

bool Processo::operator< (const Processo &other) const {
        return this->dataDeCriacao < other.dataDeCriacao;
}

std::ostream& operator<<(std::ostream& os, const Processo& processo) {
   os << "Processo " << processo.id << ": " << processo.dataDeCriacao << " | ";
   os << processo.duracao << " | " << processo.prioridadeEstatica << std::endl;

   return os;
}


// GETs
int Processo::getId() {
   return this->id;
}

int Processo::getDataDeCriacao() {
   return this->dataDeCriacao;
}

ESTADO Processo::getEstado() {
   return this->_estado;
}

int Processo::getDuracao() const {
   return this->duracao;
}

int Processo::getTempoExecutado() {
   return this->tempoExecutado;
}

//SETs
void Processo::setEstado(ESTADO estado) {
   this->_estado = estado;
}
