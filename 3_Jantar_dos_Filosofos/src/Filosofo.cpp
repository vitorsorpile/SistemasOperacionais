#include "Filosofo.h"

using namespace std;

Filosofo::Filosofo(int philosopherId, shared_ptr<Semaphore> sem, int maxMeals)
   : thread(threadFunction, this), _id(philosopherId), semaphore(sem), _maxMeals(maxMeals) 
   {
   }

Filosofo::~Filosofo() {}


void Filosofo::test(int philosopherId) {
   this_thread::sleep_for(chrono::milliseconds(10));
   int N = semaphore->getNumberOfPhilosophers();
   // Verifica se o filósofo está com fome e se os filosófos ao seu lado não estão comendo
   if (semaphore->philosophersStates[philosopherId] == HUNGRY && semaphore->philosophersStates[(philosopherId + N - 1) % N] != EATING && semaphore->philosophersStates[(philosopherId+1)%N] != EATING) {
      semaphore->philosophersStates[philosopherId] = EATING;
      semaphore->printPhilosophersStates(philosopherId);
      semaphore->philosophersCVs[philosopherId].notify_one();
   }
}

void Filosofo::behavior() {
   // Delay para dar tempo das variáveis serem inicializadas
   this_thread::sleep_for(chrono::milliseconds(10));

   unique_lock<mutex> lck(semaphore->forksMutex[this->_id]);
   int N = semaphore->getNumberOfPhilosophers();
   while (true) {

      if (semaphore->mealsEaten[this->_id] == this->_maxMeals) {
         semaphore->philosophersStates[this->_id] = THINKING;
         break;
      }
      // Pensa
      this_thread::sleep_for(THINKING_TIME);
      
      // Tenta pegar os garfos
      semaphore->forksAcessMutex.lock();
      semaphore->philosophersStates[this->_id] = HUNGRY;
      semaphore->printPhilosophersStates(this->_id);
      test(this->_id);
      semaphore->forksAcessMutex.unlock();

      // Trava o mutex desse filosofo se não conseguiu pegar os garfos
      while (semaphore->philosophersStates[this->_id] != EATING ) {
         semaphore->philosophersCVs[this->_id].wait(lck);
      }

      // Come
      this_thread::sleep_for(EATING_TIME);
      
      // Devolve os garfos   
      semaphore->forksAcessMutex.lock();
      semaphore->mealsEaten[this->_id]++;
      semaphore->philosophersStates[this->_id] = THINKING;
      semaphore->printPhilosophersStates(this->_id);

      // Testa se filósofo à sua esquerda consegue pegar os garfos
      test((this->_id + N - 1) % N);
      // Testa se filósofo à sua direita consegue pegar os garfos
      test((this->_id+1)%N);
      semaphore->forksAcessMutex.unlock();

   }

}