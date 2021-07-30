#include "Chef.h"

using namespace std;

Chef::Chef (int chefId, shared_ptr<Semaphore> sem) 
   : thread(threadFunction, this)
{
   this->_id = chefId;
   this->semaphore = sem;
}

Chef::~Chef() {}

void* Chef::threadFunction(Chef* This) {
   This->behavior(); return nullptr;
}

void Chef::behavior() {
   // Delay para dar tempo das variáveis serem inicializadas
   std::this_thread::sleep_for(chrono::milliseconds(15));
   while (true)
   {  
      semaphore->toBeProducedMutex.lock();
      if (!semaphore->down(&(semaphore->toBeProduced))) {
         semaphore->toBeProducedMutex.unlock();
         break;
      }
      semaphore->toBeProducedMutex.unlock();

      this_thread::sleep_for(PREPARE_TIME);

      semaphore->bufferMutex.lock();
      semaphore->up(&(semaphore->_buffer));
      // cout << "Chef " << id << " preparou prato " << mealsPrepared << ", restam " << semaphore->toBeProduced << endl;
      semaphore->bufferMutex.unlock();
      mealsPrepared++;

      semaphore->consumer.notify_one();
   }
}

int Chef::getMealsPrepared() {
   return this->mealsPrepared;
}

int Chef::getId() {
   return this->_id;
}
