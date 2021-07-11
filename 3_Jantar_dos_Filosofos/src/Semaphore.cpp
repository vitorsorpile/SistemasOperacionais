#include "Semaphore.h"

Semaphore::Semaphore(int numberOfPhilosophers)
   : forksMutex(numberOfPhilosophers), philosophersStates(numberOfPhilosophers), mealsEaten(numberOfPhilosophers) 
   {
   this->numberOfPhilosophers = numberOfPhilosophers;

   for (int i = 0; i < numberOfPhilosophers; i++) {
      this->philosophersStates[i] = THINKING;
      this->mealsEaten[i] = 0;
   }
}

void Semaphore::printPhilosophersStates(int id) {
   // system("clear");
   
   for(int i = 0; i < numberOfPhilosophers; i++ ) {
      string str;
      str += "Filosofo " + std::to_string(i) + " esta";

      switch (philosophersStates[i])
      {
      case HUNGRY:
         str +=  " faminto  ";
         break;
      case THINKING:
         str +=  " pensando ";
         break;
      case EATING:
         str +=  " comendo  ";
         break;
      default:
         str += " so sei que nada sei...";
         break;
      }

      str += "e ja comeu " + std::to_string(mealsEaten[i]) + " vezes.";

      if (i == id) {
         std::cout << "\033[34m" << str << std::endl << "\033[0m";
      } 
      else {
         std::cout << str << std::endl;
      }
   }

   std::cout << std::endl << std::endl;
}