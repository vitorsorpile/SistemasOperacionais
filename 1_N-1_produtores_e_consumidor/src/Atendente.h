#ifndef _ATENDENTE_H
#define _ATENDENTE_H

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
      int mealsDelivered = 0;

      Semaphore *semaphore;

   public:
      void behavior();
      void operator()();
      Atendente (int id, Semaphore *semaphore);
};

#endif