#include "Chef.h"

using namespace std;

Chef::Chef (int chefId, shared_ptr<Semaphore> sem) 
   : thread(threadFunction, this)
 {
   this->_id = chefId;
   this->semaphore = sem;
}

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
   return this->_id;
}

Chef::~Chef() {}
