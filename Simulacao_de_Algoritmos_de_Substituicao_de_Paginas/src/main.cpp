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
   // Leitura da chamada das páginas
   auto start = std::chrono::steady_clock::now();
   FIFO fifo(quadros);
   LRU lru(quadros);
   
   Pagina *pag = nullptr;
   // std::cout << "Fazendo fifo e lru..."<< std::endl;
   while (std::cin >> pagina) {
      if (pagina < 0) continue;
      // std::cout << i << std::endl;
      ordemDeChegadaDasPaginas.push_back(pagina);
      paginas.insert(pagina);
      paginas.find(pagina)->addAcessoFuturo(i);
      fifo.acessarPagina(pagina);
      lru.acessarPagina(&(*(paginas.find(pagina))),i);

      i++;
      // std::cout << "Pagina " << pagina << std::endl   ;
   } 
   // std::cout << "Terminou fifo e lru..."<< std::endl;
   i = 1;
   OPT opt(quadros, &paginas);
   // std::cout << "Começando opt..."<< std::endl;
   for (auto pagina: ordemDeChegadaDasPaginas) {
      // std::cout << i << std::endl;
      opt.acessarPagina(&(*(paginas.find(pagina))));
      i++;
   }
   // std::cout << "ordens" << std::endl;
   // for (auto& pagina: paginas) {
   //    std::cout << pagina.getId() << " -> ";
   //    for (auto x: pagina.ordemDeAcessos)
   //       std::cout << x << " ";

   //    std::cout << std::endl;
   // }
   // std::cout << "-----------" << std::endl;

   // opt.getFaltasDePagina()
   

   // paginas.find(2)->setUltimoAcesso(5);
   // std::cout << "------------- Paginas -------------" << std::endl;
   // std::cout << paginas.find(2)->getUltimoAcesso() << std::endl;
//    for (auto& pagina : paginas)
//   {
//      for(auto acesso: pagina.ordemDeAcessos)
//     std::cout << acesso << std::endl;
//   } 
   auto end = std::chrono::steady_clock::now();
   std::cout << std::chrono::duration<double>(end - start).count() << std::endl;
   std::cout << "FIFO: " << fifo.getFaltasDePagina() << " PFs" << std::endl;
   std::cout << "LRU: " << lru.getFaltasDePagina() << " PFs" << std::endl;
   std::cout << "OPT: " << opt.getFaltasDePagina() << " PFs" << std::endl;
   // FIFO.executar();
   // std::cout << quadros << std::endl;
   return 0;
}

/* 
   Vector com a ordem de acessos
   if (ultimoAcesso + 1 < vector.size())
      Acessa ultimoAcesso + 1

   Rodar FIFO e LRU concorrente, enquanto lê todos os acessos e depois roda o ótimo
*/