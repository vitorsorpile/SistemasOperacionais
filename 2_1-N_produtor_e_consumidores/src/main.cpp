#include <iostream>
#include <sstream> 
#include <thread>
#include <vector>
#include <condition_variable>

#include "Atendente.h"
#include "Chef.h"
#include "Semaphore.h"

#define NUMBER_OF_CHEFS 1
#define NUMBER_OF_ATENDENTES 6
using namespace std;


int main(int argc, char *argv[]) {
   int maxMeals = 50;
   if (argc > 1) {
      std::stringstream ss(argv[1]);
      ss >> maxMeals;
   }

   shared_ptr<Semaphore> semaphore = shared_ptr<Semaphore> (new Semaphore(maxMeals, maxMeals));
   vector<unique_ptr<Chef>> chefs; 
   vector<unique_ptr<Atendente>> atendentes; 


   for (auto i = 0; i < NUMBER_OF_CHEFS; i++) {
      // Chef chef(i+1, semaphore);
      // atendentesThreads.push_back(thread(chef));
      chefs.push_back(unique_ptr<Chef>(new Chef(i+1, semaphore)));
   }

   for (auto i = 0; i < NUMBER_OF_ATENDENTES; i++) {
      // atendentes.push_back(new Atendente(i+1, semaphore));
      atendentes.push_back(unique_ptr<Atendente>(new Atendente(i+1, semaphore)));
   }

   for (auto & th : chefs) th->join();

   for (auto & th : atendentes) th->join();
   
   int maisOcioso = 1, menosOcioso = 1, maior = atendentes[0]->getMealsDelivered(), menor = maior, meals;
   for (auto & atendente: atendentes) {
      
      meals = atendente->getMealsDelivered();
      if (meals > maior) {
         menosOcioso = atendente->getId();
         maior = meals;
      }

      if(meals < menor) {
         maisOcioso = atendente->getId();
         menor = meals;
      }

      cout << "Atendente " << atendente->getId() << " entregou " << meals << endl;
   }

   cout << "O atendente menos ocioso foi o " << menosOcioso << endl;
   cout << "O atendente mais ocioso foi o " << maisOcioso << endl;
   
   
   return 0;
}
