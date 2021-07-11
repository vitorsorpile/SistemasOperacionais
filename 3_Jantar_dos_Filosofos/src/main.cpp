#include "Filosofo.h"
#include "Semaphore.h"

#include <vector>
#include <memory>

#define NUMBER_OF_PHILOSOPHERS 5

using namespace std;

int main(int argc, char *argv[]) {

   if (argc != 2) {
      cout << "Numero invalido de argumentos. Uso: ./exercicio3 [numero-de-refeicoes]" << endl;
      return -1;
   }
   int maxMeals = 0;
   if (std::isdigit(argv[1][0]))
      maxMeals = std::stoi(argv[1]);
   else {
      cout << "Numero de refeicoes invalido. Valor precisar ser um numero maior que zero." << endl;
      return -2;
   }

   shared_ptr<Semaphore> semaphore = shared_ptr<Semaphore> (new Semaphore(NUMBER_OF_PHILOSOPHERS));
   vector<unique_ptr<Filosofo>> filosofos;   

   for(auto i = 0; i < NUMBER_OF_PHILOSOPHERS; i++) {
      filosofos.push_back(unique_ptr<Filosofo>(new Filosofo(i, semaphore, maxMeals)));
   }

   for(auto & filosofo : filosofos) {
      filosofo->join();
   }

   return 0;
}