#include "Semaphore.h"

Semaphore::Semaphore(int numberOfPhilosophers)
   : forksMutex(numberOfPhilosophers), philosophersCVs(numberOfPhilosophers),
      philosophersStates(numberOfPhilosophers), mealsEaten(numberOfPhilosophers + 1) 
   {
   this->_numberOfPhilosophers = numberOfPhilosophers;

   for (int i = 0; i < numberOfPhilosophers; i++) {
      this->philosophersStates[i] = THINKING;
      this->mealsEaten[i] = 0;
   }
   // Por algum motivo, é preciso acrescentar um elemento ao vector para evitar erros de memória 
   // na função printPhilosophersStates
   this->mealsEaten[numberOfPhilosophers] = 0;
}

Semaphore::~Semaphore() {}

void Semaphore::printPhilosophersStates(int id) {
   
   for(int i = 0; i < _numberOfPhilosophers; i++) {
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

int Semaphore::getNumberOfPhilosophers() {
   return this->_numberOfPhilosophers;
}