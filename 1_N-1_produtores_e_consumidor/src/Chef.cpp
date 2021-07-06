#include "Chef.h"

using namespace std;

Chef::Chef (int id, mutex* writeMutex,  Semaphore *semaphore) {
   this->id = id;
   this->writeMutex = writeMutex;
   this->semaphore = semaphore;
}

void Chef::behavior() {
   // unique_lock<mutex> lck(semaphore->toBeProducedMutex);

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
      semaphore->up(&(semaphore->buffer));
      // cout << "Chef " << this->id << " preparou prato " << mealsPrepared << ", restam " << semaphore->toBeProduced << endl;
      semaphore->bufferMutex.unlock();
      this->mealsPrepared++;

      semaphore->consumer.notify_one();
   }
   this->writeMutex->lock();
   std::cout << "Chefe " << this->id << " produziu " << this->mealsPrepared << endl;
   this->writeMutex->unlock();
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

Chef::~Chef() {}