#ifndef _CHEF_H
#define _CHEF_H

#include <iostream>
#include <mutex>
#include <chrono>
#include <thread>

#include "Semaphore.h"
#define PREPARE_TIME chrono::microseconds(50)

using namespace std;

class Chef : public thread {

   int _id;
   int mealsPrepared = 0;

   shared_ptr<Semaphore> semaphore;

   public:
      void behavior();
      int getMealsPrepared();
      int getId();
      static void* threadFunction(Chef* This);

      Chef (int chefId, shared_ptr<Semaphore> sem);
      ~Chef();

};

#endif