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
   while ((*(this->mealsToBeDelivered)) > 0) {
      this_thread::sleep_for(DELIVER_TIME);

      this->mutexMeal->lock();
      if ((*(this->mealsToBeDelivered)) == 0){
         this->mutexMeal->unlock();
         break;
      } 
      (*(this->mealsToBeDelivered))--;
      mealsDelivered++;
      cout << "Atendente " << this->id << " entregou prato " << mealsDelivered << ", restam " << *(this->mealsToBeDelivered) << endl;
      this->mutexMeal->unlock();
   }
}

void Atendente::operator()() {
   return this->behavior();
}