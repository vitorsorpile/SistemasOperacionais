#include "Processo.h"

Processo::Processo(int processoId, int criacao, int dur, int prioridade) {
   this->id = processoId;
   this->dataDeCriacao = criacao;
   this->duracao = dur;
   this->prioridadeEstatica = prioridade;
   this->prioridadeDinamica = prioridade;
}

Processo::~Processo() {}

void Processo::realizarCiclo() {

   if (this->_estado == PRONTO) {
      this->_estado = EXECUTANDO;
   }

   this->tempoExecutado++;
}

void Processo::envelhecer(int fatorDeEnvelhecimento) {
   this->prioridadeDinamica += fatorDeEnvelhecimento;
}

void Processo::incrementarTempoDeEspera() {
   this->tempoDeEspera++;
}

// GETs
int Processo::getId() const {
   return this->id;
}

int Processo::getDataDeCriacao() const{
   return this->dataDeCriacao;
}

ESTADO Processo::getEstado() const {
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