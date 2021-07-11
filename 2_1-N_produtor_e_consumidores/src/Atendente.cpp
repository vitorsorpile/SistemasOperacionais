#include "Atendente.h"

using namespace std;

Atendente::Atendente (int id, shared_ptr<Semaphore> semaphore)
   : thread(threadFunction, this)
   {
   this->id = id;
   this->semaphore = semaphore;
}

void* Atendente::threadFunction(Atendente* This) {
   This->behavior(); return nullptr;
}

void Atendente::behavior() {
   // Delay para dar tempo das variáveis serem inicializadas
   std::this_thread::sleep_for(chrono::milliseconds(15));
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

int Atendente::getId(){
   return this->id;
}

int Atendente::getMealsDelivered() {
   return this->mealsDelivered;
}