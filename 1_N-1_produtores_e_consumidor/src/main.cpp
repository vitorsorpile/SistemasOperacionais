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


// int foodsPrepared = 0;
int main(int argc, char *argv[]) {
   int maxMeals = 50;
   if (argc > 1) {
      std::stringstream ss(argv[1]);
      ss >> maxMeals;
   }

   // vector<Chef*> chefs;
   // Chef* aux;

   vector<thread> chefsThreads;
   vector<thread> atendentesThreads;
   mutex writeMutex;
   Semaphore semaphore(maxMeals);

   for (auto i = 0; i < NUMBER_OF_CHEFS; i++) {
      // aux = new Chef(i, &maxFoods);
      // chefs.push_back(new Chef(i, &maxFoods));
      Chef chef(i+1, &writeMutex, &semaphore);
      chefsThreads.push_back(thread(chef));
      // threads.push_back(Chef)
      // threads.push_back(thread(chefs[i].behavior()));
      // threads.push_back(thread(Chef(), i, maxFoods))  
   }

   for (auto i = 0; i < NUMBER_OF_ATENDENTES; i++) {
      Atendente atendente(i+1, &writeMutex, &semaphore);
      atendentesThreads.push_back(thread(atendente));
   }

   for (auto & th : chefsThreads) th.join();


   for (auto & th : atendentesThreads) th.join();
   
   
   
   // for (int i = 0; i < NUMBER_OF_CHEFS; i++ ) delete chefs[i];
   // for(int index = 0; index < (int)chefs.size(); index++ )
   //      	if(chefs[index])delete chefs[index];
   return 0;
}
