#include "Processo.h"

Processo::Processo(int processoId, int criacao, int dur, int prioridade) {
   this->id = processoId;
   this->dataDeCriacao = criacao;
   this->duracao = dur;
   this->prioridadeEstatica = prioridade;
   this->prioridadeDinamica = prioridade;
   // std::cout << this->prioridadeDinamica << std::endl;
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

void Processo::envelhecer(int fatorDeEnvelhecimento) {
   this->prioridadeDinamica += fatorDeEnvelhecimento;
   // std::cout << "Processo " << this->id << " agora tem prioridade " << this->prioridadeDinamica << std::endl;
}

void Processo::incrementarTempoDeEspera() {
   this->tempoDeEspera++;
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

int Processo::getDataDeCriacao() const{
   return this->dataDeCriacao;
}

ESTADO Processo::getEstado() {
   return this->_estado;
}

int Processo::getDuracao() const {
   return this->duracao;
}

int Processo::getPrioridadeEstatica() const {
   return this->prioridadeEstatica;
}

int Processo::getPrioridadeDinamica() const {
   return this->prioridadeDinamica;
}

int Processo::getTempoExecutado() const {
   return this->tempoExecutado;
}

int Processo::getDataDeFinalizacao() const {
   return this->dataDeFinalizacao;
}

int Processo::getTempoDeEspera() const {
   return this->tempoDeEspera;
}

//SETs
void Processo::setEstado(ESTADO estado) {
   this->_estado = estado;
}

void Processo::setDataDeFinalizacao(int data) {
   this->dataDeFinalizacao = data;
}

void Processo::resetarPrioridadeDinamica() {
   this->prioridadeDinamica = this->prioridadeEstatica;
}