#include "Chef.h"

using namespace std;

Chef::Chef (int id, Semaphore *sem) {
   this->_id = id;
   this->semaphore = sem;
}

Chef::~Chef() {}

void Chef::behavior(Chef* This) {

   while (true)
   {  
      This->semaphore->toBeProducedMutex.lock();
      if (!This->semaphore->down(&(This->semaphore->toBeProduced))) {
         This->semaphore->toBeProducedMutex.unlock();
         break;
      }
      This->semaphore->toBeProducedMutex.unlock();

      this_thread::sleep_for(PREPARE_TIME);

      This->semaphore->bufferMutex.lock();
      This->semaphore->up(&(This->semaphore->buffer));
      // cout << "Chef " << this->id << " preparou prato " << mealsPrepared << ", restam " << semaphore->toBeProduced << endl;
      This->semaphore->bufferMutex.unlock();
      This->mealsPrepared++;

      This->semaphore->consumer.notify_one();
   }
}

int Chef::getMealsPrepared() {
   return this->mealsPrepared;
}

int Chef::getId() {
   return this->_id;
}
