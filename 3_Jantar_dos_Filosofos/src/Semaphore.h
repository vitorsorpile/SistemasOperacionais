#ifndef _SEMAPHORE_H
#define _SEMAPHORE_H

#include <mutex>
#include <condition_variable>
#include <vector>
#include <iostream>

using namespace std;
enum PHILOSOPHERS_STATES {THINKING, HUNGRY, EATING};

class Semaphore {
   private:
      int _numberOfPhilosophers;
   
   public:
      mutex forksAcessMutex;
      vector<mutex> forksMutex;
      vector<condition_variable> philosophersCVs;
      vector<PHILOSOPHERS_STATES> philosophersStates;
      vector<int> mealsEaten;
      Semaphore(int numberOfPhilosophers);
      ~Semaphore();
      void printPhilosophersStates(int id);
      int getNumberOfPhilosophers();
};

#endif