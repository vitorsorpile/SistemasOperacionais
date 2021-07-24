#include <memory>
#include <vector>
#include <random>

#include "Pessoa.h"
#include "Banheiro.h"

#define N_PESSOAS 30
#define MAX_PESSOAS_POR_GENERO 10
// #define N_BOXES 1


int main () {
   
   Banheiro banheiro;
   std::vector<std::unique_ptr<Pessoa>> pessoas;   
   std::vector<int> pessoasPorGenero(3, 0);
   
   std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
   std::uniform_int_distribution<int> distribution(0,2);
   std::uniform_int_distribution<int> tempoParaChegar(1,7);
   
   int genero = distribution(generator);
   // int generosGerados = 0;

   // std::cout<< "g: " << genero << std::endl;

   // *** CONFERIR TEMPO ENTRE A CRIACAO DE PESSOAS ***
   for (int i = 0; i < N_PESSOAS; i++) {
      while (pessoasPorGenero[genero] >= MAX_PESSOAS_POR_GENERO)
      {
         genero = distribution(generator); 
      }
      // std::cout<< "g: " << genero << std::endl;
      pessoasPorGenero[genero]++;
      auto t = tempoParaChegar(generator);
      std::this_thread::sleep_for(std::chrono::seconds(t));
      std::cout << "Tempo entre pessoas -> " << t << std::endl;
      pessoas.push_back(std::unique_ptr<Pessoa>(new Pessoa(i+1, (GENEROS) genero, &banheiro)));
      
      // if (pessoasPorGenero[genero] == MAX_PESSOAS_POR_GENERO) {
      //    generosGerados++;
      //    if (generosGerados == 3) break;
      // }
      // std::cout << "------------------" << std::endl;
      genero = distribution(generator);
   }

   for (auto & pessoa : pessoas)
      pessoa->join();


   // std::cout << banheiro.boxUsedTime.size() << std::endl;
   for (unsigned int i = 0; i < banheiro.boxUsedTime.size(); i++) {
      std::cout << "Box " << i << " foi usado por " << banheiro.boxUsedTime[i].count() << " segundos." << std::endl;

   }
   for (int i = 0; i < 3; i++)
      std::cout << "Tempo media de espera para o genero " << i << ": " << banheiro.getTempoNaFila(i) / banheiro.getTotalPessoasPorGenero(i) << std::endl;

   for (int i = 0; i < 3; i++)
      std::cout << "Quantidade de pessoas do gênero " << i << " " << banheiro.getTotalPessoasPorGenero(i) << std::endl;
   return 0;
}