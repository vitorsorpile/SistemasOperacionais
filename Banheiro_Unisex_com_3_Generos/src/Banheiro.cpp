#include "Banheiro.h"

Banheiro::Banheiro()
   :  tempoTotalDeCadaGeneroNaFila(3, std::chrono::seconds(0)),
      tempoDeUsoDoBox(N_BOXES, std::chrono::seconds(0)),
      totalPessoasPorGenero(3, 0),
      boxes(N_BOXES, false), boxesMtxs(N_BOXES)
   {}

Banheiro::~Banheiro() {}

int Banheiro::getStall() {
    for (unsigned int i = 0; i < this->boxes.size(); i++) {
      this->boxesMtxs[i].lock();
      if (this->boxes[i] == false) {
         this->boxes[i] = true;
         this->banheiroMtx.lock();
         this->nBoxesDisponiveis--;
         this->banheiroMtx.unlock();
         this->boxesMtxs[i].unlock();
         return i;
      }
      this->boxesMtxs[i].unlock();
   }
   return -1;
}

void Banheiro::leaveStall(int boxUsado, std::chrono::time_point<std::chrono::steady_clock> comecoDoUsoDoBox) {
   this->boxesMtxs[boxUsado].lock();
   this->boxes[boxUsado] = false;
   auto agora = std::chrono::steady_clock::now();
   this->tempoDeUsoDoBox[boxUsado] += std::chrono::duration_cast <std::chrono::duration<double>> (agora - comecoDoUsoDoBox);
   this->banheiroMtx.lock();
   this->nBoxesDisponiveis++;
   this->banheiroMtx.unlock();
   this->boxesMtxs[boxUsado].unlock();
}

void Banheiro::comecarUso() {
   this->comecoDoUso = std::chrono::steady_clock::now();
}

std::chrono::time_point<std::chrono::steady_clock> Banheiro::getComecoDoUso() {
   return this->comecoDoUso;
}

int Banheiro::getN_BOXES() {
   return this->N_BOXES;
}

// void Banheiro::setGeneroUsando(int genero) {
//    this->generoUsando = genero;
// }

// int Banheiro::getGeneroUsando() {
//    return this->generoUsando;
// }

void Banheiro::setEmUso(bool estado) {
   this->emUso = estado;
}

bool Banheiro::getEmUso() {
   return this->emUso;
}

void Banheiro::addTempoNaFila(int genero, std::chrono::duration<double> tempo) {
   this->tempoTotalDeCadaGeneroNaFila[genero] += tempo;
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

double Banheiro::getTempoDeUsoDoBox(int genero) {
   return this->tempoDeUsoDoBox[genero].count();
}
