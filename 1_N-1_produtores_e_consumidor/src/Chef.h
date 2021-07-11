#ifndef _CHEF_H
#define _CHEF_H

#include <iostream>
#include <mutex>
#include <chrono>
#include <thread>

#include "Semaphore.h"
#define PREPARE_TIME chrono::microseconds(50)

using namespace std;

class Chef {
   int id;

   int mealsPrepared = 0;

   Semaphore *semaphore;

   public:
      static void behavior(Chef*);
      int getMealsPrepared();
      int getId();

      Chef (int id, Semaphore *semaphore);
      ~Chef();

};

#endif