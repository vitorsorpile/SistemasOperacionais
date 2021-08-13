#include "Sistema.h"

Sistema::Sistema(std::vector<std::shared_ptr<Processo>> processos, Escalonador* escalonador) {
   this->_processos = processos;
   this->_escalonador = escalonador;
   this->nProcessosRestantes = processos.size();
}

Sistema::~Sistema() {}

// Envia para o escalonador os processos que ficam prontos no ciclo atual
bool Sistema::enviarNovosProcessosProntosAoEscalonador() {
   bool enviouProcessos = false;
   for (auto &processo : this->_processos) {

      if (processo->getDataDeCriacao() == this->ciclo) {
         processo->setEstado(PRONTO);
         _escalonador->adicionarProcesso(processo.get());
         enviouProcessos = true;
      }
   }
   return enviouProcessos;
}

// Imprime o estado dos processos no ciclo atual
void Sistema::printCicloAtual() {
   std::string tempo = std::to_string(this->ciclo - 1) + '-' + std::to_string(this->ciclo);
   std::cout << std::left << std::setw(10) << tempo;
   
   std::string posicao;
   for (auto& processo : this->_processos) {
      int qntDeCaracteres = std::to_string(processo->getId()).length() + 1; 
      char caracter;
      switch (processo->getEstado())
      {
      case PRONTO:
         caracter = '-';
         break;
      case EXECUTANDO:
         caracter = '#';
         break;
      case FINALIZADO:
         caracter = 'x';
         break;
      default:
         caracter = ' ';
         break;
      }

      std::cout << ' ';
      for (int i = 0; i < qntDeCaracteres; i++) 
         std::cout << caracter;
   }
      std::cout << std::endl;
}

void Sistema::incrementarTemposDeEspera() {
   for (auto & processo: this->_processos) {
      if (processo->getEstado() == PRONTO) {
         processo->incrementarTempoDeEspera();
      }
   }
}

// Função principal que define o comportamento do sistema, faz o relacionamento entre o escalonador e os processos. 
void Sistema::executar() {

   // Imprime cabeçalho da saída
   std::cout << std::left << std::setw(10) << "tempo";
   std::string posicao;
   for (auto& processo: this->_processos) {
      posicao = " P" + std::to_string(processo.get()->getId());
      std::cout << posicao;
   }
   std::cout << std::endl;

   int quantum = _escalonador->getQuantum(), quantumsNesseProcesso = 0;
   int fatorDeEnvelhecimento = _escalonador->getFatorDeEnvelhecimento();
   bool escalonar = false, enviouProcessos = false;
   Processo *processoAtual = nullptr;
   
   while (this->nProcessosRestantes) {
      enviouProcessos = this->enviarNovosProcessosProntosAoEscalonador();

      processoAtual = _escalonador->getProcessoAtual();

      // Escalona se não houver processo em execução
      if (!processoAtual) {
         escalonar = true;
      } 

      // Escalona se for preemptável e tiver enviado novos processos ao escalonador 
      if (_escalonador->getPreemptavel() && enviouProcessos && quantum == -1) {
         escalonar = true;
      }

      // Escalona a cada número determinado de quantums
      if (_escalonador->getPreemptavel() && quantumsNesseProcesso % quantum == 0) {
         escalonar = true;
      }

      // Envelhece os processos caso o fator de envelhecimento seja diferente de zero
      if (fatorDeEnvelhecimento != 0) {
         _escalonador->envelhecerProcessos(fatorDeEnvelhecimento);
      }
      // Se for preciso escalonar, troca o processo em execução
      if (escalonar) {
         Processo *processoAnterior = processoAtual;
         if (processoAtual) {
            processoAtual->setEstado(PRONTO);
            processoAtual->resetarPrioridadeDinamica();
         }
         quantumsNesseProcesso = 0;
         _escalonador->escalonaProcessos();
         processoAtual = _escalonador->getProcessoAtual();
         processoAtual->setEstado(EXECUTANDO);
         if (processoAtual != processoAnterior) trocasDeContexto++;
      }
      
      this->incrementarTemposDeEspera();

      if (processoAtual) {
         processoAtual->realizarCiclo(this->ciclo);
      }

      this->ciclo++;
      this->printCicloAtual();

      // Remove o processo caso ele conclua sua execução no final do ciclo
      if (processoAtual) {
         if (processoAtual->getTempoExecutado() == processoAtual->getDuracao()) {
            this->nProcessosRestantes--;
            _escalonador->removerProcesso(processoAtual);
            processoAtual->setEstado(FINALIZADO);
            processoAtual->setDataDeFinalizacao(ciclo);
            quantumsNesseProcesso = 0;
         }
      }
      quantumsNesseProcesso++;
      escalonar = false;
   }
   
   std::cout << "--------- Turnaroud Time e Tempo de Espera ---------" << std::endl;
   double turnAroundTimeTotal = 0.0, tempoDeEsperaTotal = 0.0;

   for (auto & processo: this->_processos) {
      tempoDeEsperaTotal += processo->getTempoDeEspera();
      turnAroundTimeTotal += processo->getDataDeFinalizacao() - processo->getDataDeCriacao();
      std::cout << "Processo " << processo->getId() << ": " << processo->getDataDeFinalizacao() - processo->getDataDeCriacao() << " segundos";
      std::cout << " e " << processo->getTempoDeEspera() << " segundos"  << std::endl;

   }

   std::cout << "Turnaroud Time Médio: " << turnAroundTimeTotal/this->_processos.size() << " segundos" << std::endl; 
   std::cout << "Tempo médio de espera: " << tempoDeEsperaTotal/this->_processos.size() << " segundos" << std::endl;
   std::cout << "Trocas de contexto: " << trocasDeContexto << std::endl;
}
   


// A cada 1 segundo
// if escalonador->processoAtual():
//    processo->tempoRealizado++;
// 

// if escalonador->preemptavel:
//       escalonaProcesso()

// if prioridade_dinamica
//       envelhecerProcessos()
//
