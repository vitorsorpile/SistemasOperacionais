#ifndef _SEMAPHORE_H
#define _SEMAPHORE_H

#include <mutex>
#include <vector>
#include <iostream>

using namespace std;
enum PHILOSOPHERS_STATES {THINKING, HUNGRY, EATING};

class Semaphore {
   
   public:
      int numberOfPhilosophers;
      mutex forksAcessMutex;
      vector<mutex> forksMutex;
      vector<PHILOSOPHERS_STATES> philosophersStates;
      vector<int> mealsEaten;
      void printPhilosophersStates(int id);
      Semaphore(int numberOfPhilosophers);
};

#endif