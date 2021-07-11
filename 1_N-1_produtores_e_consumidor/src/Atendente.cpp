#include "Atendente.h"

using namespace std;

Atendente::Atendente (int id, Semaphore *semaphore) {
   this->id = id;
   this->semaphore = semaphore;
}

void Atendente::behavior() {

   while (true) {
      unique_lock<mutex> lck(semaphore->semaphoreMutex);

      semaphore->toBeDeliveredMutex.lock();
      if (!semaphore->down(&(semaphore->toBeDelivered))) {
         semaphore->toBeDeliveredMutex.unlock();
         break;
      }
      semaphore->toBeDeliveredMutex.unlock();

      while(semaphore->getBuffer() == 0) semaphore->consumer.wait(lck);
      lck.unlock();
      this_thread::sleep_for(DELIVER_TIME);

      semaphore->bufferMutex.lock();
      semaphore->down(&(semaphore->buffer));
      
      this->mealsDelivered++;
      semaphore->bufferMutex.unlock();
   }
}

void Atendente::operator()() {
   return this->behavior();
}