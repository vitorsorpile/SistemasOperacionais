#include "Atendente.h"

using namespace std;
int Atendente::mealsDelivered = 0;

Atendente::Atendente (int id, int* mealsToBeDelivered, mutex* mutexMeal, Semaphore *semaphore) 
{
   this->id = id;
   this->mealsToBeDelivered = mealsToBeDelivered;
   this->mutexMeal = mutexMeal;
   this->semaphore = semaphore;
}

void Atendente::behavior() {
   unique_lock<mutex> lck(semaphore->bufferMutex);

   while (true) {

      semaphore->toBeDeliveredMutex.lock();
      if (!semaphore->down(&(semaphore->toBeDelivered))) {
         semaphore->toBeDeliveredMutex.unlock();
         break;
      }
      semaphore->toBeDeliveredMutex.unlock();

      while(semaphore->getBuffer() == 0) semaphore->consumer.wait(lck);
      this_thread::sleep_for(DELIVER_TIME);
      // cout << "dale dele" << endl;

      // semaphore->bufferMutex.lock();
      // cout << "dale dele2" << endl;
      semaphore->down(&(semaphore->buffer));
      
      this->mealsDelivered++;
      cout << "Atendente " << this->id << " entregou seu prato #" << this->mealsDelivered << ", restam " << semaphore->toBeDelivered << endl;
      // semaphore->bufferMutex.unlock();

      // semaphore->consumer.notify_one();
   }
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