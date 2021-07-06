#include <iostream>
#include <mutex>
#include <chrono>
#include <thread>

#include "Semaphore.h"
#define PREPARE_TIME chrono::microseconds(50)

using namespace std;

class Chef {
   int id;
   // chrono::microseconds time_working = 0us;
   mutex *writeMutex;

   int mealsPrepared = 0;

   Semaphore *semaphore;

   public:
      void behavior();
      void operator()();

      Chef (int id, mutex* writeMutex, Semaphore *semaphore);
      ~Chef();

};

