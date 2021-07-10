#ifndef _FILOSOFO_H
#define _FILOSOFO_H

#include <thread>
#include <iostream>
#include <chrono>
#include <memory>

#include "Semaphore.h"

using namespace std;
   
class Filosofo : public thread {

   int id;
   shared_ptr<Semaphore> semaphore;
   int maxMeals;

   public:
      void behavior();
      Filosofo(int id, shared_ptr<Semaphore> semaphore, int maxMeals);
      bool test(int philosopherId);

      static void* threadFunction(Filosofo* This) {
         ((Filosofo *)This)->behavior(); return nullptr;
      } 
};


#endif