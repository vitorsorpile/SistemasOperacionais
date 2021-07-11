#include <iostream>
#include <sstream> 
#include <thread>
#include <vector>
#include <condition_variable>

#include "Atendente.h"
#include "Chef.h"

#define NUMBER_OF_CHEFS 6
#define NUMBER_OF_ATENDENTES 1
using namespace std;


int main(int argc, char *argv[]) {
   int maxMeals = 50;
   if (argc > 1) {
      std::stringstream ss(argv[1]);
      ss >> maxMeals;
   }

   vector<Chef*> chefs;
   vector<thread> chefsThreads;
   vector<thread> atendentesThreads;
   mutex writeMutex;
   Semaphore semaphore(maxMeals, maxMeals);

   for (auto i = 0; i < NUMBER_OF_CHEFS; i++) {

      chefs.push_back(new Chef(i+1,&semaphore));
      chefsThreads.push_back(thread(&Chef::behavior, chefs[i]));

   }

   for (auto i = 0; i < NUMBER_OF_ATENDENTES; i++) {
      Atendente atendente(i+1, &semaphore);
      atendentesThreads.push_back(thread(atendente));
   }

   for (auto & th : chefsThreads) th.join();

   for (auto & th : atendentesThreads) th.join();
   
   int maisOcioso = 1, menosOcioso = 1, maior = chefs[0]->getMealsPrepared(), menor = maior, meals;
   for (auto & chef: chefs) {
      
      meals = chef->getMealsPrepared();
      if (meals > maior) {
         menosOcioso = chef->getId();
         maior = meals;
      }

      if(meals < menor) {
         maisOcioso = chef->getId();
         menor = meals;
      }

      cout << "Chefe " << chef->getId() << " produziu " << meals << endl;
      delete chef;
   }

   cout << "O chefe menos ocioso foi o " << menosOcioso << endl;
   cout << "O chefe mais ocioso foi o " << maisOcioso << endl;
   
   
   return 0;
}
