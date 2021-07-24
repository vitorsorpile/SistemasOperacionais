#include "Pessoa.h"

std::vector<std::vector<Pessoa*>> Pessoa::filas(3);
// std::vector<GENEROS> Pessoa::ordemDeChegadaDosGeneros; 
std::mutex Pessoa::filaMtx;
std::chrono::seconds Pessoa::TEMPO_PARA_USAR_O_BANHEIRO = std::chrono::seconds(5);
// std::vector<std::chrono::seconds> tempoTotalNaFila(3, std::chrono::seconds(0));

Pessoa::Pessoa(int pessoaId, GENEROS genero, Banheiro* banheiro) 
   : std::thread(threadFunction, this)
{  
   this->_id = pessoaId;
   this->_genero = (GENEROS) genero;
   this->_banheiro = banheiro;

   // filaMtx.lock();
   // filas[genero].push_back(this);
   // this->entradaNaFila = std::chrono::steady_clock::now();
   banheiro->addPessoaDoGenero(genero);
   // filaMtx.unlock();
   // std::cout << "Pessoa do genero " << this->_genero << " criada" << std::endl;
   
   // for(auto & fila : _banheiro->filas) {
   //    for (auto & pessoa: fila)
   //       std::cout << pessoa->_genero << std::endl;
   // }
   //    std::cout << "------" << std::endl;

}

Pessoa::~Pessoa() {} 

void Pessoa::enterRestroom() {
   std::mutex mtx;
   std::unique_lock<std::mutex> lck(mtx);

   // Fica esperando até conseguir entrar no banheiro
   // LIMITAR ACESSO AQUI
   // IDEIA -> cada pessoa ter uma variavel "liberado" que comeca falsa
   // TEM QUE MUDAR PRA IDEIA PQ SE NAO SO UMA PESSOA CONSEGUE USAR O BANHEIRO
   
   // Caso em que o banheiro não está sendo utilizado
   
   _banheiro->banheiroMtx.lock();
   if (!_banheiro->getEmUso()) {
      // std::cout << this->_id <<" : banheiro nao estava sendo utilizado" << std::endl;
      this->liberarParaUsarBanheiro();
      _banheiro->setGeneroUsando(this->_genero);
      _banheiro->setEmUso(true);
      // Reavaliar necessidade de comecarUso() - Necessário para quando uma pessoa chega e o 
      // banheiro já está sendo utilizado por alguém do mesmo gênero
      _banheiro->comecarUso();
      // this->entradaNaFila = std::chrono::steady_clock::now();
      // this->sairDaFila();
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

   // Espera até ser liberado para usar banheiro
   filaMtx.lock();
   filas[this->_genero].push_back(this);
   this->entradaNaFila = std::chrono::steady_clock::now();
   // _banheiro->addPessoaDoGenero(this->_genero);
   filaMtx.unlock();

   this->entradaNaFila = std::chrono::steady_clock::now();
   while(!this->liberadoParaUsarBanheiro) this->cv.wait(lck);

   // Seta o banheiro em uso para o gênero da pessoa
   _banheiro->banheiroMtx.lock();
   _banheiro->setGeneroUsando(this->_genero);
   _banheiro->setEmUso(true);
   this->sairDaFila();
   _banheiro->banheiroMtx.unlock();

   
}

// Pessoas se autocontrolam, banheiro tem variáveis de controle
// Quando o ultimo box deixa de ser ocupado, verifica qual genero está esperando a mais tempo
// Se ninguém estiver esperando 

// CASOS DE PESSOA CHEGANDO
// - Ninguém usando banheiro
// - Mesmo genero usando
//    - Todos os boxes ocupados
//    - Box disponível e outra pessoa entrou a menos de 2 segundos
//    - Box disponivel e outra pessoa entrou a mais de 2 segundos
//    - Ninguém de outro gênero na fila
// - Outro genero usando

// Troca de genero usando o banheiro

// Quando uma pessoa chega e a fila do genero tava vazia, começa a contar o tempo em espera
// Quando remover a ultima pessoa da fila do genero, para de contar o tempo em espera

// Quando a primeira pessoa da leva entra no banheiro, soma na variável de tempo de espera do gênero ?????????????
// Tempo médio na verdade deve levar em conta o tempo de esperar de todas as pessoas
//          i = 0; while (nBoxDisponiveis)
//                   if (i==0) soma na variável
//                   contadorDePessoasDoGenero++;

// POSSIBILIDADE -> Mudar essa função para o banheiro 
void Pessoa::getStall() {
   for (unsigned int i = 0; i < _banheiro->boxes.size(); i++) {
      _banheiro->boxesMtxs[i].lock();
      if (_banheiro->boxes[i] == false) {
         // std::cout << "Pessoa " << this->_id << this->_genero << " entrou no box " << i << std::endl; 
         _banheiro->boxes[i] = true;
         this->boxUsado = i;
         _banheiro->banheiroMtx.lock();
         _banheiro->nBoxesDisponiveis--;
         _banheiro->banheiroMtx.unlock();
         _banheiro->boxesMtxs[i].unlock();
         return;
      }
      _banheiro->boxesMtxs[i].unlock();
   }

   // verifica se o próximo da fila é do mesmo genero ou se era o ultimo no banheiro
   
   // se for -> notifica o próximo para entrar

   return ;
}

void Pessoa::behavior() {
   std::this_thread::sleep_for(std::chrono::milliseconds(100));

   // std::cout << "Pessoa " << this->_id << this->_genero << " tentou entrar no banheiro" << std::endl;
   this->enterRestroom();
   // std::cout << "Pessoa " << this->_id << this->_genero << " entrou no banheiro" << std::endl;
   this->getStall();
   this->comecoDoUsoDoBox = std::chrono::steady_clock::now();
   
   std::this_thread::sleep_for(TEMPO_PARA_USAR_O_BANHEIRO);

   // SEPARAR EM leaveStall();
   _banheiro->boxesMtxs[this->boxUsado].lock();
   _banheiro->boxes[this->boxUsado] = false;
   std::cout << "Pessoa " << this->_id << '[' << this->_genero << ']' << " usou box " << this->boxUsado << std::endl;
   auto agora = std::chrono::steady_clock::now();
   _banheiro->boxUsedTime[this->boxUsado] += std::chrono::duration_cast <std::chrono::seconds> (agora - this->comecoDoUsoDoBox);
   // std::cout << _banheiro->boxUsedTime[this->boxUsado].count() << std::endl;
   _banheiro->banheiroMtx.lock();
   // std::cout << "Boxes disponiveis a-> " << _banheiro->nBoxesDisponiveis << std::endl;
   _banheiro->nBoxesDisponiveis++;
   // std::cout << "Boxes disponiveis d-> " << _banheiro->nBoxesDisponiveis << std::endl;
   _banheiro->banheiroMtx.unlock();
   _banheiro->boxesMtxs[this->boxUsado].unlock();
   
   // SEPARAR EM leaveRestroom();

   
   // SEPARAR EM avisarProximos();
   
   // verificar qual genero tem pessoa na fila
   
   // ver qual média de espera ta maior
   
   // mandar entrar primeira pessoa e quantas mais couberem
   // while (nBoxDisponiveis)
   //    ...
   // return;

   _banheiro->banheiroMtx.lock(); 
   std::cout << "Pessoa " << this->_id << '[' << this->_genero << ']' << " pegou lock para calcular o proximo genero "  << std::endl;
   // std::cout << "Boxes disponiveis -> " << _banheiro->nBoxesDisponiveis << std::endl;
   if (_banheiro->getN_BOXES() == _banheiro->nBoxesDisponiveis) {
      // Separar em calculaProximoGenero();
      filaMtx.lock();
        
      double tempoMedio[3] = {0.0};
      agora = std::chrono::steady_clock::now();
      for (int i = 0; i < 3; i++) {
         for (auto & pessoa : filas[i]) {
            // std::cout << pessoa->_id << " tempo desde a entrada na fila -> " << std::chrono::duration<double> (agora - pessoa->entradaNaFila).count() << std::endl;
            tempoMedio[i] += (std::chrono::duration<double> (agora - pessoa->entradaNaFila)).count();
         }

         if (tempoMedio[i] != 0) {
            tempoMedio[i] += _banheiro->getTempoNaFila(i);
            tempoMedio[i] /= _banheiro->getTotalPessoasPorGenero(i);
         }

         std::cout << "Tempo medio -> " << tempoMedio[i] << std::endl;

      }

      auto generoDaVez = std::distance(tempoMedio, std::max_element(tempoMedio, tempoMedio + 3)); // retorno da calculaProximoGenero();
      std::cout << "Genero da vez -> " << generoDaVez << std::endl << std::endl << std::endl;

      if (filas[generoDaVez].size() != 0) {
         for (int i = 0; i < _banheiro->nBoxesDisponiveis && (unsigned) i < filas[generoDaVez].size(); i++) {
            filas[generoDaVez][i]->liberarParaUsarBanheiro();
            filas[generoDaVez][i]->cv.notify_one();
         }
         filaMtx.unlock();

         _banheiro->banheiroMtx.unlock();
         return;
      }
   }
   filaMtx.unlock();
   _banheiro->setEmUso(false);
   _banheiro->banheiroMtx.unlock();
   // _banheiro->banheiroMtx.lock();


   // _banheiro->banheiroMtx.unlock();
   // std::vector<double> 
   // if (ordemDeChegadaDosGeneros.size()) {
      
      // filas[ordemDeChegadaDosGeneros[0]][0]->liberarParaUsarBanheiro();
            //  pessoa->liberarParaUsarBanheiro();
      // filas[ordemDeChegadaDosGeneros[0]][0]->cv.notify_one();
      // return;

      // Checar se existe pessoa daquele gênero
      // Tirar remoção do gênero da ordem de chegada de sair da fila
   // }
   // for (auto & fila : filas) {
   //    for (auto & pessoa : fila) {
   //       pessoa->liberarParaUsarBanheiro();
   //       pessoa->cv.notify_one();
   //       return;
   //    }
   // }


   return;
}

void Pessoa::liberarParaUsarBanheiro() {
   this->liberadoParaUsarBanheiro = true;
}

void Pessoa::sairDaFila() {
   _banheiro->filaMtx.lock();
   // std::cout << "Removendo pessoa " << this->_id << " da fila" << std::endl;
   // auto i = std::find(filas[this->_genero].begin(), filas[this->_genero].end(), this);
   // filas[this->_genero].erase(filas[this->_genero].begin() + i);
   filas[this->_genero].erase(std::remove(filas[this->_genero].begin(), filas[this->_genero].end(), this), filas[this->_genero].end());
   auto agora = std::chrono::steady_clock::now();
   _banheiro->addTempoNaFila(this->_genero, std::chrono::duration_cast <std::chrono::duration<double>> (agora - this->entradaNaFila));
   // ordemDeChegadaDosGeneros.erase(ordemDeChegadaDosGeneros.begin());
   _banheiro->filaMtx.unlock();
}


void Pessoa::threadFunction(Pessoa *This) {
   return This->behavior();
}
