#include "Pessoa.h"
#include <memory>
#include <vector>

#define N_PESSOAS 3

int main () {

   std::vector<std::unique_ptr<Pessoa>> pessoas;   

   for (int i = 0; i < N_PESSOAS; i++)
      pessoas.push_back(std::unique_ptr<Pessoa>(new Pessoa(i+1)));
      
   for (auto & pessoa : pessoas)
      pessoa->join();

   return 0;
}