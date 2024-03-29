#include <memory>
#include <vector>
#include <random>

#include "Pessoa.h"
#include "Banheiro.h"
#include "GeradorDePessoas.h"


int main () {
   const int nPessoas = 60;
   const bool nPessoasIgualEntreGeneros = true;

   Banheiro banheiro;
   std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();
   GeradorDePessoas gerador(nPessoas, &banheiro, nPessoasIgualEntreGeneros);
   gerador.join();

   std::chrono::time_point<std::chrono::steady_clock> end = std::chrono::steady_clock::now();
   
   auto tempoTotal = std::chrono::duration<double> (end - start);

   std::cout << std::endl;
   for (int i = 0; i < 3; i++) {
      std::cout << "Tempo médio de espera para o gênero " << i << ": " << banheiro.getTempoNaFila(i) / banheiro.getTotalPessoasPorGenero(i) << " segundos." << std::endl;
   }
   std::cout << std::endl;

   double tempoDeUsoDoBox = 0.0;
   for (unsigned int i = 0; i < banheiro.getN_BOXES(); i++) {
      tempoDeUsoDoBox = banheiro.getTempoDeUsoDoBox(i);
      std::cout << "Box " << i << " foi usado por " << tempoDeUsoDoBox / tempoTotal.count() * 100<< "% do tempo total de execução. (" ;
      std::cout << tempoDeUsoDoBox << " segundos)" << std::endl;
      std::cout << std::endl;
   }

   for (int i = 0; i < 3; i++)
      std::cout << "Quantidade de pessoas do gênero " << i << ": " << banheiro.getTotalPessoasPorGenero(i) << std::endl;

   return 0;
}