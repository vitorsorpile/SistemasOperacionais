#include <iostream>
#include <fstream>
#include <chrono>
#include <unordered_set>

#include "FIFO.h"
#include "LRU.h"
#include "OPT.h"

int main (int argc, char *argv[]) {

   if (argc != 2) {
      std::cout << "Número inválido de argumentos!" << std::endl;
      return -1;
   }

   if (argv[1] <= 0 ) {
      std::cout << "Quantidade de quadros precisa ser maior que 0." << std::endl;
      return -1;
   }

   std::unordered_set<Pagina, Pagina::HashFunction> paginas;
   int pagina = -1, quadros = std::stoi(argv[1]), i = 0;
   std::vector<int> ordemDeChegadaDasPaginas; 
  
   auto start = std::chrono::steady_clock::now();
   FIFO fifo(quadros);
   LRU lru(quadros);
  
   // Leitura da chamada das páginas
   while (std::cin >> pagina) {
      if (pagina < 0) continue;
      // Salva a ordem de chegada das páginas para executar o algoritmo ótimo
      ordemDeChegadaDasPaginas.push_back(pagina);
      
      // Adiciona a página no set
      paginas.insert(pagina);

      // Adiciona um acesso futuro na página para a execução do algoritmo ótimo
      paginas.find(pagina)->addAcessoFuturo(i);
      
      // Acessa as páginas nos algoritmos FIFO e LRU
      fifo.acessarPagina(pagina);
      lru.acessarPagina(&(*(paginas.find(pagina))), i);

      i++;
   } 

   // Execução do algoritmo ótimo 
   OPT opt(quadros);
   for (auto pagina: ordemDeChegadaDasPaginas) {
      opt.acessarPagina(&(*(paginas.find(pagina))));
   }
   
   // Impressão dos resultados
   auto end = std::chrono::steady_clock::now();
   std::cout << "Tempo de execução: " << std::chrono::duration<double>(end - start).count() << " segundos" << std::endl;
   std::cout << quadros << " quadros" << std::endl;
   std::cout << ordemDeChegadaDasPaginas.size() << " refs" << std::endl;
   std::cout << "FIFO: " << fifo.getFaltasDePagina() << " PFs" << std::endl;
   std::cout << "LRU: " << lru.getFaltasDePagina() << " PFs" << std::endl;
   std::cout << "OPT: " << opt.getFaltasDePagina() << " PFs" << std::endl;

   return 0;
}
