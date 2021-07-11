#include "Filosofo.h"

using namespace std;

Filosofo::Filosofo(int id, shared_ptr<Semaphore> semaphore, int maxMeals)
   : thread(threadFunction, this), id(id),semaphore(semaphore),maxMeals(maxMeals) 
   {
   }


bool Filosofo::test(int philosopherId) {
   int N = semaphore->numberOfPhilosophers;

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
   int N = semaphore->numberOfPhilosophers;
   while (true) {

      if (semaphore->mealsEaten[this->id] == this->maxMeals) {
         semaphore->philosophersStates[this->id] = THINKING;
         break;
      }
      // THINK
      this_thread::sleep_for(chrono::seconds(1));
      
      // TAKE FORKS
      semaphore->forksAcessMutex.lock();
      semaphore->philosophersStates[this->id] = HUNGRY;
      semaphore->printPhilosophersStates(this->id);
      test(this->id);
      semaphore->forksAcessMutex.unlock();

      // Trava a thread se não conseguiu pegar os garfos
      if (semaphore->philosophersStates[this->id] != EATING ) {
         semaphore->forksMutex[this->id].lock();
      }

      // EAT
      this_thread::sleep_for(chrono::seconds(2));
      
      // PUT FORKS   
      semaphore->forksAcessMutex.lock();
      semaphore->mealsEaten[this->id]++;
      semaphore->philosophersStates[this->id] = THINKING;
      semaphore->printPhilosophersStates(this->id);

      // Testa se filósofo da esquerda consegue pegar os garfos
      test((this->id + N - 1) % N);
      // Testa se filósofo da direita consegue pegar os garfos
      test((this->id+1)%N);
      semaphore->forksAcessMutex.unlock();

   }

}