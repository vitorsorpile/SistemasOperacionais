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
   unique_lock<mutex> lck(semaphore->semaphoreMutex);

   while (true)
   {  
      semaphore->semaphoreMutex.lock();
      if (semaphore->toBeProduced == (*mealsToBePrepared)){
         semaphore->semaphoreMutex.unlock();
         break;
      } 
      semaphore->semaphoreMutex.unlock();

      // while(semaphore->getBuffer() == semaphore->getBufferSize()) semaphore->producer.wait(lck);

      semaphore->semaphoreMutex.lock();
      if (!semaphore->down(&(semaphore->toBeProduced))) {
         semaphore->semaphoreMutex.unlock();
         break;
      }
      semaphore->semaphoreMutex.unlock();

      this_thread::sleep_for(PREPARE_TIME);
      this->mutexMeal->lock();
      mealsPrepared++;
      cout << "Chef " << this->id << " preparou prato " << mealsPrepared << ", restam " << *(this->mealsToBePrepared) << endl;
      this->mutexMeal->unlock();

      // semaphore->up(&(semaphore->produced))
   }
   

   while ((*(this->mealsToBePrepared)) > 0) {

      this_thread::sleep_for(PREPARE_TIME);
      // if (semaphore->up() == false) {

      // }

      this->mutexMeal->lock();
      if ((*(this->mealsToBePrepared)) == 0){
         this->mutexMeal->unlock();
         break;
      } 
      (*(this->mealsToBePrepared))--;
      mealsPrepared++;
      cout << "Chef " << this->id << " preparou prato " << mealsPrepared << ", restam " << *(this->mealsToBePrepared) << endl;
      this->mutexMeal->unlock();
   }
}

void Chef::operator()() {
   return this->behavior();
}