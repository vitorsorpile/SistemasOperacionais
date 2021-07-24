#include "Banheiro.h"

Banheiro::Banheiro()
   :  generosCVs(N_BOXES), 
      tempoTotalDeCadaGeneroNaFila(3, std::chrono::seconds(0)),
      totalPessoasPorGenero(3, 0),
      boxes(N_BOXES, false), boxesMtxs(N_BOXES),
      boxUsedTime(N_BOXES, std::chrono::seconds(0)),
      filas(3)
   {}

Banheiro::~Banheiro() {}


void Banheiro::comecarUso() {
   this->comecoDoUso = std::chrono::steady_clock::now();
}

std::chrono::time_point<std::chrono::steady_clock> Banheiro::getComecoDoUso() {
   return this->comecoDoUso;
}

int Banheiro::getN_BOXES() {
   return this->N_BOXES;
}

void Banheiro::setGeneroUsando(int genero) {
   this->generoUsando = genero;
}

int Banheiro::getGeneroUsando() {
   return this->generoUsando;
}

void Banheiro::setEmUso(bool estado) {
   this->emUso = estado;
}

bool Banheiro::getEmUso() {
   return this->emUso;
}

void Banheiro::addTempoNaFila(int genero, std::chrono::duration<double> tempo) {
   this->tempoTotalDeCadaGeneroNaFila[genero] += tempo;

   // std::cout << "Genero " << genero << " ja esperou no total por " << this->tempoTotalDeCadaGeneroNaFila[genero].count() << " segundos"<< std::endl;
}

double Banheiro::getTempoNaFila(int genero) {
   return  this->tempoTotalDeCadaGeneroNaFila[genero].count();
}

void Banheiro::addPessoaDoGenero(int genero) {
   this->totalPessoasPorGenero[genero]++;
}

int Banheiro::getTotalPessoasPorGenero(int genero) {
   return this->totalPessoasPorGenero[genero];
}
