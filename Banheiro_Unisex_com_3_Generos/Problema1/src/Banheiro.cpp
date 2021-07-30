#include "Banheiro.h"

Banheiro::Banheiro()
   :  tempoTotalDeCadaGeneroNaFila(3, std::chrono::seconds(0)),
      tempoDeUsoDoBox(N_BOXES, std::chrono::seconds(0)),
      totalPessoasPorGenero(3, 0),
      boxes(N_BOXES, false), boxesMtxs(N_BOXES)
   {}

Banheiro::~Banheiro() {}

// Retorna o primeiro box disponível e muda o estado do box para sendo utilizado
int Banheiro::getStall() {
    for (unsigned int i = 0; i < this->boxes.size(); i++) {
      this->boxesMtxs[i].lock();
      // Box estar false significa que não está sendo utilizado e true que está sendo utilizado
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

// A partir do time_point comecoDoUsoDoBox calcula por quanto tempo o box boxUsado foi utilizado, soma esse tempo 
// no seu contador e libera-o para uso
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

// Funções para acessar as variáveis da classe ("setters e getters")
int Banheiro::getN_BOXES() {
   return this->N_BOXES;
}

int Banheiro::getnBoxesDisponiveis() {
   return this->nBoxesDisponiveis;
}

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
