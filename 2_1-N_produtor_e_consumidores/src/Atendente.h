#ifndef _ATENDENTE_H
#define _ATENDENTE_H

#include <iostream>
#include <mutex>
#include <chrono>
#include <thread>

#include "Semaphore.h"

#define DELIVER_TIME chrono::microseconds(15)

using namespace std;

class Atendente: public thread {
   private:
      int id;
      int mealsDelivered = 0;

      shared_ptr<Semaphore> semaphore;

   public:
      void behavior();
      static void* threadFunction(Atendente* This);
      Atendente (int id, shared_ptr<Semaphore> semaphore);
      int getMealsDelivered();
      int getId();
};

#endif