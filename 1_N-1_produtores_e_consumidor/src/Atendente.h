#include <iostream>
#include <mutex>
#include <chrono>
#include <thread>

#include "Semaphore.h"

#define DELIVER_TIME chrono::microseconds(10)

using namespace std;

class Atendente {
   private:
      int id;
      // chrono::microseconds timeWorking = 0us;
      mutex *mutexMeal;
      static int mealsDelivered;
      int *mealsToBeDelivered;
      Semaphore *semaphore;

   public:
      void behavior();
      void operator()();
      Atendente (int id, int* mealsToBeDelivered, mutex* mutexMeal, Semaphore *semaphore);
};