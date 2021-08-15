#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>

#include "Processo.h"
#include "Escalonadores.hpp"
#include "Sistema.h"

int main(int argc, char *argv[]) {

   if (argc != 2) {
      std::cout << "Número inválido de argumentos!" << std::endl;
      return -1;
   }

   std::fstream file (argv[1]);

   if (!file.is_open()) {
      std::cout << "Unable to open file" << std::endl; 
      return -1;
   }

   std::string line;
   int dataDeCriacao, duracao, prioridade, id = 0;
   std::vector<std::shared_ptr<Processo>> processos;

   // Leitura do arquivo com os processos
   while ( file >> dataDeCriacao >> duracao >> prioridade )
   {
      processos.push_back(std::shared_ptr<Processo>(new Processo(id, dataDeCriacao, duracao, prioridade)) );
      id++;
   }
   file.close();

   std::cout << "Digite o numero do escalonador desejado: " << std::endl;
   std::cout << "1 -> First Come First Serve" << std::endl;
   std::cout << "2 -> Shortest Job First" << std::endl;
   std::cout << "3 -> Por prioridade sem preempcao" << std::endl;
   std::cout << "4 -> Por prioridade com preempcao" << std::endl;
   std::cout << "5 -> Round Robin com quantum 2" << std::endl;
   std::cout << "6 -> Round Robin com quantum 2 e envelhencimento" << std::endl;

   int qualEscalonador;
   std::cin >> qualEscalonador;
   Escalonador *esc;

   int tamanhoDaLinha = 14 + processos.size()*3;
   std::string escalonador;
   // Muda a cor de impressão para verde
   std::cout << std::endl << "\033[1;32;1m";
   switch (qualEscalonador)
   {
   case 1:
      escalonador = "-> First Come First Serve <-"; 
      esc = new FCFS();
      break;
   case 2:
      escalonador = "-> Shortest Job First <-";
      esc = new ShortestJobFirst();
      break;
   case 3:
      escalonador = "-> Prioridade sem Preempcao <-";
      esc = new PrioridadeSemPreempcao();
      break;
   case 4:
      escalonador = "-> Prioridade com Preempcao <-";
      esc = new PrioridadeComPreempcao();
      break;
   case 5:
      escalonador = "-> Round Robin com Quantum 2 <-";
      esc = new RoundRobin(2);
      break;
   case 6:
      escalonador = "-> Round Robin com Quantum 2 e Envelhecimento 1 <-";
      esc = new RoundRobinComEnvelhecimento(2, 1);
      break;
   default:
      std::cout << "Esse escalonador não existe..." << std::endl;
      return -1;
   }
   // Centraliza o nome do escalonador
   int espacos = (tamanhoDaLinha - escalonador.size())/2;
   if (espacos > 0) std::cout << std::string(espacos, ' ');
   std::cout << escalonador << std::endl;

   // Volta a cor de impressão para branco
   std::cout << "\033[0;m";

   Sistema sist(processos, esc);
   sist.executar();
   
   delete esc;
   return 0;
}