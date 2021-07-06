#include "Atendente.h"

using namespace std;

Atendente::Atendente (int id, mutex* writeMutex, Semaphore *semaphore) {
   this->id = id;

   this->writeMutex = writeMutex;
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
      // semaphore->bufferMutex.unlock();
      lck.unlock();
      this_thread::sleep_for(DELIVER_TIME);
      // cout << "dale dele" << endl;
      // lck.release();
      // semaphore->bufferMutex.lock();
      // cout << "dale dele2" << endl;
      

      semaphore->bufferMutex.lock();
      semaphore->down(&(semaphore->buffer));
      
      this->mealsDelivered++;
      // cout << "Atendente " << this->id << " entregou seu prato #" << this->mealsDelivered << ", restam " << semaphore->toBeDelivered << endl;
      semaphore->bufferMutex.unlock();

      // semaphore->consumer.notify_one();
   }
   writeMutex->lock();
   std::cout << "Atendente " << this->id << " entregou " << this->mealsDelivered << endl;
   writeMutex->unlock();

   // while ((*(this->mealsToBeDelivered)) > 0) {
   //    this_thread::sleep_for(DELIVER_TIME);

   //    this->mutexMeal->lock();
   //    if ((*(this->mealsToBeDelivered)) == 0){
   //       this->mutexMeal->unlock();
   //       break;
   //    } 
   //    (*(this->mealsToBeDelivered))--;
   //    mealsDelivered++;
   //    cout << "Atendente " << this->id << " entregou prato " << mealsDelivered << ", restam " << *(this->mealsToBeDelivered) << endl;
   //    this->mutexMeal->unlock();
   // }
}

void Atendente::operator()() {
   return this->behavior();
}