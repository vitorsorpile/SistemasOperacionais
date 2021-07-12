#include "Filosofo.h"

using namespace std;

Filosofo::Filosofo(int philosopherId, shared_ptr<Semaphore> sem, int maxMeals)
   : thread(threadFunction, this), _id(philosopherId), semaphore(sem), _maxMeals(maxMeals) 
   {
   }


bool Filosofo::test(int philosopherId) {
   int N = semaphore->getNumberOfPhilosophers();

   if (semaphore->philosophersStates[philosopherId] == HUNGRY && semaphore->philosophersStates[(philosopherId + N - 1) % N] != EATING && semaphore->philosophersStates[(philosopherId+1)%N] != EATING) {
      semaphore->philosophersStates[philosopherId] = EATING;
      semaphore->printPhilosophersStates(philosopherId);
      semaphore->forksMutex[philosopherId].unlock();
      return true;
   }

   return false;
}

void Filosofo::behavior() {

   // Delay para dar tempo das variáveis serem inicializadas
   this_thread::sleep_for(chrono::milliseconds(10));
   if (!semaphore) return;
   int N = semaphore->getNumberOfPhilosophers();
   while (true) {

      if (semaphore->mealsEaten[this->_id] == this->_maxMeals) {
         semaphore->philosophersStates[this->_id] = THINKING;
         break;
      }
      // THINK
      this_thread::sleep_for(chrono::seconds(1));
      
      // TAKE FORKS
      semaphore->forksAcessMutex.lock();
      semaphore->philosophersStates[this->_id] = HUNGRY;
      semaphore->printPhilosophersStates(this->_id);
      test(this->_id);
      semaphore->forksAcessMutex.unlock();

      // Trava a thread se não conseguiu pegar os garfos
      if (semaphore->philosophersStates[this->_id] != EATING ) {
         semaphore->forksMutex[this->_id].lock();
      }

      // EAT
      this_thread::sleep_for(chrono::seconds(2));
      
      // PUT FORKS   
      semaphore->forksAcessMutex.lock();
      semaphore->mealsEaten[this->_id]++;
      semaphore->philosophersStates[this->_id] = THINKING;
      semaphore->printPhilosophersStates(this->_id);

      // Testa se filósofo da esquerda consegue pegar os garfos
      test((this->_id + N - 1) % N);
      // Testa se filósofo da direita consegue pegar os garfos
      test((this->_id+1)%N);
      semaphore->forksAcessMutex.unlock();

   }

}