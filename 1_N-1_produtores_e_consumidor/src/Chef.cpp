#include "Chef.h"

using namespace std;

Chef::Chef (int id, Semaphore *semaphore) {
   this->id = id;
   this->semaphore = semaphore;
}

void Chef::behavior(Chef* This) {
   // unique_lock<mutex> lck(semaphore->toBeProducedMutex);

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
   // return nullptr;
   // this->writeMutex->lock();
   // std::cout << "Chefe " << this->id << " produziu " << this->mealsPrepared << endl;
   // this->writeMutex->unlock();
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

// void Chef::operator()() {
//    return this->behavior();
// }

int Chef::getMealsPrepared() {
   return this->mealsPrepared;
}

int Chef::getId() {
   return this->id;
}

Chef::~Chef() {}

