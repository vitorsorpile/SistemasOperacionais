#include "Sistema.h"

Sistema::Sistema(std::vector<std::shared_ptr<Processo>> processos, Escalonador* escalonador) {
   this->_processos = processos;
   this->_escalonador = escalonador;
   this->nProcessosRestantes = processos.size();
}

Sistema::~Sistema() {}


void Sistema::enviarNovosProcessosProntosAoEscalonador() {
   for (auto &processo : this->_processos) {

      // Para otimizar, sai do loop quando chega em um processo que fica pronto depois do ciclo atual
      if (processo->getDataDeCriacao() > this->ciclo) 
         break;

      if (processo->getDataDeCriacao() == this->ciclo) {
         processo->setEstado(PRONTO);
         _escalonador->adicionarProcesso(processo.get());
      }

   }
}

void Sistema::printCicloAtual() {
   std::cout << "Ciclo: "<< this->ciclo - 1 << '-' << this->ciclo << std::endl;
   
   for (auto& processo : this->_processos) {
      std::cout << "P" << processo->getId() << " -> ";
      switch (processo->getEstado())
      {
      case PRONTO:
         std::cout << "--";
         break;
      case EXECUTANDO:
         std::cout << "##";
         break;

      case FINALIZADO:
         std::cout << "xx";
         break;
      default:
         std::cout << "  ";
         break;
      }

      std::cout << std::endl;
   }

}


void Sistema::executar() {
   while (this->nProcessosRestantes) {
      this->enviarNovosProcessosProntosAoEscalonador();

      Processo *processoAtual = _escalonador->getProcessoAtual();

      if (!processoAtual || _escalonador->getPreemptavel()) {
         std::cout << "Escalonei os processinhos..." << std::endl;
         _escalonador->escalonaProcessos();
         processoAtual = _escalonador->getProcessoAtual();
      }


      // if (processoAtual) {
         processoAtual->realizarCiclo(this->ciclo);
      // }
      // processoAtual->realizarCiclo(this->ciclo);


      // std::this_thread::sleep_for(std::chrono::seconds(1));
      this->ciclo++;
      this->printCicloAtual();
      std::cout << std::endl;

      if (processoAtual->getTempoExecutado() == processoAtual->getDuracao()) {
         this->nProcessosRestantes--;
         _escalonador->removerProcesso(processoAtual);
         processoAtual->setEstado(FINALIZADO);
      }
   }
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
