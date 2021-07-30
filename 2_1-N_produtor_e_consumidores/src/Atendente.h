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
      int _id;
      int mealsDelivered = 0;

      shared_ptr<Semaphore> semaphore;

   public:
      Atendente (int atendenteId, shared_ptr<Semaphore> sem);
      ~Atendente();
      void behavior();
      static void* threadFunction(Atendente* This);
      int getMealsDelivered();
      int getId();
};

#endif