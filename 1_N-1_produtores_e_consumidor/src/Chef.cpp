#include "Chef.h"

using namespace std;

int Chef::mealsPrepared = 0;

Chef::Chef (int id, int* mealsToBePrepared, mutex* mutexMeal,  Semaphore *semaphore) {
   this->id = id;
   this->mealsToBePrepared = mealsToBePrepared;
   this->mutexMeal = mutexMeal;
   this->semaphore = semaphore;
}

void Chef::behavior() {
   // unique_lock<mutex> lck(semaphore->toBeProducedMutex);

   while (true)
   {  
      // semaphore->toBeProducedMutex.lock();
      // if (semaphore->toBeProduced ==  0 /*(*mealsToBePrepared)*/){
      //    semaphore->toBeProducedMutex.unlock();
      //    break;
      // } 
      // semaphore->toBeProducedMutex.unlock();

      // while(semaphore->getBuffer() == semaphore->getBufferSize()) semaphore->producer.wait(lck);

      semaphore->toBeProducedMutex.lock();
      if (!semaphore->down(&(semaphore->toBeProduced))) {
         semaphore->toBeProducedMutex.unlock();
         break;
      }
      semaphore->toBeProducedMutex.unlock();

      this_thread::sleep_for(PREPARE_TIME);

      semaphore->bufferMutex.lock();
      semaphore->up(&(semaphore->buffer));
      this->mealsPrepared++;
      cout << "Chef " << this->id << " preparou prato " << mealsPrepared << ", restam " << semaphore->toBeProduced << endl;
      semaphore->bufferMutex.unlock();

      semaphore->consumer.notify_all();
   }
   

   // while ((*(this->mealsToBePrepared)) > 0) {

   //    this_thread::sleep_for(PREPARE_TIME);
   //    // if (semaphore->up() == false) {

   //    // }

   //    this->mutexMeal->lock();
   //    if ((*(this->mealsToBePrepared)) == 0){
   //       this->mutexMeal->unlock();
   //       break;
   //    } 
   //    (*(this->mealsToBePrepared))--;
   //    mealsPrepared++;
   //    cout << "Chef " << this->id << " preparou prato " << mealsPrepared << ", restam " << *(this->mealsToBePrepared) << endl;
   //    this->mutexMeal->unlock();
   // }
}

void Chef::operator()() {
   return this->behavior();
}