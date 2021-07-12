#ifndef _FILOSOFO_H
#define _FILOSOFO_H

#include <thread>
#include <iostream>
#include <chrono>
#include <memory>

#include "Semaphore.h"

using namespace std;
   
class Filosofo : public thread {

   int _id;
   shared_ptr<Semaphore> semaphore;
   int _maxMeals;

   public:
      void behavior();
      Filosofo(int philosopherId, shared_ptr<Semaphore> sem, int maxMeals);
      bool test(int philosopherId);

      static void* threadFunction(Filosofo* This) {
         ((Filosofo *)This)->behavior(); return nullptr;
      } 
};


#endif