#include "Filosofo.h"

using namespace std;

Filosofo::Filosofo(int id, shared_ptr<Semaphore> semaphore, int maxMeals)
   : thread(threadFunction, this) 
   {
      this->id = id;
      this->semaphore = semaphore;
      this->maxMeals = maxMeals;
   }


bool Filosofo::test(int philosopherId) {
   if (!semaphore) return false;
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

   if (!semaphore) return;
   int N = semaphore->numberOfPhilosophers;
   while (true) {

      if (semaphore->mealsEaten[this->id] == this->maxMeals) {
         semaphore->philosophersStates[this->id] = THINKING;
         break;
      }
      // THINK
      this_thread::sleep_for(chrono::milliseconds(1500));
      
      // TAKE FORKS
      semaphore->forksAcessMutex.lock();
      semaphore->philosophersStates[this->id] = HUNGRY;
      semaphore->printPhilosophersStates(this->id);
      test(this->id);
      semaphore->forksAcessMutex.unlock();

      if (semaphore->philosophersStates[this->id] != EATING ) {
         semaphore->forksMutex[this->id].lock();
      }
      // EAT
      this_thread::sleep_for(chrono::milliseconds(1500));
      
      // PUT FORKS   
      semaphore->forksAcessMutex.lock();
      semaphore->mealsEaten[this->id]++;
      semaphore->philosophersStates[this->id] = THINKING;
      semaphore->printPhilosophersStates(this->id);
      test((this->id + N - 1) % N);
      test((this->id+1)%N);
      semaphore->forksAcessMutex.unlock();

   }


}