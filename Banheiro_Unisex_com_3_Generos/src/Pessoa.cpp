#include "Pessoa.h"

std::vector<std::vector<Pessoa*>> Pessoa::filas(3);
std::mutex Pessoa::filaMtx;
std::chrono::seconds Pessoa::TEMPO_PARA_USAR_O_BANHEIRO = std::chrono::seconds(5);

Pessoa::Pessoa(int pessoaId, GENEROS genero, Banheiro* banheiro) 
   : std::thread(threadFunction, this)
{  
   this->_id = pessoaId;
   this->_genero = (GENEROS) genero;
   this->_banheiro = banheiro;
   banheiro->addPessoaDoGenero(genero);
   
}

Pessoa::~Pessoa() {} 

void Pessoa::enterRestroom() {
   std::mutex mtx;
   std::unique_lock<std::mutex> lck(mtx);

   // Caso em que o banheiro não está sendo utilizado   
   _banheiro->banheiroMtx.lock();
   if (!_banheiro->getEmUso()) {
      this->liberarParaUsarBanheiro();
      // _banheiro->setGeneroUsando(this->_genero);
      _banheiro->setEmUso(true);
      _banheiro->comecarUso();
      _banheiro->banheiroMtx.unlock();
      return;
   }
   _banheiro->banheiroMtx.unlock();


   // Caso em que o banheiro está sendo usado por pessoas do mesmo gênero e há box disponível
   // _banheiro->banheiroMtx.lock();
   // if (_banheiro->getEmUso() && _banheiro->nBoxesDisponiveis) {
   //    if (_banheiro->getGeneroUsando() == this->_genero && _banheiro->getComecoDoUso() >= std::chrono::steady_clock::now() - std::chrono::seconds(2)) {
   //       // std::cout << this->_id <<" : banheiro ja estava sendo utilizado" << std::endl;
   //       this->liberarParaUsarBanheiro();
   //       this->entradaNaFila = std::chrono::steady_clock::now();
   //       this->sairDaFila();
   //       _banheiro->banheiroMtx.unlock();
   //       return;
   //    } 
   // }
   // _banheiro->banheiroMtx.unlock();

   // Entra na fila e espera até ser liberado para usar banheiro
   filaMtx.lock();
   filas[this->_genero].push_back(this);
   this->entradaNaFila = std::chrono::steady_clock::now();
   filaMtx.unlock();
   while(!this->liberadoParaUsarBanheiro) this->cv.wait(lck);

   // Seta o banheiro em uso para o gênero da pessoa e sai da fila
   _banheiro->banheiroMtx.lock();
   // _banheiro->setGeneroUsando(this->_genero);
   _banheiro->setEmUso(true);
   this->sairDaFila();
   _banheiro->banheiroMtx.unlock();
   
}

void Pessoa::behavior() {
   std::this_thread::sleep_for(std::chrono::milliseconds(100));

   // Tenta entrar no banheiro
   this->enterRestroom();
   
   // Pede um box para o banheiro
   int box = _banheiro->getStall();
   if (box == -1) {
      std::cout << "Algo de errado nao esta certo..." << std::endl;
      return;
   } else {
      this->boxUsado = box;
   }
   this->comecoDoUsoDoBox = std::chrono::steady_clock::now();
   
   // Usa o banheiro pelo tempo determinado
   std::this_thread::sleep_for(TEMPO_PARA_USAR_O_BANHEIRO);

   // Libera o box usado e passa quando começou a utilizá-lo para contar o tempo total de uso do box
   _banheiro->leaveStall(this->boxUsado, this->comecoDoUsoDoBox);
   std::cout << "Pessoa " << this->_id << '[' << this->_genero << ']' << " usou box " << this->boxUsado << std::endl;

   _banheiro->banheiroMtx.lock(); 

   // Verifica se foi o último do gênero a sair do box
   if (_banheiro->getN_BOXES() == _banheiro->nBoxesDisponiveis) {
      filaMtx.lock();
        
      // Calcula qual gênero deve ser o próximo a usar o banheiro
      long int generoDaVez = this->calcularProximoGenero();
      std::cout << "Genero da vez -> " << generoDaVez << std::endl << std::endl << std::endl;

      // Verifica se a fila do gênero não está vazia
      if (filas[generoDaVez].size() != 0) {
         // Libera e notifica para usar o banheiro o máximo de pessoas na fila do gênero até não ter box disponível 
         for (int i = 0; i < _banheiro->nBoxesDisponiveis && (unsigned) i < filas[generoDaVez].size(); i++) {
            filas[generoDaVez][i]->liberarParaUsarBanheiro();
            filas[generoDaVez][i]->cv.notify_one();
         }
         filaMtx.unlock();

         _banheiro->banheiroMtx.unlock();
         return;
      }
      filaMtx.unlock();
   }

   _banheiro->setEmUso(false);
   _banheiro->banheiroMtx.unlock();

   return;
}

void Pessoa::liberarParaUsarBanheiro() {
   this->liberadoParaUsarBanheiro = true;
}

long int Pessoa::calcularProximoGenero() {
   double tempoMedio[3] = {0.0};
   auto agora = std::chrono::steady_clock::now();
   
   for (int i = 0; i < 3; i++) {
      for (auto & pessoa : filas[i]) {
         tempoMedio[i] += (std::chrono::duration<double> (agora - pessoa->entradaNaFila)).count();
      }

      if (tempoMedio[i] != 0) {
         tempoMedio[i] += _banheiro->getTempoNaFila(i);
         tempoMedio[i] /= _banheiro->getTotalPessoasPorGenero(i);
      }

      std::cout << "Tempo medio -> " << tempoMedio[i] << std::endl;
   }

   return std::distance(tempoMedio, std::max_element(tempoMedio, tempoMedio + 3)); 
}

void Pessoa::sairDaFila() {
   filaMtx.lock();
   filas[this->_genero].erase(std::remove(filas[this->_genero].begin(), filas[this->_genero].end(), this), filas[this->_genero].end());
   auto agora = std::chrono::steady_clock::now();
   _banheiro->addTempoNaFila(this->_genero, std::chrono::duration_cast <std::chrono::duration<double>> (agora - this->entradaNaFila));
   filaMtx.unlock();
}


void Pessoa::threadFunction(Pessoa *This) {
   return This->behavior();
}
